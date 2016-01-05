OBJS = main_client.o ../src/convey.o
CFLAGS = -Wall -g -lm
CXXFLAGS = -Wall -g -std=c++11 `pkg-config --cflags --libs opencv`
LDFLAGS = -pthread
CC = gcc
CXX = g++
r_client.out : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $@
main_client.o : main_client.cpp ../src/convey.h
convey.o : ../src/convey.cpp ../src/convey.h
clean :
	rm *.out *.o
cleanall :
	rm *.out *.o
	rm ../src/*.o
install :
	sudo cp *.out /usr/local/bin
