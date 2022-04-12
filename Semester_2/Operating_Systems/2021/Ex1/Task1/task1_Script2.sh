#!/bin/bash
function usage { #gives an error if shift does not work
    echo "Usage: $0 atleast 3 input arguments needed"
    exit 1
}

ARG1="$1"; shift || usage #ARG1="$1" is executed and then shift, if shift is not executed successfully usage will be execute
ARG2="$1"; shift || usage
ARG3="$1"; shift || usage

grep -n "$ARG3" "$ARG1" > "$ARG2"


#manpage grep -n = -n, -- linenumber
#               Prefix each line of output with the l-based line number within its input file.

#EXAMPLE= ./task1_Script2 try1.sh try2.sh try3.sh
#                 $0        $1      §2      $3
#ARG1 = try1.sh
#ARG2 = try2.sh
#ARG3 = try3.sh

#the program assighns each ARG a input argument ARG1 get for eg. $1(try1.sh), it shifts then all input arguments one to the left
#just one because there is no additional number. The same thing happens with ARG2 and ARG3
#the grep command could be changed to grep -n try3.sh try1.sh > try2.sh
# so it searches try3.sh in try1.sh if there is one this output will be transfered to try2.sh

#as mentioned above. -n just adds the row-number of the orginal document to the output

#if there are not enough inout arguments it will call "usage", in this context it is almost like a error message if shift does not work.