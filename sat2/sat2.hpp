#pragma once

#ifdef  SAT2_EXPORTS 
/*Enabled as "export" while compiling the dll project*/
#define SAT2_API __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define SAT2_API __declspec(dllimport)  
#endif

#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cmath>
using namespace std;

struct SAT2_API directed_graph {
  vector<int> _empty_vec;
  unordered_map< int, vector< int > > _adjacency_list;

  auto begin_iterate() {
    return begin(_adjacency_list);
  }

  auto end_iterate() {
    return begin(_adjacency_list);
  }

  void add_edge(int u, int v);

  vector< int > & get_edges(int u);

  directed_graph transpose();
};

struct SAT2_API kosaraju
{
  unordered_map< int, int > _scc;

  kosaraju(directed_graph& graph);

  void dfs(directed_graph& graph, int u, unordered_set< int > & visited, vector< int > & visit_ordre);

  void dfs2(directed_graph& graph, int s, int num, unordered_set< int > & visited);

  int get_scc(int u);
};

struct SAT2_API expression
{
  vector< pair< int, int > > _clauses;
  void add_clause(int p, int q) {
    _clauses.push_back(make_pair(p, q));
  }
  auto begin_iterate() {
    return _clauses.begin();
  }
  auto end_iterate() {
    return _clauses.end();
  }
};

SAT2_API ostream& operator<< (ostream& os, pair<int, int> const& clause);

SAT2_API ostream& operator<< (ostream& os, expression const& expr);

SAT2_API expression read_sat(char* filename);

SAT2_API bool solvable(expression & expr);

