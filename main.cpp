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


int main()
{
	stringFAM_example();

	return 0;
}
