#
# Makefile for Computer Animation and Visualization coursework
#

CC=g++
CFLAGS=-Wall -lglut -lGLU -lGL

cav :
	mkdir -p bin/src/display
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/volume.o src/volume.cc
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/display/three_dimensional_display.o src/display/three_dimensional_display.cc
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/display/display_algorithm.o src/display/display_algorithm.cc
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/display/two_dimensional_display.o src/display/two_dimensional_display.cc
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/demo4.o src/demo4.cc
	$(CC) $(CFLAGS) -obin/cav2 bin/src/volume.o bin/src/display/two_dimensional_display.o bin/src/display/three_dimensional_display.o bin/src/display/display_algorithm.o bin/src/demo4.o

doxygen :
	doxygen Doxyfile

clean : 
	rm -rf bin
	rm -rf docs
