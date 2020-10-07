// sortowanko.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#define numerek 123456

using namespace std;

int random[numerek];

void sortuj() {
    int a, b, c = 0;
    do {
        c = 0;
        for (int i = 0; i < sizeof(random) / sizeof(int); i++) {
            a = random[i];
            if (random[i + 1] < a) {
            b = random[i + 1];
            random[i] = b;
            random[i + 1] = a;
            c++;
            }
        }
    } while (c != 0);
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array  
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element  
        swap(&arr[min_idx], &arr[i]);
    }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    int output[numerek]; // output array
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir == (a[i] > a[j]))
        swap(a[i], a[j]);
}

/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        // sort in ascending order since dir here is 1 
        bitonicSort(a, low, k, 1);

        // sort in descending order since dir here is 0 
        bitonicSort(a, low + k, k, 0);

        // Will merge wole sequence in ascending order 
        // since dir=1. 
        bitonicMerge(a, low, cnt, dir);
    }
}

/* Caller of bitonicSort for sorting the entire array of
   length N in ASCENDING order */
void sort(int a[], int N, int up)
{
    bitonicSort(a, 0, N, up);
}

/* Reverses arr[0..i] */
void flip(int arr[], int i)
{
    int temp, start = 0;
    while (start < i)
    {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

// Returns index of the  
// maximum element in  
// arr[0..n-1]  
int findMax(int arr[], int n)
{
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

// The main function that  
// sorts given array using  
// flip operations  
void pancakeSort(int* arr, int n)
{
    // Start from the complete  
    // array and one by one  
    // reduce current size  
    // by one  
    for (int curr_size = n; curr_size > 1; --curr_size)
    {
        // Find index of the  
        // maximum element in  
        // arr[0..curr_size-1]  
        int mi = findMax(arr, curr_size);

        // Move the maximum  
        // element to end of  
        // current array if  
        // it's not already  
        // at the end  
        if (mi != curr_size - 1)
        {
            // To move at the end,  
            // first move maximum  
            // number to beginning  
            flip(arr, mi);

            // Now move the maximum  
            // number to end by  
            // reversing current array  
            flip(arr, curr_size - 1);
        }
    }
}

int main()
{
    int n = sizeof(random) / sizeof(int);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Sortowanie " << sizeof(random) / sizeof(int) << " losowych liczb" << std::endl << std::endl << "Losowanie... ";

    std::random_device rd;
    std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> uid(0, 512);

    begin = std::chrono::steady_clock::now();
    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    std::cout << "\nSortowanie QuickSort... ";

    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    begin = std::chrono::steady_clock::now();
    quickSort(random, 0, n -1);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl; 

    std::cout << "\nSortowanie Radix Sort... ";

    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    begin = std::chrono::steady_clock::now();
    radixsort(random, n);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    std::cout << "\nSortowanie Bitonic Sort... ";

    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    begin = std::chrono::steady_clock::now();
    int up = 1;   // means sort in ascending order 
    sort(random, n, up);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    std::cout << "\nSortowanie Pancake sorting... ";

    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    begin = std::chrono::steady_clock::now();
    pancakeSort(random, n);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
    
    std::cout << "\nSortowanie (Moja metoda) ... ";

    begin = std::chrono::steady_clock::now();
    sortuj();
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    std::cout << "\nSortowanie Selection Sort... ";

    std::generate(random, random + sizeof(random) / sizeof(int), [&]() { return uid(dre); });
    begin = std::chrono::steady_clock::now();
    selectionSort(random, n);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
}