#!/bin/bash

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"

# Remove all objective files, Library Files and Derived Files
rm *.o *.dep *.lib
rm ../../lib/Kalman_Filter_Iteration.lib

# Make Analyze Image Library and Copy it to desired Location
make -f Kalman_Filter_Iteration_rtw.mk

cp Kalman_Filter_Iteration.lib ../../lib/Kalman_Filter_Iteration.lib

# Clean all object / library / derived files (not including end product)
rm *.o *.dep *.lib
