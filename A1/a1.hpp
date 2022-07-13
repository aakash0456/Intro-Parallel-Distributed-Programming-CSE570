/*  AKASH
 *  SHARMA
 *  as475
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream> 
#include <stdio.h>

using namespace std;

void isort(std::vector<short int>& Xi, MPI_Comm comm) {


	int rank = 0, size = 0;
	int m = Xi.size();
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	//Sorting subarray
	std::sort(std::begin(Xi), std::end(Xi));
	//cout << "Vector array after sorting " << '\n';
	for (int i = 0; i < m; i++)
	{
		//cout << Xi[i] << '\t';
	}

	//cout << '\n';
	
	//int* buf = (int*)malloc(sizeof(int) * (size+1));
	

	int p = size;
	int x = -(p - 1);
	int z = 0;
	vector<int> buf(2*(p - 1)+1, 0);
	

	
	
	//Calulating Frequecy
	
	for (int j = x; j <= p - 1; j++)
	{
		
		//cout << j<<'\t';
		for (int i = 0; i < m; i++)
		{
			

			if (Xi[i] == j)
			{
				buf[z]++;
			}

		}z++;
		
	}

	for (int i = 0; i < 2 * (p - 1) + 1; i++)
	{
		//cout << buf[i] << '\t';
	}
	//cout << '\n';
	vector<int>sum_count(2 * (p - 1) + 1,  0);
	
	int r_size = 2 * (p - 1) + 1;
	
	MPI_Reduce(&buf[0], &sum_count[0], r_size, MPI_INT, MPI_SUM, 0 , comm);

	if (rank == 0)
	{
		for (int i = 0; i < 2 * (p - 1) + 1; i++) {
			//cout << sum_count[i]<<'\t';
		}
		
	}
	//cout << '\n';

	//Broadcasting Frequecy of elements
	MPI_Bcast(&sum_count[0], 2 * (p - 1) + 1, MPI_INT, 0, comm);
	  

	/*if (rank == 0) {
	cout << "Frequecy array ";
		for (int i = 0; i < 2 * (p - 1) + 1; i++) {
		 cout << sum_count[i] << '\t';
		}
	}
	cout << '\n';*/

	
	int l = 0;
	int y = 0;
	int j,k;

	vector<short int> sort;
	for (int i = 0; i < size - 1; i++)
	{
		if (rank == i) {


			int c1 = sum_count[i];
			int t = sum_count[i];
			for (j = 0; j < t;j++)
			{

				if (c1 == 0)
					break;
				//cout << i - (p - 1);
				sort.push_back(i - (p - 1));
				c1--;

			}


		}
		Xi = sort;
	}

	if (rank = size - 1)
	{
		for (int i = size - 1; i < 2 * size - 1; i++)
		{
			int c1 = sum_count[i];
			int t = sum_count[i];
			for (j = 0; j < t;j++)
			{

				if (c1 == 0)
					break;
				//cout << i - (p - 1);
				sort.push_back(i - (p - 1));
				//cout << "s: " << sort[i] << "\t";
				c1--;

			}
		}
		Xi = sort;


	}
	/*cout << "Sorted Array start  ";
	for (int i = 0; i < Xi.size(); i++)
	{
		cout << Xi[i] << '\t';
	}
	cout << endl;
	cout << "Sorted Array end  ";*/
	 
		

	

} // isort

#endif // A1_HPP
