CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -lgtest -lgtest_main -pthread

SRC = main.cpp  BMPHeader.cpp BMPImg.cpp 
OBJ = $(SRC:.cpp=.o)
TARGET = lab

TEST_SRC = BMPHeader.cpp BMPImg.cpp Test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

format:
	astyle -A1 -s4 *.cpp *.h

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET) test.bmp

.PHONY: all run clean