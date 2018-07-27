// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <cstring>

#include "DynamicArray.h"
#include "StaticArray.h"

struct Course
{
  string sCode;
  int numOfSectionsTotal;
};

struct Seen
{
  string term;
  int numberOfSectionsSeen;
  DynamicArray<string> seenSectionNumbers;
};

bool dup(const string&, const string&, int&, StaticArray<Seen, 200>&);

int main()
{
  // Identification
  cout << "Programmer: Sadeem Khan\n";
  cout << "Programmer's ID: 1549921\n";
  cout << "File: " << __FILE__ << endl;

  // for parsing the inputfile
  char *token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";  

  DynamicArray<Course> records;

  int duplicates = 0;
  int x = 0;
  int count = 0;
  bool found;

  int numberOfTermsSeen = 0; // to track where we are in the following "array"
  StaticArray<Seen, 200> alreadySeen; // 200 should be plenty for the number of terms
  
  // read the input file
  while (fin.good())
  {
    count++;

    // Progress bar
    if (count % 1000 == 0) cout << '.';
    cout.flush();

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectsCode(course.begin(), course.begin() + course.find('-'));

    found = dup(term, section, numberOfTermsSeen, alreadySeen);
    if (found) 
    {
      duplicates++;
      continue;
    }

    else 
    {
      bool seen = false;
      for (int i = 0; i < x; i++)
      {
        if (records[i].sCode == subjectsCode)
        {
          records[i].numOfSectionsTotal++;
          seen = true;
          break;
        }
      }

      if (!seen)
      {
        Course a;
        a.sCode = subjectsCode;
        a.numOfSectionsTotal = 1;
        records[x] = a;
        x++;
      }
    }
  }
  
  // sorting
  for (int i = 0; i < x; i++)
    for (int j = 0; j < x; j++)
      if (records[i].sCode < records[j].sCode) swap(records[i], records[j]);
  
  // output
  cout << endl; // for spacing
  for (int i = 0; i < records.capacity(); i++) 
  {
    if (records[i].numOfSectionsTotal == 0 || records[i].sCode == "") continue;
    cout << records[i].sCode << ", " << records[i].numOfSectionsTotal << " sections." << endl;
  }
  cout  << "Total number of duplicates: " << duplicates << endl;
}

bool dup(const string &term, const string &section, int &numberOfTermsSeen, StaticArray<Seen, 200> &alreadySeen)
{
  for(int i = 0; i < numberOfTermsSeen; i++)
  {
    if(alreadySeen[i].term == term)
    {
      for (int j = 0; j < alreadySeen[i].numberOfSectionsSeen; j++) if (alreadySeen[i].seenSectionNumbers[j] == section) return true;

      // If duplicate not found, add one
      alreadySeen[i].seenSectionNumbers[alreadySeen[i].numberOfSectionsSeen] = section;
      alreadySeen[i].numberOfSectionsSeen++;
      return false;
    }
  }
  // make a new term in array
  alreadySeen[numberOfTermsSeen].term = term;
  alreadySeen[numberOfTermsSeen].numberOfSectionsSeen++;
  alreadySeen[numberOfTermsSeen].seenSectionNumbers[0] = section;
  numberOfTermsSeen++;
  return false;
}