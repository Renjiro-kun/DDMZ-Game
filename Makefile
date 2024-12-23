TARGET = game-main.elf
SRCS=$(wildcard src/*.cpp src/VMU/*.cpp src/Gameplay/Objects/*.cpp src/Gameplay/Inventory/*.cpp src/Scene/*.cpp src/Scene/ScenesImpl/*.cpp inc/*.hpp src/Sound/*.cpp src/Messages/*.cpp src/Input/*.cpp src/UI/*.cpp src/UI/HUD/*.cpp src/UI/Menu/*.cpp)
INC=$(src/)
OBJS = $(SRCS: .cpp=.o) romdisk.o
KOS_ROMDISK_DIR = romdisk

KOS_CPPFLAGS += -std=gnu++20 -I include/ -I src/

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf
	-rm -f $(OBJS)
	
rm-elf:
	-rm -f $(TARGET) romdisk.*

ifeq ($(config), debug)
KOS_CPPFLAGS += -DDEBUG
endif

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(OBJS) -lkosutils -lraylib -lGL -lm -lparallax -lpng -ljpeg -lz -lwav

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)
	
dist: $(TARGET)
	-rm -f $(OBJS) romdisk.img
	$(KOS_STRIP) $(TARGET)
