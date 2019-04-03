//
// Created by Charles.M.H on 2019-04-01.
//

#ifndef ALGO_STRING_H
#define ALGO_STRING_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Naive String Matcher.
void Naive_String_Matcher ( string T, string P )
{
	unsigned long n = T.size();
	unsigned long m = P.size();
	cout << "T:" << T << endl << "P:" << P << endl;

	/*
	 * O(Naive) = (n-m+1)*m;
	 */
	for ( int i = 0; i < n - m + 1; i++ )
	{
		for ( int j = i; j < i + m; j++ )
		{
			if ( T[j] == P[j - i] )
			{
				if ( j >= i )
					cout << "success: T[" << j << "] = P[" << j - i << "] = " << T[j]
					     << ", length = " << j - i + 1 << endl;
				if ( j == i + m - 1 )
				{
					cout << "Complete match: The whole P matches T, starts at T[" << i + 1 << "]" << endl;
				}
			}
		}
	}
	cout << "END" << endl;
}

//string with FINITE-AUTOMATON-MATCHER
class string_FAM
{
public:
	string s; //store the source string;
	vector<char> table;
	int len_alphabet;
	vector<vector<int>> states;  //to store the state transit function
	string_FAM ()
	{ };

	string_FAM ( string S ) : s(S)
	{
		alphabetBuilder();
		len_alphabet = ( int ) table.size();
	}

//CLRS: p1001. COMPUTE-TRANSITION-FUNCTION()
//TODO: why it's always not correct?
	void TRANSITION_FUNCTION_Builder ();

	void print_TRANSITION_FUNCTION ()
	{
		cout << "The source string: " << s << endl;
		int size = ( int ) states.size();
		int len = s.length();
		cout << "n:";
		for ( int i = 0; i <= len; i++ )
			cout << i << " ";
		cout << "\n";
		for ( int j = 0; j < len_alphabet; j++ )
		{
			cout << table[j] << " ";
			for ( int i = 0; i < size; i++ )
			{
				cout << states[i][j] << " ";
			}
			cout << "\n";
		}
	}


	void testPostfix ( string s, string t, int i )
	{
		cout << isPostfix(s, t, i) << endl;
	}

private:
	void alphabetBuilder ()
	{
		bool add = true;
		int len = s.length();

		for ( int i = 0; i < len; i++ )
		{
			char temp = s[i];
			int len_alpha = ( int ) table.size(); //Keep in mind: here the size of vector may change so you cannot use this.len_alphabet
			for ( int j = 0; j < len_alpha; j++ )
			{
				if ( temp == table[j] )
				{
					add = false;
					break;
				}
			}
			if ( add )table.push_back(temp);
			else add = true;
		}
	}

	bool isPostfix ( string S, string P, int i )//ver1.0, with i: check whether S is P's postfix, with i.
	{
		if ( i == 0 ) return false;  //Key point
		for ( int j = 1; j <= i; j++ )//No need to check '\0', so start at 1.
		{
			if ( S[S.size() - j] != P[P.size() - j] )
				return false;
		}
		return true;
	}

	bool isPrefix ( string S, string P, int i )//ver1.0, with i: check whether S is P's postfix, with i.
	{
		if ( i == 0 ) return false;  //Key point
		for ( int j = 0; j < i; j++ )//No need to check '\0', so start at 1.
		{
			if ( S[j] != P[j] )
				return false;
		}
		return true;
	}
};

//CLRS: p1001. COMPUTE-TRANSITION-FUNCTION()
//TODO: why it's always not correct?
void string_FAM::TRANSITION_FUNCTION_Builder ()
{
	vector<int> v(table.size() + 1, 0);//for robustness
	states.resize(s.length() + 1, v);
	int m = static_cast<int>(s.length());

	int k = 0;
	string Pk, Pqa;
	for ( int q = 0; q < m + 1; q++ )
	{
		for ( int j = 0; j < len_alphabet; j++ )
		{
			k = m + 1 > q + 2 ? q + 2 : m + 1;  //k = min (m + 1; q + 2)

			while ( true )
			{
				k = k - 1;
//				Pk = s.substr(s.size() - k,
//				              ( unsigned long ) k); //Pk is postfix, like "think", k = 2, then is "nk". for str.substr(a, b), a is start point, k is length
//				Pqa = s.substr(s.size() - q, ( unsigned long ) q); //Why q is less 1 than k? think about it!

				Pk = s.substr(0,
				              ( unsigned long ) k); //Pk is postfix, like "think", k = 2, then is "nk". for str.substr(a, b), a is start point, k is length
				Pqa = s.substr(0,
				               ( unsigned long ) q); //Why q is less 1 than k? think about it!
				Pqa += table[j];

				if ( isPostfix(Pk, Pqa, k))
					states[q][j] = k;//TODO: this is not true, I modified a little bit, but it works. Don't know why.
				else break;

//				if ( !isPrefix(Pk, Pqa, k)) break;//TODO: this is not true, I modified a little bit, but it works. Don't know why.
//				else states[q][j] = k;
			}

		}
	}
}

