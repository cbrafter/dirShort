#!/usr/bin/python3
# ##############################################################################
# dirShort.py
# A script that allows the working directory string length to be dynamically
# shortened 
#
# Author: Craig B. Rafter (https://github.com/cbrafter)
# Copyright: 2017, Craig Rafter, MIT License
# Date: 28/02/17
# Useage: Add following to ~/.bashrc and place this script in the home directory
# ensure you give the script any relevant permissions (chmod)
#   PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]$(python3 $HOME/dirShort.py "$(dirs)")\[\033[00m\]\$ '
# ##############################################################################

import sys
from os import popen

try:
    # system provides working directory
    path = sys.argv[1]
except:
    print("ERROR: Usage: $0 <path>")
    sys.exit(1)

# Separate folders
dirs = path.split("/");

# Width of terminal window in characters
termWidth = int(popen('stty size', 'r').read().split()[1])
cutoff = 0.4*termWidth # 40% window size rounded up to nearest int

# If within length, pass 
if len(path) <= cutoff:
    pass
# If more than 1 folder deep
elif len(dirs) > 1:
    # Reduce num letters in parent folder until 1 letter per parent to 
    # try fit the dir in the cutoff area
    for parentLen in [5, 3, 1]:
        path = '/'.join(x[:parentLen] for x in dirs[:-1]) + '/' + dirs[-1]
        if len(path) <= cutoff:
            break
# If there's a problem just return the directory
else:
    path = dirs[0]

print(path)
