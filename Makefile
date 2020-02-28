OBJS	= dmf2mod.o mod.o dmf.o
SOURCE	= dmf2mod.c mod.c dmf.c
HEADER	= mod.h dmf.h zconf.h zlib.h
OUT	= dmf2mod.exe
CC	 = gcc
# Use '-Wall' flag for warnings.
FLAGS	 = -g -c
LFLAGS	 = -lm -lz

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

dmf2mod.o: dmf2mod.c
	$(CC) $(FLAGS) dmf2mod.c 

mod.o: mod.c
	$(CC) $(FLAGS) mod.c 

dmf.o: dmf.c
	$(CC) $(FLAGS) dmf.c 


clean:
	$(RM) $(OUT) $(OBJS) 
