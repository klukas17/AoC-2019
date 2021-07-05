#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void part1() {
    ifstream fin("day02.txt");
    string input;
    fin >> input;    

    stringstream stream(input);
    string segment;
    vector<int> seglist;

    while(getline(stream, segment, ',')) {
        seglist.push_back(stoi(segment));
    }

    seglist[1] = 12;
    seglist[2] = 2;

    int index = 0;
    bool flag = true;
    
    while (flag) {
        switch(seglist[index]) {
            case 1:
                seglist[seglist[index+3]] = seglist[seglist[index+1]] + seglist[seglist[index+2]];
                index += 4;
                break;

            case 2:
                seglist[seglist[index+3]] = seglist[seglist[index+1]] * seglist[seglist[index+2]];
                index += 4;
                break;

            case 99:
                flag = false;
                break;
        }
    }

    cout << seglist[0] << endl;

}

void part2() {
    ifstream fin("day02.txt");
    string input;
    fin >> input;    

    stringstream stream(input);
    string segment;
    vector<int> memory;

    while(getline(stream, segment, ',')) {
        memory.push_back(stoi(segment));
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {

            vector<int> seglist(memory);

            seglist[1] = i;
            seglist[2] = j;

            int index = 0;
            bool flag = true;
            
            while (flag) {
                switch(seglist[index]) {
                    case 1:
                        seglist[seglist[index+3]] = seglist[seglist[index+1]] + seglist[seglist[index+2]];
                        index += 4;
                        break;

                    case 2:
                        seglist[seglist[index+3]] = seglist[seglist[index+1]] * seglist[seglist[index+2]];
                        index += 4;
                        break;

                    case 99:
                        flag = false;
                        break;
                }
            }

            if (seglist[0] == 19690720) {
                cout << 100 * i + j << endl;
                return;
            }

        }
    }

}

int main() {
    part1();
    part2();
}