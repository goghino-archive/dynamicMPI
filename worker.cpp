/* worker */ 
 
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) 
{ 
   int size; 
   MPI_Comm parent; 
   MPI_Init(&argc, &argv); 
   MPI_Comm_get_parent(&parent); 
   if (parent == MPI_COMM_NULL)
    {
      cerr << "No parent!" << endl;
      exit(1);
    } 
   MPI_Comm_remote_size(parent, &size); 
   if (size != 1)
    {
      cerr << "Something's wrong with the parent" << endl;
      exit(1);
    } 
 
   /* 
    * Parallel code here.  
    * The manager is represented as the process with rank 0 in (the remote 
    * group of) MPI_COMM_PARENT.  If the workers need to communicate among 
    * themselves, they can use MPI_COMM_WORLD. 
    */ 
   int rank, mpi_size;  
   MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);

   cout << "Hello from process " << rank << " from total of " << mpi_size << endl;
 
   MPI_Finalize(); 
   return 0; 
} 