//By: Anthony Sasso
//Class: CSCN73030 - Fall, 2022
//Created: 2022/09/21 (version 2 began 2022/09/22 but got most of the way through v1 before restarting)
	//Revision History
		//See Github history under Git tab > View Branch History

#include <iostream>
#include <fstream>	//standard io combined with iostream...
#include <vector>	//student list stack
#include <string>	//to allow getline to use strings

using namespace std;

//Define macros used to change file name, version, and simplify code...
#define PRE_RELEASE	//Macro flag for pre-release vs standard mode

#ifdef PRE_RELEASE
	#define DATA_FILE "StudentData_Emails.txt"
#else
	#define DATA_FILE "StudentData.txt"
#endif

#ifdef PRE_RELEASE
	#define VERSION "Pre-Release"	//set version to pre-release based on macro
#else
	#define VERSION "Standard"		//set version to standard if macro is not active
#endif

//define structures used in the program

//student struct for info pulled from file.
#ifdef PRE_RELEASE
	struct STUDENT_DATA {
		string firstName;
		string lastName;
		string email;
	};
#else
	struct STUDENT_DATA {
		string firstName;
		string lastName;
	};
#endif

//Define symbols for debug log macro, just outputs to terminal or doesn't base don compiler flag.
#ifdef _DEBUG
	#define DEBUGLOG(x) std::cout << "DEBUG_LOG: " << x << std::endl;
#else
	#define DEBUGLOG(x)
#endif

int main(void) {

	cout << "CSCN73030F22 Student List Version: " << VERSION << endl << endl;

	ifstream fileStream;
	vector<STUDENT_DATA> studentList;

	fileStream.open(DATA_FILE);

	string currentStudent;	//temp for current student
	while (getline(fileStream, currentStudent)) {
		STUDENT_DATA newStudent;

		char delimiter = ',';	//specify delimiter for substring
		string newLastName = currentStudent.substr(0, currentStudent.find(delimiter));	//get lastname from line
		currentStudent.erase(0, (currentStudent.find(delimiter) + 1));	//have to +1 so it gets , as well.
		newLastName += '\0';	//just to make strings proper for converting to cstr etc.
		newStudent.lastName = newLastName;	//add data to struct
		
		string newFirstName = currentStudent.substr(0, currentStudent.find(delimiter));	//get firstname from line, no need for changing delim or erase since last value (for now)
		newFirstName += '\0';
		newStudent.firstName = newFirstName;

#ifdef PRE_RELEASE
		//added erase here as to not use it in legacy code...
		currentStudent.erase(0, (currentStudent.find(delimiter) + 1));	//have to +1 so it gets , as well.
		string newEmail = currentStudent.substr(0, currentStudent.find(delimiter));
		newEmail += '\0';
		newStudent.email = newEmail;
#endif

		// Use debug log to only output during debug mode and not release
#ifdef PRE_RELEASE	//put second ifdef here even though I could have put this in above one since I think it was better using more for "seperate" parts of code that needed switch-cases?
		DEBUGLOG("New student = " << newStudent.firstName << " " << newStudent.lastName << " " << newStudent.email)
#else
		DEBUGLOG("New student = " << newStudent.firstName << " " << newStudent.lastName)
#endif
		
		studentList.push_back(newStudent);	//add student to stack / vector
	}

	return 1;
}