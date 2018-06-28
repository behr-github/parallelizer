# Parallelizer toolkit

This repository contains a few C++ utilities that are helpful for parallelizing simple tasks using
the Message Passing Interface (MPI) method.

## Building
To build, just type `make` in this directory. This will create the executables. This has been tested with Intel compiler ICPC version
"17.0.1 20161005". You can change which compiler is used by setting the `CXX` and `MPICXX` environmental variables for serial and
parallel compilers, respectively.

## parallelizer.exe
A C++ program that can be used to launch multiple instances of any shell command

### Use
Use this with the following syntax (assuming `parallelizer.exe` is in the current directory, otherwise give the full path to it):
```
mpirun -np N ./parallelizer.exe command
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


## file\_sorter.exe

A C++ program that can help run operations on batches of files in parallel. A common use for parallelization is to perform the same
operation on a large number of files, but it can be difficult to reliably sort batches of files into groups to pass to each task
using shell scripts. 

### Use

This program is called as follows:

```
./file_sorter.exe N G <files>
```

where `N` is the current group number (zero based), `G` is the number of groups, and `<files>` is a space-separated list of files. 
For example, if there were 20 CSV files in the current directory, then

```
./file_sorter.exe 0 4 *.csv
```

would print a space-separated list of the first five CSV files, `./file_sorter.exe 1 4 *.csv` would print the next five, and so on. This is meant for easy use with `parallelizer.exe` so that given the
`%RANK%` and `%NP%` values, it will figure out which files this task should operate on.

### Caveats

1. This has not been tested with filenames that include spaces.

2. This assumes that it is given the same list of files in the same order across all tasks. It does no sorting internally, so
if the list varies for each call to this function, it may repeat or skip some files.

3. This does no intelligent load sharing, it will just split up the lists of files as equally as practical. If every file in the
first group is done quickly and every file in the last group takes a long time, it cannot do anything to balance that.

