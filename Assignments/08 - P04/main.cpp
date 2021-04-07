/*
  Author: Kyler Wyatt
  Email: kylco13@gmail.com
  Label: P04
  Title: Processing in Trie Tree Time
  Course: 3013
  Semester: Spring 2021

  Description:
          This program reads a dictionary into a vector and then converts it into a trie tree which can be 
          searched by getching keyboard inputs and finding partial matches.

  Usage:
          Type keys to search the dictionary, type a capital Z to end the program.

  Files:
          dictionary.txt
          my_getch.hpp
          termcolor.hpp
          timer.hpp
          main.cpp
*/
#include <iostream>
#include "timer.hpp"
#include <string>
#include "termcolor.hpp"
#include <vector>
#include <fstream>
#include "my_getch.hpp"
#include <algorithm>

using namespace std;

// defines the character size of 26 for the alphabet
#define CHAR_SIZE 26


/*
    Struct Name: Trie_Node

    Description:
        A node that holds a string for a
        word and a pointer to the next wordNode

    Public Methods:
        Trie_Node()

    Private Methods:
        - None

    Usage:
        - Creates Trie Tree Node for a Prefix Tree

 */

struct Trie_Node
{
    bool Leaf;
    string Word;
    Trie_Node* Character[CHAR_SIZE];

    Trie_Node()
    {
        Leaf = false;
        Word = "";

        for (int i = 0; i < CHAR_SIZE; i++)
        {
            this->Character[i] = nullptr;
        }
    }

};


/*
    Class Name: PrefixTree

    Description:
        This class creates the Trie Tree made of Trie_Nodes

    Public Methods:
        - PrefixTree() 
        - void Insert_Data(string word)
        - vector<string> Find(string text)

    Private/Protected Methods:
        - void Find(Trie_Node* &Current, string text)

    Usage:
        Creates and initializes the prefix tree
*/

class PrefixTree
{
protected:
    Trie_Node* Root;
    vector<string> Search_Results;

    /*
    Protected : Find(Trieode* &Current, string text)

    Description:
        Finds results for the prefix and saves them to the results

    Params:
        - Trie_Node* &Current
        - string text

    Returns:
        - None, Void
*/
    void Find(Trie_Node* &Current, string text)
    {
        if (Current->Leaf)
        {
            Search_Results.push_back(text);
        }


        for (int i = 0; i < 26; i++)
        {
            if (Current->Character[i])
            {
                Find(Current->Character[i], text + char(i + 65));
            }
        }
    }

public:

    /*
        Constructor : PrefixTree

        Description:
            Creates a new dynamic memory stored Trie_Node

        Params:
           - None

        Returns:
           - None
    */
    PrefixTree()
    {
        Root = new Trie_Node;
    }

    /*
        Public : Find(string text)

        Description:
            This function recursively finds results for the current string
            and returns the vector of results

        Params:
            - string text

        Returns:
            - vector<string> Results
    */
    vector<string> Find(string text)
    {
        Trie_Node* Current = Root;

        if (Search_Results.size() != 0)
        {
            Search_Results.clear();
        }

        for (int i = 0; i < text.length(); i++)
        {
            Current = Current->Character[text[i] - 65];
        }

        Find(Current, text);
        return Search_Results;                         // return the vector of results
    }

        /*
    Public : Insert_Data(string text)

    Description:
        This method assigns a trie node to each character in the dictionary
        to help create the tree

    Params:
        - string text

    Returns:
        - None, void
    */
    void Insert_Data(string word)
    {
        Trie_Node* Current = Root;

        for (int i = 0; i < word.size(); i++)
        {
            if (Current->Character[word[i] - 65] == nullptr)
            {
                Current->Character[word[i] - 65] = new Trie_Node();
            }

            Current = Current->Character[word[i] - 65];
        }

        Current->Leaf = true;
    }

};


int main()
{
    ifstream infile;
    infile.open("dictionary.txt");

    PrefixTree The_Tree;
    vector<string> Dictionary;      // words are read into this

    char k;                 // holder for character being text
    string word = "";       // default blank word
    vector<string> Matches; // list of matches found

    string Top_Results[10];   // holds the first 10 results
    int SearchResults;        // # of results


    Timer T1;                    
    T1.Start();                  // times how long it takes to read and load the data

    while (!infile.eof())               // reads in the words and saves them to Dictionary
    {
        string the_word;

        infile >> the_word;

        Dictionary.push_back(the_word);
    }

    T1.End();

    cout << T1.Seconds() << " seconds to read in the data.\n";


    for (int z = 0; z < Dictionary.size(); z++)
    {
        string Temp = Dictionary[z];

        The_Tree.Insert_Data(Temp);
    }

    cout << endl << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // the letter Z terminates the program
    while ((k = getch()) != 'Z')
    {

        // a backspace deletes the last letter of the word
        if ((int)k == 127)
        {
            if (word.size() > 0)
            {
                word = word.substr(0, word.size() - 1);
            }
        }

        else
        {
            // makes sure only letters are pressed
            if (!isalpha(k))
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // converts words from capital to lowercase
            if ((int)k >= 97)
            {
                k -= 32;
            }
            word += k; // append char to word
        }


        Timer T2;           // Timer for how long it takes to return word suggestions and total words found

        T2.Start();
        Matches = The_Tree.Find(word);
        T2.End();

        SearchResults = Matches.size();


        if ((int)k != 32)   // only prints non spaces
        { 
            cout << "Keypressed: " << termcolor::bright_green << k << " = " 
            << termcolor::bright_red << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::bright_green << word 
            << termcolor::reset << endl;
            cout << termcolor::bright_green << SearchResults << " words found in " 
            << termcolor::bright_red << T2.Seconds() 
            << termcolor::reset << " seconds" << termcolor::reset << endl;

            // prints out the first 10 results
            if (Matches.size() >= 10)
            {
                for (int i = 0; i < 10; i++)
                {
                    Top_Results[i] = Matches[i];
                    cout << Top_Results[i] << " ";
                }
            }

            else
            {
                for (int j = 0; j < Matches.size(); j++)
                {
                    Top_Results[j] = Matches[j];
                    cout << Top_Results[j] << " ";
                }
            }

            cout << endl << endl;
        }
    }

    infile.close();
    return 0;
}
