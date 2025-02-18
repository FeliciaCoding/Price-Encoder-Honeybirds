# Encode Sale Honeybirds

## Overview
This C++ program processes a CSV file containing a "Sale" column, encodes the prices using the **HONEYBIRDS** mapping, and outputs a new CSV file with an additional "S-code" column.

## HONEYBIRDS Encoding Rules
The program translates numeric values using the following mapping:

```
1 -> H, 2 -> O, 3 -> N, 4 -> E, 5 -> Y,
6 -> B, 7 -> I, 8 -> R, 9 -> D, 0 -> S
```

Additionally:
- **"SSS"** (thousand) is replaced with **"K"**
- **"SSSSSS"** (million) is replaced with **"M"**

## Features
- Reads an input CSV file containing a **"Sale"** column.
- Converts sale values into their **HONEYBIRDS encoded representation**.
- Ensures the **"S-code"** column is correctly placed after the "Sale" column.
- Outputs the processed data into a new CSV file.

## Requirements
- C++ Compiler (GCC or Clang recommended)
- Standard C++ Libraries (iostream, fstream, sstream, unordered_map, vector)

## How to Use

### 1. Compile the Program
```sh
g++ encode_sale_honeybirds.cpp -o encode_sale_honeybirds
```

### 2. Run the Program
```sh
./encode_sale_honeybirds
```

### 3. Enter File Names
The program will prompt for the **input CSV file** and the **output CSV file**:
```
Entering Input File Name in CSV: sales.csv
Entering Output File Name in CSV: sales_with_code.csv
```

### 4. Check Output
Once processed, the output file will contain an additional **"S-code"** column right after the "Sale" column.

## Example
### Input (`sales.csv`)
| ID  | Product   | Category | Sale   |
|-----|----------|----------|--------|
| 101 | Laptop   | Tech     | 12345  |
| 102 | Phone    | Tech     | 67890  |
| 103 | TV       | Home     | 250000 |
| 104 | Camera   | Gadgets  | 98765  |

### Output (`sales_with_code.csv`)
| ID  | Product   | Category | Sale   | S-code |
|-----|----------|----------|--------|--------|
| 101 | Laptop   | Tech     | 12345  | HONEY  |
| 102 | Phone    | Tech     | 67890  | BIRDS  |
| 103 | TV       | Home     | 250000 | YOSK   |
| 104 | Camera   | Gadgets  | 98765  | DRIBY  |

## Troubleshooting
- **"Sale" column not found**: Ensure your CSV has a column titled exactly "Sale".
- **S-code misalignment**: Make sure each row in the CSV has the same number of columns.


## Author
Developed by FeliciaCoding.

