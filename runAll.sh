#!/bin/bash
rm log/*
mkdir log
ulimit -c unlimited
bin/ScComms &
bin/GNC &
sleep 3
bin/Spacecraft &
bin/CameraController &
bin/ImageProcessor &
bin/WatchDog &
