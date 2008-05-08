##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

## main output
mtn-cms: mtn-cms.o http.o mime.o sqlite3.o
	g++ -g -o $@ mtn-cms.o http.o mime.o sqlite3.o -lpthread -ldl
	
## object files
mtn-cms.o: mtn-cms.cpp
	g++ -g -c -o $@ $<
http.o: http.cpp
	g++ -g -c -o $@ $<
mime.o: mime.cpp
	g++ -g -c -o $@ $<
sqlite3.o: sqlite/sqlite3.c
	gcc -g -c -o $@ $< 
	
## clean
clean:
	rm *.o mtn-cms