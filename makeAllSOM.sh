#!/bin/bash

# Remove old executables
echo "Removing Old Executables"
rm bin/*

# Remake Libraries
echo "Making Libraries"
./Image_Processing/analyzeImagePi/makeImageLib.sh
./GNC/Kalman_Filter_Iteration/makeGNCLib.sh

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
rm -r Build_Apps build_Main
