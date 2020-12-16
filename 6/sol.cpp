#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct group {
	vector<string> people;
};


int
part_one(vector<struct group> groups)
{
	int count = 0;

	vector<string> answers; /* strings of unique answers for each group */

	for (struct group g : groups) { /* disgusting - was neater before the second part... */
		string unique;

		for (string person : g.people) { /* iterate through all the people's answers in a group */
			for (char c : person) {
				if (unique.find(string(1, c)) == string::npos) { /* if answer not already considered, count it */
					unique += c;
				}
			}
		}

		answers.push_back(unique);
	}

	for (string a : answers) {
		count += a.length();
	}

	return count;
}

int
part_two(vector<struct group> groups)
{
	int count = 0;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";

	vector<string> answers;

	/* To get shared answers, find the intersection of the individual sets of each person in the group's answers */
	for (struct group g : groups) {
		set<char> similar(alphabet.begin(), alphabet.end());

		for (string person : g.people) {
			set<char> per(person.begin(), person.end());
			set<char> newSim;

			//set_intersection(per.begin(), per.end(), similar.begin(), similar.end(), similar.begin(), similar.end()); /* requires sorted sets... */
			/* manual set intersection it is then... */
			for (char c : per) {
				if (similar.count(c) > 0) {
					newSim.insert(c);
				}
			}

			similar = newSim;
		}
		string a(similar.begin(), similar.end());

		answers.push_back(a);

	}

	for (string a : answers) {
		count += a.length();
	}

	return count;
}


int
main(int argc, char** argv)
{
	fstream f;
	f.open("data.txt", ios_base::in);
	string line;

	vector<struct group> groups; /* store string of questions answered - unique letters*/
	vector<string> people;
	struct group g;

	while (getline(f, line)) {

		if (line.length() == 0) {
			g.people = people;
			groups.push_back(g);
			g = {};
			people = {};
			continue;
		}

		people.push_back(line);
	}

	//while (getline(f, line)) data.push_back(line); /* get all the data... */

	cout << "Part one: " << part_one(groups) << endl;

	cout << "Part two: " << part_two(groups) << endl;


	return 0;
}