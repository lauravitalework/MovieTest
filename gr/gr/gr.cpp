#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "io.h" 
#include "sparser.h" 
#include "math.h"
#include "graph.h" 
#include <assert.h>
using namespace std;
using namespace ptl;

struct vector2
{
	double x, y;
};

double dis2(const vector2& a, const vector2& b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
const int NN = 1000;
double dr = 0.2;
class t_sta
{
	map<int, int> friends;
	double P[NN];
	double total;

public:

	void init(const string& name)
	{
		fill_n(P, NN, 0);
		total = 0;
	}
	void add_friend(int id, int t)
	{
		if (friends.find(id) == friends.end()) friends.insert(map<int, int>::value_type(id, 1));
		else friends[id] ++;
	}
	void gr(double r)
	{
		int i = int(r / dr);
		if (i >= NN)
		{
			//      cout << r << endl;
			return;
		}
		P[i] ++;
		total++;
	}
	double get_Pr(int i)
	{
		return P[i] / total;
	}

};

t_sta sta0;

void save_gr(vector<vector2>& loc)
{
	t_sta rand_sta;
	for (int i = 0; i < loc.size(); i++)
		for (int j = 0; j < i; j++)
			rand_sta.gr(sqrt(dis2(loc[i], loc[j])));

	ofstream file("gr.dat");
	for (int i = 0; i < NN; i++)
	{
		if (rand_sta.get_Pr(i))
		{
			double gr = sta0.get_Pr(i) / rand_sta.get_Pr(i);
			if (gr > 0.0001) file << i*dr << '\t' << gr << endl;
		}
	}

}

void update(vector<vector2>& users, int t)
{
	for (int i = 0; i < users.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			double d = sqrt(dis2(users[i], users[j]));
			sta0.gr(d);
		}
	}
}

int get_location(double x1, double y1, double x2, double y2, vector2& p)
{
	if (x1 == -1)
	{
		if (x2 == -1) return -1;
		p.x = x2;
		p.y = y2;
		return 0;
	}
	if (x2 == -1)
	{
		p.x = x1;
		p.y = y1;
		return 0;
	}
	p.x = (x1 + x2) / 2;
	p.y = (y1 + y2) / 2;
	return 0;
}

int main(int argc, char* argv[])
{
	vector<vector<double> > data;
	sscan_matrix(argv[1], data);

	dr = atof(argv[2]);
	vector<vector2> loc;
	for (int i = 0; i < data[0].size(); i++)
	{
		vector<vector2> users;
		for (int j = 1; j < data.size(); j += 4)
		{
			vector2 pos;
			double x1 = data[j][i], y1 = data[j + 1][i];
			double x2 = data[j + 2][i], y2 = data[j + 3][i];
			if (get_location(x1, y1, x2, y2, pos) == -1) continue;

			users.push_back(pos);
			loc.push_back(pos);
		}
		update(users, i);
	}
	save_gr(loc);
	return 0;
}
