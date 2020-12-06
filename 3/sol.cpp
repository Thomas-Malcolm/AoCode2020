#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int solve_general(vector<string>, int, int);

int
solve_one(vector<string> map)
{

	return solve_general(map, 3, 1);

}

int
solve_general(vector<string> map, int dx, int dy)
{

	int r = 0, c = 0, count = 0;

	int rows = map.size();
	int cols = map[0].length();

	while (r < rows) {
		if (map[r][c % cols] == '#')
			count++;

		r += dy;
		c += dx;
	}

	cout << "sol for " << dx << "," << dy << " is " << count << endl;


	return count;
}


int
main(int argc, char** argv)
{
	fstream f;
	f.open("./data.txt", ios_base::in);

	vector<string> treeMap;
	string line;

	while (f >> line) {
		treeMap.push_back(line);
	}	

	int one = solve_one(treeMap);

	cout << "Sol1: " << one << endl;

	vector<pair<int, int>> part2 = {
		{1, 1},
		{3, 1},
		{5, 1},
		{7, 1},
		{1, 2}
	};

	long int m = 1;
	for (auto [dx,dy] : part2) {
		m *= solve_general(treeMap, dx, dy);
	}

	cout << "Sol2: " << m << endl;

	return 0;
}