#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void
parse_diffs(int& a, int& b, string diff)
{
	string tok, delim = "-";
	size_t pos;

	pos = diff.find(delim);

	a = stoi(diff.substr(0, pos));
	b = stoi(diff.substr(pos+1));
}


/*
 * Check if pwd has letter in exactly one of l or r indices (1-based)
 */
bool
valid_part2(int l, int r, char let, string pwd)
{

	l--;
	r--;

	if (pwd.length() < l) {
		return false;
	}

	if (pwd.at(l) == let) {
		if (pwd.at(r) == let) {
			return false;
		} else {
			return true;
		}
	}

	if (pwd.length() > r) {
		if (pwd.at(r) == let) {
			return true;
		}
	}

	return false;
}


int
main(int argc, char** argv)
{

	fstream f;
	f.open("./data.txt", ios_base::in);

	string diff, pwd, blank;
	char let;
	int l, r, cnt, valid = 0;

	while (f >> diff >> let >> blank >> pwd){
		parse_diffs(l, r, diff);

		// part 1
		//cnt = count(pwd.begin(), pwd.end(), let);
		//
		//if ((l <= cnt) && (cnt <= r))
		//	valid++;
		
		// part2
		if (valid_part2(l, r, let, pwd))
			valid++;

		cout << "valid? " << valid << endl;

	}

	cout << "Valid: " << valid << endl;

	return 0;
}