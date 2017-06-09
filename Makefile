parcpp: parallelizer.cpp
	mpicxx -o parallelizer.exe parallelizer.cpp

.PHONY: clean
clean:
	rm -rf *.exe
