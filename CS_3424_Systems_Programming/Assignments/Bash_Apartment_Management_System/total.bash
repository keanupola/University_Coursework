#!/bin/bash

# Count the number of .apt files in the data directory
total=$(ls ./data/*.apt | wc -l)
# (a) Print the total number of .apt files within the data directory
echo "Total apartment records: $total"

