#! /bin/bash

export PATH="$PATH:/opt/toolchains/dc/mkdcdisc/builddir/"

workspaceDir="/home/vesel49k/Documents/Dreamcast-projects/raylib-test/dreamdisc24-jam"

files="-f $workspaceDir/cd/music/bgm_field.adpcm -f $workspaceDir/cd/music/sfx_boom.wav"
echo $files

mkdcdisc -e $workspaceDir/raylib-test.elf $files -o $workspaceDir/disc.cdi
