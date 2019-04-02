//
// Created by Charles on 2019-04-01.
//

#ifndef ALGO_STRING_H
#define ALGO_STRING_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

class string_FAM //string with FINITE-AUTOMATON-MATCHER
{
public:
	string s; //store the source string;
	vector<char> alphabet;
	int len_alphabet;
	vector<vector<int>> states;  //to store the state transit function
	string_FAM ()
	{ };

	string_FAM ( string S ) : s(S)
	{
		alphabetBuilder();
		len_alphabet = ( int ) alphabet.size();
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
			cout << alphabet[j] << " ";
			for ( int i = 0; i < size; i++ )
			{
				cout << states[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void testPostfix(string s, string t, int i)
	{
		cout<<isPostfix(s, t, i)<<endl;
	}

private:
	void alphabetBuilder ()
	{
		bool add = true;
		int len = s.length();

		for ( int i = 0; i < len; i++ )
		{
			char temp = s[i];
			int len_alpha = ( int ) alphabet.size(); //Keep in mind: here the size of vector may change so you cannot use this.len_alphabet
			for ( int j = 0; j < len_alpha; j++ )
			{
				if ( temp == alphabet[j] )
				{
					add = false;
					break;
				}
			}
			if ( add )alphabet.push_back(temp);
			else add = true;
		}
	}

	bool isPostfix ( string S, string P, int i )//ver1.0, with i: check whether S is P's postfix, with i.
	{
		if (i == 0) return false;  //Key point
		for ( int j = 0; j <= i; j++ )//No need to check '\0', so start at 1.
		{
			if ( S[S.size() - j] != P[P.size() - j] )
				return false;
		}
		return true;
	}

	bool isPrefix ( string S, string P, int i )//ver1.0, with i: check whether S is P's postfix, with i.
	{
		if (i == 0) return false;  //Key point
		for ( int j = 0; j < i; j++ )//No need to check '\0', so start at 1.
		{
			if ( S[j] != P[j] )
				return false;
		}
		return true;
	}
};

void string_FAM::TRANSITION_FUNCTION_Builder ()
{
	int m = s.length();
	vector<int> v(len_alphabet + 1, 0);
	states.resize(m + 1, v);

	int k = 0;
	string Pk, Pqa;
	for ( int q = 0; q < m; q++ )
	{
		for ( int j = 0; j < len_alphabet; j++ )
		{
			k = m + 1 > q + 2 ? q + 2 : m + 1;  //k = min (m + 1; q + 2)

			while(1)
			{
				k = k - 1; if (k == 0 )break;
				Pk = s.substr(s.size() - k,
				              ( unsigned long ) k); //Pk is postfix, like "think", k = 2, then is "nk". for str.substr(a, b), a is start point, k is length
				Pqa = s.substr(s.size() - q, q); //Why q is less 1 than k? think about it!
				string temp = Pqa;
				Pqa = Pqa + alphabet[j];

				if(!isPostfix(Pk, Pqa, k)) break;
			}
			states[q][j] = k;
		}
	}
}


#endif //ALGO_STRING_H
