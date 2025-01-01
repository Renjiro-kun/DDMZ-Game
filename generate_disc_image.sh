#! /bin/bash

export PATH="$PATH:/opt/toolchains/dc/mkdcdisc/builddir/"

workspaceDir="/home/vesel49k/Documents/Dreamcast-projects/raylib-test/dreamdisc24-jam"
files=""
directories="-d $workspaceDir/cd/"

mkdcdisc  -N -e $workspaceDir/game-main.elf $files $directories -o $workspaceDir/disc.cdi -n "The Last Escape"