//KMP's algorithm
class string_KMP
{
public:
	string T;
	int m;
	vector<int> pi;
	string_KMP () { };
	string_KMP ( string S ) :T ( S ), m ( S.length ( ) ) { pi.resize ( m + 1, 0 ); } //The index started at 1.;

	void COMPUTE_PREFIX_FUNCTION ( );
	void COMPUTE_PREFIX_FUNCTION_2 ( );
	void KMP_MATCHER ( string_KMP P );
	void KMP_MATCHER_PrefixIncluded ( string_KMP P );
	void printPi ( )
	{
		cout << "This next( ) is:\n";

		int size = pi.size ( );
		int len = T.size ( );

		int wid = 3;

		//print i = 1 2 3 4 5...
		for ( int i = 0; i < len; i++ ) {
			cout.setf ( ios::left );
			cout.width ( wid );
			cout << i + 1 << " ";
		}
		cout << "\n";
		//print characters
		for ( int i = 0; i < len; i++ ) {
			cout.setf ( ios::left );
			cout.width ( wid );
			cout << T[i] << " ";
		}
		cout << "\n";
		//print p[i]
		for ( int i = 1; i < size; i++ ) {
			cout.setf ( ios::left );
			cout.width ( wid );
			cout << pi[i] << " ";
		}

		cout << "\n";

	}

};

//TODO: incorrect??? -- reason is!!! in CLRS, string start at 0.
//To build this.pi. CLRS p1006. Time: O(m)
void string_KMP::COMPUTE_PREFIX_FUNCTION ( )
{
	int k = 0;
	for (int q = 2; q <= m; q++) 		
	{
		while ( k > 0 && T[k] != T[q - 1] ) { k = pi[k]; }
		if ( T[k] == T[q - 1] ) { k = k + 1; }
		pi[q] = k;
	}
}

//To build this.pi. From Dr.Zhang's version
void string_KMP::COMPUTE_PREFIX_FUNCTION_2 ( )
{
	for ( int i = 2; i <= m; i++ ) {

		int q = pi[i - 1];

		while ( q > 0 && T[i - 1] != T[q+1 - 1] ) {q = pi[q];}
		if ( T[q + 1 - 1] == T[i - 1] ) { q = q + 1; }
		pi[i] = q;
	}
}

//CLRS p1005
void string_KMP::KMP_MATCHER ( string_KMP P )
{
	cout << "source string: \n" << T << endl << "matched string:\n" << P.T << endl;
	
	int n = m;//n = T.length
	int mm = P.m;//P.length
	P.COMPUTE_PREFIX_FUNCTION ( );
	int q = 0;
	for ( int i = 1; i <= n; i++ ) 		
	{
		while ( q > 0 && P.T[q + 1 - 1] != T[i - 1]) {
			q = P.pi[q];
		}
		if ( P.T[q + 1 - 1] == T[i - 1] )
		{
			q = q + 1;
		}
		if ( q == mm ) 			
		{
			cout << "Pattern occurs with shift " << i - mm << endl;
			q = P.pi[q];
		}
	}
}

//author: Mu.H
void string_KMP::KMP_MATCHER_PrefixIncluded ( string_KMP P )
{
	cout << "source string: \n" << T << endl << "match string:\n" << P.T << endl;

	int n = m;//n = T.length
	int mm = P.m;//P.length
	P.COMPUTE_PREFIX_FUNCTION ( );
	int q = 0;
	int maxQ = q;
	for ( int i = 1; i <= n; i++ ) {
		while ( q > 0 && P.T[q + 1 - 1] != T[i - 1] ) {
			q = P.pi[q];
			cout << "Partial pattern occurs with shift " << i - 1 - maxQ << endl;
			maxQ = q;
		}
		if ( P.T[q + 1 - 1] == T[i - 1] ) {
			q = q + 1;
			maxQ = q;
		}
		if ( q == mm ) {
			cout << "Pattern occurs with shift " << i - mm << endl;
			q = P.pi[q];
			maxQ = q;
		}
	}
}

#endif //ALGO_STRING_H
