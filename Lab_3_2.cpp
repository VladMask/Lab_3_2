#include "Header.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <iterator>

using namespace std;

struct City
{
	string name;
	string state;
	int population = 0;
};

int main()
{
	string finName, foutName, scriptName;
	vector<City> cities;
	finName = "2.CityData.txt";
	foutName = "dbLog.txt";
	scriptName = "2.Script.txt";
	string cityName = "Little";
	string stateName = "Virginia";
	cities = GetData(finName);	
	CreateOutput(scriptName, foutName, cities);
}