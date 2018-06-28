all: parallelizer.exe file_sorter.exe

parallelizer.exe: parallelizer.cpp
	mpicxx -o parallelizer.exe parallelizer.cpp

file_sorter.exe: file_sorter.cpp
	$(CXX) -std=c++11 -o file_sorter.exe file_sorter.cpp

.PHONY: clean
clean:
	rm -rf *.exe
