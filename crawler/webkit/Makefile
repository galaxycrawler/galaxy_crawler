all: moc test

CC=g++ -Wall -g -ggdb
INCLUDE= -I/usr/include/qt4

WEBKIT_CORE_FILES=  webkit_core.cc webkit_core_network_access_manager.cc webkit_core_web_page.cc
WEBKIT_CORE_HEADER= webkit_core.h webkit_core_network_access_manager.h webkit_core_web_page.h

WEBKIT_CORE_OBJS= $(WEBKIT_CORE_FILES:.cc=.o)

LIBS=-lQtWebKit -lQtCore -lQtGui

moc: webkit_core.h
	/usr/bin/moc-qt4 -I/usr/include/qt4 webkit_core.h -o moc_webkit_core.cc
	$(CC) $(INCLUDE) -c moc_webkit_core.cc -o moc_webkit_core.o

.SUFFIXES: .o .cc
.cc.o:
	$(CC) $(INCLUDE) -c $< -o $@

test: test.cc $(WEBKIT_CORE_OBJS) $(WEBKIT_CORE_HEADER) 
	$(CC) $(INCLUDE) $(LIBS) $< $(WEBKIT_CORE_OBJS) moc_webkit_core.o -o test



.PHONY: clean
clean:
	rm -rf *.o
	rm -rf moc_webkit_core.cc
	rm -rf test
	rm -rf caches

