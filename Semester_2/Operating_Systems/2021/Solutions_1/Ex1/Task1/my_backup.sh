#!/bin/bash

#if there is less than 1 argument it will exit
if [ $# -lt l ]
then echo Argument is missing >&2
    exit
fi
#if path $1 does not exist it will exit
if ! [ -d "$l" ]
then echo wrong Path >&2
    exit
fi

#saves directory name for backup
CORDIRNAME=$(basename $PWD)
#saves path of backup directory
TARGETDIRECTORY="$1$CURDIRNAME/"

#looks if directory exists already in given backupppath
if ! [ -d "$TARGETDIRECTORY" ]
then echo create dierctory
    mkdir $TARGETDIRECTORY          #if not it creats a new one
else echo directory exists, only copy needed
fi



#copies file, depending on if there already is one or not
for FILE in $PWD/*; do         #goes through every file in the Directory we want to copy, we could add .sh then only those file would be copied.
    FILENAME=$(basename $FILE) #takes only each Filename
    if [ -f "$TARGETDIRECTORY$FILENAME" ]
    then TIMESTAMP=$(date +%s)
        echo copy additional: $FILENAME$TIMESTAMP
        cp -a $FILENAME $TARGETDIRECTORY/${FILENAME%%.*}-$TIMESTAMP.sh
        #.a lets us rename the file + %%.* cuts of all characters after the "."
    else echo "copy $FILENAME first time"
        cp $FILENAME $TARGETDIRECTORY
    fi
done
