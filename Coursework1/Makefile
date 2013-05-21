#
# Makefile for Computer Animation and Visualization coursework
#

CC=gcc
CFLAGS=-Wall -lglut -lGLU -lGL

cav :
	mkdir -p bin/src
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/skeleton.o src/skeleton.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/cav_utils.o src/cav_utils.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/view.o src/view.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/bone.o src/bone.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/triangle_mesh.o src/triangle_mesh.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/animation_controller.o src/animation_controller.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/edge.o src/edge.cc
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -obin/src/triangle.o src/triangle.cc
	g++ -obin/cav bin/src/view.o bin/src/triangle_mesh.o bin/src/triangle.o bin/src/skeleton.o bin/src/float_matrix.o bin/src/edge.o bin/src/cav_utils.o bin/src/bone.o bin/src/animation_controller.o -lglut -lGLU

doxygen :
	doxygen Doxyfile

clean : 
	rm -rf bin 
	rm -rf docs
