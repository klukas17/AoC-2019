#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int width = 25, height = 6;

void part1() {
	ifstream fin("day08.txt");
    string input;
    vector<string> seglist;
    fin >> input;

    while (!fin.eof()) {
        seglist.push_back(input);
        fin >> input;
    }

    int iterationCount = input.length() / (width * height);
    int currIteration = 0;

    int layer = 0, zeros = width*height + 1, result = 0;

    for (int it = currIteration; it < iterationCount; it++) {
        int local_zeros = 0, local_ones = 0, local_twos = 0;
        for (int i = 0; i < width * height; i++) {
            char c = input.at(it*width*height + i);
            switch(c) {
                case '0':
                    local_zeros++;
                    break;
                case '1':
                    local_ones++;
                    break;
                case '2':
                    local_twos++;
                    break;
            }
        }
        if (local_zeros < zeros) {
            zeros = local_zeros;
            result = local_ones * local_twos;
        }
    }

    cout << result << endl;
}

void part2() {
    ifstream fin("day08.txt");
    string input;
    vector<string> seglist;
    fin >> input;

    while (!fin.eof()) {
        seglist.push_back(input);
        fin >> input;
    }

    char message[width*height];
    for (int i = 0; i < width * height; i++) message[i] = 'x';
    
    for (int i = 0; i < input.length(); i++) {
        int index = i % (width * height);
        if (message[index] == 'x' && input.at(i) != '2') message[index] = input.at(i);
    }

    for (int i = 0; i < width * height; i++) {
        if (i % width == 0) cout << endl;
        if (message[i] == '1') cout << '.';
        else cout << " ";
    }
    cout << endl;
}

int main() {
	part1();
	part2();
}