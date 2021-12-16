#!/bin/sh

PLIST=include/problems.hpp

CURRENT_NUMBER="$(tail -n1 $PLIST | sed 's/void p\(.*\)();/\1/')"
NEW_NUMBER="$(expr $CURRENT_NUMBER + 1)"
NEW_FILE=src/p${NEW_NUMBER}.cpp

echo "void p${NEW_NUMBER}();" >> $PLIST
sed -i "s/$CURRENT_NUMBER/$NEW_NUMBER/" src/main.cpp
cp src/stub.cpp $NEW_FILE
echo -e "\nvoid p${NEW_NUMBER}() {\n\n}" >> $NEW_FILE
cmake .
