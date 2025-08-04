CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp Medicine.cpp Inventory.cpp EmailNotifier.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = MedicalManagementSystem

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
