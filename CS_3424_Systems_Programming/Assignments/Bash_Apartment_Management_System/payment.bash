#!/bin/bash

# (a) Prompt the user for an apartment number
read -p "Enter an apartment number: " apt_number

# (b) Prompt the user for a payment amount
read -p "Enter a payment amount: " payment_amount

# (c) Search for the specified apartment using the apartment number.
# Assign file name
file_name="./data/${apt_number}.apt"

# Check if file exists
if [[ -e "$file_name" ]]; then
    # Read existing data
    {
        read -r first_name last_name
        read -r lease_start lease_end
        read -r balance

    } < "$file_name"

    # (d) Update balance
    balance=$((balance - payment_amount))

    # Write the updated data back to the file
    {
        echo "$first_name $last_name"
        echo "$lease_start $lease_end"
        echo "$balance"

    } > "$file_name"

    # (e) Update data/queries.log
    echo "$(date) PAID: $apt_number - AMOUNT: $payment_amount - NEW BALANCE: $balance" >> "./data/queries.log"
else
    # (f) Print the error message if apartment not found
    echo "ERROR: apartment not found"
fi
