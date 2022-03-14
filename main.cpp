#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <random>
#include <conio.h>
#include <ctime>

using namespace std;
vector <long long> arr(1000000), L, M;
int n=arr.size();
double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}
void generate_vector(vector<long long> &arr, long long maxim)
{ mt19937_64 gen(time(NULL));
  uniform_int_distribution<long long> random(0, maxim);
  for(auto i = arr.begin(); i!=arr.end(); i++){ *i = random(gen); }
 }


void merge(vector <long long> &arr, int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = arr[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = arr[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector <long long> &arr, int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(arr, begin, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, begin, mid, end);
}


void shellSort(vector <long long> &arr)
{
    // Start with a big gap, then reduce the gap
    for (int gap = arr.size()/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < arr.size(); i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }

}

void heapify(vector <long long> &arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(vector <long long> &arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void insertionSort(vector <long long> &arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A utility function to get maximum value in arr[]
int getMax(vector <long long> &arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(vector <long long> &arr, int n, int exp)
{
    int output[n]; // output array
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
void radixSort(vector <long long> &arr, int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void printArray(vector <long long> arr) {
  for (int i = 0; i < arr.size(); i++)
     cout << arr[i] << " ";
    cout << endl;
}
int verificare_sortare(vector <long long> &arr, int n)
{
    int ok=1,i;
    for(i=1;i<n;i++)
        if (arr[i-1]>arr[i]) ok=0;
    return ok;
}


int main() {
    clock_t start, end;
  srand(time(0));
  cout<<"N = 1000000 Maxim = 999990: \n";
///SORT
 generate_vector(arr, 1000000);
 start = clock();
 sort(arr.begin(),arr.end());
 end = clock();
 cout<<"SORT dureaza: ";
 cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout <<diffclock(end,start)<<" "<<"milisecunde"<<endl;

  ///MERGESORT
  generate_vector(arr, 1000000);
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  mergeSort(arr, 0, arr.size() - 1);
  end = clock();
  cout<<"MERGESORT dureaza: ";
  cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout <<diffclock(end,start)<<" "<<"milisecunde"<<endl;

  ///HEAPSORT
  generate_vector(arr, 1000000);
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  heapSort(arr,n);
  end = clock();
  cout<<"HEAPSORT dureaza: ";
  cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout<<diffclock(end,start)<<" "<<"milisecunde"<<endl;


  ///INSERTIONSORT
  generate_vector(arr, 1000000);
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  insertionSort(arr,n);
  end = clock();
  cout<<"INSERTIONSORT dureaza: ";
  cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout<<diffclock(end,start)<<" "<<"milisecunde"<<endl;

  ///SHELLSORT
  generate_vector(arr, 1000000);
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  shellSort(arr);
  end = clock();
  cout<<"SHELLSORT dureaza: ";
  cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout<<diffclock(end,start)<<" "<<"milisecunde"<<endl;

  ///RADIXSORT
  generate_vector(arr, 1000000);
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  radixSort(arr,n);
  end = clock();
  cout<<"RADIXSORT dureaza: ";
  cout<<verificare_sortare(arr,n)<<'/n';
  //cout << "Sorted array: \n";
  //printArray(arr);
  cout<<diffclock(end,start)<<" "<<"milisecunde"<<endl;
  return 0;
}
