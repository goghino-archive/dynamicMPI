/* 
  Dynamic Process Management in MPI 

  MPI program (manager) creates new MPI processes by launching a binary and communicates with them.
*/ 
#include <mpi.h> 

using namespace std;

int main(int argc, char *argv[]) 
{ 
   int world_size, worker_size, *worker_sizep, flag; 
   MPI_Comm everyone;           /* intercommunicator to workers */ 
   const char* worker_program = "worker";
   //const char* worker_program = argv[0];
   //char worker_args[] = ["100", "10"];
 
   MPI_Init(&argc, &argv); 
   MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
 
   if (world_size != 1)
   {
       cerr << "Please run with a single process!" << endl;
       exit(1);
   } 
 
   if (argc != 2)
    {
      cerr << "Usage: $./manager NPROC" << endl; 
      exit(1);
    }
   worker_size = atoi(argv[1]);
   MPI_Comm_get_attr(MPI_COMM_WORLD, worker_size,  
                &worker_sizep, &flag);  
   
   if (worker_size == 1)
    {
      cerr << "No room to start workers" << endl; 
    }

    int version, subversion;
    MPI_Get_version(&version,&subversion);
    cout << "I’m running MPI " << version << "." << subversion << endl;
 
   /*  
    * Now spawn the workers. Note that there is a run-time determination 
    * of what type of worker to spawn, and presumably this calculation must 
    * be done at run time and cannot be calculated before starting 
    * the program. If everything is known when the application is  
    * first started, it is generally better to start them all at once 
    * in a single MPI_COMM_WORLD.  
    */ 
 
   MPI_Comm_spawn(worker_program, MPI_ARGV_NULL, worker_size,  
             MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,  
             MPI_ERRCODES_IGNORE); 
   /* 
    * Parallel code here. The communicator "everyone" can be used 
    * to communicate with the spawned processes, which have ranks 0,.. 
    * MPI_worker_size-1 in the remote group of the intercommunicator 
    * "everyone". 
    */ 
   int rank, size, size_all;
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_remote_size(everyone,&size_all);
   cout << "[MPI_COMM_WORLD]Hello from manager. I am rank " << rank << " from total of " << size << endl;
   cout << "Successfully spawned " << size_all << " processes" << endl;

   // MPI_Comm_size(everyone,&size);
   // MPI_Comm_rank(everyone,&rank);

   // cout << "[MPI_COMM_everyone]Hello from manager. I am rank " << rank << " from total of " << size << endl;


   /*
    * Sends some information to newly spawned processes in inter-communicator everyone
    * http://www.netlib.org/utk/people/JackDongarra/WEB-PAGES/SPRING-2012/Lect05-dynamicprocesses.pdf
    * http://ppomorsk.sharcnet.ca/Lecture_6_a_process_creation.pdf
    */
   int info = 555;
   for (int i=0; i<5; i++)
   {
      MPI_Send(&info, 1, MPI_INT, i, 0, everyone);
   }

   MPI_Finalize(); 
   return 0; 
}
