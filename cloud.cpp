#include "cloud.h"
#include "functions.h"

void Cloud(int height, int width, vector<string>& cloudcover_file, 
string**& cloud_map, string**& cloud_converted, int**& cloud_original) {
    vector <string> v;
    string s, value;
    vector <string> coordinate;
    int x,y;
	
	//Extract data
	for (int i=0; i<cloudcover_file.size(); i++) {
		v = SplitString(cloudcover_file[i], "-");
		s = ProcessCoordinate(v[0]);
		coordinate = SplitString(s, " ");
		x = ConvertStringToInteger(coordinate[0]);
		y = ConvertStringToInteger(coordinate[1]);

		//Assign value
		if((x < width) && (y < height)) {
			cloud_map[height - y - 1][x] = ConvertToIndex(v[1]);
			cloud_original[height - y - 1][x] = ConvertStringToInteger(v[1]);
		}

		if((x < width) && (y < height)) {
			cloud_converted[height - y - 1][x] = ConvertToLMH(ConvertStringToInteger(v[1]));	
		}
	}
}
