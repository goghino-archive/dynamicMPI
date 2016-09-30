Running the MPI spawn in multinode setting:

1. Set up the environment in the interactive session

       kardos@icsnode05 (master):~/misc/dynamicMPI$ module list
       Currently Loaded Modulefiles:
         1) use.own         2) gcc/6.1.0       3) openmpi/2.0.1

2. Configure the MCA components to use the "tcp", "sm" and "self" BTLs for the transport
of MPI messages, with TCP restricting only the eth0 interface to
communicate and using ob1 as p2p management layer. There are multiple ways how to do it,
either see the mpirun parameters in point 3) or create the configure file as shown below
(https://www.open-mpi.org/faq/?category=tuning#setting-mca-params)

       kardos@icsmaster01 (master):~/misc/dynamicMPI$ cat $HOME/.openmpi/mca-params.conf
        btl_tcp_if_include = eth0
        pml = ob1
        btl = tcp,sm,self

3. Run the code

        mpirun --mca btl_tcp_if_include eth0 --mca pml ob1 --mca btl tcp,sm,self -np 1 --hostfile my_hosts ./manager 2
        or
        mpirun -tune my_mca_setting --hostfile my_hosts -np 1 ./manager 2 #uses my_mca_setting config file
        or
        mpirun -np 1 -hostfile my_hosts ./manager 2 #uses the config file from point 2)
