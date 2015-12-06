TARGET = cotc-cli

#LIBS = -lm -L../../delivery/cloudbuilder/Linux/Debug
#CC = gcc
LIBS = -lm -L../../delivery/cloudbuilder/MacOSX/Debug
CC = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++


CFLAGS = -g -Wall -I../../delivery/cloudbuilder/headers  -std=c++11 -stdlib=libstdc++ -x c++ 

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)


%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -arch x86_64 -std=c++11 -stdlib=libstdc++ -lpthread -lCloudBuilder64Console -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

