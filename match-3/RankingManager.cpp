#include "RankingManager.h"

RankingManager::RankingManager(const string& file) : filename(file), count(0) {
	std::ifstream in(filename.c_str());
	if (!in.is_open()) {
		std::ofstream out(filename.c_str(), std::ios::trunc);
		out.close();
	}
	else {
		in.close();
	}
	load();
}

void RankingManager::load() {
	ifstream in(filename.c_str());
	count = 0;
	if (!in.is_open()) return;

	while (count < MAX_ENTRIES && in >> entries[count].name >> entries[count].score) {
		count++;
	}
	in.close();
}

void RankingManager::save() {
	ofstream out(filename.c_str(), std::ios::trunc);
	if (!out.is_open()) return;
	for (int i = 0; i < count; i++) {
		out << entries[i].name << " " << entries[i].score << "\n";
	}
	out.close();
}

void RankingManager::addEntry(const std::string& name, int score)
{
	if (count < MAX_ENTRIES) {
		entries[count].name = name;
		entries[count].score = score;
		count++;
	}
	save();
}

void RankingManager::printTop(int n)
{
	if (count == 0) {
		std::cout << "[Ranking] No hay registros aún.\n";
		return;
	}
	cout << "[Ranking Top " << n << "]\n";
	for (int i = 0; i < count && i < n; i++) {
		std::cout << (i + 1) << ". " << entries[i].name << " - " << entries[i].score << "\n";
	}
}
