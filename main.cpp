#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

string encodePrice(const string& price) {
    unordered_map<char, char> encodeMap = {
            {'1', 'H'}, {'2', 'O'}, {'3', 'N'}, {'4', 'E'}, {'5', 'Y'},
            {'6', 'B'}, {'7', 'I'}, {'8', 'R'}, {'9', 'D'}, {'0', 'S'}
    };

    string encoded = "";
    for (char ch : price) {
        if (encodeMap.find(ch) != encodeMap.end()) {
            encoded += encodeMap[ch];
        } else {
            encoded += ch;
        }
    }

    // Replace SSS (thousand) with K, and SSSSSS (million) with M
    size_t pos;
    while ((pos = encoded.rfind("SSSSSS")) != string::npos) {
        encoded.replace(pos, 6, "M");
    }
    while ((pos = encoded.rfind("SSS")) != string::npos) {
        encoded.replace(pos, 3, "K");
    }

    return encoded;
}

int main() {
    cout << "Entering Input File Name in CSV: ";
    string inputFile;  cin >> inputFile;

    cout << "Entering Output File Name in CSV: ";
    string outputFile;  cin >> outputFile;

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    vector<string> headers;
    bool firstLine = true;
    int saleColumnIndex = -1;

    while (getline(inFile, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;

        // Read each cell in the row
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (firstLine) {
            headers = row;

            // Ensure S-code is inserted at the correct index, after "Sale"
            for (size_t i = 0; i < headers.size(); i++) {
                if (headers[i] == "Sale") {
                    saleColumnIndex = i;
                    break;
                }
            }

            if (saleColumnIndex == -1) {
                cerr << "Error: 'Sale' column not found in CSV file!" << endl;
                return 1;
            }

            headers.insert(headers.begin() + saleColumnIndex + 1, "S-code");

            for (size_t i = 0; i < headers.size(); i++) {
                outFile << headers[i] << (i == headers.size() - 1 ? "\n" : ",");
            }
            firstLine = false;
        } else {
            if (saleColumnIndex >= row.size()) {
                cerr << "Error: Sale column index out of range in a row!" << endl;
                continue;
            }

            string salePrice = row[saleColumnIndex];
            string encodedPrice = encodePrice(salePrice);

            // Ensure the row has the correct number of columns before inserting "S-code"
            if (row.size() < headers.size() - 1) {
                row.resize(headers.size() - 1, "");  // Fill missing columns with empty values
            }

            // Insert "S-code" at the correct position **after Sale**
            row.insert(row.begin() + saleColumnIndex + 1, encodedPrice);

            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i] << (i == row.size() - 1 ? "\n" : ",");
            }
        }
    }

    inFile.close();
    outFile.close();

    cout << "Processing complete! Check " << outputFile << " for results." << endl;
    return 0;
}
