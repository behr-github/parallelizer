#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <mpi.h>
using namespace std;

void replaceInt(string &str, const string &from, int to);
void replaceAll(string &str, const string &from, const string &to);

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "usage: " << argv[0] << " command \n";
        cout << "  Most likely you either did not pass a command,\n"
               "  or did not enclose it in quotes so that it does\n"
               "  not get read as multiple arguments.\n";
        return 1;
    }

    int ierr, num_procs, my_id, run_err;
    string cmd_str = string(argv[1]);
    
    ierr = MPI_Init(&argc, &argv);

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    replaceInt(cmd_str, "%RANK%", my_id);
    replaceInt(cmd_str, "%NP%", num_procs);
    
    run_err = system(cmd_str.c_str());

    ierr = MPI_Finalize();

    return 0;
}

void replaceInt(string &str, const string &from, int to){
    ostringstream convert;
    convert << to;
    replaceAll(str, from, convert.str());
    // These may not be necessary
    convert.str(string());
    convert.clear();
}

void replaceAll(string &str, const string &from, const string &to){
    if(from.empty()){
        return;
    }else if (to.empty()){
        return;
    }

    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos){
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
