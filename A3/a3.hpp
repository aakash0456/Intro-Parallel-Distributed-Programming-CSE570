/* AKASH
 * SHARMA
 * as475
 */
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <algorithm>
#define ar_size 1664
#ifndef A3_HPP
#define A3_HPP

__global__ void gausian_kernal(float *input_data , float *output_data, float size, float h){
 //   extern __shared__ float arr[];
        int tid = threadIdx.x;
    int gid = tid + blockIdx.x*blockDim.x;

   __shared__ float arr[ar_size];

    float sum = 0;

     if (gid < size){
    for (int i = 0; i < gridDim.x; i++) {
        arr[tid] = input_data[i*blockDim.x + tid];
        __syncthreads();

        for (int j = 0; j < blockDim.x; j++) {
            int size_null = j+ i*blockDim.x;
           if(size_null<size){

            sum = sum + (1/(size*h*sqrt(2*3.14159265359)))*exp(-((input_data[gid] - arr[j])/h)*((input_data[gid] - arr[j])/h));

           }
        }

	 }}
    output_data[gid] = sum;
}


void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
        float *input_data, *output_data;

   int total_byte_size = n*sizeof(float);
        /*int warp_size = 32;
   int n_blockspergrid = (n + 1024 - 1)/1024;  //since max no of threads per block is 1024
  dim3 block_size(warp_size);
  dim3 grid_size(n_blockspergrid);*/

 int warp_size = 128;
  // int n_blockspergrid = (n + 1024 - 1)/1024;  //since max no of threads per block is 1024
  dim3 block_size(warp_size);
  dim3 grid_size(n/block_size.x +1);
 // cout<<x.size();
  //cout<<y.size();
   for (int i=0; i<x.size(); i++)
   {
      //cout<<x[i]<<"\t";
   }
   //cout<<"\n";
     for (int i=0; i<y.size(); i++)
   {
     // cout<<y[i]<<"\t";
   }


   cudaMalloc((float **)&input_data, total_byte_size);
   cudaMalloc((float **)&output_data, total_byte_size);

   cudaMemcpy(input_data, x.data(), total_byte_size, cudaMemcpyHostToDevice);
 //  gausian_kernal<<<grid_size,block_size,warp_size*sizeof(float)>>>(input_data, output_data,n,h);
 gausian_kernal<<<grid_size,block_size>>>(input_data, output_data,n,h);
   cudaMemcpy(y.data(), output_data, total_byte_size, cudaMemcpyDeviceToHost);
 //  float sum=0;
  for (int i=0; i<y.size(); i++)
   {
//   std::cout<<y[i]<<"\t";
    //sum = sum+y[i];
   }
   //cout<<"\n"<<sum;
   //cout<<A<<endl;
   cudaFree(input_data);
   cudaFree(output_data);

} // gaussian_kde