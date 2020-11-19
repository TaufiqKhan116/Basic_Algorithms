#include <iostream>
#define N 8
#define INF INT_MAX

using namespace std;

/*
Multistage Graph :
        A Multistage graph is a directed graph in which the nodes can be divided into a set of stages such that all edges are from a stage to next stage
    only (In other words there is no edge between vertices of same stage and from a vertex of current stage to previous stage).

Explanation :
        We have to traverse the graph from last stage. The dist[i] array contains the distance from vertex i to last vertex(sink). The distance of last
    vertex(Sink) from itself is 0. About the rest of the vertices dist[i] will be the minimum distance of i to j and j to last vertex for all j between i
    and last vertex recursively.

Complexity :
        Time complexity of this algorithm is O(n^2).

Sample Output :
9

References :
        Youtube => https://youtu.be/9iE9Mj4m8jk
        Website => https://www.geeksforgeeks.org/multistage-graph-shortest-path/#:~:text=A%20Multistage%20graph%20is%20a,current%20stage%20to%20previous%20stage).
        Algorithm => https://www.geeksforgeeks.org/multistage-graph-shortest-path/#:~:text=A%20Multistage%20graph%20is%20a,current%20stage%20to%20previous%20stage).
*/

int dist[N] = {0};                                                  //Distance from vertex i to last(sink) vertex
int adjMat[N][N] = {{INF, 1, 2, 5, INF, INF, INF, INF},             //Adjacency matrix
                   {INF, INF, INF, INF, 4, 11, INF, INF},
                   {INF, INF, INF, INF, 9, 5, 16, INF},
                   {INF, INF, INF, INF, INF, INF, 2, INF},
                   {INF, INF, INF, INF, INF, INF, INF, 18},
                   {INF, INF, INF, INF, INF, INF, INF, 13},
                   {INF, INF, INF, INF, INF, INF, INF, 2}};

int shortestPathLength() {
    dist[N - 1] = 0;                                                //Distance from last vertex to itself is 0

    for(int i = N - 2; i >= 0; i--) {                               //For all other vertices traverse the adjacency matrix
        dist[i] = INF;
        for(int j = 0; j < N; j++) {
            if(adjMat[i][j] != INF) {
                dist[i] = min(dist[i], adjMat[i][j] + dist[j]);     //Minimum distance between calculated distance from i to sink till now and distance from i to sink through j where j is all vertices of stage between i and sink
            }
        }
    }
    return dist[0];                                                 //Distance from vertex 0 to sink vertex
}

int main()
{
    cout << "Shortest path length :" << endl;
    cout << shortestPathLength() << endl;
    return 0;
}
