#!/bin/bash

OUTPUT_FILE="calculator"
SOURCE_FILE="calculator.cpp"

pkg-config --cflags --libs gtk+-3.0 > flags.txt
g++ -o $OUTPUT_FILE $SOURCE_FILE $(<flags.txt)
rm flags.txt

echo "Compilation complete. Executable file: $OUTPUT_FILE"

