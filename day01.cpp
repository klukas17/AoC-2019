#include <iostream>
#include <fstream>

using namespace std;

void part1() {
    ifstream fin("day01.txt");
    int mass = 0, temp;
    fin >> temp;
    while (!fin.eof()) {
        mass += temp / 3 - 2;
        fin >> temp;
    }
    cout << mass << endl;
}

void part2() {
    ifstream fin("day01.txt");
    int mass = 0, temp;
    fin >> temp;
    while (!fin.eof()) {
        while (temp >= 0) {
            temp = temp / 3 - 2;
            if (temp >= 0) mass += temp;
        }
        
        fin >> temp;
    }
    cout << mass << endl;
}

int main() {
    part1();
    part2();
}