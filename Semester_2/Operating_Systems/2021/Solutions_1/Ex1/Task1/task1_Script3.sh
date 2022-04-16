#!/bin/bash
#makedir "$1" 2> /mnt/c/Users/olive/Documents/OS/Ex1/error.sh
makedir "$1" 2> /dev/null

#this program should make a new directory and if there is an error it should redirect it to the device
# file in /dev/null (simply discards anything)

#the error redirect works (if u really simply want to discard the error),
#but in this case u wont see the error, that makedir does not exist,
#it has to be changed to mkdir so it should work as intended(i think).

#if we change it to mkdir it creats a directory

#if we use input parameters it will creat a new directory with the input arguement as name 
#if already such a directory exists it will redirect the error, or any other error

#another error is e.g. if we do not use parameters, in this case it cant make a directory with "" as name, 
# therefore it will redirct an error to /dev/null