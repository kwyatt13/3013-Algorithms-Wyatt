/*
  Author: Kyler Wyatt
  Email: kylco13@gmail.com
  Label: P02
  Title: Processing in Linear Time
  Course: 3013
  Semester: Spring 2021

  Description:
          This program reads a dctionary into a vector and then converts it into a linked list which can be searched by getching keyboard inputs and finding partial matches.

  Usage:
          Type keys to search the dictionary, type a capital Z to end the program.

  Files:
          dictionary.txt
          my_getch.hpp
          termcolor.hpp
          timer.hpp
          main.cpp
*/

#include "my_getch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>


using namespace std;
/**
 * Struct wordNode
 * 
 * Description:
 *      creates an object that is able to hold a word and a next pointer.
 * 
 * Public Methods:
 *      - wordNode()
 *
 * Private Methods:
 *      - None
 *    
 * 
 * Usage: 
 * 
 *     wordNode x;              
 */

struct wordNode
{
  string word;
  wordNode* next;
  wordNode()
  {
    word = "";
    next = NULL;
  }
};

/**
 * Class LinkedList
 * 
 * Description:
 *      creates a linked list of wordNodes
 * 
 * Public Methods:
 *      - LinkedList()
 *      - [int] getSize
 *      - [void] New_Node
 *      - [void] Print
 *      - [vector<string>] FindWords
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *      LinkedList x; x.New_Node[wordNode y];
 *      
 */

class LinkedList
{
protected:
  wordNode* head;
  wordNode* tail;
  int size;
public:;

  LinkedList()            
  {
    head = NULL;
    tail = NULL;
    size = 0;
  }

  /**
     * Public : getSize
     * 
     * Description:
     *      gets the size of the linked list;
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      [int] size   : the size of the linked list
     */
int getSize()
{
  return size;
}
  /**
     * Public : New_Node
     * 
     * Description:
     *      Add a wordNode onto the linked list
     * 
     * Params:
     *      [wordNode*]    :  A pointer to an object of the type wordNode
     * 
     * Returns:
     *      None
     */
  void New_Node(wordNode* letter)
  {
    if(head == NULL)
    {
      head = tail = letter;
    }
    else
    {
      tail->next = letter;
      tail = letter;
    }
    size++; 
  }
  /**
     * Public : FindWords
     * 
     * Description:
     *      Searches the dictionary for matches to the typed string
     * 
     * Params:
     *      [string] text   : the word that was read in
     * 
     * Returns:
     *      [vector<string>] matches   : a vector of the matches found
     */
  vector<string> FindWords(string text) 
  {
    vector<string> matches; // to hold any matches
    wordNode* current = head;
    int length;
    while (current != NULL)
    {
      string temp = " ";
      temp = current->word;
      length = text.length();
      if (temp.substr(0,length)==text)
      {
        matches.push_back(temp);
      }
      current = current->next;
    }
    return matches;
  }
  /**
     * Public : Print
     * 
     * Description:
     *      Prints the linked list of wordNodes
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  void Print()
  {
    wordNode* current = head;
    while (current != NULL)
    {
      cout << current->word << endl;
      current = current->next;
    }
  }
};

// driver of the program
int main() 
{
    ifstream infile;
    infile.open("dictionary.txt");
    char k;                         // k = typed character
    string word = "";               // var to concatenate letters to
    vector<string> LoadDictionary;  // vector of words
    vector<string> matches;         // holds the matches
    LinkedList List;                
    Timer T;                        // time to read in the words
    Timer T2;                       // time to find matches
    int Results;                    // the number of results found

    T.Start();
    //Create a vector of the dictionary names
    while(!infile.eof())
    {
      string readWords;
      infile >> readWords;
      LoadDictionary.push_back(readWords);
    }
    //Create the linked list from the vector of dictionary names
    for (int i = 0;i < LoadDictionary.size();i++)
    {
      wordNode* temp = new wordNode;
      string HoldWord = LoadDictionary[i];
      temp->word = HoldWord;
      List.New_Node(temp);
    }
    T.End();



    // print out the time to read in the dictionary file
    cout << T.Seconds() << " seconds to read in and create a linked list" << endl;
    cout << T.MilliSeconds() << " millisecods to read in and create a linked list" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') 
    {
        
        // checks for a backspace and if pressed deletes
        // last letter from "word".
        cout << termcolor::yellow << "Current Substring: " << termcolor::reset;
        if ((int)k == 127) 
        {
            if (word.size() > 0) 
            {
                word = word.substr(0, word.size() - 1);
            }
        } 
        else 
        {
            // Make sure a letter is pressed
            if (!isalpha(k)) 
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // Any letter with ascii value >= 97 is capital so we
            // lower it.
            // this seems backwards but is the only way it would work
            if ((int)k < 97) 
            {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any words in the array that partially match
        T2.Start();                   // start it
        matches = List.FindWords(word);
        T2.End();                     // end the current timer
        Results = matches.size();             //number of 
        
        

        vector<string>Matches(10);
        if ((int)k != 32) 
        { 
            // prints the word if it is not a space
            // gives the text some color
            cout << termcolor::on_bright_green << termcolor::blue << word << endl << termcolor::reset;
            cout << Results << " words found in " << T2.Seconds() << " seconds\n";
            // print the top ten matches
            if (matches.size() > 10)
            {
              for(int i = 0; i < 10; i++)
              {
                cout << termcolor::magenta;
                Matches[i] = matches[i];
                cout << Matches[i] << " ";
                cout << termcolor::reset;
              }
            }
            else  // print all the matches there is
            {
              for (int i = 0; i < Results; i++)
              {
                cout << termcolor::magenta;
                Matches[i] = matches[i];
                cout << Matches[i] << " ";
                cout << termcolor::reset;
              }
            }
            cout << endl << endl;
        }

    }

    infile.close();
    return 0;
}
