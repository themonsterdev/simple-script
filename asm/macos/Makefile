# Variables for compilation tools
AS = as
ASFLAGS = -o

LD = ld
LDFLAGS = -o

# Source and object file names
SRC = hello.s
OBJ = hello.o
OUT = hello

# Default targets
.PHONY: all clean

# Default target: build the executable
all: $(OUT)

# Target for the executable
$(OUT): $(OBJ)
	@echo "Linking $@..."
	$(LD) $(LDFLAGS) $@ $^

# Target for the object file
$(OBJ): $(SRC)
	@echo "Assembling $@..."
	$(AS) $(ASFLAGS) $@ $<

# Target for cleaning up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(OUT)

# Display executed commands
$(VERBOSE).SILENT:
