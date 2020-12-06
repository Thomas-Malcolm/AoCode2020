#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct passport {
	int byr, iyr, eyr, hgt;
	string hcl, ecl, pid, cid;

	int fieldCount; /* if count is 8 then we know is valid - small optimisation */
};

/**
 * Quick function to hash a string so it can be switch'd up
 * Warning: do not use in production code...
 */
long int constexpr str_hash(const char* s)
{
	int field[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}; /* try reduce risk of collisions */
	int i = 0, len = 11; /* field length */

	long int hash = 0;

	for (int j = 0; j < strlen(s); j++) {
		hash += (int) s[j] * field[i++];
		i %= len;
	}

	return hash;

}

/**
 * Data format inconsistent - can't just pipe (is that what << is called?) into a variable
 */
void fill_passport(struct passport& p, string line)
{
	string tok, delim = ":";
	size_t pos;

	pos = line.find(delim);

	string type = line.substr(0, pos), val = line.substr(pos + 1);

	switch (str_hash(type.c_str())) {
		case str_hash("byr"):
			p.byr = stoi(val);
			break;
		case str_hash("iyr"):
			p.iyr = stoi(val);
			break;
		case str_hash("eyr"):
			p.eyr = stoi(val);
			break;
		case str_hash("hgt"):
			p.hgt = stoi(val);
			break;
		case str_hash("hcl"):
			p.hcl = val;
			break;
		case str_hash("ecl"):
			p.ecl = val;
			break;
		case str_hash("pid"):
			p.pid = val;
			break;
		case str_hash("cid"):
			p.cid = val;
			break;
		default:
			cout << "Lol whoops" << endl;
			exit(1);
	}

	p.fieldCount++;
}

int
part_one(const vector<struct passport> pports)
{
	int count = 0;



	for (struct passport p : pports) {
		if (p.fieldCount == 8) { /* auto accept - all fields there */
			count++;
			continue;
		}

		if ((p.fieldCount >= 7) && (p.cid.empty())) { /* yehhh ok get in there */
			count++;
			continue;
		}
	}		

	return count;
}

int
main(int argc, char** argv)
{
	vector<struct passport> pports;

	struct passport pp;
	string line;

	fstream f;
	f.open("data.txt", ios_base::in);

	while (getline(f, line)) {

		if (line.length() == 0) {
			pports.push_back(pp);
			pp = {};
			continue;
		}

		string entry;
		stringstream s(line);

		while (s >> entry) {
			fill_passport(pp, entry);
		}	
			
	}

	pports.push_back(pp); /* stupid file not being newline terminated */

	cout << "Part one: " << part_one(pports) << endl;

	return 0;
}