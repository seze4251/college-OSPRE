#!/bin/bash
ulimit -c unlimited

bin_test/testAnalyzeImage
bin_test/testByteBuffer
bin_test/testCircularBuffer
bin_test/testExternalBuilderParser
bin_test/testInternalBuilderParser
