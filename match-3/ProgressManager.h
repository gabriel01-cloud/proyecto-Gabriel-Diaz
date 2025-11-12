#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ProgressManager
{
private:
	string filename;

public:
	ProgressManager(const string& file = "progreso.xml") {
		filename = file;
		ensureFileExists();
	}
	void ensureFileExists();
	int loadMaxUnlocked();
	void saveMaxUnlocked(int newValue);
};

