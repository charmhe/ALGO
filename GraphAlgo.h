//
// Created by Charles on 2019-04-03.
//

#ifndef ALGO_GRAPHALGO_H
#define ALGO_GRAPHALGO_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Graph
{
public:
	vector<vector <int>> v;         //using int 2*d matrix to create
	vector<bool> aux;               //for DFS/BFS/ etc...
	vector<vector <double>> weight; //for Single-Source Shortest-Paths/ etc...
	vector<double> d;               //d[v] is an upper bound on the weight of a shortest path from source s to v.
	vector<double> pi;              //π[v] is used to represent the shortest paths.
	Graph( ) = default;
	Graph (double **arr, int size);
	void DFS( );
	void Single_Source_Shortest_Paths( );
	bool Bellman_Ford(int s);// s is the start point.
	bool Dijkstra(int s);

	//int** getMatrix( ); //get the matrix version of v.//TODO:

	void print()
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

Graph::Graph (double **arr, int size)
{
	int size_row = size;
	int size_col = size;

	for(int i = 0; i < size_row; i++)
	{
		vector <int> temp (0);
		v.push_back(temp);
		vector <double> temp_2 (0);
		weight.push_back(temp_2);
		for(int j = 0; j < size_col; j++)
		{
			if (arr[i][j] != 0){
				v[i].push_back(j);
				weight[i].push_back(arr[i][j]);
			}
		}
	}
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
		pi.push_back(INFINITY);
	}
	d[s] = 0;
}
//CLRS p649
void Graph::Relaxation (int u, int v)
{
	if(d[v] < d[u] + weight[u][v])
	{
		d[v] = d[u] + weight[u][v];
		pi[v] = u;
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

void Graph::printPi()
{
	unsigned long len_Pi = pi.size();
	for (int i = 0; i < len_Pi; i++)
	{
		cout << " " << pi[i];
	}
	cout << endl;
}

void Graph::printWeight()
{
	unsigned long len_w = weight.size();
	for (int i = 0; i < len_w; i++)
	{
		unsigned long len_E = weight[i].size();
		for(int j = 0; j < len_E; j++)
		{
			cout << " " << weight[i][j];
		}
		cout << endl;
	}
}

bool Graph::Dijkstra(int s)// s is the start point.
{
	Initialization(s);

	vector<int> S;
	vector<vector <int>>  Q = v;
	while(Q.size()!=0)
	{
		
	}

}

#endif //ALGO_GRAPHALGO_H


























































