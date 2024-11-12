#!/usr/bin/env python3

import os
import sys

"""Organizes a directory by project names"""
def organize_directory(dir_path):

    # Check directory existence
    if not os.path.isdir(dir_path):
        print("Error: " + dir_path + " does not exist!")
        sys.exit(1)

    # Create misc directory if it doesn't exist
    misc_dir = dir_path + "/misc"
    if not os.path.isdir(misc_dir):
        os.system("mkdir " + misc_dir)

    # Process each file in directory
    for filename in os.listdir(dir_path):
        file_path = dir_path + '/' + filename
        
        if os.path.isdir(file_path):  # Skip directories
            continue

        dot_index = filename.find('.') # Returns -1 if there is no filename extension
    
        # Extract prefix and suffix
        prefix = filename[:4]
        if dot_index != -1:
            suffix = filename[4:dot_index]
        else:
            suffix = filename[4:]
    
        # "proj" files
        if prefix == "proj":
            if suffix:
                assignment_dir = dir_path + "/assignment" + suffix
            else:
                assignment_dir = dir_path + "/assignment"
        
            # Directory existence check
            if not os.path.isdir(assignment_dir):
                os.system("mkdir " + assignment_dir)
            os.system("mv " + file_path + " " + assignment_dir)
        # misc files
        else:
            os.system("mv " + file_path + " " + misc_dir)

"""Zips the specified assignment folder and places it into the base directory"""
def zip_assignment(dir_path, assignment_suffix):

    assignment_dir = "assignment" + assignment_suffix
    zip_file_name = dir_path + "/" + assignment_dir + ".zip" # dir_path to put zip into base directory

    if not os.path.isdir(dir_path + "/" + assignment_dir):
        print("Error: " + assignment_dir + " does not exist!")
        sys.exit(1)

    # Use the zip command
    cmd_string = "zip " + zip_file_name + " " + dir_path + "/" + assignment_dir + "/*"
    os.system(cmd_string)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: " + sys.argv[0] + " <dirpath> [assignment_dir suffix]")
        sys.exit(1)

    dir_path = sys.argv[1]
    organize_directory(dir_path)
    
    # Optional zip function call
    if len(sys.argv) == 3:
        zip_assignment(dir_path, sys.argv[2])
