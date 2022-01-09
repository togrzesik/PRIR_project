#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <mpi.h>

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

int main(int argc, char *argv[])
{
    vector<int> nums;
  
    int k = 3;
    int my_rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &k);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    double startParallel, stopParallel;
    startParallel = MPI_Wtime();
    for (int i(0); i < 10; i++)
        nums.push_back(rand() % 100);

    cout << "Array:";
    for (int i : nums)
        cout << i << "\n";

    //cout << k << " Largest1:" << KthLargest1(nums, k) << endl;

    cout << k << " Largest2:" << KthLargest2(nums, k) << endl;
    stopParallel = MPI_Wtime();
    double Diff = stopParallel - startParallel;
    cout << "Execution time: " << Diff;
    MPI_Finalize();
}