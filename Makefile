TARGET = raylib-test.elf
SRCS=$(wildcard src/*.cpp src/Scene/*.cpp inc/*.hpp)
INC=$(src/)
OBJS = $(SRCS: .cpp=.o) romdisk.o
KOS_ROMDISK_DIR = romdisk

PCH_SRC = pch.cpp
PCH_HEADER = pch.h
PCH_OUT = pch.gch

KOS_CPPFLAGS += -std=gnu++17 

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf
	-rm -f $(OBJS)
	
rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(OBJS) -lkosutils -lraylib -lGL -lm -ltsunami -lparallax -lpng -ljpeg -lz -lkmg -lexpat

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)
	
dist: $(TARGET)
	-rm -f $(OBJS) romdisk.img
	$(KOS_STRIP) $(TARGET)
