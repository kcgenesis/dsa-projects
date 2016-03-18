// 
// This program allows the user to manipulate a binary heap.
// The program only inserts string ids with associated keys
// into the heap. The heap class, however, is capable of storing
// arbitrary pointers along with each heap item.
//

#include <iostream>
#include <fstream> 
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <locale> 
#include <cstdlib>
#include <string>
#include "heap.h"

using namespace std;
// Read an integer from standard input; if a non-integer is in the
// buffer, the state is fixed and the user is re-prompted;
// either way, the remainder of the buffer is cleared
void getInteger(string message, int &ref)
{
  bool inputGood = false;
  while (!inputGood) 
  {
    inputGood = true;

    cout << message;
    cin >> ref;

    if (!cin) {
      // Non-integer in input buffer, get out of "fail" state
      cin.clear();
      inputGood = false;
    }
    while (cin.get() != '\n'); // clear buffer
  }
}

int main()
{
  int capacity = 0;
  int option;
  string stringTmp;
  int key, id;
  int retVal;
  string line;
  string cmdfile = "load.txt";
  ifstream file1 (cmdfile.c_str());
  if (!file1) 
  {
    cerr << "Error: could not open " << file1 << endl;
    exit(1);
  }

  if (file1.is_open())
  {
    capacity = 1000;
    heap myHeap1(capacity);
    string args[5];
    while (getline(file1,line))
    {
      int i;
      for(i=0;i<5;i++)
      {
        args[i] = "";
      }
      i = 0;
      for (string::iterator it = line.begin();it != line.end();it++)
      {
        if (*it != ' ')
        {
          args[i] += *it;
        }
        else
        {
          i++;
          args[i] = "";
        }
      } 
      cout<<"\n\n\narguments: "<<args[0]<<" "<<args[1]<<" "<<args[2]<<" "<<endl;

    if (args[0][0] == '1') //insert
    {
      stringTmp = args[1];
      key = atoi(args[2].c_str());
      retVal = myHeap1.insert(stringTmp, key);
      cout << "Call to 'insert' returned: " << retVal << endl;
      myHeap1.print();
    }
    else if (args[0][0] == '2') //setkey
    {
      stringTmp = args[1];
      key = atoi(args[2].c_str());
      retVal = myHeap1.setKey(stringTmp, key);
      cout << "Call to 'setKey' returned: " << retVal << endl;
      myHeap1.print();
    }
    else if (args[0][0] == '3') //remove
    {
      stringTmp = args[1];
      key = atoi(args[2].c_str());
      retVal = myHeap1.remove(stringTmp, &key);
      cout << "Call to 'delete' returned: " << retVal << endl;
      if (retVal == 0) {
       cout << "Deleted item with string id " << stringTmp <<endl
            << " and key " << key << endl;
      }
      myHeap1.print();
    }
    else if (args[0][0] == '4') //deleteMin
    {
      retVal = myHeap1.deleteMin(&stringTmp, &key);
      cout << "Call to 'deleteMin' returned: " << retVal << endl;
      if (retVal == 0) {
        cout << "Deleted item with string id " << stringTmp <<endl
             << " and key " << key << endl;
      }
      myHeap1.print();
    }
    else if (args[0][0] == '5')
    {
      cout << "\nGoodbye!" << endl;
      exit(0);
    }
    else 
    {
      //cerr << "Error, that input is not valid!" << endl;
      //exit (1);
      cout<<"doin nothing"<<endl;
    }

    //cerr << "Error, we should never get here!" << endl;
    //exit (1);
  }
 }   
  file1.close();
}

