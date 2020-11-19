#include <iostream>
#define infinity 1000
#define size 6
#define numberOfEdges 9

using namespace std;

/*
Bellman-Ford Algorithm :
        The Bellman–Ford algorithm is an algorithm that computes shortest paths from a single source vertex to all of the other vertices in a weighted
    digraph. It is slower than Dijkstra's algorithm for the same problem, but more versatile, as it is capable of handling graphs in which some of the
    edge weights are negative numbers. Dijkstra's algorithm may or may not give correct solution for graphs with negative weighted edges but Bellman-Ford
    algorithm guarantees correctness.

Complexity :
        Time complexity, O(|E|.|V|) where |E| is number of edges and |V| is number of vertices. In other words, O(n^2).

Sample input :
0
0 1 6
0 2 4
0 3 5
1 4 -1
2 1 -2
2 4 3
3 2 -2
3 5 -1
4 5 3
-1 -1 -1

Sample output :
0 1 3 5 0 3

References :
        Youtube => https://youtu.be/KudAWAMiQog
        Youtube => https://youtu.be/FtN3BYH2Zes
        Wikipidea => https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
        Algorithm => https://youtu.be/KudAWAMiQog
*/

int costMat[size][size] = {0};
int edgeList[numberOfEdges][2] = {0};
int dist[size];

void bellmanFord(int source) {
    dist[source] = 0;

    for(int iteration = 0; iteration < size - 1; iteration++) {
        for(int i = 0; i < 9; i++) {
            int currentEdgeCost = costMat[edgeList[i][0]][edgeList[i][1]];
            int initialVertexOfCurrentEdge = edgeList[i][0];
            int terminalVertexOfCurrentEdge = edgeList[i][1];

            if(dist[terminalVertexOfCurrentEdge] > dist[initialVertexOfCurrentEdge] + currentEdgeCost) {
                dist[terminalVertexOfCurrentEdge] = dist[initialVertexOfCurrentEdge] + currentEdgeCost;
            }
        }
    }
}

int main()
{
    int i = 0, j = 0, w = 0, c = 0, source;

    for(int i = 0; i < 6; i++) {
        dist[i] = infinity;
    }


    cout << "Enter source and <initialVertex terminalVertex weight> (Enter -1 -1 -1 to terminate):" << endl;
    cin >> source;
    do {
        cin >> i;
        cin >> j;
        cin >> w;

        if(i >= 0 && j >= 0) {
            costMat[i][j] = w;
            edgeList[c][0] = i;
            edgeList[c][1] = j;
            c++;
        }

    } while(i >= 0);

    bellmanFord(source);

    cout << "\nShortest paths from " << source << "vertex is :" << endl;
    for(int i = 0; i < 6; i++)
        cout << dist[i] << " ";

    return 0;
}
