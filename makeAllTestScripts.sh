#!/bin/bash

# Remove Old Executables
echo "Removing Old Executables"
rm bin_test/*

# Remake Libraries
echo "Making Libraries"
./Image_Processing/analyzeImagePi/makeImageLib.sh
./GNC/Kalman_Filter_Iteration/makeGNCLib.sh

# Compiling OSPRE
mkdir -p build_test
mkdir -p bin_test
echo "Compiling OSPRE"
make -j --file=makeTestScripts bin_test/testAnalyzeImage
make -j --file=makeTestScripts bin_test/testByteBuffer
make -j --file=makeTestScripts bin_test/testCircularBuffer
make -j --file=makeTestScripts bin_test/testExternalBuilderParser
make -j --file=makeTestScripts bin_test/testInternalBuilderParser

# Remvoing .o files
echo "Cleaning"
make --file=makeTestScripts clean
