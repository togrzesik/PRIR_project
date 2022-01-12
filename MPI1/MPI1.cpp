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
#define MAX 5000
int main(int argc, char *argv[])
{
    vector<int> nums;
  
    float tab[MAX];
    int k = 3;
    int my_rank;
    int size = 10;
    int i, d;
    int y, z;
    int wartosc;
    int reszta;
    double tmp = 0;
    double wynik = 0;
    double startParallel = 0.0, stopParallel = 0.0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Request reql;
    MPI_Status status;
    int* tabAll = new int{ size };
    if (my_rank == 0) {
        startParallel = MPI_Wtime();
        for (d = 0; d < size; d++) {
            if (d != my_rank) {
                int a = 4;
                MPI_Send(&a, 1, MPI_INT, d, 13, MPI_COMM_WORLD);
            }
        }
    }
    else if (my_rank != 0) {
        int b;
        MPI_Recv(&b, 1, MPI_INT, 0, 13, MPI_COMM_WORLD, &status);
    }
    reszta = MAX % size;
    if (reszta == 0) wartosc = MAX / size;
    else {
        if (my_rank == 0) wartosc = MAX;
        else wartosc = 0;
        if (my_rank == 0) {
            cout << "Nie można podzielić tablicy na %d " << size << "równych części!";
            cout << "K-ta wartość zostanie wyliczona przez 1 proces.";
        }
    }
    y = wartosc * my_rank;
    z = wartosc * my_rank + wartosc;
    for (i = y; i < z; i++) {
        tab[i] = i+1;
    }
    for (int i = y; i < z; i++)
         nums.push_back(rand() % 100000);
    
    stopParallel = MPI_Wtime();
    cout << "Array: ";
    double Diff = stopParallel - startParallel;
    // for (int i : nums)
      //   cout << i << "\n";

    //cout << k << " Largest1:" << KthLargest1(nums, k) << endl;

    cout << k << " Largest:" << KthLargest2(nums, k) << endl;
    cout << "Execution time: " << Diff;
    MPI_Finalize();
}