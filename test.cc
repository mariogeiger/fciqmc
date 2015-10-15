#include <map>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string serialize(const pair<int,int>& kv)
{
	ostringstream oss;
	oss << kv.first << ' ' << kv.second;
	return oss.str();
}

pair<int,int> unserialize(const string& str)
{
	istringstream iss(str);
	pair<int,int> kv;
	iss >> kv.first >> kv.second;
	return kv;
}

#include "mpi_map.hh"

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int mpi_size;
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	int mpi_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);


	mpi_map<int, int> ys(mpi_rank, mpi_size);

	map<int, int> xs;
	xs[mpi_rank] = 1;
	xs[10*mpi_rank] = 10;
	xs[100*mpi_rank] = 100;

	ys.mpi_sumup(xs);

	for (auto x : ys) {
		cout << mpi_rank << ':' << x.first << ' ' << x.second << endl;
	}

	MPI_Finalize();

	return 0;
}