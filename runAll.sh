#!/bin/bash
rm log/*
mkdir log
ulimit -c unlimited
bin/CameraController &
bin/GNC &
bin/ImageProcessor &
bin/ScComms &
bin/Spacecraft &
bin/WatchDog &
