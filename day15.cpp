#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class IntcodeComputer {
    public:
        map<long long, long long> seglist;
        queue<long long> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
        int halted = 0;
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

        int simulate(int signal) {

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
                        input = signal;
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

enum Directions {
    NORTH = 1,
    SOUTH = 2,
    WEST = 3,
    EAST = 4
};

enum Status {
    HIT_WALL = 0,
    MOVED = 1,
    FOUND = 2
};

enum Tile {
    UNEXPLORED = 0,
    TRAVERSABLE = 1,
    PENDING = 2,
    WALL = 3,
};

int x_oxygen, y_oxygen;
int x_max, x_min, y_max, y_min;
map<int, map<int,int>> nodes;
map<int, map<int, int>> oxygen;

void part1() {
    ifstream fin("day15.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    IntcodeComputer* computer = new IntcodeComputer();

    int curr = 0;
    while (getline(stream, segment, ',')) {
        computer->seglist[curr] = stoi(segment);
        curr++;
    }

    map<int, map<int, tuple<int,int>>> previous;
    stack<int> directions;
    stack<int> coordinates;

    int x = 0, y = 0;
    x_max = y_min = y_max = y_min = 0;
    nodes[x][y] = TRAVERSABLE;
    bool found = false;
    int distance;

    do {

        if (nodes[x+1][y] == UNEXPLORED) {
            coordinates.push(y);
            coordinates.push(x+1);
            nodes[x+1][y] = PENDING;
            previous[x+1][y] = tuple<int,int>(x,y);
        }

        if (nodes[x-1][y] == UNEXPLORED) {
            coordinates.push(y);
            coordinates.push(x-1);
            nodes[x-1][y] = PENDING;
            previous[x-1][y] = tuple<int,int>(x,y);
        }

        if (nodes[x][y+1] == UNEXPLORED) {
            coordinates.push(y+1);
            coordinates.push(x);
            nodes[x][y+1] = PENDING;
            previous[x][y+1] = tuple<int,int>(x,y);
        }

        if (nodes[x][y-1] == UNEXPLORED) {
            coordinates.push(y-1);
            coordinates.push(x);
            nodes[x][y-1] = PENDING;
            previous[x][y-1] = tuple<int,int>(x,y);
        }

        int x_new = coordinates.top();
        coordinates.pop();
        int y_new = coordinates.top();
        coordinates.pop();

        if (x_new > x_max) x_max = x_new;
        else if (x_new < x_min) x_min = x_new;
        if (y_new > y_max) y_max = y_new;
        else if (y_new < y_min) y_min = y_new;

        int x_prev = get<0>(previous[x_new][y_new]);
        int y_prev = get<1>(previous[x_new][y_new]);

        while (x != x_prev || y != y_prev) {
            int direction = directions.top();
            directions.pop();

            switch(direction) {

                case NORTH:
                    computer->simulate(SOUTH);
                    y--;
                    break;

                case SOUTH:
                    computer->simulate(NORTH);
                    y++;
                    break;

                case EAST:
                    computer->simulate(WEST);
                    x--;
                    break;

                case WEST:
                    computer->simulate(EAST);
                    x++;
                    break;
            }
        }

        int signal;

        if (x_new == x+1 && y_new == y) {
            signal = EAST;
        } else if (x_new == x-1 && y_new == y) {
            signal = WEST;
        } else if (x_new == x && y_new == y+1) {
            signal = NORTH;
        } else if (x_new == x && y_new == y-1) {
            signal = SOUTH;
        }

        int result = computer->simulate(signal);

        switch(result) {

            case 0:
                nodes[x_new][y_new] = WALL;
                break;

            case 1: case 2:
                nodes[x_new][y_new] = TRAVERSABLE;
                directions.push(signal);
                x = x_new;
                y = y_new;
                break;
        }

        if (result == 2) {
            found = true;
            distance = directions.size();
            x_oxygen = x_new;
            y_oxygen = y_new;
        }

    } while (coordinates.size() > 0);

    cout << distance << endl;
}

void part2() {
    
    for (int i = x_min; i <= x_max; i++) {
        for (int j = y_min; j <= y_max; j++) {
            if (nodes[i][j] == TRAVERSABLE) oxygen[i][j] = -1;
        }
    }

    queue<int> this_minute;
    queue<int> next_minute;

    next_minute.push(x_oxygen);
    next_minute.push(y_oxygen);

    int minutes = -1;

    while (next_minute.size() > 0) {
        this_minute = next_minute;
        next_minute = queue<int>();

        while (this_minute.size() > 0) {
            int x = this_minute.front();
            this_minute.pop();
            int y = this_minute.front();
            this_minute.pop();

            oxygen[x][y] = minutes;

            if (oxygen[x+1][y] == -1) {
                oxygen[x+1][y] = -2;
                next_minute.push(x+1);
                next_minute.push(y);
            }

            if (oxygen[x-1][y] == -1) {
                oxygen[x-1][y] = -2;
                next_minute.push(x-1);
                next_minute.push(y);
            }

            if (oxygen[x][y+1] == -1) {
                oxygen[x][y+1] = -2;
                next_minute.push(x);
                next_minute.push(y+1);
            }

            if (oxygen[x][y-1] == -1) {
                oxygen[x][y-1] = -2;
                next_minute.push(x);
                next_minute.push(y-1);
            }
        }

        minutes++;
    }

    cout << minutes << endl;
}

int main() {
    part1();
    part2();
}
