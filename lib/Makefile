TARGET = minlib.a

ARCH = i686-elf
CC = $(ARCH)-gcc
AS = $(ARCH)-as
AR = $(ARCH)-ar
LINKER = $(ARCH)-ld

CFLAGS = -m32 -g -I include/ -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fno-stack-protector
ASFLAGS = --32 -g
ARFLAGS = -rcs
LDFLAGS = -m elf_i386

SRCDIR = src
OBJDIR = obj
INCDIR = include

.PHONY: all clean clean-all mkobj

ASM_SOURCES := $(shell find $(SRCDIR) -name \*.S)
C_SOURCES := $(shell find $(SRCDIR) -name \*.c)
INC_HEADERS := $(shell find $(INCDIR) -name \*.h)

C_OBJECTS	:= $(C_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
S_OBJECTS	:= $(ASM_SOURCES:$(SRCDIR)/%.S=$(OBJDIR)/%.s.o)

all: mkobj $(INC_HEADERS) $(TARGET) 

	
$(C_OBJECTS): $(OBJDIR)/$(notdir %.o) : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo [OK] Compiled $<!

$(S_OBJECTS): $(OBJDIR)/$(notdir %.s.o) : $(SRCDIR)/%.S
	@$(AS) $(ASFLAGS) -c $< -o $@
	@echo [OK] Compiled $<!

mkobj:
	@rsync -v -a -f"+ */" -f"- *" $(SRCDIR)/ $(OBJDIR)/
	@echo [OK] Generated objects directory tree!


$(TARGET): $(C_OBJECTS) $(S_OBJECTS)
	$(AR) $(ARFLAGS) $(TARGET) $^
	@echo [OK] Successfully linked. Library generated!

clean:
	@rm -fv $(C_OBJECTS) $(S_OBJECTS)

clean-all:
	$(MAKE) clean
	@rm -rfv $(TARGET) $(OBJDIR)
