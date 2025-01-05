#! /bin/bash

export PATH="$PATH:/opt/toolchains/dc/mkdcdisc/builddir/"

workspaceDir=$(dirname "$(readlink -f "$0")")
files=""
directories="-d $workspaceDir/cd/"

echo "Generating emulator image"
mkdcdisc  -N -e $workspaceDir/game-main.elf $files $directories -o $workspaceDir/disc.cdi -n "The Last Escape"
echo "Generating CD image"
mkdcdisc  -e $workspaceDir/game-main.elf $files $directories -o $workspaceDir/disc_dc.cdi -n "The Last Escape"