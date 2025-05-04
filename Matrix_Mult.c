#include <stdio.h>
#include <cuda.h>

#define N 16  // Matrix dimension (N x N). You can increase this for larger matrices.

__global__ void matrixMulKernel(int* A, int* B, int* C, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < width && col < width) {
        int sum = 0;
        for (int k = 0; k < width; k++) {
            sum += A[row * width + k] * B[k * width + col];
        }
        C[row * width + col] = sum;
    }
}

void printMatrix(int* M, int width) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            printf("%4d ", M[i * width + j]);
        }
        printf("\n");
    }
}

int main() {
    int size = N * N * sizeof(int);

    // Allocate host memory
    int* h_A = (int*)malloc(size);
    int* h_B = (int*)malloc(size);
    int* h_C = (int*)malloc(size);

    // Initialize host matrices
    for (int i = 0; i < N * N; i++) {
        h_A[i] = 1;  // or any value you want
        h_B[i] = 2;  // or any value you want
    }

    // Allocate device memory
    int *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Copy matrices from host to device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Kernel launch configuration
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((N + 15) / 16, (N + 15) / 16);

    // Launch kernel
    matrixMulKernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();

    // Copy result from device to host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Print matrices
    printf("Matrix A:\n");
    printMatrix(h_A, N);

    printf("\nMatrix B:\n");
    printMatrix(h_B, N);

    printf("\nMatrix C = A * B:\n");
    printMatrix(h_C, N);

    // Cleanup
    free(h_A); free(h_B); free(h_C);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);

    return 0;
}
