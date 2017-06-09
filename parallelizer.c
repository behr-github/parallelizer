#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("usage: %s command\n", argv[0]);
        printf("  Most likely you either did not pass a command,\n"
               "  or did not enclose it in quotes so that it does\n"
               "  not get read as multiple arguments.\n");
        return 1;
    }

    int ierr, num_procs, my_id, run_err;

    ierr = MPI_Init(&argc, &argv);
    
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    run_err = system(argv[1]);
    printf("Process %d finished with exit code %d\n", my_id, run_err);

    //printf("Would execute command %s on process %d of %d\n", argv[1], my_id, num_procs);

    ierr = MPI_Finalize();

    return 0;
}
