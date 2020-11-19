#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
Fractional Knapsack :
        The knapsack problem is, given a set of items, each with a weight and a value, determine the number of each item to include in a collection
    so that the total weight is less than or equal to a given limit and the total value(profit) is as large as possible. It derives its name from the problem
    faced by someone who is constrained by a fixed-size knapsack and must fill it with the most valuable items.
        Knapsack problems are of two types : 01Knapsack and Fractional Knapsack. In case of Fractional Knapsack as the name describes, a fraction of an item
    can be included if needed unlike 01Knapsack problem where an item can either be included or fully excluded into the solution set and can't be included
    fractionally. Fractional Knapsack problem can be solved using Greedy Subset Subset paradigm.

Explanation :
        We will evolve suboptimal solution sets at each step by including single item based on some predefined optimization measures. Here, being greedy on
    basis of the ratio of item's value and weight (value / weight) guarantees an optimal solution. So, at each step we will take the item of highest value-
    weight ratio and check for feasibility (Either it will cross the constraint weight or not). If it is feasible we will include it into the output set.
    If it is not feasible, we will try to partially include it and fill the knapsack fully.
        Here, objective is maximizing total value(profit) and constraint is maximum weight capacity of the knapsack. Any solution set that won't cross the
    capacity of the Knapsack is feasible. Among them the solution set maximizing total value is optimal.

Sample Input :
3 20
25 18
24 15
15 10

Sample output :
Solution subset :15 10
Max profit :31.5

References :
        Book => Fundamentals of Computer Algorithms by Sartaj Sahni -page210
        Algorithm => Fundamentals of Computer Algorithms by Sartaj Sahni -page220
*/

typedef struct object {
    int weight;
    int profit;
    float isIncluded;
};

void GreedyKnapsack(object arr[], int size, int constraint) {
    int u = constraint;

    //Being greedy on basis of profit-weight ratio of objects
    for(int i = 0; i < size; i++) {
        if(arr[i].weight > u) {                             //If further inclusion of object crosses the knapsack's weight capacity try to fraction up the object and fill the knapsack fully
            arr[i].isIncluded = (float)u / arr[i].weight;
            break;
        }

        arr[i].isIncluded = 1;
        u = u - arr[i].weight;
    }
}

int main()
{
    object arr[100];
    int n, m;
    float maxProfit = 0.0;

    cout << "Enter object number, constraints and attributes(profit weight) :" << endl;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> arr[i].profit;
        cin >> arr[i].weight;
        arr[i].isIncluded = 0;
    }

    //Sorting object in descending order of profit-weight ratio
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++) {
            if((float)arr[j].profit / arr[j].weight > (float)arr[i].profit / arr[i].weight) {
                object tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }

    GreedyKnapsack(arr, n, m);

    cout << "Solution subset :";
    for(int i = 0; i < n; i++) {
        if(arr[i].isIncluded != 0.0) {
            cout << arr[i].weight << " ";
            maxProfit += arr[i].profit * arr[i].isIncluded;
        }
    }
    cout << endl;
    cout << "Max profit :" << maxProfit << endl;

    return 0;
}
