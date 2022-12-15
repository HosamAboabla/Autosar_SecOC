CC = gcc
CFLAGS = -c 
INCS = -I ../include/
SRC = $(wildcard *.c)
OBJ = CanIF.o Com.o Csm.o main.o Pdur_Canif.o PduR_Com.o Pdur_SecOC.o SecOC.o SecOC_Lcfg.o SecOC_PBcfg.o 
project_name = SecOC_Implementation

# This line is to make not cause error which is interrupt during make clean
SHELL=C:/Windows/System32/cmd.exe

all: $(project_name).exe
	@echo "Build is done"

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) $< -o $@

$(project_name).exe: $(OBJ)
	$(CC) $(OBJ) -o $@

clean_all:
	rm *.o *.exe 

clean:
	rm *.exe 
