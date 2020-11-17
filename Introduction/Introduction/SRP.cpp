/*
Single Responsibility Principle
*/

#include <fstream>
#include <string>
#include <vector>


/*
=== the voilating way ===
*/
struct JournalOld {
	std::string title;
	std::vector<std::string> entries;

	JournalOld(std::string title) : title(title) {}

	void add(std::string& entry) {
		this->entries.push_back(entry);
	}

	void save(std::string& fileName) {
		std::fstream ofs(fileName);
		for (auto& entry : entries)
			ofs << entry << std::endl;
	}
};

/*
=== the better way ===
*/
struct Journal {
	std::string title;
	std::vector<std::string> entries;

	Journal(std::string &title) : title(title) {}

	void add(std::string &entry) {
		this->entries.push_back(entry);
	}
};

/*
Not adding save and other requirement in the Journal itself.
Journal is not responsible for saving itself. If we wished to change
the attributes or the format of saving, we would have to change the
Journal itself. Hance shift the responsibility of saving
*/
struct PersistentManager {
	static void save(const Journal &j, std::string& fileName) {
		std::ofstream ofs(fileName);
		for (auto& entry : j.entries)
			ofs << entry << std::endl;
	}
};