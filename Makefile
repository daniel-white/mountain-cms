##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

mtn-cms: mtn-cms.o sqlite3.o
	g++ -o $@ $< -lpthread
	
mtn-cms.o: mtn-cms.cpp
	g++ -c -o $@ $<

sqlite3.o: sqlite/sqlite3.c
	gcc -c -o $@ $<