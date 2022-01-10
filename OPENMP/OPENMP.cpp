#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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
    unsigned long sum = 0;
    int quantity = 0;
    int k = 3;
    int th = 1;
    int my_rank;
    int silk = 5000;
    double startParallel, stopParallel;
    startParallel = omp_get_wtime();
#pragma omp parallel for reduction(+:sum,quantity) num_threads(th)
    for (int i(0); i < silk; i++)
        nums.push_back(rand() % 10000);

    cout << "Array:";
    cout << k << " Largest2:" << KthLargest2(nums, k) << endl;
    stopParallel = omp_get_wtime();
    double Diff = stopParallel - startParallel;
    cout << "Execution time: " << Diff;
}