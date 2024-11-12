#!/bin/bash

# Check if /data exists, if not then create
if [ ! -d "data" ]; then
    mkdir data
fi

# Menu Prompt
while true ; do
    echo "Enter one of the following actions or press CTRL-D to exit."
    echo "C - create a new apartment record"
    echo "R - read an existing apartment record"
    echo "U - update an existing apartment record"
    echo "D - delete an existing apartment record"
    echo "P - record payment for an existing tenant"
    echo "T - get total apartments"
    # add break for EOF, otherwise infinite loop
    read choice || break

    # Choice case
    case "$choice" in
    [cC]) ./create.bash ;;
    [rR]) ./read.bash ;;
    [uU]) ./update.bash ;;
    [dD]) ./delete.bash ;;
    [pP]) ./payment.bash ;;
    [tT]) ./total.bash ;;
    # Invalid option
    *)
        echo "ERROR: invalid option"
        continue
        ;;
    esac
done
