CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -std=c++17
SRC=src/main.cpp
BIN=dev-gen

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)
