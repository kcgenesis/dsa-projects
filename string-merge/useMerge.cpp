#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale>
#include <list>
#include <stack>
using namespace std;


/*
	
	Kirk Cameron -- String Merge
	
	This program checks whether a string is a merge of two other strings.
	It uses the two operand strings as the axes of a matrix of booleans.  
	The values of each of these strings at a slot in this matrix is compared to the 
	value of the merge-string in question at the sum of the matrix indices.


	The subproblem for stepping through the matrix involves checking the position
	below and to the right of the current position, and then updating to the 
	appropriate position.

	The current position is a "trap spot" if the positions below and to the 
	right of the current position are both zeroes.  "Trap-spots" are dealt 
	with by looping through the matrix again from bottom right to top left, 
	turning them from 1's (good merge paths) to	zeroes (forbidden paths).

*/


bool cMat[1000+1][1000+1];

void printm(bool (*m)[1001],int x,int y)
{
	for(int i=0;i<x;++i)
	{
		for(int j=0;j<y;++j)
		{
			if (m[i][j]==true)
			{
				cout << "[" << (int)m[i][j] << "]";
			}
			else
			{
				cout << "[" << " " << "]";
			}
			
		}
		cout<<endl;
	}
	cout<<"\n\n";
}

int main() 
{
	locale loc;
	string fname;
	string f2name;

	
	cout<<"Please enter name of input file: "<<endl;
	cin >> fname;
	cout << "Please enter name of the output file: ";
	cin >> f2name;
	

	//fname = "load.txt";
	//f2name = "out.txt";


	ifstream infile (fname.c_str());
	if (!infile) 
	{
		cerr << "Error: could not open " << infile << endl;
		exit(1);
	}
	ofstream outfile (f2name.c_str());
	if (!outfile) 
	{
		cerr << "Error: could not open " << outfile << endl;
		exit(1);
	}

	if (infile.is_open() && outfile.is_open())
	{
		string A,B,C;
		string line;
		string merge;
		string fail = "*** NOT A MERGE ***";
		int x_pos, y_pos;
		int xdim, ydim;
		int ct = 0;
		while (getline(infile,line))
		{
			if(ct==0)
			{
				A = line;
			}
			else if(ct==1)
			{
				B = line;
			}
			else if(ct==2)
			{
				C = line;
			}

			ct++;
			if (ct==3)
			{
				merge = "";
				xdim = (int)A.length()+2;
				ydim = (int)B.length()+2;
				//clear
				for(int i=0;i<xdim;++i)
				{
					for(int j=0;j<ydim;++j)
					{
						cMat[i][j] = false;
					}
				}
				

				//adjust to inner
				xdim--;
				ydim--;
				for(int m=0;m<xdim;++m)
				{
					for(int n=0;n<ydim;++n)
					{
						if((C[m+n-1] != A[m-1])&&(C[m+n-1] != B[n-1]))
						{
							cMat[m][n] = false;
						}
						else
						{
							cMat[m][n] = true;
						}
					}
				}
				
				ydim--;
				xdim--;
				
				for(int n=ydim-1;n>=0;--n)
				{
					if((cMat[xdim+1][n]==false)&&(cMat[xdim][n+1]==false))
					{
						cMat[xdim][n] = false;
					}	
				}

				
				

				
				xdim--;
				for(int m=xdim;m>=0;--m)
				{
					for(int n=ydim;n>=0;--n)
					{
						if((cMat[m+1][n]==0)&&(cMat[m][n+1]==0))
						{
							cMat[m][n] = 0;
						}
					}
				}
				xdim++;
				x_pos = 0;
				y_pos = 0;
				for (int n=0; n<(int)C.length(); ++n)
				{
					
					if((x_pos == xdim)&&(y_pos == ydim))
					{
						break;
					}
					else
					{

						if ((cMat[x_pos][y_pos+1] == false)&&(cMat[x_pos+1][y_pos] == false))
						{
							merge = fail;
						} 
						else if ((cMat[x_pos][y_pos+1] == false)&&(cMat[x_pos+1][y_pos] == true))
						{
							merge += toupper(C[n],loc);
							x_pos++;
						} 
						else if((cMat[x_pos][y_pos+1] == true)&&(cMat[x_pos+1][y_pos] == false))
						{
							merge += C[n];
							y_pos++;
						}
						else 
						{
							merge += toupper(C[n],loc);
							x_pos++;
						}
					}
				}
				outfile << merge << endl;
				//printm(cMat,(int)A.length()+2,(int)B.length()+2);
				ct=0;
			}
		}
		outfile.close();
		infile.close();
	}	
	return 0;
}





