OBJS = main.o detecting.o serial.o
CFLAGS = -Wall -g -lm
CXXFLAGS = -Wall -g -std=c++11 `pkg-config --cflags --libs opencv`
LDFLAGS = -pthread
CC = gcc
CXX = g++
r_dtmove_cv3.out : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $@
main.o : main.cpp detecting.h serial.h
detecting.o : detecting.cpp detecting.h
serial.o : serial.cpp serial.h
clean :
	rm *.out *.o
install :
	sudo cp *.out /usr/local/bin
