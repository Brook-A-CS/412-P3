CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = loadbalancer

SRCS = main.cpp LoadBalancer.cpp RequestGenerator.cpp WebServer.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean