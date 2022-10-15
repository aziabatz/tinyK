KERNEL_NAME = unexOS
TARGET = $(KERNEL_NAME).bin

ARCH = i686-elf
CC = $(ARCH)-gcc
AS = $(ARCH)-as
LINKER = $(ARCH)-ld

GRUB = grub
MKISO = $(GRUB)-mkrescue

CFLAGS = -m32 -g $(foreach dir,$(INCLUDES),-I$(dir)) -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fno-stack-protector
ASFLAGS = --32 -g
LDFLAGS = -m elf_i386

SRCDIR = src
OBJDIR = obj
ISODIR = iso

INCLUDES = ./include/ ./lib/include/
LIBRARIES = ./lib/minlib.a

define GRUB_ENTRY
"set timeout=5\n\
set default=0\n\
\n\
menuentry \"$(KERNEL_NAME)\" {\n\t\
	multiboot /boot/$(TARGET)\n\t\
	boot \n\
}"
endef

.PHONY: all clean clean-iso clean-all iso mkobj

ASM_SOURCES := $(shell find $(SRCDIR) -name \*.S)
C_SOURCES := $(shell find $(SRCDIR) -name \*.c)

C_OBJECTS	:= $(C_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
S_OBJECTS	:= $(ASM_SOURCES:$(SRCDIR)/%.S=$(OBJDIR)/%.s.o)

all: bin iso

bin: mkobj $(TARGET)

$(TARGET): $(C_OBJECTS) $(S_OBJECTS) $(LIBRARIES)
	@$(LINKER) $(LDFLAGS) -T link.ld -o $(TARGET) $^
	@echo [OK] Successfully linked. Binary generated!

$(C_OBJECTS): $(OBJDIR)/$(notdir %.o) : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo [OK] Compiled $<!

$(S_OBJECTS): $(OBJDIR)/$(notdir %.s.o) : $(SRCDIR)/%.S
	@$(AS) $(ASFLAGS) -c $< -o $@
	@echo [OK] Compiled $<!


iso: $(TARGET)
	@mkdir -pv $(ISODIR)/boot/grub
	@cp -v $(TARGET) $(ISODIR)/boot/
	@printf $(GRUB_ENTRY) > $(ISODIR)/boot/grub/grub.cfg
	@$(MKISO) $(ISODIR)/ -o $(KERNEL_NAME).iso
	@echo [OK] Generated ISO image successfully!

mkobj:
	@rsync -v -a -f"+ */" -f"- *" $(SRCDIR)/ $(OBJDIR)/
	@echo [OK] Generated objects directory tree!

$(LIBRARIES):
	cd lib && $(MAKE)

clean:
	@rm -fv $(C_OBJECTS) $(S_OBJECTS)

clean-iso:
	@rm -rfv $(ISODIR) $(KERNEL_NAME).iso

clean-all:
	$(MAKE) clean clean-iso
	cd lib && $(MAKE) clean-all
	@rm -rfv $(TARGET) $(OBJDIR)
