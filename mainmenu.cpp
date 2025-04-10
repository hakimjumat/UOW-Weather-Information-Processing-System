#include "mainmenu.h"
#include "functions.h"
#include "city.h"
#include "cloud.h"
#include "pressure.h"
#include "weather.h"

string student_id = "8575848";
string student_name = "Fayyah Hakim Bin Jumat";
bool fileRead = false;

// variables for handling file
vector <string> info;
string file_in;
int width;
int height;
vector <string> city_file;
vector <string> cloudcover_file;    
vector <string> pressure_file;

string** city_map;
vector <string> city_name;
vector <string> city_id;

string** cloud_map;
string** cloud_converted;
int** cloud_orginal;

string** pressure_map;
string** pressure_converted;
int** pressure_orginal;

// struct defined in weather.h
vector <City_report> alist;

// vector <City_report> alist;
// int width;
// int height;

//Displays main menu based on Appendix F
void DisplayMenu() {
    string choice;
	while(true) {
		cout << "======================================" << endl;
		cout << "Student ID   : " << student_id << endl;
		cout << "Student Name : " << student_name << endl;
		cout << "======================================" << endl;
		cout << "Welcome to Weather Information Processing System!\n" << endl;
		cout << "1)\tRead in and process a configuration file" << endl;

		// If configuration file is already read, display options 2-7.
		if(fileRead) {
			cout << "2)\tDisplay city map" << endl;
			cout << "3)\tDisplay cloud coverage map (cloudiness index)" << endl;
			cout << "4)\tDisplay cloud coverage map (LMH symbols)" << endl;
			cout << "5)\tDisplay atmospheric pressure map (pressure index)" << endl;
			cout << "6)\tDisplay atmospheric pressure map (LMH symbols index)" << endl;
			cout << "7)\tShow weather forecast summary report" << endl;
		}
		cout << "8)\tQuit\n" << endl;
        cout << "Please enter your choice: ";
        // ensures no empty input by user
		while(choice == "") {
			cin >> choice;
		}

		//Cleans user input before evaluating
		choice = TrimSpace(choice);
		bool result = UserInputPrompt(choice);

		//If user choose quit, result is true and program exits
        if(result) break;

		//Reset choice
		choice = "";
    }
}


// Evaluating user input based on 8 options
bool UserInputPrompt(string choice) {
    if(choice == "1") {
        // Read configuration file
        ReadConfig();
        // Allocate memory
        AllocateMemory();
		// Process weather data
		City(height, width, city_file, city_map, city_name, city_id);
		Cloud(height, width, cloudcover_file, cloud_map, cloud_converted, cloud_orginal);
		Pressure(height, width, pressure_file, pressure_map, pressure_converted, pressure_orginal);
		alist.clear();

		//Process weather report
		ComputeWeatherData(height, width, city_name, city_id, city_map, cloud_map, pressure_map, pressure_orginal, cloud_orginal, alist);
		return false;
    }
	else if ((choice == "2") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "[Display city map]" << endl;

		// Displays 2d array city map
		PrintMap(city_map, width, height);
		ReturnMenu();
		ClearScreen();
    	return false; 
	} else if((choice == "3") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "[Display cloud coverage map (cloudiness index)]\n" << endl;

		//Display cloud map (cloud index)
		PrintMap(cloud_map, width, height);
		ReturnMenu();
		ClearScreen();
    	return false;
	} else if((choice == "4") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "[Display cloud coverage map (LMH symbols)]\n" << endl;

		//Display cloud map (LMH format)
		PrintMap(cloud_converted, width, height);
		ReturnMenu();
		ClearScreen();
    	return false;
	} else if((choice == "5") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "[Display atmospheric pressure map (pressure index)]\n" << endl;

		//Display pressure map (pressure index)
		PrintMap(pressure_map, width, height);
		ReturnMenu();
		ClearScreen();
    	return false;
	} else if((choice == "6") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "[Display atmospheric pressure map (LMH symbols index)]\n" << endl;

		//Display pressure map (LMH format)
		PrintMap(pressure_converted, width, height);
		ReturnMenu();
		ClearScreen();
    	return false;
	} else if((choice == "7") && (fileRead)) {
		ClearScreen();
		cout << endl;
		cout << "Weather Forecast Summary Report" << endl;
		cout << "-------------------------------" << endl;

		//Display weather forecast report
		Weather(alist);
		ReturnMenu();
		ClearScreen();
		return false;
	}  else if(choice == "8") {
		cout << endl;
		cout << "[Quit]";

		//clear memory allocated so far
		ClearMemory();
		ClearScreen();
		return true;
	} else {
		cout << endl;
		ClearScreen();
		return false;
	}
}

// Function to read the configuration file
void ReadConfig() {
	fstream inputFile;
	string aLine;
	vector <string> vStr;
	cout << endl;

	cout << "[Read in and process a configuration file]" << endl;
	cout << "Please enter config file name: ";
	cin >> file_in;
	inputFile.open(file_in.c_str());
    cout << endl;
    info.clear();

	//Extracting data from configuration file
    if(!inputFile) {
    	cout << "Error when reading input file" << endl;
    	cout << endl;
	} else {
    	while (inputFile) {
    		getline (inputFile, aLine);
            //skips comments and empty lines
    		if(aLine[0] == '/') continue;
    		if(aLine == "") continue;
            //stores the data in a vector "info"
    		info.push_back(aLine);
		}
		inputFile.close();
		cout << "Reading in " << info[0] << " " << "...";
		cout << " done!" << endl;
		cout << "Reading in " << info[1] << " " << "...";
		cout << " done!" << endl;
		cout << endl;
		cout << "Storing data from input file :" << endl;

		//Extracting width and height from the configuration file
        // split the range by "-" to get the max value
        vStr = SplitString(info[0], "-");
		width = ConvertStringToInteger(vStr[1]);
		vStr = SplitString(info[1], "-");
		height = ConvertStringToInteger(vStr[1]);
        // for padding, increase both width and height by 1
		width ++;
		height ++;

		//Read other text file and stores them in respective vectors
		city_file = ReadFile(info[2]);
		cloudcover_file = ReadFile(info[3]);
		pressure_file = ReadFile(info[4]);

		cout << endl;
		cout << "All records successfully stored. Going back to main menu ... " << endl;
		if(!fileRead) fileRead = true;
		cout << endl;
	}
    ClearScreen();
}

// Function to allocate memory for the maps
void AllocateMemory() {
	// Allocate memory for city map
    city_map = new string*[height];
    GenerateMap( city_map, width, height);

    // Allocate memory for cloud coverage map
	cloud_map = new string * [height];
	cloud_converted = new string * [height];
	cloud_orginal = new int* [height];
    GenerateMap(cloud_map, width, height);
    GenerateMap(cloud_converted, width, height);
    GenerateIntegerMap(cloud_orginal, width, height);

    // Allocate memory for atmospheric pressure map
	pressure_map = new string*[height];
	pressure_converted = new string*[height];
	pressure_orginal = new int*[height];
	GenerateIntegerMap(pressure_orginal, width, height);
    GenerateMap(pressure_map, width, height);
    GenerateMap(pressure_converted, width, height);
}


void ClearMemory() {
	// Clear memory for city map
	DeleteMap(city_map, height);

	// Clear memory for cloud coverage map
	DeleteMap(cloud_map, height);
	DeleteMap(cloud_converted, height);
	DeleteIntMap(cloud_orginal, height);

	// Clear memory for atmospheric pressure map
	DeleteMap(pressure_map, height);
	DeleteMap(pressure_converted, height);
	DeleteIntMap(pressure_orginal, height);
}