#include "city.h"
#include "functions.h"

void City(int height, int width, vector<string>& city_file, 
string**& city_map, vector<string> &city_name, vector<string> &city_id) {   

    string value;
    string name;
    string s;
    vector <string> coordinate;
    vector <string> v;
    int x,y;
    
    //Clear vector before compute (handle re-read configuration file)
    city_name.clear();
    city_id.clear();
    
	//Extract data
	for (int i=0; i<city_file.size(); i++) {
		v = SplitString(city_file[i], "-");
		s = ProcessCoordinate(v[0]);
		value = v[1];
		name = v[2];
		
		//Assign value
		if(!count(city_name.begin(), city_name.end(), name)) {
			city_name.push_back(name);
			city_id.push_back(value);
		}
		
		coordinate = SplitString(s, " ");
		x = ConvertStringToInteger(coordinate[0]);
		y = ConvertStringToInteger(coordinate[1]);
		
		//Rotate map 
		if((x < width) && (y < height)) {
			city_map[height - y - 1][x] = value;	
		}		
	}
}