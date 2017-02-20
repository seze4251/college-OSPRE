#!/bin/bash

# Remove old executables
echo "Removing Old Executables"
rm bin/*

# Compile OSPRE
echo "Compiling OSPRE"
make -j bin/WatchDog
make -j bin/ScComms
make -j bin/CameraController
make -j bin/ImageProcessor
make -j bin/GNC
make -j bin/Spacecraft

# Cleaning .o Files
echo "Cleaning OSPRE"
make clean
