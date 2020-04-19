#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"
#include "Cube.h"
using namespace std;
class Editor;



string getFileName(string str)
{
	cout << "Enter the file name: ";
	cin >> str;
	return str;
}



int main(int argc, char *argv[])
{
	string stl_file_name = "./figures/TestFigure.stl";
	if (argc == 2) {
		stl_file_name = argv[1];
	}
	else if (argc > 2) {
		cout << "ERROR: Too many command line arguments" << endl;
		return 0;
	}


	Editor *editor = new Editor;
	string chooser;
	while (true)
	{
		cout << "---------------------------------WELCOME----------------------------------\n| 1 - create cube \n| 2 - create sphere \n| 3 - divide figure \n| 4 - exit\n";
		cin >> chooser;
		if (chooser == "1") //Cube
		{
			editor->initiateCube(stl_file_name);
		}
		else if (chooser == "2") //Sphere
		{
			editor->initiateSphere(stl_file_name);
		}
		else if (chooser == "3") //Split
		{
			editor->initiateSplit(stl_file_name);
		}
		else if (chooser == "4") //Exit
		{
			break;
		}
		else //Error
		{
			system("cls");
			cout << "Error value, try again:\n";
			continue;
		}
		cout << "--------------------------------------------------------------------------\n1 - One more action | 2 - Exit\n";
		cin >> chooser;
		if (chooser == "1") {system("cls"); continue;}
		else if (chooser == "2") break;
		else { system("cls"); cout << "Error value, try again:\n"; continue; }
	}

	delete editor;
	//system("pause");
	return 0;
}