#include <iostream>

using namespace std;

/*
Counting Sort :
        Counting Sort is  is an algorithm for sorting a collection of objects according to keys that are small integers;
    that is, it is an integer sorting algorithm. If variation in keys is significantly greater than number of items then it is not suitable.
    It is used as a subroutine in Radix Sort.

Explanation :
        Let's say we have an array a = [2, 1, 1, 0, 2, 5, 4, 0, 2, 8, 7, 7, 9, 2, 0, 1, 9] here maximum value is max(number of keys) = 9 and total item number n = 17.
    As they are not significantly different, we can apply Counting Sort here.
        Firstly, we have to determine the frequency of given data. Let's say we have 10 buckets corresponding each key from 0 to 9. If we put our data into corresponding bucket,
    each bucket will contain data as follows,
            bucket[0] = 3 data (As array has 3 0's)
            bucket[1] = 3 data (As array has 3 1's)
            bucket[2] = 4 data (As array has 4 2's)
            bucket[3] = 0 data (As array has 0 3)
            bucket[4] = 1 data (As array has 1 4)
            bucket[5] = 1 data (As array has 1 5)
            bucket[6] = 0 data (As array has 0 6)
            bucket[7] = 2 data (As array has 2 7's)
            bucket[8] = 1 data (As array has 1 8)
            bucket[9] = 2 data (As array has 2 9's)
        Secondly, we have to determine cumulative frequency. The cumulative frequency of Nth bucket is number of total data from bucket 0 to bucket N
    (Including the data in Nth bucket). Thus we will gate how many data are exactly before a particular data which determines the position index of that
    particular data in the output array. So, the cumulative frequency will be,
            tillBucket[0] = 3 data (3 0's)
            tillBucket[1] = 6 data (3 0's, 3 1's)
            tillBucket[2] = 10 data (3 0's, 3 1's, 4 2's)
            tillBucket[3] = 10 data (3 0's, 3 1's, 4 2's, 0 3)
            tillBucket[4] = 11 data (3 0's, 3 1's, 4 2's, 0 3, 1 4)
            tillBucket[5] = 12 data (3 0's, 3 1's, 4 2's, 0 3, 1 4, 1 5)
            tillBucket[6] = 12 data (3 0's, 3 1's, 4 2's, 0 3, 1 4, 1 5, 1 6)
            tillBucket[7] = 14 data (3 0's, 3 1's, 4 2's, 0 3, 1 4, 1 5, 1 6, 2 7's)
            tillBucket[8] = 15 data (3 0's, 3 1's, 4 2's, 0 3, 1 4, 1 5, 1 6, 2 7's, 1 8)
            tillBucket[9] = 15 data (3 0's, 3 1's, 4 2's, 0 3, 1 4, 1 5, 1 6, 2 7's, 1 8, 2 9's)
        Now, in the output array, we have to place each data at its bucket's cumulative frequency - 1 (As started from 0) position and then reduce the cumulative
    frequency by 1. Suppose, we want to know the position of 8 in output array. How many data before 8? The number of data before 8 is equal to cumulative frequency
    of 8th bucket (key 8) - 1 which is, tillBucket[8] - 1 = 15 - 1 = 14. So, output[14] will be 8. Thus, the sorted output array will be,
            output[0] = 0
            output[1] = 0
            output[2] = 0
            output[3] = 1
            output[4] = 1
            output[5] = 1
            output[6] = 2
            output[7] = 2
            output[8] = 2
            output[9] = 2
            output[10] = 4
            output[11] = 5
            output[12] = 7
            output[13] = 7
            output[14] = 8
            output[15] = 9
            output[16] = 9

Complexity :
        Counting Sort is a linear time algorithm. So, it is O(n) where n is input array size.
    Specifically, the complexity is, O(n + k) where k is number of keys. if k >> n this algorithm won't be
    efficient or suitable.

Sample Input :
        17
        2 1 1 0 2 5 4 0 2 8 7 7 9 2 0 1 9

Sample Output :
        0 0 0 1 1 1 2 2 2 2 4 5 7 7 8 9 9

References :
        Youtube => https://youtu.be/pEJiGC-ObQE
        Wikipidea => https://en.wikipedia.org/wiki/Counting_sort
*/

int maxInArray(int arr[], int size) {
    int maxVal = arr[0];

    for(int i = 0; i < size; i++)
        if(arr[i] > maxVal)
            maxVal = arr[i];

    return maxVal;
}

void countingSort(int arr[], int size) {
    int maxVal = maxInArray(arr, size);
    int *bucket = new int[maxVal];
    int output[size];

    //Initializing Bucket
    for(int i = 0; i < maxVal; i++)
        bucket[i] = 0;

    //Determining frequency (How many data in a particular bucket)
    for(int i = 0; i < size; i++)
        bucket[arr[i]]++;

    //Determining cumulative frequency (How many data up to a particular bucket)
    for(int i = 1; i <= maxVal ; i++)
        bucket[i] += bucket[i - 1];

    //Placing data to the correct position
    for(int i = size - 1; i >= 0; i--) {
        output[bucket[arr[i]] - 1] = arr[i];
        bucket[arr[i]]--;
    }

    //Copying data to the array from output array
    for(int i = 0; i < size; i++)
        arr[i] = output[i];
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

    countingSort(arr, n);

    cout << "Sorted array :" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}
