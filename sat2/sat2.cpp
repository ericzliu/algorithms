#include "sat2.hpp"
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

void directed_graph::add_edge(int u, int v) {
  _adjacency_list[u].push_back(v);
}

vector< int > & directed_graph::get_edges(int u) {
  if (_adjacency_list.count(u) > 0)
  {
    return _adjacency_list[u];
  }
  return _empty_vec;
}

directed_graph directed_graph::transpose() {
  directed_graph digraph;
  for (auto& u : _adjacency_list) {
    for (auto& v : u.second) {
      digraph.add_edge(v, u.first);
    }
  }
  return digraph;
}

kosaraju::kosaraju(directed_graph& graph) {
  vector< int > visit_ordre;
  unordered_set< int > visited;
  for (auto u = graph.begin_iterate(); u != graph.end_iterate(); u++) {
    if (visited.count(u->first) == 0)
    {
      dfs(graph, u->first, visited, visit_ordre);
    }
  }
  auto trans_graph = graph.transpose();
  unsigned scc = 0;
  unordered_set< int > visited2;
  for (auto u = rbegin(visit_ordre); u != rend(visit_ordre); u++) {
    if (visited2.count(*u) == 0)
    {
      dfs2(trans_graph, *u, ++scc, visited2);
    }
  }
}

void kosaraju::dfs(directed_graph& graph, int u, unordered_set< int > & visited, vector< int > & visit_ordre) {
  stack< int > s;
  s.push(u);
  visited.insert(u);
  while (!s.empty())
  {
    auto u = s.top();
    auto& out_edges = graph.get_edges(u);
    bool finished = true;
    for (auto v : out_edges) {
      if (visited.count(v) == 0) {
        s.push(v);
        visited.insert(v);
        finished = false;
      }
    }
    if (finished) {
      s.pop();
      visit_ordre.push_back(u);
    }
  }
}

void kosaraju::dfs2(directed_graph& graph, int s, int num, unordered_set< int > & visited) {
  stack< int > pile;
  pile.push(s);
  visited.insert(s);
  _scc[s] = num;
  while (!pile.empty())
  {
    auto u = pile.top();
    pile.pop();
    auto& out_edges = graph.get_edges(u);
    for (auto v : out_edges) {
      if (visited.count(v) == 0) {
        pile.push(v);
        visited.insert(v);
        _scc[v] = num;
      }
    }
  }
}

int kosaraju::get_scc(int u) {
  if (_scc.count(u) > 0) {
    return _scc[u];
  }
  return 0;
}

ostream& operator<< (ostream& os, pair<int, int> const& clause) {
  os << "(";
  auto literal = clause.first;
  if (literal < 0)
  {
    os << "~";
  }
  os << abs(literal);
  os << "v";
  auto literal2 = clause.second;
  if (literal2 < 0)
  {
    os << "~";
  }
  os << abs(literal2);
  os << ")";
  return os;
}

ostream& operator<< (ostream& os, expression const& expr) {
  auto& clauses = expr._clauses;
  if (!clauses.empty())
  {
    os << clauses.front();
    auto length = clauses.size();
    for (size_t i = 1; i < length; i++)
    {
      os << "^";
      os << clauses[i];
    }
  }
  return os;
}

expression read_sat(char* filename) {
  ifstream input(filename);
  string line;
  size_t num;
  getline(input, line);
  istringstream iss(line);
  iss >> num;
  expression expr;
  for (size_t i = 0; i < num; i++)
  {
    getline(input, line);
    istringstream iss(line);
    int literal1;
    int literal2;
    iss >> literal1;
    iss >> literal2;
    expr.add_clause(literal1, literal2);
  }
  return expr;
}

bool solvable(expression & expr) {
  directed_graph digraph;
  for (auto c = expr.begin_iterate(); c != expr.end_iterate(); c++) {
    auto p = c->first;
    auto q = c->second;
    digraph.add_edge(-p, q);
    digraph.add_edge(-q, p);
  }
  kosaraju scc(digraph);
  for (auto i = digraph.begin_iterate(); i != digraph.end_iterate(); i++)
  {
    auto u = i->first;
    if (scc.get_scc(u) == scc.get_scc(-u) && scc.get_scc(u) != 0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc != 2)
  {
    exit(1);
  }
  auto expr = read_sat(argv[1]);
  cout << solvable(expr) << endl;
  return 0;
}
