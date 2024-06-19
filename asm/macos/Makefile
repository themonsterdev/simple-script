AS = as
LD = ld
ASFLAGS = -o hello.o
LDFLAGS = -o hello

hello: hello.o
	$(LD) $(LDFLAGS) hello.o

hello.o: hello.s
	$(AS) $(ASFLAGS) hello.s

clean:
	rm -f hello.o hello
