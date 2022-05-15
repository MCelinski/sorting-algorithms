#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>
#include<string>
//chrono do mierzenia casu
using namespace std::chrono;
using namespace std;

//global variables for the algorithm functions
const int MAX = 1e6;
int id[MAX], nodes, edges;
pair <long long, pair<int, int> > p[MAX];

void initialize()
{
    for (int i = 0; i < MAX; ++i)
        id[i] = i;
}

int root(int x)
{
    while (id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void union1(int x, int y)
{
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

//funkcja kruskala
long long kruskal(pair<long long, pair<int, int> > p[])
{
    int x, y;
    long long cost, minimumCost = 0;

    cout << "Minimum Spanning Tree (MST): "<<endl;
    for (int i = 0; i < edges; ++i)
    {
        // Selecting edges one by one in increasing order from the beginning Krawdedzie jeden po drugim i
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;

        //sprawdzenie czy wybrana krwedz tworzy cykl
        if (root(x) != root(y))
        {
            minimumCost += cost;
            union1(x, y);
            cout << "(" << x << "," << y << ")";
        }
    }
    return minimumCost;
}

int main()
{
    FILE *times;
    times = fopen("times.txt","w");

    string NAME = "10.txt";
    int x, y;
    long long weight, cost, minimumCost;


    initialize();

    ifstream infile;
    infile.open(NAME);

    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }



    //start mierzenia czau
    auto start = high_resolution_clock::now();

    //wczytywanie liczb z pliku
    infile >> nodes;

    for (int i = 0; !infile.eof(); ++i) {
        //wczytanie wez³ow oraz ich wagi
        infile >> x >> y >> weight;

        if (weight == 1073741824) {
            cout << "I see there is no direct route between " << x << " and " << y << endl;
            edges += 1;
        }

        //mtworzenie par
        else {
            p[i] = make_pair(weight, make_pair(x, y));
           //licznik krawedzi
            edges += 1;
        }
    }
    // sortowanie krawedzi malejaco
    sort(p, p + edges);
    minimumCost = kruskal(p);

    auto stop = high_resolution_clock::now();


    auto duration = duration_cast<milliseconds>(stop - start);
    int time= duration.count();
    cout << endl << "Total Executiontime: " << duration.count() << "ms" << endl;

    cout << "Minimum Cost = " << minimumCost << endl;
    infile.close();

    return 0;

    }



