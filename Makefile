CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lraylib -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

SRC = main.cpp grid.cpp tetrominoes.cpp game.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = tetris

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)