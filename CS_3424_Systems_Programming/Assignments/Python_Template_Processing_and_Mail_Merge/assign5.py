#!/usr/bin/env python3

import sys
import os
import re
import glob

# Read the template file
def read_template(template_file):
    with open(template_file, 'r') as file:
        return file.read()

# Replace placeholders in the template with values from the dictionary
def apply_template(template, values):
    for key in values:
        placeholder = "<<" + key + ">>"
        # Replace placeholders with values and cast to str
        template = template.replace(placeholder, str(values[key]))
    return template


# Write the filled template to an output file
def write_output(filled_template, last_name, output_dir):
    # Replace spaces with underscores in the last name for filename
    last_name_fixed = re.sub(r'\s+', '_', last_name)
    # Create initial file path
    file_path = os.path.join(output_dir, last_name_fixed + '.mail')

    # Initialize counter for duplicates
    counter = 1
    while os.path.exists(file_path):
        # If file exists, increment the counter and append 
        file_path = os.path.join(output_dir, last_name_fixed + str(counter) + '.mail')
        counter += 1

    # Write the filled template to the file
    with open(file_path, 'w') as output_file:
        output_file.write(filled_template)

# Process apt files with balances and write output files using the template
def process_apt_file(file_path, template, date, output_dir):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        # Separate after one space to get multiple last names
        name_parts = lines[0].strip().split(' ', 1)
        first_name = name_parts[0]
        last_name = name_parts[1]
        lease_start, lease_end = lines[1].strip().split()
        balance = int(lines[2].strip())
        
        # Check files for those that have a balance
        if balance > 0:
            # Create dictionary to store values to be replaced in template
            values = {
                'first_name': first_name,
                'last_name': last_name,
                'lease_start': lease_start,
                'lease_end': lease_end,
                'balance': balance,
                # Split base filename without extension
                'apt_number': os.path.splitext(os.path.basename(file_path))[0], 
                'date': date
            }

            # Apply template to actual values
            filled_template = apply_template(template, values)
            # Write output to file
            write_output(filled_template, last_name, output_dir)


def main(data_dir, template_file, date, output_dir):
    # Directory existence check
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    template = read_template(template_file)
    # Put .apt files from data dir into a list
    data_files = glob.glob(os.path.join(data_dir, '*.apt'))
    
    for file_path in data_files:
        process_apt_file(file_path, template, date, output_dir)


if __name__ == '__main__':
    # Arg check
    if len(sys.argv) != 5:
        print("Usage: assign5.py [data directory] [template file] [date] [output directory]")
        sys.exit(1)

    data_dir = sys.argv[1]
    template_file = sys.argv[2]
    date = sys.argv[3]
    output_dir = sys.argv[4]

    main(data_dir, template_file, date, output_dir)
