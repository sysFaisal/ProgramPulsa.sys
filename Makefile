# Lokasi Folder
DIR = ../ProgramPulsa.sys/ReferensiCode

# For C-only project (Teori/Tubes is now C, not C++)
SRC_C   = $(wildcard $(DIR)/*.c)

COMPILER = gcc
SRC      = $(SRC_C)

FLAGS = -I"$(DIR)" -Wall -Wextra -Wshadow -std=c17 -O2

DEBUG_FLAGS = -g -O0

ifeq ($(OS),Windows_NT)

    TARGET = program.exe
    LDFLAGS = -lm -static-libgcc

    RM = if exist $(TARGET) del $(TARGET)

    CLEAN_MSG = @echo Delete file program ...

else

    TARGET = program
    LDFLAGS = -lm

    RM = rm -f $(TARGET)

    CLEAN_MSG = @echo "Delete file program ..."

endif

all:
	@echo "Compiler : $(COMPILER)"
	@echo "Source   : $(SRC)"
	$(COMPILER) $(FLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	@echo --------------------------------
	@echo .                              .
	@./$(TARGET)
	@echo .                              .
	@echo --------------------------------
	@$(RM)

debug_build:
	@echo "Creating DEBUG build..."
	$(COMPILER) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
	@echo "Ready for debugging!"

clean:
	$(CLEAN_MSG)
	@$(RM)
