#include <iostream>
#define infinity 1000
#define size 4

using namespace std;

/*
Floyd-Warshall Algorithm :
        The Floyd–Warshall algorithm (also known as Floyd's algorithm, the Roy–Warshall algorithm, the Roy–Floyd algorithm, or the WFI algorithm)
    is an algorithm for finding shortest paths in a weighted graph with positive or negative edge weights (but with no negative cycles).
        Unlike Dijkstra's shortest path algorithm or BellMan-Ford algorithm which are used to get shortest path from a single source vertex, this algorithm
    is used to get shortest path between each pair of vertices.

Explanation :
        In this algorithm, we will first select a vertex. Then, we will traverse through all the edges that does not contain the selected vertex. Let's say,
    the selected vertex is s and we are currently traversing (u, v) edge. We will check that if it is possible to break the edge (u, v) into (u, s) and (s, v)
    such that Cost(u, s) + Cost(s, v) < Cost(u, v). If we can, that means the path (u, v) was not short enough. The shorter path fro u to v will be (u, s, v).
        We will do this selecting vertex process for all our vertices and do the testing process for all edges including each selected vertex.

Complexity :
        Time complexity, O(n^3)

Sample input :
0 3 -1 7
8 0 2 -1
5 -1 0 1
2 -1 -1 0

Sample output :
0 3 5 6
5 0 2 3
3 6 0 1
2 5 7 0

References :
        Youtube => https://youtu.be/oNI0rf2P9gE
        Wikipidea => https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
        Algorithm => https://youtu.be/oNI0rf2P9gE
*/

int costMat[size][size];

void FloydWarshall() {
    for(int k = 0; k < size; k++) //Selecting each vertex
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                costMat[i][j] = min(costMat[i][j], costMat[i][k] + costMat[k][j]); //Checking the possibility of shorter path including selected vertex and updating cost matrix accordingly
}

int main()
{
    cout << "Enter the cost matrix (Enter -1 for unreachable vertex and 0 for not having self loop) :" << endl;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            int n;
            cin >> n;

            if(n == -1)
                costMat[i][j] = infinity;
            else
                costMat[i][j] = n;
        }

    FloydWarshall();

    cout << "\nMatrix for shortest distance between each pair of vertices :" << endl;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(costMat[i][j] >= 1000)
                cout << "i" << " ";
            else
                cout << costMat[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
