#!/bin/bash

# (a) Prompt user for apt number
read -p "Enter an apartment number: " apt_number

# Assign file name
file_name="./data/${apt_number}.apt"

if [[ -e "$file_name" ]]; then
    # (b) Delete apartment's file
    rm "$file_name"
    # (c) Update data/queries.log
    echo "$(date) DELETED: $apt_number" >> "./data/queries.log"
    # (d) Delete successful
    echo "$apt_number was successfully deleted."
else
    # (e) Apt not found
    echo "ERROR: apartment not found"
fi
