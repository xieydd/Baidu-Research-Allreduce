#include "mpi.h"
#include <cstdlib>
#include <iostream>

using namespace std;
/**
* function: return a random array
* @Prama proc generate random with this procs
* @Param num_elements array size
* @Return (double *) a random doubll array with size of num_elements and all in range of 0 and 1
*/
double *create_rand_nums(int num_elements, int proc) {
    double *rand_nums = (double *)malloc(sizeof(double) * num_elements);
    srand(proc)
    for (i = 0; i< num_elements; i++) {
        // Get random double num in range 0 and 1
        rand_nums[i] = (rand() /(double)RAND_MAX );
    }
    return rand_nums;
}

unsigned int log2(unsign int x) {
    unsigned int ans = 0;
    while(x>>=1) ans++;
    return ans;
}

/**
* function: Wrapper MPI function all_reduce, and sample the params
* @Param sendbuf the send buffer, this is a double array (input)
* @Param recvbuf same like the sendbuf (output)
* @Param count size of the array
*/
void allreduce(double *sendbuf,double *recvbuf, int count ) {
    MPI_Allreduce(sendbuf, recvbuf, count, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
}

/**
* function: Wrapper MPI function all_reduce, and 
* @Param sendbuf the send buffer, this is a double array (input)
* @Param recvbuf same like the sendbuf (output)
* @Param count size of the array
*/
void allreduceRSAG(double *sentbuf, double *recvbuf, int count) {
    int thisproc, nproc;

    MPI_Comm_rank(MPI_COMMON_WORLD, &thisproc);
    MPI_Comm_size(MPI_COMMON_WORLD, &nproc);

    int steps = log2(nproc);
    int counter = 0;

    // reduce-scatter op
    for (int step = 0; step < steps; step++) {
        int offset = (thisproc % (1<<(step+1))) < (1 << step)? 1 << step : -(1 << step);
        int sendTo = thisproc + offset;

        double sendToArray[count/2];

        if (offset > 0) {
            // send upper half
            int j = 0;
            for (int i = count/2; i <count; i++) {
                sendToArray[j++] = sendbuf[i];
            }
        }else {
            //send under half
            for (int i = 0; i < count/2; i++) {
                sendToArray[i] = sendbuf[i];
            }
        }

        MPI_Send(sendToArray, count/2, MPI_DOUBLE, sendTo, 0, MPI_COMMON_WORLD);
        MPI_Recv(recvbuf, count/2, MPI_DOUBLE, sendTo, 0, MPI_COMMON_WORLD, MPI_STATUS_IGNORE)


        if (offset > 0) {
            //receive the upper half
            for (int i = 0; i < count/2 ;i++) {
                sendbuf[i] += recvbuf[i]; 
            }
        }else {
            // receive uppper half
            int j = 0;
            int k = 0;
            for (int i = count/2; i< count;i++) {
                sendbuf[j++] = sendbuf[i] + recvbuf[k++];
            }
        }
        counter++;
        count = count/2;
    }

    // all-together op
    for (int step = steps -1; step > 0; step--) {
        int operationStep = step;
        int offset = (thisproc % (1<<(step+1))) < (1 << step)? 1 << step : -(1 << step);
        int sendTo = offset + thisproc;
        double sendToArray[count]

        for (int i = 0; i < count; i++) {
            sendToArray[i] = sendbuf[i];
        }

        MPI_Send(sendToArray, count, MPI_DOUBLE, sendTo, 0, MPI_COMM_WORLD);
        MPI_Recv(recvbuf, count, MPI_DOUBLE, sendTo, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        if (offset > 0) {
            //receive upper half
            int j = 0;
            for (int i = count; i < count*2; i++) {
                sendbuf[i] = 
            }
        }
    }
}



int main(int argc, char* argv[]) {

    int thisproc,numprocs;
    //Params is from main func (format)
    MPI_Init(&argc, &argv); 

    // Get the current procs and all procs
    MPI_Comm_rank(MPI_COMMON_WORLD,&thisproc);
    MPI_Comm_size(MPI_COMMON_WORLD,&numprocs);

    double *rand_nums = NULL
    rand_nums = create_rand_nums(8, thisproc);

    //Test mpi all_reduce op and 
    double *recvbuf = (double *)malloc(sizeof(double) * num_elements);
    double *recvbuftest = (double *)malloc(sizeof(double) * num_elements);

    allreduce(rand_nums, recvbuf, 8)
    allreduceRSAR(rand_nums, recvbuftest, 8)
}

