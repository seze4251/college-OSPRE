#!/bin/bash
rm log/*
mkdir -p log
ulimit -c unlimited

# The order is this way so that GNC and ScComms get a link so that when Spacecraft comes online, GNC gets all messages from S/C for SIM Mode, Could add simple adjustment so that ScComms does not accept Spacecrafts connection until all OSPRE processes are up and running (future use)
bin/ScComms &
bin/GNC &
sleep 5
bin/Spacecraft
sleep 2
bin/WatchDog &
bin/CameraController &
bin/ImageProcessor &

