##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

## main output
mtn-cms: mtn-cms.o http.o sqlite3.o
	g++ -o $@ mtn-cms.o http.o sqlite3.o -lpthread -ldl
	
## object files
mtn-cms.o: mtn-cms.c
	g++ -c -o $@ $<
http.o: http.c
	g++ -c -o $@ $<
sqlite3.o: sqlite/sqlite3.c
	gcc -c -o $@ $<
	
## clean
clean:
	rm *.o mtn-cms