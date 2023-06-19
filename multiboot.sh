#!/bin/bash

file=$1

exec_command=$(grub-file --is-x86-multiboot "$file")
code=$?

# Verifica el código de salida y muestra el mensaje correspondiente
if [ $code -eq 0 ]; then
  echo "La salida del comando fue 0. ¡El fichero binario es compatible con Multiboot!"
else
  echo "Error: No se reconoce ninguna cabecera de Multiboot en el fichero"
fi
