//
// Created by Charles on 2019-04-03.
//

#ifndef ALGO_RODCUT_DP_H
#define ALGO_RODCUT_DP_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

//CLRS v3, p363.
double CUT_ROD_naive ( map<int, int> p, unsigned long n )//p is the price table, n = the maximum length we can have.
{
	if ( n == 0 ) return 0;
	double q = -INFINITY;
	for ( int i = 1; i <= n; i++ )//Here is the point: in CLRS, it's said: for i = 1 to n.
	{
		q = max<double>(q, p[i] + CUT_ROD_naive(p, n - i));
	}
	return q;
}

//from CLRS ver3, p366, private method only for CUT_ROD_topdown
double CUT_ROD_AUX( map<int, int> p, unsigned long n, vector<double> r)
{
	double q;
	if(r[n] >=0)
		return r[n];
	if(n==0)q = 0;
	else
	{
		q = -INFINITY;
		for (int i = 1; i<=n; i++)
		{
			q = max<double>(q, p[i] + CUT_ROD_AUX(p, n - i, r));
		}
	}
	r[n] = q;

	return q;
}

//TODO: bug???
//from CLRS ver3, p365
double CUT_ROD_topdown ( map<int, int> p, unsigned long n )
{
	vector<double> r(n, -INFINITY);
	return CUT_ROD_AUX(p, n, r);
}

//CLRS p366
double CUT_ROD_bottomup ( map<int, int> p, unsigned long n )
{
	vector<double> r(n, -INFINITY);
	r[0] = 0;
	double q;
	for (int j = 1; j<=n; j++)
	{
		q = -INFINITY;
		for (int i = 1; i<=j; i++)//key point. from 1 to j, not to n.
		{
			q = max<double>(q, p[i] + r[j-i]);
		} r[j] = q;
	}
	return r[n];
}

#endif //ALGO_RODCUT_DP_H
