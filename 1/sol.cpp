#include <iostream>
#include <fstream>
#include <vector>
#include <map>


using namespace std;

int
solve(vector<int>& nums, int want)
{
	map<int, int> m;

	for (int i : nums) {
		if (m.find(i) == m.end())
			m[i] = 0;
	}

	for (const auto [i,j] : m) {

		int x = want - (int) i;

		if (m.find(x) != m.end()) {
			return m.find(x)->first * i;
		}
	}

	return 0;

}


/*
 * Three part sum
 */
int
part2(vector<int>& nums, int want)
{
	map<int, pair<int, int>> sumMap;
	map<int, int> m;

	for (int i : nums) {
		if (m.find(i) == m.end())
			m[i] = 0;
	}

	for (int i : nums) {
		pair<int, int> v;
		v.first = i;

		for (int j : nums) {
			v.second = j;
			if (sumMap.find(i + j) == sumMap.end())
				sumMap[i + j] = v;
		}
	}

	for (const auto [i, v] : sumMap) {
		int x = want - i;

		if (m.find(x) != m.end())
			return x * v.first * v.second;
	}

	return -1;

}


int
main(int argc, char **argv)
{
	vector<int> nums;

	fstream f;
	f.open("./data.txt", ios_base::in);

	int x;

	f >> x;

	do {
		nums.push_back(x);
	} while(f >> x);

	//int sol = solve(nums, 2020);
	int sol = part2(nums, 2020);

	cout << "Solution: " << sol << endl;

	return 0;
}