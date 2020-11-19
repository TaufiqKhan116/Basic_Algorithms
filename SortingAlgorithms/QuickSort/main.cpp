#include <iostream>

using namespace std;

/*
Quick Sort :
        Quick Sort is a divide-and-conquer algorithm. This can be done in-place, requiring small additional amounts of memory to perform the sorting.
    When implemented well, it can be about two or three times faster than its main competitors, Merge Sort and Heap Sort.

Explanation :
        Firstly, we have to take a pivot element from the array. Then we will compare each other element with pivot. We will swap all the pairs of elements
    consisting one element smaller than pivot and one element greater than pivot if they are at wrong side of the pivot. Doing so will place the pivot at
    correct position. All elements to the pivot's right will be smaller and to the left will be greater (Conventionally). Now, we will do the same with the
    unsorted right and left portion recursively.

Complexity :
        Worst case complexity O(n^2)
        Best case complexity O(nlogn)
        Average case complexity O(nlogn)

Sample Input :
        5
        4 1 5 0 3

Sample Output :
        0 1 3 4 5

Reference :
        Youtube => https://www.youtube.com/watch?v=QN9hnmAgmOc
        Youtube => https://youtu.be/7h1s2SojIRw
        Wikipidea => https://en.wikipedia.org/wiki/Quicksort
*/



int partition(int arr[], int low, int high) {

    //Selecting a pivot
    int pivot = arr[low];
    int i = low;
    int j = high;

    while(i < j) {

        //Looping till element less than or equal to pivot is got
        while(arr[i] <= pivot){
            i++;
        }

        //Looping till element greater than to pivot is got
        while(arr[j] > pivot) {
            j--;
        }

        //When both of the loops stop
        if(i < j)
            swap(arr[i], arr[j]);
    }

    //Placing pivot at correct position
    swap(arr[low], arr[j]);

    return j;
}

void quickSort(int arr[], int low, int high) {

    int j;

    if(low < high) {
        j = partition(arr, low, high);

        quickSort(arr, low, j - 1); //Recursive call for left portion of pivot
        quickSort(arr, j + 1, high); //Recursive call for left portion of pivot
    }
}

int main()
{
    int n = 0;
    int i = 0;
    int arr[100];

    cout << "Enter array size and array elements :" << endl;
    cin >> n;

    for(i = 0; i < n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n - 1);

    cout << "Sorted array :" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
