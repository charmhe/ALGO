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
	vector<double> s(n, -INFINITY);//Add this if you wanna trace back.
	r[0] = 0;
	double q;
	for (int j = 1; j<=n; j++)
	{
		q = -INFINITY;
		for (int i = 1; i<=j; i++)//key point. from 1 to j, not to n.
		{
			//q = max<double>(q, p[i] + r[j-i]);//**
			/*
			 * This is the replacement of line ** if you wanna get trace-back.
			 */
			 if(q < p[i]+r[j-i])
			 {
				 q = p[i] + r[j - i];
				 s[j] = i;
			 }

		} r[j] = q;
	}
	for(int i = 0; i<n; i++)cout<<s[n]<<" ";
	return r[n];
	//return r[n] & s[n]; //This is the replacement of line ** if you wanna get trace-back.
}

/*
 * PS: The Pseudo-code for LCS: Longest Common Subsequence
 * Comments: Consider rewrite it in two array but not an 2*2 array.
1. for i from 0 to n
2.     L[i, 0] ← 0,
3. for j from 0 to m
4.     L[0, j] ← 0,
5. for i from 1 to n
6.     for j from 1 to m
7.         if ai = bj
8.             L(i, j) ← 1 + L(i − 1, j − 1)
9.         else
10.            L(i, j) ← max{L(i − 1, j), L(i, j − 1)}
 *
 *
 * Exercises listed by Kaizhong Zhang:
 * - 1. Write the backtracking pseudo-code for the LCS problem.
 * - 2. In the textbook (pp. 394), in addition to an array c[i, j] (the same as our L[i, j]),
 *      an array b[i, j] is used to assist the backtracking. Is it necessary?
 * - 3. Do we need another array for backtracking?
 * - 4. The time and space complexity of the DP for LCS.
 *
 * */

#endif //ALGO_RODCUT_DP_H

