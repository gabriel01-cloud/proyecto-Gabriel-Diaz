#include "ProgressManager.h"

void ProgressManager::ensureFileExists()
{
	ifstream in(filename.c_str());
	if (!in.is_open()) {
		ofstream out(filename.c_str(), ios::trunc);
		if (out.is_open()) {
			out << "<Progress><MaxUnlocked>1</MaxUnlocked></Progress>";
			out.close();
		}
	}
	else {
		in.close();
	}
}

int ProgressManager::loadMaxUnlocked()
{
	ifstream in(filename.c_str());
	if (!in.is_open()) return 1;
	string all, line;
	while (getline(in, line))all += line;
	in.close();

	const string openTag = "<MaxUnlocked>";
	const string closeTag = "</MaxUnlocked>";
	size_t a = all.find(openTag);
	size_t b = all.find(closeTag);
	if (a == string::npos || b == string::npos || b <= a) {
		return 1;
	}
	a += openTag.size();
	try {
		int value = stoi(all.substr(a, b - a));
		if (value < 1) {
			return 1;
		}
		return value;
	}
	catch (...) {
		return 1;
	}
}

void ProgressManager::saveMaxUnlocked(int newValue)
{
	if (newValue < 1)newValue = 1;
	ofstream out(filename.c_str(), ios::trunc);
	if (out.is_open()) {
		out << "<Progress><MaxUnlocked>" << newValue << "</MaxUnlocked></Progress>";
		out.close();
	}
}
