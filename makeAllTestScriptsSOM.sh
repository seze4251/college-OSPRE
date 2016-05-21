#!/bin/bash

# Remove Old Executables
echo "Removing Old Executables"
rm bin_test/*

# Compiling OSPRE
echo "Compiling OSPRE"
make --file=makeTestScripts bin_test/testByteBuffer
make --file=makeTestScripts bin_test/testCircularBuffer
make --file=makeTestScripts bin_test/testExternalBuilderParser
make --file=makeTestScripts bin_test/testInternalBuilderParser

# Remvoing .o files
echo "Cleaning"
make --file=makeTestScripts clean
