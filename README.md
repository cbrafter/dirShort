# dirShort
A dynamic working directory string directory shortener for BASH terminals.

## Description
A Python and C file are provided that enable you to customise your terminal so that the working directory string will be shortened such that the string will not occupy more than ~40% of the terminal width. The C version is faster than the python version.

## Useage
### Python - dirShort.py
1. Place the script in the home directory
2. Give the script the relevant permissions to execute on your system. `chmod 755 dirShort.py` for example.
3. Add the following to your ~/.bashrc file (change the colors if you wish):
  `PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]$(python3 $HOME/dirShort.py "$(dirs)")\[\033[00m\]\$ '`

### C - dirShort.c
1. Compile the file using `gcc -O3 -Wall -std=c99 dirShort.c -o dirShort`
2. Place the executable in the home directory. (`dirShort` is you used the above command)
2. Give the executable the relevant permissions to execute on your system. `chmod 775 dirShort` for example.
3. Add the following to your ~/.bashrc file (change the colors if you wish):
  `PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]$($HOME/dirShort "$(dirs)")\[\033[00m\]\$ '`

## Notes
- You may wish to tweek the limits in the file to suit your own terminal needs
- The programs are currently buggy for terminal widths less than about 10 characters 
