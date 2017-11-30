#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;

struct directed_graph {
	unordered_map< int, vector< int > > _adjacency_list;

	void add_edge(int u, int v) {

	}

	vector< int > & get_edges(int u) {

	}
};

struct kosaraju
{
	directed_graph* _graph;
	kosaraju(directed_graph& graph) {
		_graph = &graph;
	}
	int get_scc(int u) {
		return 0;
	}
};

struct expression
{
	vector< pair< int, int > > _clauses;
	void add_clause(int p, int q) {
		_clauses.push_back(make_pair(p, q));
	}
};

ostream& operator<< (ostream& os, expression const& expr) {

}

void read_sat(char* filename, directed_graph& graph) {
	ifstream input(filename);
	string line;
	size_t num;
	getline(input, line);
	istringstream iss(line);
	iss >> num;
	for (size_t i = 0; i < num; i++)
	{
		getline(input, line);
		istringstream iss(line);
		int literal1;
		int literal2;
		iss >> literal1;
		iss >> literal2;
	}
}
