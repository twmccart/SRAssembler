/*
 * MPIWrapper.cpp
 *
 *  Created on: Oct 16, 2011
 *     Authors: Hsien-chao Chou (first version); Thomas McCarthy and Volker Brendel (modifications)
 */

#include "MPIWrapper.h"
#include <string.h>
#include <iostream>
#ifdef MPIMODE
#include <mpi.h>
#endif

long long get_mpi_code_value(mpi_code code){
	// code.action can be 2 digits.
	// code.value1 can be 5 digits.
	// code.value2 can be 9 digits.
	// code.value3 can be 2 digits.
	return 10000000000000000 * code.action + 100000000000 * code.value1 + 100* code.value2 + code.value3;
}

mpi_code get_mpi_code(long long code_value){
	mpi_code code;
	code.action = code_value / 10000000000000000;
	code.value1 = code_value / 100000000000 % 100000;
	code.value2 = code_value / 100 % 1000000000;
	code.value3 = code_value % 100;
	return code;
}

void mpi_send( const char* msg, const int& to ) {
#ifdef MPIMODE
	int len = strlen( ( char* )msg );
	MPI::COMM_WORLD.Send( &len, 1,   MPI::INT,  to, ( int )1 );
	MPI::COMM_WORLD.Send(  msg, len, MPI::CHAR, to, ( int )1 );
#endif
}

void mpi_receive( char* msg, int& source ) {
#ifdef MPIMODE
	int len;
	MPI::Status status;

	MPI::COMM_WORLD.Recv( &len, 1, MPI::INT, MPI::ANY_SOURCE,MPI::ANY_TAG,  status );
	source = ( ( int )status.Get_source(  ) );
	MPI::COMM_WORLD.Recv(  msg, len, MPI::CHAR, source, MPI::ANY_TAG );
	msg[len] = '\0';
#endif
}

void mpi_send( const long long& code_value, const int& to ) {
#ifdef MPIMODE
	MPI::COMM_WORLD.Send( &code_value, 1,   MPI::LONG_LONG_INT,  to, ( int )1 );
#endif
}

void mpi_bcast(const long long& code_value) {
	int mpiSize = mpi_get_size();
	int rank = mpi_get_rank();
	for (int i=0;i<mpiSize;i++)
		if (rank != i)
			mpi_send(code_value, i);
}

void mpi_receive( long long& code_value, int& source ) {
#ifdef MPIMODE
	MPI::Status status;
	MPI::COMM_WORLD.Recv( &code_value, 1, MPI::LONG_LONG_INT, MPI::ANY_SOURCE,MPI::ANY_TAG,  status );
	source = ( ( int )status.Get_source(  ) );
#endif
}

void mpi_init(int argc, char * argv[] ) {
#ifdef MPIMODE
	MPI::Init(argc,argv);
#endif
}

int mpi_get_rank(){
#ifdef MPIMODE
	return MPI::COMM_WORLD.Get_rank();
#else
	return 0;
#endif
}

int mpi_get_size(){
#ifdef MPIMODE
	return MPI::COMM_WORLD.Get_size();
#else
	return 1;
#endif
}

void mpi_finalize(){
#ifdef MPIMODE
	MPI::Finalize();
#endif
}
