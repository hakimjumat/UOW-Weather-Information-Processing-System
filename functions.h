#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;

string TrimSpace(string str);
vector<string> SplitString(string input, string splitby);
int ConvertStringToInteger(string s);
vector<string> ReadFile(string name);
string ProcessCoordinate(string str);
string CheckSurrounding(string **map, int x, int y, int tableWidth, int tableHeight);
string ConvertToLMH(int val);
string ConvertToIndex(string val);

void GenerateMap(string** arr, int width, int height);
void GenerateIntegerMap(int** arr, int width, int height); 
void DeleteMap(string** arr, int height);
void DeleteIntMap(int** arr, int height);  
void PrintMap(string** arr, int width, int height);

void ReturnMenu();
void ClearScreen();

#endif