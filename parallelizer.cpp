#include <iostream>
using namespace std;

void replaceAll(string &str, const string &from, const string &to);

int main(int argc, char* argv[]){
    if(argc != 4){
        cout << "usage: " << argv[0] << " string from to\n";
        cout << "  Most likely you either did not pass a command,\n"
               "  or did not enclose it in quotes so that it does\n"
               "  not get read as multiple arguments.\n";
        return 1;
    }

    string orig_str, old_substr, new_substr;
    
    orig_str = string(argv[1]);
    old_substr = string(argv[2]);
    new_substr = string(argv[3]);

    cout << "Original string: " << orig_str << "\n";
    replaceAll(orig_str, old_substr, new_substr);
    cout << "New string: " << orig_str << "\n";

//    int ierr, num_procs, my_id, run_err;

//    ierr = MPI_Init(&argc, &argv);
    
//    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
//    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

//    run_err = system(argv[1]);
//    printf("Process %d finished with exit code %d\n", my_id, run_err);

    //printf("Would execute command %s on process %d of %d\n", argv[1], my_id, num_procs);

//    ierr = MPI_Finalize();

    return 0;
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
