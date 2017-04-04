#!/bin/bash

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"

# Remove all objective files, Library Files and Derived Files
rm *.o *.dep *.lib
rm ../../lib/analyzeImage.lib

# Make Analyze Image Library and Copy it to desired Location
make -f analyzeImage_rtw.mk

# Move Library to Lib Folder
cp analyzeImage.lib ../../lib/analyzeImage.lib

# Clean all object / library / derived files (not including end product)
rm *.o *.dep *.lib
