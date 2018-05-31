#include <stdio.h>
#include <mpi.h>
#include <limits.h>


int main() {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//    printf("World size is: %d\n", world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//    printf("My rank is: %d\n", world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

//    printf("Hello world from processor %s, rank %d"
//           " out of %d processors\n",
//            processor_name, world_rank, world_size);


    if(world_size < 2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    short int number = 0;
    int sender = world_rank - 1;
    int receiver = world_rank + 1;

    if(world_rank == 0) {
        MPI_Send(&number, 1, MPI_SHORT, receiver, 0, MPI_COMM_WORLD);
        sender = world_size -1;
    }
    if(world_rank == world_size -1) {
        receiver = 0;
    }

    while(number > -1) {
        MPI_Recv(&number, 1, MPI_SHORT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printf("Process %d received number %d from process %d\n", world_rank, number, sender);
        if(number < 0) {
            printf("Process %d received negative value of number %d\n", world_rank, number);
            MPI_Send(&number, 1, MPI_SHORT, receiver, 0, MPI_COMM_WORLD);
            printf("Terminating. Process %d sent number %d to process %d\n", world_rank, number, receiver);
            break;
        } else {
            number++;
            MPI_Send(&number, 1, MPI_SHORT, receiver, 0, MPI_COMM_WORLD);
            //printf("Process %d sent number %d to process %d\n", world_rank, number, receiver);
        }
    }
    printf("Terminated loop process %d with number %d\n", world_rank, number);

    MPI_Finalize();
}