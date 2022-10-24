// =================================================================
//
// File: main.cpp
// Author: Arturo Diaz
// Date: 18/10/22
//
// =================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "insertion.h"
using namespace std;

int main(int argc, char *argv[]){
  
  ifstream inputFile;
  ofstream outputFile;

  if (argc != 3){
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  outputFile.open(argv[2]);

  if (!inputFile.is_open()){
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  int n;
  std::string idSearch, date, time, port, id;

  struct registry{
    int year, month, day;
    string date_, time, port, id;
  };
  
  vector<registry> ships;

  inputFile >> n;
  inputFile >> idSearch;

  for (int i = 0; i < n; i++){
    inputFile >> date >> time >> port >> id;

    std::string day = date.substr(0, date.find("-"));
    std::string month = date.substr(3, date.find("-"));
    std::string year = date.substr(6);

    size_t found = id.rfind(idSearch);
    if (found != string::npos){
      ships.push_back({stoi(year), stoi(month), stoi(day), date, time, port, id});
    }
  }

  insertionSortDay(ships);
  insertionSortMonth(ships);

  std::string months[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
  vector<string> med;
  vector<string> red;
  int currentBoat = 0;

  for (int i = 0; i < 12; i++){
    while (ships[currentBoat].month == i + 1){
      ships[currentBoat].port == "M" ? med.push_back(ships[currentBoat].id) : red.push_back(ships[currentBoat].id);
      currentBoat++;
    }

    if (med.size() > 0 || red.size() > 0){
      outputFile << months[i] << "\n"
                 << "M " << med.size() << ": ";
      for (int m = 0; m < med.size(); m++){
        outputFile << med[m] << " ";
      }
      outputFile << "\n"
                 << "R " << red.size() << ": ";
      for (int m = 0; m < red.size(); m++){
        outputFile << red[m] << " ";
      }
      outputFile << "\n";
    }

    med.clear();
    red.clear();
  }

  inputFile.close();
  outputFile.close();

  return 0;
}