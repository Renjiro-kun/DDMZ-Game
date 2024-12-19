#! /bin/bash

export PATH="$PATH:/opt/toolchains/dc/mkdcdisc/builddir/"

workspaceDir="/home/vesel49k/Documents/Dreamcast-projects/raylib-test/dreamdisc24-jam"
files=""
directories="-d $workspaceDir/cd/titlescreen -d $workspaceDir/cd/music"

mkdcdisc  -N -e $workspaceDir/raylib-test.elf $files $directories -o $workspaceDir/disc.cdi -n "DreamDisc Game"