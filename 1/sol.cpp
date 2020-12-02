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

int
main(int argc, char **argv)
{
	vector<int> nums;

	fstream f;
	f.open("./data.txt", ios_base::in);

	int x;

	do {
		nums.push_back(x);
	} while(f >> x);

	int sol = solve(nums, 2020);

	cout << "Solution: " << sol << endl;

	return 0;
}