#!/bin/bash
rm log/*
ulimit -c unlimited

bin/CameraController &
bin/GNC &
bin/ImageProcessor &
bin/ScComms &
bin/Spacecraft &
bin/WatchDog &
