#!/bin/bash

# (a) Read prompts
read -p "Enter apartment number (three-digit integer): " apt_number
read -p "Enter full name (string possibly containing whitespace): " first_name last_name
read -p "Enter lease start date (string with slashes): " lease_start
read -p "Enter lease end date (string with slashes): " lease_end

# Determine file name based on the apartment number
file_name="./data/${apt_number}.apt"

# Check if the file already exists
if [[ -e "$file_name" ]]; then
    # (d) Print error if apt exists
    echo "ERROR: apartment already exists"
else
    # (b) Create apartment file with provided data
    echo "$first_name $last_name" > "$file_name"
    echo "$lease_start $lease_end" >> "$file_name"
    echo "900" >> "$file_name"

    # (c) Log creation date
    echo "$(date) CREATED: $apt_number" >> "./data/queries.log"
fi
