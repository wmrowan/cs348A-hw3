###############################################################################
# complier definition and its flags
##############################################################################
CC= g++

SHELL=/bin/sh

# FLTK directories -- edit these to specify non-default FLTK location
FL_INCLUDE =
FL_LIBDIR =
FL_LIBS = -lfltk_gl -lfltk

# Additional libraries needed to link with OpenGL and any platform specific stuff
GLLIBS = -lGL -lGLU -lX11 -lm

CFLAGS= -O2 $(FL_INCLUDE)

LFLAGS = -O2

###############################################################################
# basic headers and files *.o to be linked together
###############################################################################
HEADBAS= pp1_ui.h pp1.h
OBJBAS= pp1_ui.o

###############################################################################
# files to be build in default case
###############################################################################
all: pp1

###############################################################################
# linking
###############################################################################
pp1: pp1.o $(OBJBAS)
		@echo Linking pp1
		$(CC) pp1.cxx -o pp1 $(FL_INCLUDE) $(LFLAGS) $(OBJBAS) $(FL_LIBDIR) \
		$(FL_LIBS) $(GLLIBS)

###############################################################################
# compilation of main file
###############################################################################
pp1.o: pp1_ui.h pp1.cxx
		@echo Compiling pp1
		$(CC) $(CFLAGS) -c pp1.cxx

###############################################################################
# compilation of other files
###############################################################################
pp1_ui.o: pp1_ui.h pp1_ui.cxx
		@echo Compiling pp1_ui
		$(CC) $(CFLAGS) -c pp1_ui.cxx

###############################################################################
# initial procedure
###############################################################################
clean:
		@rm -fr *.o *% .*% \
		pp1

tags:
	ctags -R .
