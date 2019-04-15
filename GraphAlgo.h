//
// Created by Charles on 2019-03-10.
//

#ifndef ALGO_GRAPHALGO_H
#define ALGO_GRAPHALGO_H

#include <iostream> 
#include <cmath>
#include <vector>

#include "heap.h"

using namespace std;

class Graph
{
public:
	vector<vector <int>> v;         //using int 2*d matrix to create
	vector<bool> aux;               //for DFS/BFS/ etc...
	vector<vector <double>> weight; //for Single-Source Shortest-Paths/ etc...
	vector<double> d;               //d[v] is an upper bound on the weight of a shortest path from source s to v.
	vector<pair<int, double>> pi;              //π[v] is used to represent the shortest paths.
	vector<int> predecessor;        //predecessor is used in shortest map, to represent the shortest tree.
	Graph( ) = default;
	Graph(int size);
	Graph (double *arr, int size);
	void DFS( );
	void Single_Source_Shortest_Paths( );
	bool Bellman_Ford(int s);// s is the start point.
	void Dijkstra(int s);
	void relax(int from, int to, double weight);

	//int** getMatrix( ); //get the matrix version of v.//TODO:

	void print();
	void printTraceback();
	void printPi();
	void printWeight();

private:
	void DFS_aux (int i);
	/* Initialization & Relax of Single-Source Shortest-Paths. From Dr.Zhang's slides
	 * for Bellman_Ford,
	 */
	void Initialization (int s);
	void Relaxation (int u, int v);
};

Graph::Graph ( int size )
{
	vector <int> temp (0);

	for(int i = 0; i < size; i++)
	{
		v.push_back(temp);
	}


}

Graph::Graph (double *arr, int size)
{
	int size_row = size;
	int size_col = size;

	vector <int> temp (0);
	vector <double> temp_2 (0);

	for(int i = 0; i < size_row; i++)
	{
		v.push_back(temp);

		weight.push_back(temp_2);
		pi.emplace_back(i, INFINITY);
		for(int j = 0; j < size_col; j++)
		{
			if (*(arr + i* size + j) != 0){
				v[i].push_back(j);
				weight[i].push_back(*(arr + i* size + j));
			}
		}
	}
}

void Graph::print ()
{
	cout << "===========\n";
	for(int i = 0; i < v.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===========\n";
}

void Graph::printPi()
{
	cout << "The start point to the this following point's shortest distance is:" <<endl;
	cout << "===========\n";
	unsigned long len_Pi = pi.size();
	for (int i = 1; i < len_Pi; i++)
	{
		cout << " " << pi[i].second;
	}
	cout << endl;
	cout << "===========\n";
}

void Graph::printWeight()
{
	cout << "===========\n";
	unsigned long len_w = weight.size();
	for (int i = 0; i < len_w; i++)
	{
		unsigned long len_E = weight[i].size();
		cout << i << ": ";
		for(int j = 0; j < len_E; j++)
		{
			cout << " " << weight[i][j];
		}
		cout << endl;
	}
	cout << "===========\n";
}

void Graph::printTraceback()
{
	cout << "===========\n";
	unsigned long len_w = predecessor.size();
	for (int i = 1; i < len_w; i++)
	{
		if(predecessor[i] == -1) cout << i << " -> " << "STOP" << ";\n";
		else cout << i << " -> " << predecessor[i] << ";\n";
	}
	cout << "===========\n";
}

/*
 * The classical DFS algorithm
 *
 * An possible extended version:
 *
 * To build a DFS tree:
 *
 * Use DFS with following postwork:
 *     add edge (v,w) to T
 * */
void Graph::DFS( )
{
	aux.resize(v.size(), false); //set all visited[] = false;
	DFS_aux(0);
}

void Graph::DFS_aux (int i)
{
	aux[i] = true;
	//Pre - work here
	cout << " " << i;
	unsigned long size = v[i].size( );
	for(int iter = 0; iter < size; iter++)
	{
		int w = v[i][iter]; //For each vertex w adjacent to v do
		if(!aux[w])         //if not visited[w] then
		{
			DFS_aux(w);
			//Post - work here
		}
	}
}

void Graph::Single_Source_Shortest_Paths( )
{

}
//CLRS p648
void Graph::Initialization (int s)
{
	unsigned long len = v.size();
	for (int i = 0; i < len; i++)
	{
		d.push_back(INFINITY);
		predecessor.push_back(-1);
	}
	pi[s].second = 0;
}
//CLRS p649
void Graph::Relaxation (int u, int v)
{
	if(d[v] < d[u] + weight[u][v])
	{
		d[v] = d[u] + weight[u][v];
		pi[v].second = u;
	}
}

//TODO: Incorrect
//CLRS p651
bool Graph::Bellman_Ford(int s)// s is the start point.
{
	Initialization(s);
	unsigned long len_V = v.size();

	for (int i = 1; i < len_V - 1; i++)
	{
		unsigned long len_E = v[i].size();
		for(int j = 0; j < len_E; j++)
		{
			Relaxation(i, j);
		}
	}

	for (int i = 0; i < len_V; i++)
	{
		unsigned long len_E = v[i].size();
		for(int j = 0; j < len_E; j++)
		{
			if(d[j] > d[i] + weight[i][j])
				return false;
		}
	}

	return true;
}

void Graph::relax(int from, int to, double w){

	if (pi[to].second > pi[from].second + w)
	{
		pi[to].second = pi[from].second + w;
		predecessor[to] = from;
	}
}


void Graph::Dijkstra(int start)// s is the start point.
{
	Initialization(start);

	heap_ASN q = heap_ASN(pi);

	while (!q.isEmpty()) {
		int u = q.extractMin();
		int i = 0;
		for (auto itr = v[u].begin(); itr != v[u].end(); itr++) {
			relax(u, *itr, weight[u][i]);
			i+=1;
			q.decrease_key((*itr), pi[(*itr)].second);
		}
	}
}

#endif //ALGO_GRAPHALGO_H