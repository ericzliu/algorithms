#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "app.h"
using namespace std;

double infinity = numeric_limits<double>::max();

weight::weight(vector< node > & nodes)
{
   auto node_num = nodes.size();
   _weights = vector< vector< double > >(node_num, vector< double >(node_num, infinity));
   for (unsigned i = 0; i < node_num; i++)
   {
      _weights[i][i] = 0.0;
   }
   for (unsigned i = 0; i < node_num; i++)
   {
      for (unsigned j = i + 1; j < node_num; j++)
      {
         auto dx = (nodes[i].x - nodes[j].x);
         auto dy = (nodes[i].y - nodes[j].y);
         _weights[i][j] = sqrt(dx * dx + dy * dy);
      }
   }
   for (unsigned i = 0; i < node_num; i++)
   {
      for (unsigned j = 0; j < i; j++)
      {
         _weights[i][j] = _weights[j][i];
      }
   }
}

double weight::get_weight(int i, int j)
{
   return _weights[i][j];
}

unsigned upow(unsigned base, unsigned exponent)
{
   unsigned p = 1;
   for (unsigned i = 0; i < exponent; i++)
   {
      p = p * base;
   }
   return p;
}

unsigned comb_size(signed comb)
{
   signed size = 0;
   while (comb > 0)
   {
      if (comb & 1)
      {
         size += 1;
      }
      comb >>= 1;
   }
   return size;
}


comb_iterator::comb_iterator(unsigned limit, unsigned comb)
{
   _limit = limit;
   _comb = comb;
   _size = comb_size(comb);
   _ind = 0;
   _loc = 0;
}

bool comb_iterator::has_next()
{
   return _ind < _size && _loc < _limit;
}

unsigned comb_iterator::next()
{
   _ind += 1;
   for (unsigned l = _loc, m = 1 << l; _loc < _limit; m <<= 1, _loc += 1)
   {
      if (_comb & m)
      {
         auto v = _loc++;
         return v;
      }
   }
   throw runtime_error("iteration failure");
}

unsigned comb_remove(unsigned comb, unsigned elem)
{
   unsigned ret = comb;
   ret &= ~(1u << elem);
   return ret;
}

bool comb_test(unsigned comb, unsigned elem)
{
   return comb & (1u << elem);
}

vector< node > read_tsp(const char* filename)
{
   ifstream input(filename);
   string line;
   unsigned node_count = 0;
   if (getline(input, line))
   {
      istringstream iss(line);
      iss >> node_count;
   }
   vector< node > nodes(node_count);
   unsigned i = 0;
   while (getline(input, line))
   {
      istringstream iss(line);
      iss >> nodes[i].x;
      iss >> nodes[i].y;
      i += 1;
   }
   return nodes;
}

combs::combs(unsigned elem_num)
{
   _combs = vector< vector< unsigned > >(elem_num + 1, vector< unsigned >());
   auto p = upow(2, elem_num);
   for (auto i = 0u; i < p; i++)
   {
      auto size = comb_size(i);
      _combs[size].push_back(i);
   }
}

vector<unsigned>& combs::get_combs(unsigned size)
{
   return _combs[size];
}

double tsp_dp(vector< node > & nodes)
{
   if (nodes.empty() || nodes.size() == 1u)
   {
      return 0.0;
   }
   auto elem_num = nodes.size();
   weight weights(nodes);
   unordered_map<unsigned, vector<double> >* subset_dist_map = new unordered_map<unsigned, vector<double>>();
   unordered_map<unsigned, vector<double> >* subset_dist_map_new = new unordered_map<unsigned, vector<double>>();
   (*subset_dist_map)[1u] = vector<double>(elem_num, infinity);
   (*subset_dist_map)[1u][0u] = 0.0;
   combs all_combs(elem_num);
   for (unsigned cardi = 2; cardi <= elem_num; cardi++)
   {
      auto & subsets = all_combs.get_combs(cardi);
      for (unsigned subset : subsets)
      {
         if (!comb_test(subset, 0))
         {
            continue;
         }
         comb_iterator jiterator(elem_num, subset);
         while (jiterator.has_next())
         {
            unsigned j = jiterator.next();
            if (j == 0)
            {
               continue;
            }
            unsigned small_set = comb_remove(subset, j);
            if ((*subset_dist_map).count(small_set) == 0)
            {
               continue;
            }
            comb_iterator kiterator(elem_num, small_set);
            double min_dist = infinity;
            while (kiterator.has_next())
            {
               unsigned k = kiterator.next();
               auto sub = (*subset_dist_map)[small_set][k];
               if (sub != infinity)
               {
                  auto dist_new = sub + weights.get_weight(k, j);
                  if (dist_new < min_dist)
                  {
                     min_dist = dist_new;
                  }
               }
            }
            if (min_dist != infinity)
            {
               vector<double> & dists = (*subset_dist_map_new)[subset];
               if (dists.empty())
               {
                  dists = vector<double>(elem_num, infinity);
               }
               dists[j] = min_dist;
            }
         }
      }
      swap(subset_dist_map, subset_dist_map_new);
      subset_dist_map_new->clear();
   }
   auto& subsets = all_combs.get_combs(elem_num);
   auto& total = subsets[0];
   double min_tsp = infinity;
   for (unsigned node = 1; node < elem_num; node++)
   {
      auto const& dist = (*subset_dist_map)[total][node];
      if (dist < infinity)
      {
         auto dist_new = dist + weights.get_weight(node, 0);
         if (dist_new < min_tsp)
         {
            min_tsp = dist_new;
         }
      }
   }
   delete subset_dist_map;
   delete subset_dist_map_new;
   return min_tsp;
}

int main(int argc, char** argv) {
   if (argc != 2)
   {
      exit(1);
   }
   auto& graph = read_tsp(argv[1]);
   double tsp = tsp_dp(graph);
   cout << tsp << endl;
   return 0;
}
