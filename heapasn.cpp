//
// author @Charles.H. For 3340 asn3.
//

#include "heapasn.h"

bool heap_ASN::in_heap ( int id )
{
	for(pair<int, double> p : arr)
	{
		if(p.first == id)
		{
			return true;
		}
	}
	return false;
}

double heap_ASN::min_key ()
{
	return arr[1].second;
}

int heap_ASN::min_id ()
{
	return arr[1].first;
}

double heap_ASN::key ( int id )
{
	if(in_heap(id))
		for(pair<int, double> p : arr)
		{
			if(p.first == id)
			{
				return p.second;
			}
		}
}

void heap_ASN::delete_min ()
{
//	cout << arr[size] << endl;
//	cout << arr[1] << endl;
	swap(1, size);
	arr.pop_back();
	size -= 1;
	min_heapify(1);
}

void heap_ASN::decrease_key ( int id, int new_key )
{
	for(int i = 1; i < arr.size(); i++)
	{
		pair<int, double> &p = arr[i];//this is the key point
		if(p.first == id && p.second > new_key)
		{
			//cout << "found" << endl;
			p.second = new_key;
			this->build_min_heap();
			return;
		}
	}
}

bool heap_ASN::isEmpty ()
{
	return ( this->arr ).size() == 1;
}

double heap_ASN::extractMin ()
{
	double min = this->min_id();
	this->delete_min();
	return min;
}

heap_ASN::heap_ASN(initializer_list<pair<int, double >> param)
{
	pair<int, double > ass(-1,-1);
	arr.push_back(ass);
	for(pair<int, double > ptr : param)
	{
		arr.push_back(ptr);
		size++;
	}
	build_min_heap();
}

heap_ASN::heap_ASN ( vector<pair<int, double >> param )
{
	pair<int, double > ass = pair<int, double >(-1,-1);
	arr.push_back(ass);
	for( int i = 1; i < param.size(); i++)
	{
		arr.push_back(param[i]);
		size++;
	}
	build_min_heap();
}

void heap_ASN::build_min_heap( )
{
	for ( unsigned int i = size/2; i >= 1; i-- )
	{
		//print(i);
		min_heapify(i);
	}
}

void heap_ASN::min_heapify ( unsigned int i )
{
	unsigned int l = left(i);
	unsigned int r = right(i);
	unsigned int smallest;
	if ( l <= size && arr[l].second < arr[i].second ) smallest = l;
	else smallest = i;
	if ( r <= size && arr[r].second < arr[smallest].second ) smallest = r;
	if ( smallest != i )
	{
		swap(i, smallest);
		min_heapify(smallest);
	}
}

void heap_ASN::swap(unsigned int i, unsigned int j)
{
	pair<int, double> temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void heap_ASN::print( )
{
	string os = "==========\n";
	int level = 1;
	int count = level;
	for(int i = 1; i <= size; i++)
	{
		auto ptr = arr[i];
		os+= "("; os += to_string(ptr.first); os+= " "; os += to_string(ptr.second) ; os += ")  ";
		count-=1;
		if(count == 0)
		{
			os+="\n";
			//avoiding to print unnecessary last branch
			//if(i!=size) for(count = 0; count < level; count++) os += "|       \\       ";
			os+="\n";
			level *= 2;
			count = level;
			continue;
		}
	}
	std::cout<<os<<std::endl;
}