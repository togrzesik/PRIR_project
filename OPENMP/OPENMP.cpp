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
    int k = 3;
    int th = 10;
    omp_set_num_threads(th);
    int n = 50000;
    int i;
    for (int i = 0; i < n; i++)
        nums.push_back(rand() % 100000);
    double startParallel = 0.0, stopParallel = 0.0;
    startParallel = omp_get_wtime();
#pragma omp parallel for num_threads(th)
    for (int i = 0; i < th; i++)
        KthLargest2(nums, k);
    stopParallel = omp_get_wtime();
    cout << "Array: ";
    cout << k << " Largest:" << KthLargest2(nums, k) << endl;
    double Diff = stopParallel - startParallel;
    cout << "Execution time: " << Diff;
}