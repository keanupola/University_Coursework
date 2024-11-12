#!/bin/bash

# (a) Prompt the user for an apartment number
read -p "Enter an apartment number: " apt_number

# (b) Search for the specified apartment using the apartment number
# Check file name based on the apartment number
file_name="./data/${apt_number}.apt"

# Check if file exists
if [[ ! -e "$file_name" ]]; then
    # (d) Print error if file DNE
    echo "ERROR: apartment not found"

else
    # Read each line and assign variables
    { 
        read -r first_name last_name
        read -r lease_start lease_end
        read -r balance

    } < "$file_name"

    # (c) Display information
    echo "Apartment Number: $apt_number"
    echo "Tenant Name: $last_name, $first_name"
    echo "Lease Start: $lease_start"
    echo "Lease End: $lease_end"
    echo "Current Balance: $balance"
fi
