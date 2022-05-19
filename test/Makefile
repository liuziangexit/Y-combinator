CXXFLAGS = -O3 -std=c++14

all::main

main: main.cpp
					g++ $(CXXFLAGS) -c main.cpp -o main.o
					g++ main.o -o main.dll

clean:
				rm -rf *.o *.dll