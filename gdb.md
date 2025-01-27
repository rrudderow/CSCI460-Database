list to get C++ source code in gdb
b 6 to break at line 6
    then run to actually break at that line
b otherfile.cpp:6 to break in another file
info regi to view registers - have to run first
bt to backtrace = what called what function called what function

if seg fault = go into gdb and run
then can bt

list=look through code
b 17 = break at line 17 
p d = print variable d
x /16bx p = show 16 bytes of memory starting at location p
x /16bx &d = "" starting at location of variable d