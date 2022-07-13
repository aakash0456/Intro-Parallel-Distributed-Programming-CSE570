/*  AKASH
 *  SHARMA
 *  as475
 */

#ifndef A0_HPP
#define A0_HPP

#include <iostream>
#include  <omp.h>
#include <vector>


void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
	
std::vector<float> A1=A;
int x=0;
int arr[(m-2)*(n-2)] ={0};
#pragma omp parallel default(shared)
{

int mul[27]={-(m+1),-m,-(m-1),-(m+1),-m,-(m-1),-(m+1),-m,-(m-1),-1,0,1,-1,0,1,-1,0,1,(m-1),m,(m+1),(m-1),m,(m+1),(m-1),m,(m+1)};
int kmul[27]={0,3,6,1,4,7,2,5,8,0,3,6,1,4,7,2,5,8,0,3,6,1,4,7,2,5,8};



#pragma omp for schedule(auto)


for(int rowA=m; rowA<=(n*m-(m+1)); rowA++)
 {



     if(rowA%m!=0 && (rowA+1)%m!=0)
      {int k=0;

        for(int rowK=0; rowK<27; rowK++)
        {
            arr[x]=arr[x]+A[rowA+mul[k]]*K[kmul[rowK]];

             k++;
             A1[rowA]=arr[x];
        }

        x++;
    }
 }
}

A=A1;


} // filter_2d

#endif // A0_HPP
