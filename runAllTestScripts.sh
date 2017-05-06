#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"

ulimit -c unlimited

bin_test/testAnalyzeImage
bin_test/GNC_Unit_Test
bin_test/testImageReading
bin_test/testByteBuffer
bin_test/testCircularBuffer
bin_test/testExternalBuilderParser
bin_test/testInternalBuilderParser
