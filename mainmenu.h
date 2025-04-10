#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void DisplayMenu();
bool UserInputPrompt(string choice);
void ReadConfig();
void AllocateMemory();
void ClearMemory();
#endif