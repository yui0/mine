CC	      = gcc
CFLAGS      = -O2 -g
#CFLAGS      = -O2 -g -D_MINGW32_
LDFLAGS      = -lm

DEST	      = .

LD	      = gcc

SDL_LDFLAGS 	= $(shell sdl-config --libs)
SDL_CFLAGS	= $(shell sdl-config --cflags)

MAKEFILE      = Makefile

OBJS	      = mine.o CTime.o CBmps.o Cffont.o
 
PRINT	      = pr

PROGRAM       = mine

SHELL	      = /bin/sh

%.o:		%.c
		$(CC) $(SDL_CFLAGS) $(CFLAGS) -c $<
all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		$(LD) -o $(PROGRAM) $(OBJS) $(SDL_LDFLAGS)  $(LDFLAGS) 

