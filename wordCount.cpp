/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <fstream>
using namespace std;
typedef int Count;

void readFile(Map <string, Count> & counts, const string & fileName);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string wordFrequency;
   string fileName;
   Map <string, Count> counts;
   cout << "What is the filename to be counted? ";
   cin >> fileName;
   readFile(counts, fileName);
   
   cout << "What word whose frequency is to be found. Type ! when done\n";
   cin >> wordFrequency;
   
   MapIterator < string, Count > it;
   for (it = counts.begin(); it != counts.end(); ++it)
      cout << "  " << *it;
      
}

/********************************************************
 * READ FILE
 * Opens and reads a file
 *********************************************************/
void readFile(Map <string, Count> & counts, const string & fileName)
{
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Error, cannot read file ";
      fin.close();
   }
   
   string word;
   
   while(!fin.eof() && fin >> word)
   {
      counts[word]  += 1;
     // cout << word;
     // cout << endl;
   }
   fin.close();
}
