#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class IntcodeComputer1 {
    public:
        map<long long, long long> seglist;
        queue<long long> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
        int halted = 0;
        IntcodeComputer1() {}

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
                        halted = 1;
                        return;
                }
            }
        }
};

int max_x = 0, max_y = 0;

void part1() {
    ifstream fin("day13.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    IntcodeComputer1* computer = new IntcodeComputer1();
    vector<int> v;

    int curr = 0;
    while(getline(stream, segment, ',')) {
        computer->seglist[curr] = stoi(segment);
        curr++;
    }

    while (!computer->halted) computer->simulate();

    while (computer->out.size() > 0) {
        v.push_back(computer->out.front());
        computer->out.pop();
    }

    int ind = 2;
    int blocks = 0;

    for (int i = 0; i < v.size(); i++) {
        ind = (ind + 1) % 3;
        
        switch(ind) {

            case 0:
                if (v[i] > max_x) max_x = v[i];
                break;

            case 1:
                if (v[i] > max_y) max_y = v[i];
                break;

            case 2:
                if (v[i] == 2) blocks++;
                break;
        }
    }

    cout << blocks << endl;
    free(computer);
}

class IntcodeComputer2 {
    public:
        map<long long, long long> seglist;
        queue<long long> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
        int halted = 0;
        IntcodeComputer2() {}

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

        int simulate(int joystick) {

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
                        input = joystick;
                        set_value(modes[0], pc + 1, input);
                        pc += 2;
                        break;
                    
                    case 4:
                        params[0] = get_value(modes[0], pc + 1);
                        pc += 2;
                        return params[0];
                    
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
                        halted = 1;
                        return 0;
                }
            }
        }
};

void part2() {
    ifstream fin("day13.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    IntcodeComputer2* computer = new IntcodeComputer2();

    int curr = 0;
    while(getline(stream, segment, ',')) {
        computer->seglist[curr] = stoi(segment);
        curr++;
    }

    computer->seglist[0] = 2;
    int joystick = 0;
    int score = 0;
    vector<vector<int>> screen;

    for (int i = 0; i <= max_y; i++) {
        vector<int> vec;
        for (int j = 0; j <= max_x; j++) {
            vec.push_back(0);
        }
        screen.push_back(vec);
    }

    while (!computer->halted) {

        int x = computer->simulate(joystick);
        int y = computer->simulate(joystick);
        int z = computer->simulate(joystick);

        if (x == -1 && y == 0) score = z;
        else screen[y][x] = z;

        int paddle = -1, ball = -1;

        for (int i = 0; i < screen.size(); i++) {
            for (int j = 0; j < screen[0].size(); j++) {
                if (screen[i][j] == 3) paddle = j;
                if (screen[i][j] == 4) ball = j;
            }
        }

        if (paddle > 0 && ball > 0) {
            if (ball < paddle) joystick = -1;
            else if (ball > paddle) joystick = 1;
            else joystick = 0;
        }
    }

    cout << score << endl;
}

int main() {
    part1();
    part2();
}