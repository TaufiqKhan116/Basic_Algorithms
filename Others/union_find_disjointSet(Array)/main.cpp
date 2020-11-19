#include <iostream>

#define size 1000
#define LOOP(counter, init, fin) for(int counter = init; counter < fin; counter++)

using namespace std;

/*
Here basically Kruskal's algorithm is implemented
using Union Find Disjoint Set (UFDS) data structure.

Vertices are represented as indices of an array. And
parents are represented by array element. Negative array
element indicates the index to be a root and absolute value
of the array element indicates rank (How many vertices are
connected as children to this root.
i.e.
    arr[2] = 3  :=> 2's parent is 3
    arr[3] = -4 :=> 3 is a root and has 4 children
*/

class UFDS
{
    int arr[size];

  public :
    UFDS()
    {
        int i;
        LOOP(i, 0, size)
        {
            arr[i] = -1;
        }
    }

  private :
    int parent(int v) //Find parent of a vertex, initially null(-1)
    {
        if(arr[v] < 0)
            return v;
        return parent(arr[v]);
    }

  public :
    bool find(int u, int v) //Checks if parents of two vertices are same or not
    {
        return parent(u) == parent(v);
    }

    void unionSet(int u, int v) //Union two sets based upon rank and update the rank of parent
    {
        int parentOfU = parent(u);
        int parentOfV = parent(v);

        if(arr[parentOfU] <= arr[parentOfV])
        {
            int tmp = arr[parentOfV];
            arr[parentOfV] = parentOfU;
            arr[parentOfU] += tmp;
        }
        else
        {
            int tmp = arr[parentOfU];
            arr[parentOfU] = parentOfV;
            arr[parentOfV] += tmp;
        }
    }
};

typedef struct
{
    int u;
    int v;
    int weight;
    bool flag;

} Edge;

int main()
{
    Edge graph[9] = {{1, 3, 7, false}, {1, 2, 1, false}, {3, 4, 2, false}, {2, 4, 5, false}, {2, 5, 6, false}, {5, 7, 9, false}, {7, 8, 4, false}, {5, 6, 3, false}, {6, 8, 8, false}};
    UFDS ob;
    int i, j;

    LOOP(i, 0, 8)
    {
        LOOP(j, i + 1, 9)
        {
            if(graph[j].weight < graph[i].weight)
            {
                Edge tmp = graph[i];
                graph[i] = graph[j];
                graph[j] = tmp;
            }
        }
    }

    LOOP(i, 0, 9)
    {
        if( !ob.find(graph[i].u, graph[i].v) )
        {
            ob.unionSet(graph[i].u, graph[i].v);
            graph[i].flag = true;
        }
    }

    cout << "Weights of edges to make Minimum Cost Spanning Tree :" << endl;
    LOOP(i, 0, 9)
    {
        if(graph[i].flag)
            cout << graph[i].weight << endl;
    }
    return 0;
}
