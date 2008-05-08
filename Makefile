##
## Mountain CMS
## Daniel A. White
##
## Makefile
## The make file for Mountain CMS
##

## main output
mtn-cms: mtn-cms.o http.o mime.o pb.o sqlite3.o CppSQLite3.o
	g++ -DSQLITE_THREADSAFE=1 -g -o $@ mtn-cms.o http.o mime.o pb.o sqlite3.o CppSQLite3.o -lpthread -ldl
	
## object files
mtn-cms.o: mtn-cms.cpp mtn-cms.h
	g++ -DSQLITE_THREADSAFE=1 -g -c -o $@ $<
http.o: http.cpp http.h
	g++ -DSQLITE_THREADSAFE=1 -g -c -o $@ $<
mime.o: mime.cpp mime.h
	g++ -DSQLITE_THREADSAFE=1 -g -c -o $@ $<
pb.o: pb.cpp pb.h
	g++ -DSQLITE_THREADSAFE=1 -g -c -o $@ $<
sqlite3.o: sqlite/sqlite3.c
	gcc -DSQLITE_THREADSAFE=1 -g -c -o $@ $<
CppSQLite3.o: sqlite/CppSQLite3.cpp sqlite/CppSQLite3.h
	g++ -DSQLITE_THREADSAFE=1 -g -c -o $@ $< 
	
## clean
clean:
	rm *.o mtn-cms