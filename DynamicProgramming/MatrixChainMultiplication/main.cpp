#include <iostream>
#define size 100

using namespace std;

/*
Matrix Chain Multiplication (MCM) :
        Matrix chain multiplication (or Matrix Chain Ordering Problem, MCOP) is an optimization problem. Given a sequence of matrices, the goal is to find
    the most efficient way to multiply these matrices. The problem is not actually to perform the multiplications, but merely to decide the sequence of the
    matrix multiplications involved.

Explanation :
        Suppose we have matrices A1, A2, A3, ..., An. Here, cost[i, j] means total number of multiplication need to be done for multiplying Ai with Aj. The recursive
    formula here for calculating cost is, cost[i, j] = i <= k < j min{cost[i, k] + cost[k + 1, j] + d[i - 1] * d[k] * d[j]}. Where cost[i, k] is the total number of multiplications
    to be done for multiplying matrices Ai and Ak where i <= k < j and d[i] represents the ith common dimension of matrices. The base case for this recursive formula
    is cost[i, i] = 0;
        An analogy is, to multiply Ai with Aj we have to break it into Ai Ak and Ak Aj portions. Here k has to be selected in a way such that Ai and Aj take
    minimum number of multiplications. So, we have to record this k for each iteration and put parenthesis around Ai and Ak (Means we have to multiply Ai and Ak first)
    to get required minimization.
        Here, let's say record of k is,
            0 1 1 3
            0 0 2 3
            0 0 0 3
            0 0 0 0
    k[1, 4] = 3 (Indexing from 1). So, put parenthesis around A3 from A1 to A4. Therefore, (A1 A2 A3) (A4). Now abut (A1, A2, A3). k[1, 3] = 1. So, put parenthesis around
    A1 from A1 to A3. Therefore ((A1)(A2 A3)). Now, none is left. So, final answer is, ((A1)(A2 A3))(A4). If chain multiplication is done this way, number of multiplications
    will be minimum.


Complexity :
    Time complexity of this algorithm using memoization is O(n^3)

Sample Input :
4
3 2 4 2 5

Sample Output :
Cost table :
0 24 28 58
0 0 16 36
0 0 0 40
0 0 0 0

Parenthesis table :
0 1 1 3
0 0 2 3
0 0 0 3
0 0 0 0

References :
        Youtube => https://youtu.be/_WncuhSJZyA
*/

int d[size] = {3, 2, 4, 2, 5};  //Array of common dimensions i.e. if matrices are A3x2, B2x4, C4x2, D2x5 the array d will be d[5] = {3, 2, 4, 2, 5}
int cost[size][size] = {0};     //Cost of multiplication (Total number of multiplications) for multiplying Ai with Aj for each pair of i and j. If i = j, cost[i][j] = 0.
int M[size][size] = {0};        //Record of minimum value of k for multiplying Ai with Aj for all pair of i and j
int numberOfMatrices = 4;       //Number of matrices


void minimumCost() {
    for(int k = 1; k <= numberOfMatrices - 1; k++) {
        for(int i = 1; i <= numberOfMatrices - k; i++) {
            int j = i + k;
            int min = cost[i][i] + cost[i + 1][j] + d[i - 1] * d[i] * d[j];
            int m;

            for(int v = i; v < j; v++) {
                if(cost[i][v] + cost[v + 1][j] + d[i - 1] * d[v] * d[j] <= min) {
                    min = cost[i][v] + cost[v + 1][j] + d[i - 1] * d[v] * d[j];     //Calculating the minimum cost of multiplying for Ai and Aj for each pair of i and j
                    m = v;
                }
            }


            cost[i][j] = min;
            M[i][j] = m;                                                            //Keeping record of m where parenthesis to be put to get minimum cost
        }
    }

    cout << "\nCost table :" << endl;
    for(int i = 1; i <= numberOfMatrices; i++) {
        for(int j = 1; j <= numberOfMatrices; j++) {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Parenthesis table :" << endl;
    for(int i = 1; i <= numberOfMatrices; i++) {
        for(int j = 1; j <= numberOfMatrices; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Enter number of matrices and their common dimensions :" << endl;
    cin >> numberOfMatrices;

    for(int i = 0; i <= numberOfMatrices; i++)
        cin >> d[i];

    minimumCost();
    return 0;
}
