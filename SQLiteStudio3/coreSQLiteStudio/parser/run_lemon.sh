#!/bin/sh

#lemon -l -q -s sqlite3_parse.y
lemon -l -q sqlite3_parse.y
mv sqlite3_parse.c sqlite3_parse.cpp

lemon -l -q sqlite2_parse.y
mv sqlite2_parse.c sqlite2_parse.cpp
