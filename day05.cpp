#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void part1() {
    ifstream fin("day05.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    vector<int> seglist;

    while(getline(stream, segment, ',')) {
        seglist.push_back(stoi(segment));
    }

    int in = 1, out = 0, index = 0;
    bool flag = true;

    while (flag) {

        int arg1, arg2, arg3;

        int instruction = seglist[index];
        int opcode = instruction % 100;
        instruction /= 100;
        int mode1 = instruction % 10;
        instruction /= 10;
        int mode2 = instruction % 10;
        instruction /= 10;
        int mode3 = instruction % 10;

        if (opcode == 1 || opcode == 2) {
            if (mode1 == 0) arg1 = seglist[seglist[index+1]];
            else arg1 = seglist[index+1];

            if (mode2 == 0) arg2 = seglist[seglist[index+2]];
            else arg2 = seglist[index+2]; 
        }

        switch(opcode) {
            case 1:
                arg3 = arg1 + arg2;
                if (mode3 == 0) seglist[seglist[index+3]] = arg3;
                else seglist[index+3] = arg3;
                index += 4;
                break;

            case 2:
                arg3 = arg1 * arg2;
                if (mode3 == 0) seglist[seglist[index+3]] = arg3;
                else seglist[index+3] = arg3;
                index += 4;
                break;

            case 3:
                if (mode1 == 0) seglist[seglist[index+1]] = in;
                else seglist[index+1] = in;
                index += 2;
                break;

            case 4:
                if (mode1 == 0) out = seglist[seglist[index+1]];
                else out = seglist[index+1];
                index += 2;
                break;

            case 99:
                flag = false;
                break;
        }
    }

    std::cout << out << endl;
}

void part2() {
	ifstream fin("day05.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    vector<int> seglist;

    while(getline(stream, segment, ',')) {
        seglist.push_back(stoi(segment));
    }

    int in = 5, out = 0, index = 0;
    bool flag = true;

    while (flag) {

        int arg1, arg2, arg3;

        int instruction = seglist[index];
        int opcode = instruction % 100;
        instruction /= 100;
        int mode1 = instruction % 10;
        instruction /= 10;
        int mode2 = instruction % 10;
        instruction /= 10;
        int mode3 = instruction % 10;

        if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8) {
            if (mode1 == 0) arg1 = seglist[seglist[index+1]];
            else arg1 = seglist[index+1];

            if (mode2 == 0) arg2 = seglist[seglist[index+2]];
            else arg2 = seglist[index+2]; 
        }

        switch(opcode) {
            case 1:
                arg3 = arg1 + arg2;
                if (mode3 == 0) seglist[seglist[index+3]] = arg3;
                else seglist[index+3] = arg3;
                index += 4;
                break;

            case 2:
                arg3 = arg1 * arg2;
                if (mode3 == 0) seglist[seglist[index+3]] = arg3;
                else seglist[index+3] = arg3;
                index += 4;
                break;

            case 3:
                if (mode1 == 0) seglist[seglist[index+1]] = in;
                else seglist[index+1] = in;
                index += 2;
                break;

            case 4:
                if (mode1 == 0) out = seglist[seglist[index+1]];
                else out = seglist[index+1];
                index += 2;
                break;
                
            case 5:
            	if (arg1 != 0) index = arg2;
            	else index += 3;
            	break;
            	
            case 6:
            	if (arg1 == 0) index = arg2;
            	else index += 3;
            	break;
            	
            case 7:
                arg3 = seglist[index+3];
            	seglist[arg3] = arg1 < arg2;
            	index += 4;
            	break;
            	
            case 8:
                arg3 = seglist[index+3];
            	seglist[arg3] = arg1 == arg2;
            	index += 4;
            	break;

            case 99:
                flag = false;
                break;
        }
    }

    std::cout << out << endl;
}

int main() {
    part1();
    part2();
}
