// tsp_heuristic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

struct city
{
	double _x;
	double _y;
	city() : _x(0), _y(0) {

	}
};

vector<city> read_cities(char* filename) {
	ifstream input(filename);
	unsigned city_num = 0;
	string line;
	if (getline(input, line)) {
		istringstream iss(line);
		iss >> city_num;
	}
	vector< city > cities;
	unsigned ind = 0;
	while (getline(input, line) && ind < city_num) {
		city c;
		istringstream iss(line);
		unsigned id;
		iss >> id;
		iss >> c._x;
		iss >> c._y;
		cities.push_back(c);
	}
	return cities;
}

double distance(city& c1, city& c2) {
	auto dx = c1._x - c2._x;
	auto dy = c1._y - c2._y;
	return sqrt(dx * dx + dy * dy);
}

void tsp_nearest_neighbor(vector< city > & cities, list<city>& perm) {
	list<city> unvisited(begin(cities), end(cities));
	perm.insert(perm.end(), *unvisited.begin());
	unvisited.erase(unvisited.begin());
	city* current = &perm.front();
	while (!unvisited.empty())
	{
		double min = numeric_limits<double>::max();
		auto where = unvisited.end();
		for (auto loc = unvisited.begin(); loc != unvisited.end(); ++loc)
		{
			auto dist = distance(*loc, *current);
			if (dist < min) // if there is a tie, then the first one will be taken
			{
				min = dist;
				where = loc;
			}
		}
		perm.insert(perm.end(), *where);
		unvisited.erase(where);
		current = &perm.back();
	}
}

double total_distance(list< city > & perm) {
	double total = 0.0;
	list< city >::iterator prev = perm.end();
	advance(prev, -1);
	for (auto loc = perm.begin(); loc != perm.end(); loc++)
	{
		total += distance(*loc, *prev);
		prev = loc;
	}
	return total;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		exit(1);
	}
	auto cities = read_cities(argv[1]);
	list< city > perm;
	tsp_nearest_neighbor(cities, perm);
	double total = total_distance(perm);
	cout << setprecision(15) << total << endl;
    return 0;
}

