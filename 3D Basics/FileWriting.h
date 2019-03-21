#pragma once
// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

class FileWriting
{
public:
	FileWriting(std::string fileName);
	~FileWriting();

	void WriteToFile(std::string stringToWrite);

private:
	std::string fileName;
};

