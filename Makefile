##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

mtn-cms: sqlite3.o
	g++ -o $@ $< -lpthread

sqlite3.o: sqlite/sqlite3.c
	gcc -c -o $@ $<