#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;

map<string, vector<float> > build_junc_map(char filename[]) {

	map<string, vector<float> > junc_map;
	string line;
	ifstream myfile (filename);

	if (myfile.is_open()) {

		while(getline(myfile,line)) {

			unsigned found = line.find_last_of(',');

			string junc = line.substr(0,found);
			string dist = line.substr(found+1);

			junc_map[junc].push_back(atof(dist.c_str()));
			junc_map[junc].push_back(0);
		}
	}
	else {
		cout << "Can't access file. what did you do? \n";
	}

	return junc_map;
}

void calc_stress_factor(map<string, vector<float> > junc_map, char filename[]) {

	string line;
	ifstream myfile (filename);

	if (myfile.is_open()) {
		// sum # of routes going through each road
		while(getline(myfile,line)) {

			for (size_t i = 0; i+4 < line.size(); i += 3) {

				junc_map[line.substr(i,5)][1] += 1;
			}
		}
		// calc stress factor
		for (map<string, vector<float> >::iterator it=junc_map.begin(); it!=junc_map.end(); ++it) {
    		it->second.push_back(it->second[1] / it->second[0]);

    		cout << it->first << " : " << it->second[2] << endl; 

    	}
	}
}

void export_stress_factor(map<string, vector<float> > junc_map, char newfilename[]) {

	ofstream myfile (newfilename);
	if (myfile.is_open()) {

		for (map<string, vector<float> >::iterator it=junc_map.begin(); it!=junc_map.end(); ++it) {
			myfile << it->first << "," << it->second[2] << endl;
		}
	myfile.close();

	}
}


int main () {

	map<string, vector<float> > junc_map = build_junc_map((char*) "Roads.conf");
	calc_stress_factor(junc_map,(char*) "Routes.conf");

	export_stress_factor(junc_map,(char*) "RoadStress.out");

	return 0;
}