#!/bin/bash
for FN in "$@" #$@ expants to all input arguements
do
    chmod 0750 "$FN" #sets rwx for user, r and x for group, and none for other
done

#if we execute, the script with the input arguements, and if the arguements are files,
#it changes the rights for the use of the user, for the group and for other users,
#if there is no input arguement then there is also no output, because there is no file
# to give rights to. And if we dont use a word that is a directory,
#it will give us a error like "there exists no such directory"