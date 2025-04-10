#include "weather.h"
#include "functions.h"
string ToString(City_report r);
int *city_size;
int *cloud_sum;
int *pressure_sum;
int rp_size, id;
City_report *report_list;
void Assign(City_report &r);

// To Print weather forecast report
void Weather(vector <City_report> alist) {
	for(int i=0; i<rp_size; i++) {
		cout << ToString(alist[i]) << endl;
	}
	
}

//Handle weather report data
void ComputeWeatherData(int height, int width, vector<string> &city_name, vector<string> &city_id, 
string**& city_map, string**& cloud_map, string**& pressure_map, int**& pressure_original, int**& cloud_original, vector <City_report> &alist) {
    string city_belong;

	rp_size = static_cast<int>(city_name.size());
	report_list = new City_report[rp_size];
	cloud_sum = new int[rp_size];
	pressure_sum = new int[rp_size];
	city_size = new int[rp_size];
	
	for(int i = 0; i< rp_size; i++) {
		report_list[i].name = city_name[i];
		report_list[i].id = city_id[i];
		cloud_sum[i] = 0;
		pressure_sum[i] = 0;
		city_size[i] = 0;
	}
	
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
			city_belong = CheckSurrounding(city_map, i, j, height, width);
			if(city_belong != "") {
				id = ConvertStringToInteger(city_belong);
				id --;
				city_size[id]++;
				cloud_sum[id] += cloud_original[i][j];
				pressure_sum[id] += pressure_original[i][j];
			}
		}
	}
	
	for(int i = 0; i< rp_size; i++) {
		report_list[i].ave_cloud = cloud_sum[i] / static_cast<double>(city_size[i]);
		report_list[i].ave_pressure = pressure_sum[i] / static_cast<double>(city_size[i]);	
	}

	for(int i = 0; i< rp_size; i++) {
		Assign(report_list[i]);
		alist.push_back(report_list[i]);
	}

	delete[] report_list;
	delete[] cloud_sum;
	delete[] pressure_sum;
	delete[] city_size;
}

// Generating weather report results
string ToString(City_report r) {

	ostringstream oss;
	string value;
	oss << "City Name : " << r.name << endl;
	oss << "City ID   : " << r.id << endl;
	// setprecision(2) used to print 2dp.
	oss << "Ave. Cloud Cover (ACC)	: " << setprecision(2) << fixed << r.ave_cloud << " (" << r.cloud_lv <<")" << endl;
	oss << "Ave. Pressure (AP)	: " << setprecision(2) << fixed << r.ave_pressure << " (" << r.pres_lv <<")" << endl;
	oss << "Probability of rain (%)	: " << setprecision(2) << fixed << r.rain << endl;
	oss << r.symbol << endl;
	return (oss.str());
}


// To Convert average values to string format
void Assign(City_report &r){

	if (static_cast<int>(r.ave_cloud) >= 0 && static_cast<int>(r.ave_cloud) <= 34) {
		r.cloud_lv = "L";
	}
	else if (static_cast<int>(r.ave_cloud) >= 35 && static_cast<int>(r.ave_cloud) <= 64) {
		r.cloud_lv = "M";
	}
	else {
		r.cloud_lv = "H";
	}


	if (static_cast<int>(r.ave_pressure) >= 0 && static_cast<int>(r.ave_pressure) <= 34) {
		r.pres_lv = "L";
	}
	else if (static_cast<int>(r.ave_pressure) >= 35 && static_cast<int>(r.ave_pressure) <= 64) {
		r.pres_lv = "M";
	}
	else {
		r.pres_lv = "H";
	}

	if(r.pres_lv == "L") {
		if(r.cloud_lv == "L") {
			r.rain = 70.0;
			r.symbol = "~~~~\n~~~~~\n  \\\\\\";
		} else if(r.cloud_lv == "M") {
			r.rain = 80.0;
			r.symbol = "~~~~\n~~~~~\n \\\\\\\\";
		} else {
			r.rain = 90.0;
			r.symbol = "~~~~\n~~~~~\n\\\\\\\\\\";
		}
	} else if(r.pres_lv == "M") {
		if(r.cloud_lv == "L") {
			r.rain = 40.0;
			r.symbol = "~~~~\n~~~~~\n";
		} else if(r.cloud_lv == "M") {
			r.rain = 50.0;
			r.symbol = "~~~~\n~~~~~\n    \\";
		} else {
			r.rain = 60.0;
			r.symbol = "~~~~\n~~~~~\n   \\\\";
		}
	} else{
		if(r.cloud_lv == "L") {
			r.rain = 10.0;
			r.symbol = "~\n~~\n";
		} else if(r.cloud_lv == "M") {
			r.rain = 20.0;
			r.symbol = "~~\n~~~\n";
		} else {
			r.rain = 30.0;
			r.symbol = "~~~\n~~~~\n";
		}
	}
}
