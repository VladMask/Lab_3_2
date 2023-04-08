#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Header.h"

using namespace std;

struct City
{
	string name;
	string state;
	int population = 0;
};

bool CompareByPopulation(City c1, City c2)
{
	return c1.population < c2.population;
}

bool CompareByName(City c1, City c2)
{
	return c1.name < c2.name;
}

// returns index of city in vector or -1 if city is not founded
int FindCityIndex(string name, vector<City> cities)
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].name == name)
			return i;
	}
	return -1;
}

//prints exit messege
void Exit(ofstream& fout)
{
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Exit command found" << endl;
	fout << "--------------------------------------------------------------------" << endl;
	fout.close();
}

//joins info about city in one string or returns error statement
string JoinCityInfo(string cityName, vector<City> cities)
{
	int index = FindCityIndex(cityName, cities);
	if (index != -1)
		return to_string(index + 1) + ":\t" + cities[index].name +
		" \t" + cities[index].state + "\t" + to_string(cities[index].population);
	else
		return "City with name " + cityName + " is not founded";
}

//prints info about cities is some state or error mesegge is state is not founded
void StateInfo(ofstream& fout, string stateName, vector<City> cities)
{
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Looking for cities in:\t" << stateName << endl;
	bool flag = false;
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].state == stateName)
		{
			fout << JoinCityInfo(cities[i].name, cities) << endl;
			flag = true;
		}
	}
	if (!flag)
		fout << "State with name " + stateName + " is not founded" << endl;
	fout << "--------------------------------------------------------------------" << endl;
}

//prints info about city to file using JoinCityInfo() func
void CityInfo(ofstream& fout, string cityName, vector<City> cities)
{
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Looking for city named:\t" << cityName << endl;
	fout << JoinCityInfo(cityName, cities) << endl;
	fout << "--------------------------------------------------------------------" << endl;
}

//sorts vector of cities in order to some criteria
void Sort(ofstream& fout, vector<City>& cities, string criteria)
{
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Sorting by " + criteria << endl;
	if (criteria == "name")
		sort(cities.begin(), cities.end(), CompareByName);
	else
		sort(cities.begin(), cities.end(), CompareByPopulation);
	fout << "--------------------------------------------------------------------" << endl;
}

//prints info about cities with populations in some range or error messege
void ShowInRange(ofstream& fout, vector<City> cities, string line)
{
	int lowerBound = stoi(line.substr(line.find('\t'), (line.rfind('\t') - line.find('\t') - 1)));
	int upperBound = stoi(line.substr(line.rfind('\t'), (line.find('\n') - 1 - line.find('\t'))));
	bool flag = false;
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Looking for populations between " << lowerBound << " and " << upperBound << ":" << endl;
	for (int i = 0; i < cities.size(); i++)
	{
		if ((cities[i].population >= lowerBound) and (cities[i].population <= upperBound))
		{
			fout << JoinCityInfo(cities[i].name, cities) << endl;
			flag = true;
		}
	}
	if (!flag)
		fout << "Cities with population in such range is not founded" << endl;
	fout << "--------------------------------------------------------------------" << endl;
}

//updates info about population in some city or prints error messege
void UpdatePopulation(ofstream& fout, vector<City>& cities, string line)
{
	string cityName = line.substr(line.find('\t') + 1, line.rfind('\t') - line.find('\t') - 1);
	int newValue = stoi(line.substr(line.rfind('\t'), (line.find('\n') - line.find('\t') - 1)));
	fout << "--------------------------------------------------------------------" << endl;
	fout << "Updating population for:\t" << cityName << endl;
	int index = FindCityIndex(cityName, cities);
	if (index == -1)
	{
		fout << "ERROR" << endl;
	}
	else
	{
		cities[index].population = newValue;
		fout << JoinCityInfo(cityName, cities) << endl;
		fout << "--------------------------------------------------------------------" << endl;
	}
}

//runs command from script.txt file
void RunCommand(ofstream& fout, string line, vector<City> cities)
{
	string command = line.substr(0, line.find('\t'));
	if (command == "city")
	{
		CityInfo(fout, line.substr(line.find('\t') + 1, (line.find('\n') - 1 - line.find('\t'))), cities);
	}
	else if (command == "state")
	{
		StateInfo(fout, line.substr(line.find('\t'), (line.find('\n') - 1 - line.find('\t'))), cities);
	}
	else if (command == "sort")
	{
		Sort(fout, cities, line.substr(line.find('\t') + 1, (line.find('\n') - 1 - line.find('\t'))));
	}
	else if (command == "update")
	{
		UpdatePopulation(fout, cities, line);
	}
	else if (command == "range")
	{
		ShowInRange(fout, cities, line);
	}
	else if (command == "exit")
	{
		Exit(fout);
	}
	else
		fout << "Undefined command" << endl;
}

//creates output file
void CreateOutput(string scriptName, string foutName, vector<City> cities)
{
	ofstream fout;
	fout.open(foutName);
	ifstream script;
	script.open(scriptName);
	fout << "Project: Laboratory work number 3" << endl;
	fout << "Programmer: ME" << endl;
	fout << "--------------------------------------------------------------------" << endl;
	while (!script.eof())
	{
		string command;
		getline(script, command, '\n');
		RunCommand(fout, command, cities);
	}
	script.close();
}

//gets data from input file
vector<City> GetData(string finName)
{
	ifstream fin;
	fin.open(finName);
	vector<City> cities;
	while (!fin.eof())
	{
		City city;
		getline(fin, city.name, '\t');
		getline(fin, city.state, '\t');
		fin >> city.population;
		fin.ignore(1, '\n');
		cities.push_back(city);
	}
		return cities;
}