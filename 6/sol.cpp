#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;


int
part_one(vector<string> groups)
{
	int count = 0;

	for (string g : groups) {
		count += g.length();
	}

	return count;
}


int
main(int argc, char** argv)
{
	fstream f;
	f.open("data.txt", ios_base::in);
	string line;

	vector<string> groups; /* store string of questions answered - unique letters*/
	string group;

	while (getline(f, line)) {

		if (line.length() == 0) {
			groups.push_back(group);
			group = "";
			continue;
		}

		for (char c : line) {
			if (group.find(string(1, c)) == string::npos) {
				group += c;
			}
		}
	}

	cout << "Sum of counts: " << part_one(groups) << endl;


	return 0;
}