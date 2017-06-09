# parallelizer
A C++ program that can be used to launch multiple instances of any shell command

## Building
To build, just type `make` in this directory. This will create `parallelizer.exe`. On the UCB savio cluster, it has been tested with the `intel/2013_sp1.4.211` and `openmpi/1.6.5-intel` modules loaded. Other versions should work.

## Use
Use this with the following syntax:
```
mpirun -np N parallelizer.exe command
```
This will launch it with N threads and will execute `command` on each thread. `command` must be a single string, so be sure to enclose it in quotes
if it has spaces in it, e.g.:
```
mpirun -np 4 parallelizer.exe "python hello.py"
```
You can add two special words to the command, `%RANK%` and `%NP%`. `%RANK%` will be replaced with the process rank, i.e. which number
process it is. For an MPI task launched with N processes, rank will be a number between 0 and N-1. %NP% will be replaced with the total
number of processes. For example:
```
mpirun -np 5 parallelizer.exe "python pytest.py %RANK% %NP%"
```
would execute the following commands, one per task:
```
python pytest.py 0 5
python pytest.py 1 5
python pytest.py 2 5
python pytest.py 3 5
python pytest.py 4 5
```
(though not necessarily in that order). You can try this out with the provided `pytest.py` script. The above command would print the 
following five lines, again, not necessarily in this order:
```
I am running on processor 0 of 5
I am running on processor 1 of 5
I am running on processor 2 of 5
I am running on processor 3 of 5
I am running on processor 4 of 5
```
Therefore, if you have a script that you want to do different things on different processors, it will need to take a number as a command
line argument and set its behavior based on the value of that number.
