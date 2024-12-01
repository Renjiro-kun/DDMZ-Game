TARGET = raylib-test.elf
SRCS=$(wildcard src/*.cpp src/Gameplay/TurnBased/*.cpp src/Scene/*.cpp src/Scene/ScenesImpl/*.cpp inc/*.hpp src/Sound/*.cpp src/Messages/*.cpp src/Input/*.cpp src/UI/*.cpp)
INC=$(src/)
OBJS = $(SRCS: .cpp=.o) romdisk.o
KOS_ROMDISK_DIR = romdisk

PCH_SRC = pch.cpp
PCH_HEADER = pch.h
PCH_OUT = pch.h.gch

KOS_CPPFLAGS += -std=gnu++17 -I include/ -I src/

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf
	-rm -f $(OBJS)
	
rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(OBJS) -lkosutils -lraylib -lGL -lm -ltsunami -lparallax -lpng -ljpeg -lz -lkmg -lwav

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)
	
dist: $(TARGET)
	-rm -f $(OBJS) romdisk.img
	$(KOS_STRIP) $(TARGET)
