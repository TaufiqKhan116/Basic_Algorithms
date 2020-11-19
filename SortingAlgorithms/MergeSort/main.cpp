#include<iostream>
#define size 20
using namespace std;

/*
Merge sort :
        Merge Sort is an efficient, general-purpose, comparison-based sorting algorithm. Most implementations produce a stable sort, which means that the
    order of equal elements is the same in the input and output. Merge sort is a divide and conquer algorithm that was invented by John Von Neumann in 1945.

Explanation :
        Consider a array a[1:10] with some elements. Now it will divide into two equal sub arrays (a[1:5] and a[6:10]). This process will continue until it
    becomes one element sub arrays (a[1],a[2]....a[10]). It is maintained in a recursive mechanism. No data will changed their position. After that this sub
    arrays will be merged like a[1:2] and that time the elements will be sorted. After completing all those recursive calls finally our array a[1:10] will
    be fully sorted.

Complexity :
        Time complexity of Merge Sort is O(n * log n)

Sample input :
10
310 285 179 652 351 423 861 254 450 520

Sample output :
179 254 285 310 351 423 450 520 652 861

Credit :
        Salauddin Fahad Rashik
        CSE'17, RUET
*/

int a[size], b[size];

void Merge(int low, int mid, int high)
{
    int h = low, i = low, j = mid + 1, k;

    while(h <= mid && j <= high){

        if (a[h] <= a[j]){
            b[i] = a[h];
            h = h + 1;
        } else {
            b[i] = a[j];
            j = j + 1;
        }
        i = i + 1;
    }

    if (h > mid)
        for(k = j; k <= high; k++) {
            b[i] = a[k];
            i = i + 1;
        } else
            for(k = h; k <= mid; k++) {
                b[i] = a[k];
                i = i + 1;
            }

    for(k = low; k <= high; k++)
        a[k] = b[k];
}
void MergeSort(int low, int high)
{
    int mid;
    if(low < high)
    {
        mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);
        Merge(low, mid, high);
    }
}
int main()
{
    int n;

    cout << "Enter number of elements and elements :" << endl;
    cin >> n;
    for(int i = 0; i < n ; i++)
        cin >> a[i];

    MergeSort(0,n-1);

    cout << "\nAfter sorting: " << endl;
    for(int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
