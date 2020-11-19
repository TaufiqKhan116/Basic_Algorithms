#include<stdio.h>
#include<bits/stdc++.h>
#define NumberOfNodes 4

using namespace std;

/*
Graph Coloring :
        Graph Coloring in its simplest form is a way of coloring the vertices of a graph such that no two adjacent vertices are of the same color. If m colors
    are given and the question, if a graph G can be colored with m colors is asked then the problem is called m Coloring decision problem. And if the question,
    what is minimum number of color can be used to color the graph is asked, then it is called m Coloring optimization problem.

Explanation :
        Here we are considering m Coloring Decision problem. Let's say we have m colors and Graph G. For assigning colors 1 to m to first(initial) vertex, we will
    generate colors for other vertices recursively till implicit constraint(No two adjacent vertices can have same color) is satisfied. If the implicit constraint
    is crossed we will skip that sequence and backtrack to initial position.

Comlexity :
        Time complexity of this algorithm is O(m^n)
    Where, m is number of color and n is total vertex number.

Sample Input :
Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)

Sample Output :
Solution Exists.
Following are the assigned colors :
1 2 3 2
Chromatic Number: 3

Credit :
        Audity Ghosh
        CSE'17, RUET

*/


void printSolution(int colorArray[])
{
    cout << "Solution Exists." << endl;
    cout << "Following are the assigned colors :" << endl;
    for (int i = 0; i < NumberOfNodes; i++)
      cout << colorArray[i] << " ";
    cout << endl;
}

/*
A utility function to check if the current color assignment is safe for current vertex v i.e. graph[v][i]==1 checks whether the edge does exist or not.If
the edge exist then checks whether the color to be filled in the new vertex(color is sent in the parameter) is already used by its adjacent vertices
(i represents adjacent vertices) or not i.e. colorArray[i] == color
*/
bool isSafe (bool graph[NumberOfNodes][NumberOfNodes], int colorArray[], int currentVertex, int color)
{
    for (int i = 0; i < NumberOfNodes; i++)
        if (graph[currentVertex][i] && color == colorArray[i])
            return false;

    return true;
}

//A recursive utility function to solve m coloring problem
bool graphColoringUtil(bool graph[NumberOfNodes][NumberOfNodes], int numberOfColors, int color[], int currentVertex) {

    if (currentVertex == NumberOfNodes)                                                 //Base case: If all vertices are assigned a color then return true
        return true;

    for (int c = 1; c <= numberOfColors; c++) {                                         //Consider this vertex v and try different colors

        if (isSafe(graph, color, currentVertex, c)) {                                   //Check if assignment of color c to v is fine
           color[currentVertex] = c;
           if (graphColoringUtil (graph, numberOfColors, color, currentVertex + 1))     //Recur to assign colors to rest of the vertices
             return true;

           color[currentVertex] = 0;                                                    //If assigning color c does not lead to a solution then remove it
        }
    }

    return false;                                                                       //If no color can be assigned to this vertex then return false
}



/*
This function solves the m Coloring problem using Backtracking. It mainly uses graphColoringUtil() to solve the problem. It returns false if the m colors
cannot be assigned, otherwise return true and prints assignments of colors to all vertices. Please note that there may be more than one solutions, this
function prints one of the feasible solutions.
*/
bool graphColoring(bool graph[NumberOfNodes][NumberOfNodes], int numberOfColors) {

    int *color = new int[NumberOfNodes];                        //Initialize all color values as 0. This initialization is needed correct functioning of isSafe()
    for (int i = 0; i < NumberOfNodes; i++)
       color[i] = 0;

    if (!graphColoringUtil(graph, numberOfColors, color, 0))    //Call graphColoringUtil() for vertex 0
        return false;

    printSolution(color);                                       // Print the solution

    return true;
}

//Driver program to test above function
int main()
{
    int chromaticNumber = 1;
    bool graph[NumberOfNodes][NumberOfNodes] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };

    while(true)
    {
      if(graphColoring (graph, chromaticNumber)) {

            cout << "Chromatic Number: " << chromaticNumber << endl;
            break;

        } else
            chromaticNumber++;
    }

    return 0;
}
