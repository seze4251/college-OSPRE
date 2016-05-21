#!/bin/bash

# Remove old executables
echo "Removing Old Executables"
rm bin/*

# Compile OSPRE
echo "Compiling OSPRE"
make bin/WatchDog
make bin/ScComms
make bin/CameraController
make bin/ImageProcessor
make bin/GNC
make bin/Spacecraft

# Cleaning .o Files
echo "Cleaning OSPRE"
make clean
