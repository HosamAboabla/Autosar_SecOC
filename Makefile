# This line is to make not cause error which is interrupt during make clean
SHELL=C:/Windows/System32/cmd.exe

build:
	gcc ./source/*.c -I ./include/
	@echo "Build is done."