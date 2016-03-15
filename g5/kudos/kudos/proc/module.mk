# Makefile for the kernel module

# Set the module name
MODULE := proc

FILES := elf.c syscall.c process.c syscall_handler.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))

