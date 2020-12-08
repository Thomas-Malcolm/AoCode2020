#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

#define CARVE_ROW(n) (128 - (n >> 3) - 1)
#define CARVE_COL(n) (n & 0x07)
#define PRINT_BITS(n) {bitset<10> bb(n); cout << "bits: " << bb << endl;} /* debugging */

#define CALC_ID(r,c) (r*8 + c)

struct bpass {
	int row, col, sid;

	int16_t wordVal = 0;
};

void
store_bpasses(vector<string> bids, vector<struct bpass> &passes)
{
	struct bpass bp;

	for (string sid : bids) {

		bp = {};

		int rl = 0, ru = 127, cl = 0, cu = 7, r, c;

		int16_t wordVal = 0x000;
		
		for (int i = 0; i < 7; i++) {
			switch (sid.at(i)) {
				case 'F': /* Treated as a logical 1 */
					ru = floor((ru + rl) / 2.0f);
					wordVal |= (1 << (10 - i - 1));
					break;
				case 'B':
					rl = ceil((ru + rl) / 2.0f);
					break;
			}

		}

		r = min(rl, ru);

		for (int i = 7; i < 10; i++) {
			switch (sid.at(i)) {
				case 'R': /* Treated as a logical 1 */
					cl = ceil((cu + cl) / 2.0f);
					wordVal |= (1 << (10 - i - 1));
					break;
				case 'L':
					cu = floor((cu + cl) / 2.0f);
					break;
			}
		}

		c = max(cl, cu);

		bp.row = r;
		bp.col = c;
		bp.sid = CALC_ID(r, c);
		bp.wordVal = wordVal;
		passes.push_back(bp);		
	}

}


int
part_one(vector<struct bpass> &passes)
{
	int maximum = -1;

	for (struct bpass bp : passes) {
		if (bp.sid > maximum) {
			maximum = bp.sid;
		}
	}
	
	return maximum;
}


/*
 * Treat F as 1 and B as 0 (bits) in a 7-bit integer
 * Note: row = 128 - (val + 1)
 * 		 col = 3-bit value at end of string [R : 1, L : 0]
 * - these values are already stored in the wordVal of each boarding pass; can be carved out
 * Can find the missing number in the range using bit manipulation - 
 */

int
part_two(vector<struct bpass> passes)
{
	int16_t out = 0, i = 0;

	for (i = 0; i < passes.size(); i++) {
		out = out ^ i ^ passes[i].wordVal;
	}

	out ^= i;

	return CALC_ID(CARVE_ROW(out), CARVE_COL(out));
}

int
main(int argc, char** argv)
{
	vector<string> bids;
	vector<struct bpass> passes;
	string line;

	fstream f;
	f.open("data.txt", ios_base::in);

	while (f >> line) {
		bids.push_back(line);
	}

	store_bpasses(bids, passes);

	cout << "Max: " << part_one(passes) << endl;

	cout << "Our seat id: " << part_two(passes) << endl;

	return 0;
}