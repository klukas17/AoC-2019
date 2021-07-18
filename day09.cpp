#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class IntcodeComputer {
    public:
        map<long long, long long> seglist;
        queue<long long> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
        IntcodeComputer() {}

        long long get_value(int mode, long long loc) {
            switch(mode) {

                case 0:
                    return seglist[seglist[loc]];

                case 1:
                    return seglist[loc];

                case 2:
                    return seglist[seglist[loc] + offset];
            }

            return 0;
        }

        void set_value(int mode, long long loc, long long value) {
            switch(mode) {

                case 0:
                case 1:
                    seglist[seglist[loc]] = value;
                    return;

                case 2:
                    seglist[seglist[loc] + offset] = value;
                    return;
            }
        }

        void simulate() {

            while (true) {

                long long params[3]{0,0,0}, modes[3]{0,0,0}, result, input;
                int instruction, opcode;

                instruction = seglist[pc];
                opcode = instruction % 100;
                instruction /= 100;
                modes[0] = instruction % 10;
                instruction /= 10;
                modes[1] = instruction % 10;
                instruction /= 10;
                modes[2] = instruction % 10;

                switch(opcode) {

                    case 1:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        result = params[0] + params[1];
                        set_value(modes[2], pc + 3, result);
                        pc += 4;
                        break;
                    
                    case 2:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        result = params[0] * params[1];
                        set_value(modes[2], pc + 3, result);
                        pc += 4;
                        break;
                    
                    case 3:
                        input = in.front();
                        in.pop();
                        set_value(modes[0], pc + 1, input);
                        pc += 2;
                        break;
                    
                    case 4:
                        params[0] = get_value(modes[0], pc + 1);
                        out.push(params[0]);
                        lastOutput = params[0];
                        pc += 2;
                        break;
                    
                    case 5:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        if (params[0] != 0) pc = params[1];
                        else pc += 3;
                        break;
                    
                    case 6:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        if (params[0] == 0) pc = params[1];
                        else pc += 3;
                        break;
                    
                    case 7:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        set_value(modes[2], pc + 3, params[0] < params[1]);
                        pc += 4;
                        break;
                    
                    case 8:
                        params[0] = get_value(modes[0], pc + 1);
                        params[1] = get_value(modes[1], pc + 2);
                        set_value(modes[2], pc + 3, params[0] == params[1]);
                        pc += 4;
                        break;
                    
                    case 9:
                        params[0] = get_value(modes[0], pc + 1);
                        offset += params[0];
                        pc += 2;
                        break; 
                    
                    case 99:
                        return;
                }
            }
        }
};

void part1() {
    ifstream fin("day09.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;

    int curr = 0;
    IntcodeComputer *computer = new IntcodeComputer();
    while(getline(stream, segment, ',')) {
        computer->seglist[curr] = stoll(segment);
        curr++;
    }

    computer->in.push(1);
    computer->simulate();

    cout << computer->lastOutput << endl;

    free(computer);
}

void part2() {
    ifstream fin("day09.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;

    int curr = 0;
    IntcodeComputer *computer = new IntcodeComputer();
    while(getline(stream, segment, ',')) {
        computer->seglist[curr] = stoll(segment);
        curr++;
    }

    computer->in.push(2);
    computer->simulate();

    cout << computer->lastOutput << endl;

    free(computer);
}

int main() {
    part1();
    part2();
}