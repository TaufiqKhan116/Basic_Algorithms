#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
BFS :
        Breadth-first search (BFS) is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root
    (or some arbitrary node of a graph, sometimes referred to as a 'search key'[1]), and explores all of the neighbor nodes at the present
    depth prior to moving on to the nodes at the next depth level.

Visited node :
        In a graph or tree, if a node is reached but its adjacent nodes are not yet reached then the node is said to be visited.

Explored node :
        In a graph or tree, if all adjacent nodes of a node is visited, then the node is said to be explored.

Rules :
        1. After selecting a vertex to explore, all of its adjacent nodes are must be visited first before any other node exploration.
        2. Node for exploration must choose from queue front only.

Procedure :
        Initially, we have to mark the initial (arbitrary) vertex as visited and push it into a queue. It is pushed into that queue to be explored a little bit
    later.
        Next, we have to pop a vertex (For first time it will be the initial vertex) out from the queue front, explore it aka visit all of its adjacent
    nodes, mark all of them visited and push all of them to queue to explore later.
        Then, we have to repeat previous step until the queue is empty aka all nodes are explored.

Sample input :
0
0 1
0 3
1 0
1 2
1 4
1 6
1 7
2 1
2 3
2 8
2 9
3 0
3 2
4 1
4 5
4 6
5 4
6 1
6 4
6 7
7 1
7 4
7 6
8 2
9 2
-1 -1

Sample output :
0 1 3 2 4 6 7 8 9 5

Reference :
        Youtube => https://youtu.be/pcKY4hjDrxk
        Book => Fundamentals of Computer Algorithms by Sartaj Sahni, page-341
        Wikipidea => https://en.wikipedia.org/wiki/Breadth-first_search
*/

int adjMat[10][10] = {0}; //Initializing adjacent matrix
int visited[10] = {0}; //Initializing visited array
queue<int> q; //Queue for visited nodes
vector<int> v; //Output vector

void BFS(int start) {

    int u;

    //Initial step
    visited[start] = 1; //Initial node visited
    q.push(start); //Pushing visited node into queue

    //Repetitive step
    while(!q.empty()) {
        u = q.front(); //Fetching a visited node from queue to explore

        for(int i = 0; i < 10; i++) { //Exploring the fetched visited node
            if(adjMat[u][i] == 1 && visited[i] == 0) { //Visiting adjacent nodes of the fetched node
                visited[i] = 1;//Marking new nodes as visited
                q.push(i); //Pushing newly visited nodes into queue for later exploration
            }
        }
        v.push_back(u); //Adding the explored node into output vector
        q.pop(); //Pop the explored node from queue front
    }
}

int main() {

    int i, j, start;

    cout << "Enter start vertex and edges (edge1 edge2), Enter -1 -1 to terminate:" << endl;
    cin >> start;

    do {
        cin >> i;
        cin >> j;
        if(i >= 0) {
            adjMat[i][j] = 1;
        }
    } while(i >= 0);

    BFS(start);

    cout << "\nBFS : \n";
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    return 0;
}
