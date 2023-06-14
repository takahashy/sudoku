CXX = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3
EXEC     = sudoku

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): sudoku_solver.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	rm -f *core* *.o $(EXEC)