#! /bin/bash

export PATH="$PATH:/opt/toolchains/dc/mkdcdisc/builddir/"

mkdcdisc -e '/home/vesel49k/Documents/Dreamcast-projects/raylib-test/dreamdisc24-jam/raylib-test.elf' -o '/home/vesel49k/Documents/Dreamcast-projects/raylib-test/dreamdisc24-jam/disc.cdi'
