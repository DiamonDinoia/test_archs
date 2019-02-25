#include <iostream>
#include <unistd.h>
#include "pdqsort_marco.h"
#include "pdqsort.h"
#include <stdlib.h>
#include <chrono>
#include <vector>

using namespace std;

/* Function to sort an array using insertion sort*/
template <typename T>
void insertionSort(vector<T> arr)
{
    int i, j;
    auto const n = arr.size();
    #pragma unroll
    for (i = 1; i < n; i++)
    {
        auto const key = arr[i];
        j = i-1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}


int main() {

    srand(42);

    std::cout << "Hello, World!" << std::endl;
    auto const L1 = sysconf(_SC_LEVEL1_DCACHE_SIZE);
    auto const L2 = sysconf(_SC_LEVEL2_CACHE_SIZE);
    auto const L3 = sysconf(_SC_LEVEL3_CACHE_SIZE);

    std::cout << "L1 CACHE SIZE " << L1 << " bytes" << std::endl;
    std::cout << "L2 CACHE SIZE " << L2 << " bytes" << std::endl;
    std::cout << "L3 CACHE SIZE " << L3 << " bytes" << std::endl;

    vector<int> test;
    for (int i = 0; i < L1/sizeof(int); ++i) {
        test.emplace_back(rand());

    }
    vector<int> test2(test);

    std::chrono::time_point<std::chrono::high_resolution_clock> total_start, total_end;

    total_start = std::chrono::high_resolution_clock::now();
    pdqsort_marco(test.begin(), test.end());
    total_end = std::chrono::high_resolution_clock::now();
    cout << "time qsort " << std::chrono::duration_cast<std::chrono::nanoseconds>(total_end - total_start).count() << endl;
    total_start = std::chrono::high_resolution_clock::now();
    pdqsort(test2.begin(), test2.end());
    total_end = std::chrono::high_resolution_clock::now();
    cout << "time modified_sort " << std::chrono::duration_cast<std::chrono::nanoseconds>(total_end - total_start).count() << endl;

    return 0;
}