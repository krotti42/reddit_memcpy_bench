# Target Output
TARGET			= bench

# Generic shell commands
RM			= rm -rf
CP			= cp -Rf

# Toolchain
CC			= gcc
LD			= gcc
OBJCOPY			= objcopy

# Generic C compiler flags
#CCFLAGS			+= -O2
CCFLAGS			+= -Wall
CCFLAGS			+= -Wextra
CCFLAGS			+= -I ./

CCFLAGS_TARGET		= $(CCFLAGS)

# Generic GNU ld flags
LDFLAGS_TARGET_CM7	= $(CCFLAGS)

ASRC_TARGET		+= cycle.S
ASRC_TARGET		+= memcpy_asm.S

CSRC_TARGET		+= memcpy_c.c
CSRC_TARGET		+= bench.c

AOBJ_TARGET		+= $(ASRC_TARGET:.S=.o)
COBJ_TARGET		+= $(CSRC_TARGET:.c=.o)

all: target

# Link object files
target: $(AOBJ_TARGET) $(COBJ_TARGET)
	@echo "   [LD] $(TARGET)"
	@$(LD) -o $(TARGET) $(LDFLAGS_TARGET) $(AOBJ_TARGET) $(COBJ_TARGET)

# Compile assembly sources
$(AOBJ_TARGET): %.o: %.S
	@echo "   [AS] $@"
	@$(CC) -c $(CCFLAGS_TARGET) $(ASFLAGS_TARGET) -o $@ $<

# Compile C sources
$(COBJ_TARGET): %.o: %.c
	@echo "   [CC] $@"
	@$(CC) -c $(CCFLAGS_TARGET) -o $@ $<

.PHONY: clean
clean:
	@echo "[CLEAN]"
	@$(RM) $(AOBJ_TARGET)
	@$(RM) $(COBJ_TARGET)
	@$(RM) $(TARGET)
