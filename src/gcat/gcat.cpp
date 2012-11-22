/*
* Copyright © 2012 Ryan Barrie
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<string> files;

	bool flagN = false;

	for(int i = 1; i < argc; i++)
	{
		string curarg = argv[i];
		if(curarg[0] == '-')
		{
			if(curarg == "-v" || curarg == "--version")
			{
				cout << "gcat 0.1" << endl;
				return 0;
			}
			else if(curarg == "-h" || curarg == "--help")
			{
				cout << "Usage: cat file1 [file2] ... [-n]" << endl;
				cout << "-n: number lines" << endl;
				return 0;
			}
			else if(curarg == "-n" || curarg == "--number")
			{
				flagN = true;
			}
			else
			{
				cout << "Option " << curarg << " not recognized." << endl;
				return -1;
			}
		}
		else
		{
			files.push_back(curarg);
		}
	}

	long long curline = 0;

	for(unsigned int i = 0; i < files.size(); i++)
	{
		ifstream inFile;
		inFile.open(files[i].c_str(), ios::in);

		if(inFile)
		{
			string in;
			while(getline(inFile, in))
			{
				if(flagN)
				{
					curline++;
					cout << curline << ". ";
				}
				cout << in << endl;
			}
		}
	}
}
