## A Makefile for Paintshop
# Created by CSCI3081W Guru
# Copyright (c) CSCI3081W Guru. All rights reserved.

UNAME = $(shell uname)
CC 		= g++
CFLAGS 	= -c -Wall
LDFLAGS =
GLUI = glui
GLUI_PATH = ./glui
GLUI_LIB = $(GLUI_PATH)/lib/lib$(GLUI).a
LINK_LIBS += -L./$(GLUI)/lib/ -l$(GLUI)
OBJECT_DIR = object_files
SOURCE_DIR = src
INCLUDE = -I./$(GLUI)/include 

OBJECTS = $(addprefix $(OBJECT_DIR)/,  $(FILENAMES:.cpp=.o)) 
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cpp)
FILENAMES =  $(notdir $(CPPFILES))

ifeq ($(UNAME), Darwin) # Mac OSX 
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = paintshop
else # LINUX
	LINK_LIBS += -lglut -lGL -lGLU
	EXECUTABLE = paintshop
endif


build: setup $(EXECUTABLE)

rebuild: clean build

# Create the object_files directory only if it does not exist. 
setup: | $(OBJECT_DIR)

$(OBJECT_DIR): 
	mkdir -p $(OBJECT_DIR)

$(EXECUTABLE): $(GLUI_LIB) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $@

# Explicitly defined build targets because of dependancy on other header files
$(OBJECT_DIR)/PaintShop.o: $(SOURCE_DIR)/PaintShop.cpp $(SOURCE_DIR)/PaintShop.h $(SOURCE_DIR)/ColorData.h $(SOURCE_DIR)/PixelBuffer.h
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/PixelBuffer.o: $(SOURCE_DIR)/PixelBuffer.cpp $(SOURCE_DIR)/PixelBuffer.h $(SOURCE_DIR)/ColorData.h 
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

# Pattern build targets
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.h
	#@echo 'Compiling arbitrary .cpp file with .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	#@echo 'Compiling arbitrary .cpp file without .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

clean:
	\rm -rf $(OBJECT_DIR) $(EXECUTABLE) 

cleanglui:	
	 $(MAKE)  -C ./$(GLUI)/ clean

$(GLUI_LIB): 
	$(MAKE) -C ./$(GLUI)/ all