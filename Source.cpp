#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <limits>
#include<fstream> 
#include <iomanip>
#include<conio.h>

using namespace std;
using std::cout;
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	// Declare variables for menu, number value, and exit
	fstream frequencyData; // Allows for file frequency.dat to be read
	bool exit = false; // Allows user to exit loop/program
	string itemName; // For menmu selection 2, specific item lookup
	string item; // For file reading of frequency.dat
	int menuVal; // Menu value
	int count; // For file reading of frequency.dat
	int x; // Allows histogram to have a cleaner look


	// While loop allows user to conitnuously use program until 4 is entered on menu selection
	// Exit message is displayed and exit variable becomes true which quits the loop and ends program
	while (!exit) {

		// Display Menu to user
		std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;
		std::cout << "|" << std::right << std::setfill(' ') << std::setw(46) << "Corner Grocer Sales Tracking Menu";
		std::cout << std::left << std::setfill(' ') << std::setw(16) << " " << "|" << std::endl;
		std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;

		cout << "1: Display a list of items purchased and their frequency." << endl;
		cout << "2: Display the frequency of a specific item purchased." << endl;
		cout << "3: Display a histogram of items purchased." << endl;
		cout << "4: Exit" << endl << endl;
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

		// Get user menu selection
		cin >> menuVal;

		// Switch statement allows proper action to occur once user makes menu selection.
		// If user enters: 
		// 1: A list is displayed of items on input file and the numerical frequency they appear.
		// 2: User can search for specific item frequency on input file
		// 3. A histogram representatoin is displayed of input file and text file frequency.dat 
		//	  created with list of items purchased and frequency.
		// 4: Program exits.
		// Any other input will result in an error message and user returns to menu.
		switch (menuVal) {

			// Cases 1-3 call python functions to take appropriate action.
			// Screen will clear so only relevant information displayed.
			// User must tap any button to continue.
			case 1:
				system("cls"); // Clear screen and show border
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;
				std::cout << "|" << std::right << std::setfill(' ') << std::setw(36) << "Item List";
				std::cout << std::left << std::setfill(' ') << std::setw(26) << " " << "|" << std::endl;
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;

				CallProcedure("TotalFrequency"); // Call Python function
				cout << endl;
				cout << endl;
				cout << "Tap any key to continue..." << endl;
				_getch(); // Wait for user to tap key before clearing screen and returning to menu.
				system("cls");
				break;

			case 2:
				system("cls"); // Clear screen and show border
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;
				std::cout << "|" << std::right << std::setfill(' ') << std::setw(36) << "Item Lookup";
				std::cout << std::left << std::setfill(' ') << std::setw(26) << " " << "|" << std::endl;
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;

				cout << "Enter Item Name: ";
				cin >> itemName;  // Get item name

				system("cls");
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;
				std::cout << "|" << std::right << std::setfill(' ') << std::setw(36) << "Item Lookup";
				std::cout << std::left << std::setfill(' ') << std::setw(26) << " " << "|" << std::endl;
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;

				cout << itemName << ": " << callIntFunc("SpecificFrequency", itemName) << endl; // Call Python function
				cout << endl;
				cout << endl;
				cin.clear();
				cout << "Tap any key to continue..." << endl;
				_getch(); // Wait for user to tap key before clearing screen and returning to menu.
				system("cls");
				break;

			case 3:
				system("cls"); // Clear screen 
				CallProcedure("WriteFile"); // Call Python function
				frequencyData.open("frequency.dat.txt", ios::in); // Open frequency.dat.txt file

				if (!frequencyData.is_open()) { // If open file fails an error message displays
					cout << "Could not open file frequency.dat.txt." << endl;
					break;
				}

				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;
				std::cout << "|" << std::right << std::setfill(' ') << std::setw(36) << "Item Histogram";
				std::cout << std::left << std::setfill(' ') << std::setw(26) << " " << "|" << std::endl;
				std::cout << std::setfill('*') << std::setw(64) << "*" << std::endl;

				// Loop gets item and item count from file until end and then outputs item name and a histogram
				// representation of each item count where charcter '$' = 1.
				while (!frequencyData.eof()) {
					if (frequencyData >> item) {
						frequencyData >> count;
						x = item.length();
						cout << item;
						for (int y = 0; y < 15 - x; y++) {
							cout << " ";
						}
						for (int i = 0; i < count; i++) {
							cout << "$";
						}
						cout << endl;
					}
				}

				frequencyData.close(); // Close file
				cout << endl;
				cout << endl;
				cout << "Tap any key to continue..." << endl;
				_getch(); // Wait for user to tap key before clearing screen and returning to menu.
				system("cls");
				break;

			// User exits program
			case 4:
				system("cls"); // Screen cleared and goodbye message dispolayed.
				cout << "The program has ended. Goodbye." << endl;
				exit = true; // Allows for program to exit.
				break;

			// The default case occurs when the user makes an invalid selection. 
			// A message is displayed and the user can try again.
			default:
				system("cls");
				cout << "ERROR: Invalid selection." << endl;
				cout << "Please only enter 1, 2, 3, or 4." << endl << endl;
				cin.clear();// Clear error flag.
				cin.ignore();
				break;
		}
	}
}