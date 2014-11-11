// include guard
#ifndef ROAD_MAINTENANCE_H
#define ROAD_MAINTENANCE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;

// define variables
std::map<string, vector<float> > junc_map;

// define functions
map<string, vector<float> > build_junc_map(char filename[]);
void calc_stress_factor(map<string, vector<float> >& junc_map, char filename[]);
void export_stress_factor(map<string, vector<float> >& junc_map, char newfilename[]);

#endif