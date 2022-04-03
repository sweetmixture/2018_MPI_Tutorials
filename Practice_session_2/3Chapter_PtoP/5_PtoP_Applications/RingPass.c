
// +1 (AFTER)	: (rank + 1)%comm_sz
// -1 (BEFORE)	: (rank + comm_sz - 1)%comm_sz


// RingPass Scheme ... code pattern

if( rank%2 == 0 )
{
	dest   = (rank + 1)%comm_sz;
	source = (rank + comm_sz - 1)%comm_sz;

	MPI_Send(msg, size, MPI_TYPE, /* dest */ dest, 0, comm);
	MPI_Recv(new_mgs, size, MPI_TYPE, /* src */ source, 0, comm, MPI_STATUS_IGNORE);
}
else // (rank%2 != 0 )
{
	dest   = (rank + 1 )%comm_sz;
	source = (rank + comm_sz - 1)%comm_sz;

	MPI_Recv(new_msg, size, MPI_TYPE, /* src */ source, 0, comm, MPI_STATUS_IGNORE);
	MPI_Send(msg, size, MPI_TYPE, /* dest */ dest, 0, comm);
}

/* Comment

possibly use - MPI_Sendrecv(void* send, int send_size, TYPE, dest, send_tag,
			    void* recv, int recv_size, TPYE, src , recv_tag,
		 	    comm, status_p);
// send, recv could be same

if send-recv buffer same

int MPI_Sendrecv_replace( void* buf, int buf_size, TYPE, dest, send_tag, src, recv_tag, comm, status_p )
