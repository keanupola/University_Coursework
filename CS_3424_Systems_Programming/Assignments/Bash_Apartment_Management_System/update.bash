#!/bin/bash

# (a) Prompt user
read -p "Enter an apartment number (three digit integer): " apt_number
read -p "Enter full name (or leave blank to keep unchanged): " new_first_name new_last_name
read -p "Enter lease start date (or leave blank to keep unchanged): " new_lease_start
read -p "Enter lease end date (or leave blank to keep unchanged): " new_lease_end
read -p "Enter balance (or leave blank to keep unchanged): " new_balance

#  (b) Assign file name to use for search
file_name="./data/${apt_number}.apt"

# Check if file exists
if [[ ! -e "$file_name" ]]; then
    # (e) Print error if apt DNE
    echo "ERROR: apartment not found"

else
    # Read existing data 
    {
        read -r first_name last_name
        read -r lease_start lease_end
        read -r balance

    } < "$file_name"

    # (c) Update each of the corresponding fields based on the user input
    # Check if new input is not empty and update existing variables
    [[ -n "$new_first_name" ]] && first_name="$new_first_name"
    [[ -n "$new_last_name" ]] && last_name="$new_last_name"
    [[ -n "$new_lease_start" ]] && lease_start="$new_lease_start"
    [[ -n "$new_lease_end" ]] && lease_end="$new_lease_end"
    [[ -n "$new_balance" ]] && balance="$new_balance"

    # Write the updated data back to the file
    {
        echo "$first_name $last_name"
        echo "$lease_start $lease_end"
        echo "$balance"

    } > "$file_name"

    # (d) Update log
    echo "$(date) UPDATED: $apt_number" >> "./data/queries.log"
fi
