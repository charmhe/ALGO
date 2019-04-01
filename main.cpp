/*
 * Some algorithms in CPRS.
 *
 * @author M.H.
 * @date 19-3-31
 *
 * */

#include <iostream>
#include "heap.h"
#include "queue.h"

using namespace std;

void heap_example()
{
	//heap<double> h = heap<double >({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});//example from CPRS v3 p155.
	queue<double> h = queue<double >({4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
	//Why we must apply max(2) here but max(1) will be wrong?
	cout<<h.pop( )<<endl;
	cout<<h.pop( )<<endl;
	h.insert(32);
//	cout<<h.pop( )<<endl;
	h.print();
}

int main()
{
	heap_example();

	return 0;
}
