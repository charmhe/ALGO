/*
 * Some algorithms in CPRS.
 *
 * @author M.H.
 * @date 19-3-31
 *
 * */

#include <iostream>
#include <string>
#include "heap.h"
#include "queue.h"
#include "stringAlgo.h"
#include "dp.h"

using namespace std;

void heap_example()
{
	heap<double> h = heap<double >({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});//example from CPRS v3 p155.
	h.print();
}

void queue_example()
{
	queue<double> h = queue<double >({4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
	//Why we must apply max(2) here but max(1) will be wrong?
	cout<<h.pop( )<<endl;
	cout<<h.pop( )<<endl;
	h.insert(32);
//	cout<<h.pop( )<<endl;
}

void stringAlgo_example()
{
	string A = "fuckyoyou";
	string B = "you";
	Naive_String_Matcher(A,B);
}

void stringFAM_example()
{
	string_FAM A = string_FAM("ababaca");
	A.TRANSITION_FUNCTION_Builder();
	A.print_TRANSITION_FUNCTION();
}

void stringKMP_example ( )
{
	string_KMP A = string_KMP ( "babbcabbabcbababbacbb" );
	A.KMP_MATCHER ( string_KMP ( "cb" ) );
	A.KMP_MATCHER ( string_KMP ( "ca" ) );
	A.KMP_MATCHER ( string_KMP ( "cccc" ) );
	//A.printPi( );
	system ( "pause" );
}

void dp_example()
{
	//test of CUT_ROD. Example from CLRS, p 360
	map<int,int> ROD; //the price table of this rod.
	ROD.insert (pair<int, int>(1, 1)); //a unit-long rod is $1.
	ROD.insert (pair<int, int>(2, 5));
	ROD.insert (pair<int, int>(3, 8));
	ROD.insert (pair<int, int>(4, 9));
	ROD.insert (pair<int, int>(5, 10));
	ROD.insert (pair<int, int>(6, 17));
	ROD.insert (pair<int, int>(7, 17));
	ROD.insert (pair<int, int>(8, 20));
	ROD.insert (pair<int, int>(9, 24));
	ROD.insert (pair<int, int>(10, 30));//10-long rod is 30, but sometimes we cannot get a 10m rod. So in CUT_ROD_naive you can specify the length.

	cout<<"The best price is: "<< CUT_ROD_naive(ROD, 9) <<endl;

}

int main()
{
	dp_example ();
	return 0;
}
