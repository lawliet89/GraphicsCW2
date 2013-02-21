# MAKEFILE

#-------------------------------------------------------------------------------
# USER SETTINGS
#-------------------------------------------------------------------------------

# Variable that contains the name of the program
PROGRAM := raycast

OBJ_LIST := image.o \
	scene_parser.o \
	sphere.o \
	group.o \
	orthographic_camera.o \
	raycast.o

HEADER_LIST := hit.h image.h ray.h scene_parser.h vectors.h \
	object3d.h group.h camera.h orthographic_camera.h


COMPILER := g++
CXXFLAGS := -g -pedantic -std=c++0x -Wall -Wextra -Werror=return-type -Wno-reorder
CFLAGS  := -O2 -I. -c
LDFLAGS := -lm

SCENE_DIR := ../scenes/
OUTPUT_DIR := ./output/

#-------------------------------------------------------------------------------
# ACTUAL TARGETS
#-------------------------------------------------------------------------------
$(PROGRAM): $(OBJ_LIST)
	$(COMPILER) $(OBJ_LIST) -o $(PROGRAM) $(CXXFLAGS) $(LDFLAGS)
	
image.o: image.cc $(HEADER_LIST) 
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

orthographic_camera.o: orthographic_camera.cc $(HEADER_LIST)
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

scene_parser.o: scene_parser.cc $(HEADER_LIST) 
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

sphere.o: sphere.cc $(HEADER_LIST) 
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

group.o: group.cc $(HEADER_LIST) 
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

raycast.o: raycast.cc $(HEADER_LIST) 
	$(COMPILER) $(CXXFLAGS) $(CFLAGS) -o $@ $<

#-------------------------------------------------------------------------------
# PHONY TARGETS
#-------------------------------------------------------------------------------
.PHONY : clean again all git debug windows 1 2 3 4 5 6 run
all: $(PROGRAM)

clean:
	rm -rf $(OBJ_LIST) $(PROGRAM) *~ $(OUTPUT_DIR)/*

again:
	make clean
	make

git:
	make
	git add .
	git commit -m "$(m)"
	
debug:
	make
	gdb $(PROGRAM)

# start X server on Cygwin
windows:
	startxwin
    
1:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 200 200 -output $(OUTPUT_DIR)scene$@.ppm -depth 9 10 $(OUTPUT_DIR)depth$@.ppm
	
2:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 200 200 -output $(OUTPUT_DIR)scene$@.ppm -depth 8 12 $(OUTPUT_DIR)depth$@.ppm
	
3:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 200 200 -output $(OUTPUT_DIR)scene$@.ppm -depth 8 12 $(OUTPUT_DIR)depth$@.ppm
	
4:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 200 200 -output $(OUTPUT_DIR)scene$@.ppm -depth 13 16 $(OUTPUT_DIR)depth$@.ppm
	
5:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 300 300 -output $(OUTPUT_DIR)scene$@.ppm -depth 0.1 2 $(OUTPUT_DIR)depth$@.ppm
	
6:
	make
	./$(PROGRAM) -input $(SCENE_DIR)scene$@.txt -size 300 300 -output $(OUTPUT_DIR)scene$@.ppm -depth 1 7 $(OUTPUT_DIR)depth$@.ppm

run:
	make 1
	make 2
	make 3
	make 4
	make 5
	make 6