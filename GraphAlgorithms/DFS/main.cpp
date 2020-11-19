#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
DFS :
        Depth-first search (DFS) is an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node
    (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking.

Procedure :
        Initially, we have to take an initial(arbitrary) vertex and mark it visited.
        Then, we have to recursively go to all of the adjacent nodes of initial vertex and visit them and same with all of their children with the condition that
    the adjacent node is not visited yet. If a process reaches to a vertex that has no adjacent node unvisited or no adjacent node at all, that thread of process
    ends there.

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

References :
        Youtube => https://youtu.be/pcKY4hjDrxk
        Book => Fundamentals of Computer Algorithms by Sartaj Sahni, page-344
        Wikipidea => https://en.wikipedia.org/wiki/Depth-first_search
*/

int adjMat[10][10] = {0}; //Initializing adjacent matrix
int visited[10] = {0}; //Initializing visited array
vector<int> v; //Output vector

void DFS(int start) {

    //Initial step
    visited[start] = 1; //Marking node as visited
    v.push_back(start); //Adding visited node to output vector

    //Repetitive backtracking step
    for(int i = 0; i < 10; i++) {
        if(adjMat[start][i] == 1 && visited[i] == 0) //Get adjacent node from adjacent matrix and if it is not visited apply DFS recursively
            DFS(i);
    }

}

int main()
{
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

    DFS(start);

    cout << "\nDFS : \n";
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    return 0;
}
