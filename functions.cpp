#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "functions.h"

//to clear all spaces from string of user input
string TrimSpace(string str) {
    str.erase(remove(str.begin(),str.end(),' '),str.end());
    return str;
}

// Get data from string after splitting with separator
vector<string> SplitString(string input, string splitby) {
    size_t pos = 0;
    string element;
    vector<string> result;
    
    //ensures string is split until no separators found
    while ((pos = input.find(splitby)) != string::npos) {
        element = input.substr(0, pos);     
        result.push_back (element);
        // trims string after each split and before loop
        input.erase(0, pos + splitby.length());
    }
    
    // ensures last element is added to vector
    result.push_back (input);
    return (result);
}

// Get coordinate data inside bracket ([3, 4] -> 3 4) 
string ProcessCoordinate(string str) {
	char chars[] = "[],";
   	for (unsigned int i = 0; i < sizeof(chars); ++i) {
      str.erase (std::remove(str.begin(), str.end(), chars[i]), str.end());
   	} 	
   	return str;
}

//converts string to integer
int ConvertStringToInteger(string s) {
	int x;
	stringstream ss;
	ss.clear();
	ss.str(s);
	ss >> x;
	return x;
}

// Read weather data from a file (eg. citylocation.txt)
vector<string> ReadFile(string name) {
    fstream inputFile;
    string aLine;
	vector<string> result;
	cout << name << " ... ";
	inputFile.open(name.c_str());
    while (inputFile) {
    	getline (inputFile, aLine);
    	if (aLine == "") {
    		continue;
		}
    	result.push_back(aLine);
	}
	inputFile.close();	
	cout << "done!" << endl;
	return result;
}

// To generate empty 2D string array
void GenerateMap(string** arr, int width, int height) {
    for (int i = 0; i < height; i++) {
        arr[i] = new string[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = " ";
        }
    }
}

// Generate 2d int array 
void GenerateIntegerMap(int** arr, int width, int height) {
	for (int i = 0; i < height; i++) {
        arr[i] = new int[width];
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = 0;
        }
    }
}

// To delete 2D string array
void DeleteMap(string** arr, int height) {
    for(int i=0;i<height;i++) {
        delete [] arr[i];    	
    }
    delete [] arr;
}

// To delete 2D int array
void DeleteIntMap(int** arr, int height) {
    for(int i=0;i<height;i++) {
		delete [] arr[i];   
	}
	delete [] arr;
}

// Prints the 2d map to screen
void PrintMap(string** arr, int width, int height) {
	string border = " ";
	for(int i=0; i< width + 2; i++) {
		border += "#  ";
	}
	
	cout <<  " " << "  " << border << endl;
	
	for (int i = 0; i < height; i++) {
		cout<< setw(2) << height - i - 1 << "  " << "#" << "  ";
        for (int j = 0; j < width; j++) {
            cout << arr[i][j] << "  ";
        }
        cout << "#";
        cout << endl;
    }
    cout << " " << "  " << border << endl;
    cout << setw(6) << " ";
    for(int i=0; i< width; i++) {
    	cout << setw(2) << i << " ";
	}
	cout << "\n" << endl;
}

/* Check neighbor to see which city it belongs to */
string CheckSurrounding(string **map, int x, int y, int tableWidth, int tableHeight) {
	string value;
	//Current pos
	value = map[x][y];
	if(value != " ") {
		return value;
	}
	
	// Left
	if((x-1)>=0){
		value = map[x-1][y];
		if(value != " ") {
			return value;
		}
    }

    // Right
    if((x+1)<tableWidth){
		value = map[x+1][y]; 
		if(value != " ") {
			return value;
		}
    }

    //Up
    if((y-1)>=0){
		value = map[x][y-1];
		if(value != " ") {
			return value;
		}
    }

    //Down
    if((y+1)<tableHeight) {
		value = map[x][y+1];
        if(value != " ") {
			return value;
		}
    }

    // Left down
    if((x-1)>=0 && ((y+1)<tableHeight)) {
		value = map[x-1][y+1];
		if(value != " ") {
			return value;
		}
    }

    // Right Down
    if((x+1)<tableWidth && (y+1)<tableHeight) {
   		value = map[x+1][y+1];
   		if(value != " ") {
			return value;
		}
    }

    // Right UP
    if((x+1)<tableWidth && (y-1)>=0) {
   		value = map[x+1][y-1];
   		if(value != " ") {
			return value;
		}
    }

    // Left Up
    if((x-1)>=0 && (y-1)>=0){
    	value = map[x-1][y-1];
    	if(value != " ") {
			return value;
		}
    }
    
    //Not belong to any city
	return "";
}

/* Convert data to LMH */
string ConvertToLMH(int val) {
    if (val >= 0 && val <= 34) {
        return "L";
    }
    else if (val >= 35 && val <= 64) {
        return "M";
    }
    else {
        return "H";
    }
}



string ConvertToIndex(string val) {
	string value;
	if (TrimSpace(val).size() == 1) {
		value = "0";
	} else {
		value = val.substr(0, 1);
	}
	return value;
}

void ReturnMenu() {
	string test = "1";
	cout << "Press <enter> to go back to main menu ..." << endl;
	cin.ignore();
	do {
        // gets user input and stores in test
		getline(cin, test);
        // if enter is not inputted, loop continues
	} while(test.length() != 0);
}


// clears screen for both windows and ubuntu to make it tidy
void ClearScreen() {
	#ifdef WIN32
	system("cls");
	#define windows
	#else
	system("clear");
	#define ubuntu
	#endif
}