#
#	 Makefile
#	 OSPRE
#
#	 Created by Hilton Lipschitz on 2015-09-01.
#	 Copyright (c) 2015 Maritime Capital LP. All rights reserved.
#
#        Modified By Seth Zegelstein
#        Date Modified: 11/26/2016

# HIL: No spaces or comments after otherwise it captures them!
# Determine the platform

UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
  CC := clang++ -arch x86_64
else
  CC := g++
endif


# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

# Targets (6 executables)
#WATCHDOG
EXECUTABLE_WatchDog := WatchDog
TARGET_WatchDog := $(TARGETDIR)/$(EXECUTABLE_WatchDog)

#SCCOMMS
EXECUTABLE_ScComms := ScComms
TARGET_ScComms := $(TARGETDIR)/$(EXECUTABLE_ScComms)

#CAMERA CONTROLLER
EXECUTABLE_CameraController := CameraController
TARGET_CameraController := $(TARGETDIR)/$(EXECUTABLE_CameraController)

#IMAGE PROCCESSOR
EXECUTABLE_ImageProcessor := ImageProcessor
TARGET_IMAGEPROC := $(TARGETDIR)/$(EXECUTABLE_ImageProcessor)

#GNC
EXECUTABLE_GNC := GNC
TARGET_GNC := $(TARGETDIR)/$(EXECUTABLE_GNC)

#SPACECRAFT
EXECUTABLE_SPACECRAFT := Spacecraft
TARGET_SPACECRAFT := $(TARGETDIR)/$(EXECUTABLE_SPACECRAFT)

# Main OBJS
MAINDIR := Main_Files
MAINOBJ_DIR := build_Main

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Folder Lists
# Note: Intentionally excludes the root of the include folder so the lists are clean
INCDIRS := $(shell find include/**/* -name '*.h' -exec dirname {} \; | sort | uniq)
BUILDLIST := $(patsubst include/%,$(BUILDDIR)/%,$(INCDIRS))
INCLIST := $(patsubst include/%,-I include/%,$(INCDIRS))
# Having trouble getting Header files for library to link
#INCLIST += $(shell find Image_Processing/analyzeImagePi/ -name '*.h' -exec dirname {} \; | sort | uniq)

# Shared Compiler Flags
CFLAGS := -c #-Wall -Wextra
INC := -I include $(INCLIST) -I /usr/local/include


# Platform Specific Compiler Flags
ifeq ($(UNAME_S),Linux)
    CFLAGS += -std=gnu++11 -O2 # -fPIC

    # PostgreSQL Special
    PG_VER := 9.3
    INC += -I /usr/pgsql-$(PG_VER)/include
    LIB += -L /usr/pgsql-$(PG_VER)/lib
else
  CFLAGS += -std=c++11 -stdlib=libc++ -O2
endif

#WATCHDOG
$(TARGET_WatchDog): $(OBJECTS) $(MAINOBJ_DIR)/mainWatchDog.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_WatchDog)\n"; $(CC) $^ -o $(TARGET_WatchDog)


#SCCOMMS
$(TARGET_ScComms): $(OBJECTS) $(MAINOBJ_DIR)/mainScComms.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_ScComms)\n"; $(CC) $^ -o $(TARGET_ScComms)

#CAMERA CONTROLLER
$(TARGET_CameraController): $(OBJECTS) $(MAINOBJ_DIR)/mainCameraController.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_CameraController)\n"; $(CC) $^ -o $(TARGET_CameraController)

#IMAGE PROCCESSOR
$(TARGET_IMAGEPROC): $(OBJECTS) $(MAINOBJ_DIR)/mainImageProcessor.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_IMAGEPROC)\n"; $(CC) $^ -o $(TARGET_IMAGEPROC) -I ././Image_Processing/analyzeImagePi ./Image_Processing/lib/analyzeImage.lib

#GNC
$(TARGET_GNC): $(OBJECTS) $(MAINOBJ_DIR)/mainGNC.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_GNC)\n"; $(CC) $^ -o $(TARGET_GNC) 

#SPACECRAFT
$(TARGET_SPACECRAFT): $(OBJECTS) $(MAINOBJ_DIR)/mainSpacecraft.o
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "	 Linking $(TARGET_SPACECRAFT)\n"; $(CC) $^ -o $(TARGET_SPACECRAFT)


$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDLIST)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


# Need to have all dependencies mapped out for building 
$(MAINOBJ_DIR)/%.o: $(MAINDIR)/%.$(SRCEXT)
	@mkdir -p $(MAINOBJ_DIR)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning .o Files…"; $(RM) -r $(BUILDDIR) $(TARGET); rm build_Main/*;

#install:
#	@echo "Installing $(EXECUTABLE)..."; cp $(TARGET) $(INSTALLBINDIR)
	
#distclean:
#	@echo "Removing $(EXECUTABLE)"; rm $(INSTALLBINDIR)/$(EXECUTABLE)

.PHONY: clean