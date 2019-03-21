#include "FileWriting.h"

#include <iostream>
#include <fstream>
using namespace std;

FileWriting::FileWriting(std::string fileName)
{
	this->fileName = fileName;
}


FileWriting::~FileWriting()
{
}

void FileWriting::WriteToFile(std::string stringToWrite)
{
	/*ofstream myfile (fileName);
	myfile.open(fileName);
	myfile << stringToWrite.c_str();
	myfile.close();*/
	fstream file; //object of fstream class

   //opening file "sample.txt" in out(write) mode
	file.open("Output.txt", ios::out);

	if (!file)
	{
		cout << "Error in creating file!!!" << endl;
		return;
	}

	cout << "File created successfully." << endl;
	//write text into file
	file << stringToWrite.c_str();
	//closing the file
	file.close();

	//again open file in read mode
	file.open("sample.txt", ios::in);

	if (!file)
	{
		cout << "Error in opening file!!!" << endl;
		return;
	}

	//read untill end of file is not found.
	char ch; //to read single character
	cout << "File content: ";

	while (!file.eof())
	{
		file >> ch; //read single character from file
		cout << ch;
	}

	file.close(); //close file

}
