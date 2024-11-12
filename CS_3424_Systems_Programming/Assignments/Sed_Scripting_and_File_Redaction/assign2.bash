#!/bin/bash

# Invalid input
if [ "$#" -lt 2 ]; then
    echo "Invalid input: $0 <directory> <days> [-r]"
    exit 1
fi

# Assign variables
directory=$1
days=$2
recursive="" # default value to check for recursion

# Optional recursion logic
if [ "$#" -eq 3 ] && [ "$3" == "-r" ]; then
    recursive="-r"
fi

# Store find command with no recursion
finder="find $directory -maxdepth 1 -type f -mtime +$days"
# Update find command if recursion was input
if [ "$recursive" == "-r" ]; then
    # find is recursive by default so "-maxdepth" is removed
    finder="find $directory -type f -mtime +$days"
fi

# Execute sed script to files found with find command
$finder | while read file; do
    # Run redact script extended and edit file in place
    sed -E -f redact.sed -i "$file"
done

