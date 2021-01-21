///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Kyler Wyatt
// Email:            kylco13@gmail.com
// Label:            A04
// Title:            Assignment 4 - Commenting C++ Code
// Course:           CMPS 3013 - Algorithms
// Semester:         Spring 2021
//
// Description:
//       This program implements a class that allows a linked list to be used just like 
//       an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
//       array elements, but really it traverses the list to find the specified node using
//       an index value. It also overloads the "+" and "-" signs allowing a user to "add"
//       or "push" items onto the end of the list, as well as "pop" items off the end of our 
//       array. This class is not meant to replace the STL vector library, its simply a project
//       to introduce the beginnings of creating complex / abstract data types. 
//
// Usage:
//      - $ ./main filename
//      - This will read in a file containing whatever values to be read into our list/array. 
// Files:    
//      - main.cpp    : driver program
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int A[100]; // creates an linked list of integers of size 100

/**
 * Node
 * 
 * Description:
 *      Creates a node so that we can traverse the list
 *
 * Usage: 
 * 
 *      Initialized upon creation of a list object (Node *Head;)
 *      and used as a pointer throughout the functions.
 *      
 */
struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      Creates a list and includes functions to access members
 *      of the list like an array
 * 
 * Public Methods:
 *              List()
 *      void    Push(int val)
 *      void    Insert(int val)
 *      void    PrintTail()
 *      string  Print()
 *      int     Pop()
 *      List operator+(const List &Rhs)
 *      int operator[](int index)
 *      friend ostream &operator<<(ostream &os, List L)
 * 
 * Private Methods:
 *      None
 * 
 * Usage: 
 * 
 *      List L1;
 *      L1.Push(i);
 *      L1.PrintTail();
 */
class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
      /**
     * Public : List()
     * 
     * Description:
     *      Constructor to initialize the Head and Tail to NULL
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
        /**
     * Public : Push()
     * 
     * Description:
     *      Pushes nodes down the list and adds a new Node to the begginning of the list
     * 
     * Params:
     *      int val : value to be put in the new node
     * 
     * Returns:
     *      None
     */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
        /**
     * Public : Insert()
     * 
     * Description:
     *      Inserts a new node at the end of the list
     * 
     * Params:
     *      int val : value to be put in the new node
     * 
     * Returns:
     *      None
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }
        /**
     * Public : PrintTail()
     * 
     * Description:
     *      Prints the tail node
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }
      /**
     * Public : Print()
     * 
     * Description:
     *      Prints the list in full with arrows between nodes
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      list
     */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }
      /**
     * Public : Pop()
     * 
     * Description:
     *      Decreases the size of the list by 1
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }
      /**
     * Public : operator+()
     * 
     * Description:
     *      Overloads the + operator to add lists together
     * 
     * Params:
     *    const List &Rhs
     * 
     * Returns:
     *    List    NewList
     */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }
      /**
     * Public : operator[]
     * 
     * Description:
     *      Overloads the [] operator 
     * 
     * Params:
     *      int index
     * 
     * Returns:
     *      int Temp->x or int os
     */
    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }
      /**
     * Public : ostream &operator<<
     * 
     * Description:
     *      Prints the list from the os
     * 
     * Params:
     *      ostream &os
     *      ostream &os, List L
     *
     * Returns:
     *      ostream &os
     */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;  // initializes list 1
    List L2;  // initializes list 2

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i); // pushes a new node onto the list from 0-24
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i); // pushes a new node onto the list from 50-99
    }

    //cout << L1 << endl;
    L1.PrintTail(); // prints the tail of List 1
    L2.PrintTail(); // prints the tail of List 2

    List L3 = L1 + L2; // creates a 3rd list that is an addition of the first two
    cout << L3 << endl; // prints List 3

    cout << L3[5] << endl; // prints the fifth index of list 3
    return 0;
}
