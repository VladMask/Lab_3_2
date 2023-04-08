#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;


struct City;

bool CompareByPopulation(City c1, City c2);

bool CompareByName(City c1, City c2);

// returns index of city in vector or -1 if city is not founded
int FindCityIndex(string name, vector<City> cities);

//prints exit messege
void Exit(ofstream& fout);

//joins info about city in one string or returns error statement
string JoinCityInfo(string cityName, vector<City> cities);

//prints info about cities is some state or error mesegge is state is not founded
void StateInfo(ofstream& fout, string stateName, vector<City> cities);

//prints info about city to file using JoinCityInfo() func
void CityInfo(ofstream& fout, string cityName, vector<City> cities);

//sorts vector of cities in order to some criteria
void Sort(ofstream& fout, vector<City>& cities, string criteria);

//prints info about cities with populations in some range or error messege
void ShowInRange(ofstream& fout, vector<City> cities, string line);

//updates info about population in some city or prints error messege
void UpdatePopulation(ofstream& fout, vector<City>& cities, string line);

//runs command from script.txt file
void RunCommand(ofstream& fout, string line, vector<City> cities);

//gets data from input file
vector<City> GetData(string finName);

//creates output file
void CreateOutput(string scriptName, string foutName, vector<City> cities);