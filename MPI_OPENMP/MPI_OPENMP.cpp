#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <mpi.h>
#include <omp.h>
using namespace std;

/*int KthLargest1(vector<int>& nums, int k)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    return nums[n - k];
} */

int KthLargest2(vector<int>& nums, int k)
{
    priority_queue<int, vector<int>, greater<int> > pq;

    for (int i : nums)
    {
        if (pq.size() < k)
            pq.push(i);
        else
        {
            if (pq.top() < i)
            {
                pq.pop();
                pq.push(i);
            }
        }
    }

    return pq.top();
}

int main(int argc, char* argv[])
{
    vector<int> nums;

    int k = 3;
    int th = 2;
    int my_rank;
    int silk = 2000;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &th);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    double startParallel, stopParallel;
    startParallel = MPI_Wtime();
    #pragma omp parallel for num_threads(th)
    for (int i(0); i < silk; i++)
        nums.push_back(rand() % 10000);

//    MPI_Send(&silk, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
//    MPI_Recv(&k, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    cout << "Array:";
    cout << k << " Largest2:" << KthLargest2(nums, k) << endl;
    stopParallel = MPI_Wtime();
    double Diff = stopParallel - startParallel;
    cout << "Execution time: " << Diff;
    MPI_Finalize();
}