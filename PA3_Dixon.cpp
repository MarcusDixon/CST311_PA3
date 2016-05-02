/*
* Marcus Dixon
* CST 311
* Progamming Assignment 3
*/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

vector<unsigned > minDist(unsigned index, vector<unsigned> dist, vector<vector<unsigned > > table);
unsigned minIndex(vector<unsigned> dist, vector<unsigned> nodes);
vector<unsigned > initialize(vector<vector<unsigned > > table, unsigned node);
vector<vector<unsigned > > getTable();
void compute(vector<vector<unsigned > > table, unsigned node);
void print(vector<unsigned> dist);
void print(vector<vector<unsigned > > table);



int main()
{
 // used to pick node to start with
 unsigned node = 0;

 //get the matrix from a file
 vector<vector<unsigned > > table = getTable();

 cout << "Enter starting node number(starting with 0): ";
 cin >> node;

 //Djikstra’s algorithm
 compute(table, node);
}

//return a matrix from file
vector<vector<unsigned > > getTable()
{
	char fileName[100];  //file name
	ifstream file;
	string lines; 
	vector<vector<unsigned > > table;

	cout << "Enter a file name: ";
	cin >> fileName;

	file.open(fileName);

	while (getline(file, lines))
	{
		istringstream buffer(lines);

		vector<unsigned > num((istream_iterator<unsigned >(buffer)), istream_iterator<unsigned >());

		table.push_back(num);
	}
	
	//replace all 0's with INT_MAX function
	for (unsigned i = 0; i < table.size(); i++)
	{
		for (unsigned j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] == 0)
			{
				table[i][j] = INT_MAX;
			}
		}
	}
	
	return table;
}

//Djikstra’s algorithm
void compute(vector<vector<unsigned > > table, unsigned node)
{
	//this is N'
	vector<unsigned> nodes;
	nodes.push_back(node);

	vector<unsigned> dist = table[node];
	dist[node] = 0;

	print(dist);

	//STARTING LOOP
	
	for (unsigned i = 0; i < dist.size() - 1; i++)
	{
		unsigned index = 0;

		index = minIndex(dist, nodes);

		nodes.push_back(index);

		dist = minDist(index, dist, table);

		print(dist);
	}
	cout << "nodes in N': " << endl;
	print(nodes);
}

//not used
vector<unsigned > initialize(vector<vector<unsigned > > table, unsigned node)
{
	vector<unsigned> dist;

	for (unsigned i = 0; i < table.size(); i++)
	{
		if (table[node][i] == 0)
		{
			dist.push_back(INT_MAX);
		}
		else
		{
			dist.push_back(table[node][i]);
		}
	}
	dist[node] = 0;

	return dist;
}

//replaces with min distance
vector<unsigned > minDist(unsigned index, vector<unsigned> dist, vector<vector<unsigned > > table)
{
	for (unsigned i = 0; i < dist.size(); i++)
	{
		dist[i] = min(dist[i], dist[index] + table[index][i]);
	}

	return dist;
}

//returns the shortest index from the distance vector
unsigned minIndex(vector<unsigned> dist, vector<unsigned> nodes)
{
	unsigned	minNumb = INT_MAX,
				min_index;

	for (unsigned i = 0; i < dist.size(); i++)
	{
		if (dist[i] < minNumb)
		{
			vector<unsigned>::iterator it;
			it = find(nodes.begin(), nodes.end(), i);
			if (it != nodes.end())
			{

			}
			else
			{
				minNumb = dist[i];
				min_index = i;
			}
		}
	}
	return min_index;
}

//prints out one line of the table/distance
void print(vector<unsigned> dist)
{
	for (unsigned i = 0; i < dist.size(); i++)
	{
		cout << setw(4) << dist[i] << " ";
	}
	cout << endl;
}

//prints out a matrix
void print(vector<vector<unsigned > > table)
{
	for (unsigned n = 0; n < table.size(); n++)
	{
		for (unsigned m = 0; m < table[n].size(); m++)
		{
			cout << setw(4) << table[n][m] << " ";
		}
		cout << endl;
	}
	cout << endl;
}