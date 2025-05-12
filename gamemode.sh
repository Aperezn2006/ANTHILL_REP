#!/bin/bash
# chmod +x gamemode.sh
# ./gamemode.sh

echo " ----------------------------------"
echo "|   Welcome to the Anthill game    |"
echo " ----------------------------------"
echo "Which mode do you want to play?"
echo "  1. Standard graphics"
echo "  2. Fancy graphics    [!] You must have SLD2, tft.h and image.h installed"
echo "  3. Exit"
echo " "
read mode
echo " "

if [ "$mode" -eq 1 ]; then
  make clean
  make run
elif [ "$mode" -eq 2 ]; then
  make clean
  make run_sdl
elif [ "$mode" -eq 3 ]; then
  echo "Goodbye"
else 
  echo "Invalid mode"
fi
