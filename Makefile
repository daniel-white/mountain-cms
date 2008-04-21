##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

mtn-cms: sqlite3.o
	gcc -o $@ $<

sqlite3.o: sqlite/sqlite3.c
	g++ -c -o $@ $<