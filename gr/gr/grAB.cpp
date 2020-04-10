#define _CRT_SECURE_NO_WARNINGS
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
using namespace std;
using namespace ptl;

struct vector2
{
  double x,y,theta;
};

double dis2(const vector2& a, const vector2& b)
{
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
const int NN = 1000;
double dr = 0.2;
class t_sta
{
  map<int,int> friends;
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
    if (friends.find(id) == friends.end()) friends.insert( map<int,int>::value_type(id, 1));
    else friends[id] ++;
  }
  void gr(double r)
  {
    int i = int(r/dr);
    if (i >= NN)
    {
//      cout << r << endl;
      return;
    }
    P[i] ++;
    total ++;
  }
  double get_Pr(int i)
  {
    return P[i]/total;
  }
  
};

t_sta sta0;

void save_gr(const vector<vector2>& locA, const vector<vector2>& locB)
{
  t_sta rand_sta;
  for (int i = 0; i < locA.size(); i ++)
    for (int j = 0; j < locB.size(); j ++)
      rand_sta.gr(sqrt(dis2(locA[i],locB[j])));
  
  ofstream file("gr.dat");
  for (int i = 0; i < NN; i ++)
  {
    if (rand_sta.get_Pr(i))
    {
      double gr = sta0.get_Pr(i)/rand_sta.get_Pr(i);
      if (gr > 0.0001) file << i*dr << '\t' << gr << endl;
    }
  }
  
}

void update(const vector<vector2>& usersA, const vector<vector2>& usersB, int t)
{
  for (int i = 0; i < usersA.size(); i ++)
  {
    for (int j = 0; j < usersB.size(); j ++)
    {
      double d = sqrt(dis2(usersA[i],usersB[j]));
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
  p.x = (x1+x2)/2;
  p.y = (y1+y2)/2;
  return 0;
}

int main(int argc, char* argv[])
{
  vector<vector<double> > data;
  sscan_matrix(argv[1], data);
  
  dr = atof(argv[2]);
  vector<vector2> locA, locB;
  
  int child_num = 10;
  
  if (argc > 3) child_num = atoi(argv[3]);
  
  int totalN = (data.size()-1)/4;
  
  if (data.size() != totalN*4+1)
  {
    cout << data.size() << endl;
    return -1;
  }
  for (int i = 0; i < data[0].size(); i ++)
  {
    vector<vector2> usersA, usersB;
    for (int k = 0; k < child_num; k ++)
    {
      vector2 pos;
      int j = 4*k;
      double x1 = data[j+1][i], y1 = data[j+2][i];
      double x2 = data[j+3][i], y2 = data[j+4][i];
      if (get_location(x1, y1, x2, y2, pos) == -1) continue;
      
      usersA.push_back(pos);
      locA.push_back(pos);
    }
    for (int k = child_num; k < totalN; k ++)
    {
      vector2 pos;
      int j = 4*k;
      double x1 = data[j+1][i], y1 = data[j+2][i];
      double x2 = data[j+3][i], y2 = data[j+4][i];
      if (get_location(x1, y1, x2, y2, pos) == -1) continue;
      
      usersB.push_back(pos);
      locB.push_back(pos);
    }
    update(usersA,usersB, i);
  }
  save_gr(locA, locB);
  return 0;
}
