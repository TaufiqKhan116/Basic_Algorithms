#include <iostream>

using namespace std;

/*
Radix Sort :
        Radix Sort or Bucket Sort or Digital Sort unlike other sorting techniques(like Merge Sort, Selection Sort etc) is a non-comparative
    sorting algorithm which distributes data into buckets according to their radix.
Radix (base) :
        In a positional numeral system, the radix or base is the number of unique digits, including the digit zero,
    used to represent numbers. In simple words base of number system (If data is numeric).

Explanation :
    Let's say we have an array a = [247, 321, 515, 227, 642, 413, 109, 248, 754, 930] and as the base or radix of integer is 10,
    we have 10 buckets starting from 0 to 9. Now in first pass we will put the numbers into these buckets according to their least
    significant digit.
    So, bucket[0] = 1 number (930)
        bucket[1] = 1 number (321)
        bucket[2] = 1 number (642)
        bucket[3] = 1 number (413)
        bucket[4] = 1 number (754)
        bucket[5] = 1 number (515)
        bucket[6] = 0 number (No number with last digit 6)
        bucket[7] = 2 numbers (247, 227)
        bucket[8] = 1 number (248)
        bucket[9] = 1 number (109)
    Now we have to get the cumulative frequencies of those buckets. Simply the cumulative frequency of Nth bucket is total number of
    elements contained by the buckets 0th to Nth (Including Nth bucket).
    So, tillBucket[0] = 1 numbers (930)
        tillBucket[1] = 2 numbers (930 in bucket 0, 321)
        tillBucket[2] = 3 numbers (930 in bucket 0, 321 in bucket 1, 642)
        tillBucket[3] = 4 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413)
        tillBucket[4] = 5 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754)
        tillBucket[5] = 6 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754 in bucket 4, 515)
        tillBucket[6] = 6 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754 in bucket 4, 515 in bucket 5)
        tillBucket[7] = 8 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754 in bucket 4, 515 in bucket 5, 247, 227)
        tillBucket[8] = 9 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754 in bucket 4, 515 in bucket 5, 247 and 227 in bucket 7, 248)
        tillBucket[9] = 10 numbers (930 in bucket 0, 321 in bucket 1, 642 in bucket 2, 413 in bucket 3, 754 in bucket 4, 515 in bucket 5, 247 and 227 in bucket 7, 248 in bucket 8, 109)
    Now we exactly know how many elements(numbers) there are before each bucket that is it's cumulative frequency. Now if asked where a particular data, let's say
    a[7] = 248, should be placed in output array? To answer this we have to ask in which bucket is it now? It is in bucket[8] as its last digit is 8. How many
    elements till bucket[8]? 9 elements including 248. Then How many elements should be before 248? 8 elements excluding 248. So, at which index of output array
    will 248 be? It will be at index 8 (As counted from 0) aka output[8] = 248. Following this process at first pass we get output array as,
        output[0] = 930
        output[1] = 321
        output[2] = 642
        output[3] = 413
        output[4] = 754
        output[5] = 515
        output[6] = 247
        output[7] = 227
        output[8] = 248
        output[9] = 109
        The array is sorted based on first digit (LSD). Now we have to sort the output array again following same process with second most significant digit, then
    third, fourth and thus till number of digits of maximum number.

Complexity :
        Time complexity of Radix Sort is O(n).
    Specifically, it is O(kw), where k is number of keys and w is length of keys.

Sample Input :
        10
        247 321 515 227 642 413 109 248 754 930

Sample Output :
        109 227 247 248 321 413 515 642 754 930

References :
        Youtube => https://youtu.be/GWGr5XQFXPc
        YOutube => https://youtu.be/pEJiGC-ObQE
        Wikipidea => https://en.wikipedia.org/wiki/Radix_sort
*/

int maxInArray(int arr[], int size) {
    int maxVal = arr[0];

    for(int i = 0; i < size; i++)
        if(arr[i] > maxVal)
            maxVal = arr[i];

    return maxVal;
}

void countingSort(int arr[], int size, int exp, int maxVal) {
    int *bucket = new int[10];
    int output[size];

    //Initializing buckets
    for(int i = 0; i < 10; i++)
        bucket[i] = 0;

    //Determining frequency(How many values in a particular bucket)
    for(int i = 0; i < size; i++)
        bucket[(arr[i] / exp) % 10]++;

    //Determining cumulative frequency (How many values up to a particular bucket)
    for(int i = 1; i < 10 ; i++)
        bucket[i] += bucket[i - 1];

    //Placing value to the correct position
    for(int i = size - 1; i >= 0; i--) {
        output[bucket[(arr[i] / exp) % 10] - 1] = arr[i];
        bucket[(arr[i] / exp) % 10]--;
    }

    //Copying data to the array from output array
    for(int i = 0; i < size; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int size) {
    int maxVal = maxInArray(arr, size);

    //Gradually applying Counting Sort on LSD to MSD
    for(int exp = 1; maxVal/exp > 0; exp *= 10) // exp gradually becomes 1, 10, 100, ... till 10^n where n is number of digits of maximum value in array.
        countingSort(arr, size, exp, maxVal);

}

int main()
{
    int n = 0;
    int arr[100];

    for(int i = 0; i < n; i++)
        arr[i] = 0;

    cout << "Enter size of array and array elements :" << endl;

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    radixSort(arr, n);

    cout << "Sorted array :" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}
