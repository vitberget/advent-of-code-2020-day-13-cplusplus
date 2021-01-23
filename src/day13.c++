#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cassert>
#include <numeric>
#include <execution>
#include <utility>
#include <type_traits>
#include <algorithm>

using namespace std;

using bignumber =  unsigned long long int;

int puzzle1(int earliest, vector<int> buses);
bignumber puzzle2(vector<int> buses);

int main() {
	cout << "---=== Advent of code 2020, day 13 ===---" << endl;

	fstream puzzle_file;
	puzzle_file.open("puzzle.txt", ios::in);
	if(!puzzle_file) {
		cerr << "No file!" << endl;
		return -1;
	}

	string earliest_line;
	getline(puzzle_file, earliest_line);
	int earliest = stoi(earliest_line);

	vector<int> buses;
	string bus_string;
	while(getline(puzzle_file, bus_string, ',')) {
		if(bus_string == "x") {
			buses.push_back(0);
		} else {
			buses.push_back(stoi(bus_string));
		}
	}

	int p1 = puzzle1(earliest, buses);
	cout << "puzzle 1: " << p1 << endl;
	bignumber p2 = puzzle2(buses);
	cout << "puzzle 2: " << p2 << endl;

	return 0;
}

int puzzle1(int earliest, vector<int> buses) {
	int fastest_bus = -1;
	int fastest_time = INT_MAX; 

	for(auto const& bus : as_const(buses)) {
		if(bus!=0) {
			int time = bus - earliest % bus;
			if(time<fastest_time) {
				fastest_bus = bus;
				fastest_time = time;
			}
		}
	}

	return fastest_bus * fastest_time;
}


bignumber puzzle2(vector<int> buses) {
	vector<pair<bignumber,bignumber>> buses_id;

	vector<bignumber> idxs(buses.size());
	generate(idxs.begin(),idxs.end(),[n=0]()mutable{return n++;});

	transform(
			buses.begin(), 
			buses.end(), 
			idxs.begin(), 
			back_inserter(buses_id),
			[](bignumber bus, bignumber id){return pair<bignumber,bignumber>(id,bus);});

	pair<bignumber,bignumber> largest_bus = accumulate(
			buses_id.begin(),
			buses_id.end(),
			pair<bignumber,bignumber>(0, 0),
			[](pair<bignumber,bignumber> p1, pair<bignumber,bignumber> p2) { return p1.second > p2.second ? p1 : p2; });

	bignumber step = largest_bus.second;
	bignumber timestamp = largest_bus.second - largest_bus.first;

	for(;; timestamp += step ) {
		vector<pair<bignumber,bignumber>> bus_rem;
		transform(
				buses_id.begin(), 
				buses_id.end(),
				back_inserter(bus_rem),
				[&](pair<bignumber,bignumber>bus_id) {
					return bus_id.second==0 
						? pair<bignumber,bignumber>(1,0)
						: pair<bignumber,bignumber>(bus_id.second, ( timestamp + bus_id.first ) % bus_id.second);
					});

		pair<bignumber,bignumber> i_need_a_name = accumulate(
				bus_rem.begin(),
				bus_rem.end(),
				pair<bignumber,bignumber>(1,0),
				[](pair<bignumber,bignumber> p1, pair<bignumber,bignumber> p2) {
					bignumber first = p2.second > 0 ? p1.first : p1.first * p2.first;
					bignumber second = p1.second + p2.second;
					return pair<bignumber,bignumber>(first, second);
				} );

		if(i_need_a_name.second == 0) return timestamp;
		step = i_need_a_name.first;
	}

	return -1;
}
