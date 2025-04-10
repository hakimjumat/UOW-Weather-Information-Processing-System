#include "pressure.h"
#include "functions.h"

void Pressure(int height, int width, vector<string>& pressure_file, 
string**& pressure_map, string**& pressure_converted, int**& pressure_orginal) {
    vector <string> v;
    string s;
    vector <string> coordinate;
    int x,y;

	//Extracting data
    for (int i=0; i<pressure_file.size(); i++) {
		v = SplitString(pressure_file[i], "-");
		s = ProcessCoordinate(v[0]);
		coordinate = SplitString(s, " ");
		x = ConvertStringToInteger(coordinate[0]);
		y = ConvertStringToInteger(coordinate[1]);

		//Assign value
		if((x < width) && (y < height)) {
			pressure_map[height - y - 1][x] = ConvertToIndex(v[1]);	
			pressure_orginal[height - y - 1][x] = ConvertStringToInteger(v[1]);
		}		
		
		if((x < width) && (y < height)) {
			pressure_converted[height - y - 1][x] = ConvertToLMH(ConvertStringToInteger(v[1]));	
		}		
	}
}

