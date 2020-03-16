CXX = g++
CXXFLAGS = -g

SRC = SRT_method.cpp
DEP = SRT_method.h
TARGET = srt
OBJS = main.o SRT_method.o

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

main.o: SRT_method.h main.cpp
SRT_method.o : SRT_method.h SRT_method.cpp

clean:
	rm -rf *.o $(TARGET)
