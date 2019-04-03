//
// Created by Charles on 2019-04-03.
//

#ifndef ALGO_DP_H
#define ALGO_DP_H

#include <iostream>
#include <cmath>
#include <map>

using namespace std;

//CLRS v3, p363.
double CUT_ROD_naive(map<int, int> p, unsigned long n)//p is the price table, n = the maximum length we can have.
{
	if( n==0 ) return 0;
	double q = -INFINITY;
	for(int i = 1; i <= n; i++)//Here is the point: in CLRS, it's said: for i = 1 to n.
	{
		q = max<double>(q, p[i] + CUT_ROD_naive(p, n-i));
	}
	return q;
}


#endif //ALGO_DP_H
