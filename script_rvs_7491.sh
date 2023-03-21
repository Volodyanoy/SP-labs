#!/bin/bash

# Script information
echo " "
echo "...Some information..."
echo " "
echo "Author: Vladimir Repkin"
echo "Program name: script_rvs_7491.sh"
echo "Description: This script asks for the name of a file and outputs information about the file if it exists."
echo "Files: "
ls -1
echo " "
echo "...Working..."
echo " "
# Loop until user chooses to quit
while true; do
    # Ask user for file name
    read -p "Enter the name of a file: " filename
    
    # Check if file exists
    if [ -e "$filename" ]; then
        # Output file information
    	echo "File name: $(basename "$filename")"
    	echo "File type: $(file "$filename" | cut -d: -f2-)"
    	echo "File size: $(stat -c %s "$filename") bytes"
    	echo "File owner: $(stat -c %U "$filename")"
    	echo "Access rights: $(stat -c %A "$filename")"
    	echo "File creation date: $(date -d "$(stat -c %w "$filename")" +"%Y-%m-%d %H:%M:%S")"
    else
        # Output error message if file doesn't exist
        echo "Error: File $filename does not exist." >&2 2>> errors.txt
    fi
    
    # Ask user if they want to continue or quit
    read -p "Do you want to continue? (y/n): " choice
    case "$choice" in 
        y|Y )
            continue
            ;;
        n|N )
            echo " "
            echo "...Exiting..."
	    echo " "
            break
            ;;
        * )
            echo "Invalid choice"
            echo " "
            echo "...Exiting..."
	    echo " "
            exit 1
            ;;
    esac
done 

