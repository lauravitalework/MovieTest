#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "io.h" 
using namespace std;
using namespace ptl;

int gettime(ostream& os, string& data)
{
	struct tm info;
	data[4] = ':';
	data[7] = ':';

	vector<int> stime;
	sscan(data.c_str(), stime);

	if (stime.size() != 7)
	{
		cout << "err - " << data << endl;
		for (int i = 0; i < stime.size(); i++)
		{
			cout << stime[i] << endl;
		}
		return 1;
	}

	info.tm_year = stime[0] - 1900;
	info.tm_mon = stime[1] - 1;
	info.tm_mday = stime[2];
	info.tm_hour = stime[3];
	info.tm_min = stime[4];
	info.tm_sec = stime[5];
	info.tm_isdst = -1;

	os << mktime(&info) << '.' << stime[6];
	return 0;
}

map<string, int> file_list;

void get_info(const char* name)
{
	ifstream file(name);

	while (1)
	{
		char sl[10000];
		file.getline(sl, 10000);
		if (file.eof()) break;

		string s;
		vector<string> str;
		for (const char* p = sl; *p != '\0'; ++p)
		{
			if (*p == ',')
			{
				str.push_back(s);
				s = "";
			}
			else s += *p;
		}
		str.push_back(s);

		if (str.size() < 6)
		{
			cout << "err - " << sl << endl;
			continue;
		}

		s = str[1] + ".dat";
		ofstream save(s.c_str(), ios_base::app);
		file_list[s] = 0;
		if (gettime(save, str[2]))
		{
			cout << "err2 - " << sl << endl;
			continue;
		}
		save << '\t' << str[3] << '\t' << str[4] << '\t' << str[5];
		if (str.size() == 7) save << '\t' << str[6];
		save << endl;
	}

}


int main(int argc, char* argv[])
{

	for (int i = 1; i < argc; i++)
	{
		
		get_info(argv[i]);
	}
	ofstream file("list.dat");
	for (map<string, int>::iterator i = file_list.begin(); i != file_list.end(); ++i)
	{
		file << i->first << endl;
	}


	return 0;
}
