PROGRAM = main
SRCS = main.cpp Snake.cpp SnakeMap.cpp GameManager.cpp

PROGRAM_DEPS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CXX = g++
INC = -lncurses
CXXFLAGS = -g $(INC) -std=c++11

.SUFFIXES : .cc .o
.PHONY : all clean

all : $(PROGRAM)

$(PROGRAM) : $(PROGRAM_DEPS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.d : %.cpp
	$(CXX) -M -MP -MT "$(@:.d=.o) $@" -MF $@ $<

clean :
	rm -rf $(PROGRAM_DEPS) core $(DEPS)

-include $(DEPS)
