#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include "../include/road_maintenance.hpp"
using namespace std;

map<string, vector<float> > build_junc_map(char filename[]) { 											// create map with junctions for indices, vector for length and stress calculation

	map<string, vector<float> > junc_map;
	string line;
	ifstream myfile (filename);

	if (myfile.is_open()) {

		while(getline(myfile,line)) {

			unsigned found = line.find_last_of(',');													// last comma on each line will always come before length of road

			string junc = line.substr(0,found);															// string containing two junctions
			string dist = line.substr(found+1);															// string containing distance between the two

			junc_map[junc].push_back(atof(dist.c_str()));												// at 'junc' index, [0] of vector will be the distance
			junc_map[junc].push_back(0);																// [1] of vector will contain # of routes passing between these junctions. initialized to 0.
		}
	}
	else {
		cout << "Can't access file. what did you do? \n";
	}

	return junc_map;
}

void calc_stress_factor(map<string, vector<float> >& junc_map, char filename[]) {

	string line;
	ifstream myfile (filename);

	if (myfile.is_open()) {

		while(getline(myfile,line)) {		

			// initialize indices to help iterate through each line, grabbing one road at a time
			size_t begin = 0;
			size_t mid = line.find(',');
			size_t end = line.find(',',mid+1);

			while(end!=std::string::npos) {																// iterate until we reach end of line

				junc_map[line.substr(begin,end - begin)][1] += 1;

				begin = mid +1;
				mid = end;
				end = line.find(',',mid+1);

			}
			junc_map[line.substr(begin)][1] += 1;														// tie up loose ends..
			
		}
																										// calc stress factor
		for (map<string, vector<float> >::iterator it=junc_map.begin(); it!=junc_map.end(); ++it) {
    		it->second.push_back(it->second[1] / it->second[0]);

    		cout << it->first << " : " << it->second[2] << endl; 										// print result to cli. because lazy.

    	}
	}
}

void export_stress_factor(map<string, vector<float> >& junc_map, char newfilename[]) {					// create .out file, export stress factors.

	ofstream myfile (newfilename);																		// create new file
	if (myfile.is_open()) {

		for (map<string, vector<float> >::iterator it=junc_map.begin(); it!=junc_map.end(); ++it) {		// initialize map iterator, for every index (=road) include stress factor.
			myfile << it->first << "," << it->second[2] << endl;
		}
	myfile.close();																						// close file. satey first.

	}
}


int main () {

	map<string, vector<float> > junc_map = build_junc_map((char*) "../Roads.conf");
	
	calc_stress_factor(junc_map,(char*) "../Routes.conf");

	export_stress_factor(junc_map,(char*) "../RoadStress.out");

	return 0;
}