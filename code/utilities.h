#pragma once
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iterator>
#include <cctype>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <filesystem>
using namespace std;

const int MAX = 101;

//just some functions that might be useful for inputting, it does data validation
int    add(int a, int b);
double read_double();
int    read_int();
long   read_long();
char   read_char();
float  read_float();
bool   isNumeric(const string & str);
string read_string();
string removeWhitespace(const string & str);
string getCurrentDateMMDDYYYY();
int checkIfFileEmptyAndOpenable(const string & filename);
void printServices(const string & filename);
int generateProviderReport(map<string, vector<vector<string>>> & providerRecords, const string & filename);
void printProviderReport(const map<string, vector<vector<string>>> & providerRecords);
int generateMemberReport(map<string, vector<vector<string>>> & memberRecords, const string & filename);
void printMemberReport(const map<string, vector<vector<string>>> & memberRecords);
void generateWeeklyEFTReport(const string& providerReportFilename);