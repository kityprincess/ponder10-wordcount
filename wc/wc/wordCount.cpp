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
#include <iostream>
#include <fstream>

using namespace std;
typedef int Count;

/*****************************************************
* READFILE
* Read in the file and search for the word
*****************************************************/
void readFile(Map <string, Count> & counts, const string & fileName)
{
   string word;

   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Error, cannot read file";
      fin.close();
   }

   while (!fin.eof() && fin >> word)
   {
      counts[word] += 1;
   }
   fin.close();
}

/*****************************************************
* DISPLAY
* Display the word & its count
*****************************************************/
void display(Map <string, Count> & counts)
{
   string word = "";

   cout << "What word whose frequency is to be found. Type ! when done\n";

   while (true)
   {
      cout << "> ";
      cin >> word;
      if (word == "!")
         break;
      cout << "\t" << word << " : " << counts[word] << endl;
   }
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string fileName;
   Map <string, Count> counts;

   cout << "What is the filename to be counted? ";
   cin >> fileName;
   readFile(counts, fileName);
   display(counts);
}