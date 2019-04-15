/*
 * Some algorithms in CPRS.
 *
 * @author M.H.
 * @date 19-3-31
 *
 * */

#include <iostream>
#include <fstream>

#include "heap.h"
#include "queue.h"
#include "stringAlgo.h"
#include "rodcut_dp.h"
#include "GraphAlgo.h"
#include "heapasn.cpp"

#define SIZE 10

using namespace std;

void heap_example ()
{
	heap<double> h = heap<double>({ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 });//example from CPRS v3 p155.
	h.print();
}

void heap_ASN_example ()
{
//	heap_ASN h = heap_ASN({ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 });//example from CPRS v3 p155.
//	h.print();
//	h.decrease_key(3, 0);
//	h.print();
//	h.delete_min();
//	h.print();
//	cout << "--------" << endl;
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";
//
//	//cout << h.delete_min() << endl;
//	h.print();
//	cout << h.isEmpty() << endl;
}

void heap_ASN_pair_version_example()
{
	heap_ASN h = heap_ASN({ pair<int, double>(1, 1.33),
	                        pair<int, double>(2, 2.44),
	                        pair<int, double>(3, 9.68),
	                        pair<int, double>(4, 6.32),
	                        pair<int, double>(5, 2.17),
	                        pair<int, double>(6, 4.33),
	                        pair<int, double>(7, 0.33),
	                        pair<int, double>(8, 5.33),
	                        pair<int, double>(9, 7.33)});
	h.print();
	h.decrease_key(2, 1);
	h.print();
	h.delete_min();
	h.print();
	cout << "--------" << endl;
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
	cout << h.extractMin()<<" ";
//	cout << h.extractMin()<<" ";

	//cout << h.delete_min() << endl;
	cout << "\nafter operation:" << endl;
	h.print();
	cout << h.isEmpty() << endl;

};

void queue_example ()
{
	queue<double> h = queue<double>({ 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 });
	//Why we must apply max(2) here but max(1) will be wrong?
	cout << h.pop() << endl;
	cout << h.pop() << endl;
	h.insert(32);
//	cout<<h.pop( )<<endl;
}

void stringAlgo_example ()
{
	string A = "fuckyoyou";
	string B = "you";
	Naive_String_Matcher(A, B);
}

void stringFAM_example ()
{
	string_FAM A = string_FAM("ababaca");
	A.TRANSITION_FUNCTION_Builder();
	A.print_TRANSITION_FUNCTION();
}

void stringKMP_example ()
{
	string_KMP A = string_KMP("babbcabbabcbababbacbb");
	A.KMP_MATCHER(string_KMP("cb"));
	A.KMP_MATCHER(string_KMP("ca"));
	A.KMP_MATCHER(string_KMP("cccc"));
	//A.printPi( );
	system("pause");
}

void dp_ROD_CUT ()
{
	//test of CUT_ROD. Example from CLRS, p 360
	map<int, int> ROD; //the price table of this rod.
	/*ROD.insert(pair<int, int>(1, 1)); //a unit-long rod is $1.
	ROD.insert(pair<int, int>(2, 5));
	ROD.insert(pair<int, int>(3, 8));
	ROD.insert(pair<int, int>(4, 9));
	ROD.insert(pair<int, int>(5, 10));
	ROD.insert(pair<int, int>(6, 17));
	ROD.insert(pair<int, int>(7, 17));
	ROD.insert(pair<int, int>(8, 20));
	ROD.insert(pair<int, int>(9, 24));
	ROD.insert(pair<int, int>(10,
	                          30));*///10-long rod is 30, but sometimes we cannot get a 10m rod. So in CUT_ROD_naive you can specify the length.

	ROD.insert(pair<int, int>(1, 60)); //a unit-long rod is $1.
	ROD.insert(pair<int, int>(2, 100));
	ROD.insert(pair<int, int>(3, 120));


	cout << "The best price is: " << CUT_ROD_naive(ROD, 5) << endl;
	//cout << "The best price is: " << CUT_ROD_topdown(ROD, 5) << endl;
	cout << "The best price is: " << CUT_ROD_bottomup(ROD, 5) << endl;

}

void Graph_example ()
{
	//test of graph's instructor

	double **arr;
	arr = new double* [4];
	arr[0] = new double[4] {0,1,1,1};
	arr[1] = new double[4] {0,0,1,0};
	arr[2] = new double[4] {0,0,0,1};
	arr[3] = new double[4] {0,1,0,0};

	Graph g = Graph(arr, 4);
	g.print();

	//dfs

	g.DFS( );

}

//TODO: Incorrect
void Graph_BellmanFord_Algo ()
{
	//test of graph's instructor

	double **arr;
	arr = new double* [4];
	arr[0] = new double[4] {0,-4,1,2};
	arr[1] = new double[4] {-3,0,2,0};
	arr[2] = new double[4] {0,1,0,2};
	arr[3] = new double[4] {0,3,3,3};

	Graph g = Graph(arr, 4);
	g.print();

	//Bellman_Ford
	cout<< "The result of Bellman: " << g.Bellman_Ford(1) << endl;
	g.printPi();
	g.printWeight();

}

void Graph_Dijstra ()
{
	fstream file("../fdata.txt");

	int x, y, z;

	file >> x;

	double aux[SIZE][SIZE] = {0};

	while(!file.eof())
	{
		file >> x >> y >> z;
		aux[x][y] = z;
	}

	Graph g = Graph(*aux, SIZE);

	g.print();

	g.Dijkstra(9);
	g.printPi();
	g.printTraceback();
}


int main ()
{
	heap_ASN_pair_version_example();
	return 0;
}
