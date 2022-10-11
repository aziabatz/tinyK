#!/bin/bash
#version: v1

#ex: qemu-system-i386 (-kernel) (-S -s) (-serial file:serial_out.log) [kernel or iso]

mboot_mode="-kernel"
gdb_debug="-S -s"
serial_debug="-serial:file $file"

cmd=""

function version {
	echo 
	echo "OS-Dev QEMU Starter. Version v1"
	echo "Author: Ahmed Ziabat."
	echo
}

function help {
	echo
	echo "Usage: $0 [options] image{.iso, .img, .bin}"
	echo
	echo "Options:"
	echo "-k: Pass multiboot kernel image to QEMU."
	echo "-s: Write serial port output to file."
	echo "-d: Debug remotely with GDB."
	echo "-f: Define file for serial port output."
	
	echo
	echo "Use-alone options:"
	echo "-h: Print this help message."
	echo "-v: Print version."
	echo
}

function parse {
	for argv in "$@"
	do
		if [ $# -gt 2 ] && ([ $argv == "-h" ] || [ $argv == "-v" ])
		then
			echo
			echo "Error: -v and -h options must be used exclusively"
			echo
			exit 1
		fi
	done
}

if [ $# -lt 1 ]
then
	echo
	echo "Error: At least one argument is needed"
	help
elif [ $# -gt 4 ]
then
	echo
	echo "Error: Too much arguments"
	help	
else
	parse $@
	$(qemu-system-i386 $k $d $s $img)
fi
