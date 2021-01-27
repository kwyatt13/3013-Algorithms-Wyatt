///////////////////////////////////////////////////////////////////////////////
//
// Author:           Kyler Wyatt
// Email:            kylco13@gmail.com
// Label:            P01
// Title:            Program 01 - Resizing the Stack
// Course:           3013
// Semester:         Spring 2021
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack{
private:
  int *A;           // pointer to array of int's
  int top;          // top of stack 

public:
double size;         // current max stack size
int resize_count = 0; 
 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(){
    size = 10;
    A = new int[size];
    top = -1;
  }

 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(int s){
    size = s;
    A = new int[s];
    top = -1;
  }

 /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
  bool Empty(){
    return (top <= -1);
  }
  
 /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
  bool Full(){
    return (top >= size-1);
  }

 /**
  * Public bool: TooSmall
  * 
  * Description:
  *      Stack too small?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
  bool TooSmall(){
    return (size > 10 && top <= size * 0.15);
  }
 /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
  int Peek(){
    if(!Empty()){
      return A[top];
    }
    
    return -99; // some sentinel value
                // not a good solution
  }

 /**
  * Public void: Pop
  * 
  * Description:
  *      Removes top value from the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void Pop(){
if(!Empty()){
    top--;
    }
    CheckResize();

  }

 /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void Print(){
    for(int i=0;i<=top;i++){
      cout<<A[i]<<" ";
    }
    cout<<endl;
  } 

 /**
  * Public void: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      NULL
  */
  void Push(int x){
    CheckResize();
    A[++top] = x;
  }

 /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void ContainerGrow(){
    int newSize = size*2;       // double size of original
    int *B = new int[newSize];  // allocate new memory

    for(int i=0;i<size;i++){    // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                // delete old array

    size = newSize;             // save new size

    A = B;                      // reset array pointer
  }

   /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void ContainerShrink(){
    int newSize = size / 2;       // halves size of original
    int *B = new int[newSize];  // allocate new memory
    for(int i=0;i<size / 2;i++){    // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                // delete old array

    size = newSize;             // save new size

    A = B;                      // reset array pointer

  }

	/**
	 * Public void: CheckResize
	 *
	 * Description: Checks to see whether the stack is full or empty
   *              and calls the function to resize the stack
	 * Params: None
	 * Returns: None
	 */
	void CheckResize()
	{
		if (Full())
		{
			ContainerGrow();	
			resize_count++;	
		}
		if(TooSmall())
		{
			ContainerShrink();
			resize_count++;		
		}
	}

};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main() {
  ofstream outfile;
  ifstream infile;
  infile.open("nums_test.dat");
  outfile.open("Output.txt");

  outfile << "######################################################################\n";
  outfile << "Program 1 - Resizing the Stack\n";
  outfile << "CMPS 3013\n";
  outfile << "Kyler Wyatt\n";

  ArrayStack stack;

  int input;
  int max = stack.size;
  int end_size;

  while(!infile.eof())
  {
      infile >> input;

      if (input%2==0)
      {
        stack.Push(input);
        if (max < stack.size)
        {
          max = stack.size;
        }
      }
      else
      {
        stack.Pop();
      }
      end_size = stack.size;
  }
  int count = stack.resize_count;     //Tracks number of time stack resizes

  outfile <<"Max Stack Size: "
          << max
          <<"\nEnd Stack Size: "
          << end_size
          <<"\nStack Resized: "
          <<count
          <<" times\n"
          << "######################################################################";
outfile.close();

return 0;
}
