# PROJECT SETTINGS
OUTPUT_NAME	= particles
BUILD		= build
INCLUDES	= -Iinc
SOURCES		= src/*.c
OPTIONS		= -Wall -O3 -lSDL2main -lSDL2
ARGS		= # Used to pass a config path to the system


# PROJECT COMPILATION
cmp-w:
	x86_64-w64-mingw32-gcc -o $(BUILD)/$(OUTPUT_NAME)-windows $(INCLUDES) $(SOURCES) -lmingw32 $(OPTIONS) 

cmp-l:
	x86_64-linux-gnu-gcc -o $(BUILD)/$(OUTPUT_NAME)-linux $(INCLUDES) $(SOURCES) $(OPTIONS)


# PROJECT EXECUTION
run-w:
	$(BUILD)/$(OUTPUT_NAME)-windows.exe $(ARGS)

run-l:
	$(BUILD)/$(OUTPUT_NAME)-linux $(ARGS)