OBJS = main.o ../src/detecting.o ../src/serial.o ../src/convey.o
CFLAGS = -Wall -g -lm
CXXFLAGS = -Wall -g -std=c++11 `pkg-config --cflags --libs opencv`
LDFLAGS = -pthread
CC = gcc
CXX = g++
r_dtmove_cv3.out : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $@
main.o : main.cpp ../src/detecting.h ../src/serial.h ../src/convey.h
detecting.o : ../src/detecting.cpp ../src/detecting.h
serial.o : ../src/serial.cpp ../src/serial.h
convey.o : ../src/convey.cpp ../src/convey.h
clean :
	rm *.out *.o
cleanall :
	rm *.out *.o
	rm ../src/*.o
install :
	sudo cp *.out /usr/local/bin
