#pragma once
#include <vector>
using namespace std;

#ifdef  MYDLL_EXPORTS 
/*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

struct DLLEXPORT node
{
   node()
   {
      x = 0;
      y = 0;
   }

   node(double _x, double _y)
   {
      x = _x;
      y = _y;
   }

   double x;
   double y;
};

struct DLLEXPORT weight
{
   vector< vector< double > > _weights;
   weight(vector< node > & nodes);
   double get_weight(int i, int j);
};

unsigned
DLLEXPORT upow(unsigned base, unsigned exponent);

unsigned 
DLLEXPORT comb_size(signed comb);

struct DLLEXPORT comb_iterator
{
   unsigned _limit;
   unsigned _comb;
   unsigned _loc;
   unsigned _size;
   unsigned _ind;
   comb_iterator(unsigned limit, unsigned comb);
   bool has_next();
   unsigned next();
};

unsigned DLLEXPORT comb_remove(unsigned comb, unsigned elem);

bool DLLEXPORT comb_test(unsigned comb, unsigned elem);

vector< node > DLLEXPORT read_tsp(const char* filename);

struct DLLEXPORT combs
{
   combs(unsigned elem_num);
   vector<unsigned>& get_combs(unsigned size);
   vector< vector < unsigned > > _combs;
};

double DLLEXPORT tsp_dp(vector< node > & nodes);
