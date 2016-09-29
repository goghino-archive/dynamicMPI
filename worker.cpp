/* worker */ 

#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) 
{ 
    MPI_Init(&argc, &argv); 
    
    int size; 
    MPI_Comm parent_comm; 

    //Get inter-communicator to parent process
    MPI_Comm_get_parent(&parent_comm); 
    if (parent_comm == MPI_COMM_NULL)
    {
        cerr << "No parent!" << endl;
        exit(1);
    } 
    MPI_Comm_remote_size(parent_comm, &size); 
    if (size != 1)
    {
        cerr << "Something's wrong with the parent" << endl;
        exit(1);
    } 

    /*   
     * The manager is represented as the process with rank 0 in (the remote 
     * group of) parent_comm.  If the workers need to communicate among 
     * themselves, they can use MPI_COMM_WORLD. 
     */ 
    int rank, mpi_size;  

    MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    cout << "[worker]Hello from process " << rank << " from total of " << mpi_size << endl;
    char name[200];
    gethostname(name, 200);
    cout << "[worker]Rank #" << rank << " runing on node " << name << endl;
    

    //send something to manager using intercomm
    int info = rank*100;
    cout << "[worker]sending data..." << endl;
    MPI_Send(&info, 1, MPI_INT, 0, 0, parent_comm);

    //get something from manager
    cout << "[worker]waiting for data ..." << endl;
    MPI_Recv(&info, 1, MPI_INT, 0, 0, parent_comm, MPI_STATUS_IGNORE);
    cout << "[worker]Recieved info: " << info << endl; 

    //wait for the comm to finish and free the communicator
    MPI_Comm_disconnect(&parent_comm);
    cout << "[worker]Disconnected" << endl;
    MPI_Finalize(); 
    return 0; 
} 
