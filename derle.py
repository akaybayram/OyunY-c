import os
import sys

path = sys.argv[0]
path = path.replace('\\derle.py', '')
os.chdir(path)

# os.system("scons -c")
os.system("scons")
os.system(".\OyunY.exe")
