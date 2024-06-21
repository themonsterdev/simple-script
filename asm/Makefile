# Variables for compilation tools
NASM = nasm
NASMFLAGS = -f macho64

LD = ld
LDFLAGS = -static

# Source and object file names
SRC = output.asm
OBJ = output.o
OUT = output

# Default targets
.PHONY: all clean

# Default target: build the executable
all: $(OUT)

# Target for the executable
$(OUT): $(OBJ)
	@echo "Linking $@..."
	$(LD) $(LDFLAGS) -o $@ $^

# Target for the object file
$(OBJ): $(SRC)
	@echo "Assembling $@..."
	$(NASM) $(NASMFLAGS) -o $@ $<

# Target for cleaning up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(OUT)

# Display executed commands
$(VERBOSE).SILENT:
