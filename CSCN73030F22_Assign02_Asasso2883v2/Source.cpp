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
//Define macros used to change file name etc and simplify code...
#define DATA_FILE "StudentData.txt"

//student struct for info pulled from file.
struct STUDENT_DATA {
	string firstName;
	string lastName;
};


int main(void) {

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

		studentList.push_back(newStudent);	//add student to stack / vector
	}

	return 1;
}