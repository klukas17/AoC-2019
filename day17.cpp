#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class IntcodeComputer1 {
    public:
        map<long long, long long> seglist;
        queue<char> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
        vector<vector<char>> terrain;
        vector<char> curr;
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
                        if (lastOutput == 10) {
                            terrain.push_back(curr);
                            curr = vector<char>();
                        } else curr.push_back((char) lastOutput);
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
                        terrain.pop_back();
                        return;
                }
            }
        }
};

class IntcodeComputer2 {
    public:
        map<long long, long long> seglist;
        queue<char> in;
        queue<long long> out;
        long long lastOutput = 0;
        long long offset = 0;
        long long pc = 0;
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

vector<vector<char>> v;

void part1() {
    ifstream fin("day17.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    IntcodeComputer1* computer = new IntcodeComputer1();

    int curr = 0;
    while (getline(stream, segment, ',')) {
        computer->seglist[curr] = stoi(segment);
        curr++;
    }

    computer->simulate();

    int result = 0;

    v = computer->terrain;
    for (int i = 1; i < v.size() - 1; i++) {
        for (int j = 1; j < v[0].size() - 1; j++) {
            if (v[i][j] == '#') {
                if (v[i-1][j] == '#' && v[i+1][j] == '#' && v[i][j-1] == '#' && v[i][j+1] == '#')
                    result += i * j;
            }
        }
    }

    cout << result << endl;
}

vector<int> map_moves(vector<vector<char>> m) {
    
    vector<char> moves;

    int x, y, max_x = m.size() - 1, max_y = m[0].size() - 1;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            if (m[i][j] == '^' || m[i][j] == '>' || m[i][j] == 'V' || m[i][j] == '<') {
                x = i;
                y = j;
            }
        }
    }

    bool end_reached = false;

    while (!end_reached) {

        switch(m[x][y]) {

            case '^':
                if (x != 0 && m[x-1][y] == '#') {
                    moves.push_back('F');
                    m[x][y] = '#';
                    m[x-1][y] = '^';
                    x--;
                } else if (y != max_y && m[x][y+1] == '#') {
                    moves.push_back('R');
                    m[x][y] = '>';
                } else if (y != 0 && m[x][y-1] == '#') {
                    moves.push_back('L');
                    m[x][y] = '<';
                } else end_reached = true;
                break;

            case '>':
                if (y != max_y && m[x][y+1] == '#') {
                    moves.push_back('F');
                    m[x][y] = '#';
                    m[x][y+1] = '>';
                    y++;
                } else if (x != 0 && m[x-1][y] == '#') {
                    moves.push_back('L');
                    m[x][y] = '^';
                } else if (x != max_x && m[x+1][y] == '#') {
                    moves.push_back('R');
                    m[x][y] = 'V';
                } else end_reached = true;
                break;

            case 'V':
                if (x != max_x && m[x+1][y] == '#') {
                    moves.push_back('F');
                    m[x][y] = '#';
                    m[x+1][y] = 'V';
                    x++;
                } else if (y != max_y && m[x][y+1] == '#') {
                    moves.push_back('L');
                    m[x][y] = '>';
                } else if (y != 0 && m[x][y-1] == '#') {
                    moves.push_back('R');
                    m[x][y] = '<';
                } else end_reached = true;
                break;

            case '<':
                if (y != 0 && m[x][y-1] == '#') {
                    moves.push_back('F');
                    m[x][y] = '#';
                    m[x][y-1] = '<';
                    y--;
                } else if (x != 0 && m[x-1][y] == '#') {
                    moves.push_back('R');
                    m[x][y] = '^';
                } else if (x != max_x && m[x+1][y] == '#') {
                    moves.push_back('L');
                    m[x][y] = 'V';
                } else end_reached = true;
                break;
        }
    }

    vector<int> instructions;

    for(int i = 0; i < moves.size(); i++) {
        if (moves[i] != 'F') instructions.push_back(moves[i]);
        else {
            int count = 1;
            while (moves[++i] == 'F') count++;
            instructions.push_back(count);
            i--;
        }
    }

    return instructions;
}

void part2() {
    ifstream fin("day17.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;
    IntcodeComputer2* computer = new IntcodeComputer2();
    
    int curr = 0;
    while (getline(stream, segment, ',')) {
        computer->seglist[curr] = stoi(segment);
        curr++;
    }

    vector<int> moves = map_moves(v);

    computer->seglist[0] = 2;

    vector<int> a, b, c, a_starts, b_starts, c_starts;
    vector<int> indexes_found;
    
    for (int i = 0; i < moves.size(); i++) indexes_found.push_back(0);

    for (int i = 0; i < 4; i++) a.push_back(moves[i]);

    for (int i = 0; i < moves.size() - 4; i++) {
        if (moves[i] == a[0] && moves[i+1] == a[1] && moves[i+2] == a[2] && moves[i+3] == a[3]) {
            a_starts.push_back(i);
            for (int j = 0; j < 4; j++) indexes_found[i+j] = 1;
        }
    }

    int a_size = 4;

    bool flag = true;
    while (flag) {

        if (indexes_found[a_size] == 1) break;

        char c = moves[a_starts[0] + a_size];
        
        for (auto s : a_starts) if (moves[s + a_size] != c) flag = false;

        if (flag) {
            a.push_back(c);
            for (auto s : a_starts) indexes_found[s + a_size] = 1;
            a_size++;
        }
    }

    int first_free = -1;
    for (int i = 0; i < indexes_found.size(); i++) {
        if (indexes_found[i] == 0) {
            first_free = i;
            break;
        }
    }

    for (int i = 0; i < 4; i++) b.push_back(moves[first_free + i]);

    for (int i = first_free; i < moves.size() - 4; i++) {
        if (moves[i] == b[0] && moves[i+1] == b[1] && moves[i+2] == b[2] && moves[i+3] == b[3]) {
            b_starts.push_back(i);
            for (int j = 0; j < 4; j++) indexes_found[i+j] = 1;
        }
    }

    int b_size = 4;

    flag = true;
    while (flag) {

        if (indexes_found[b_size + b_starts[0]] == 1) break;

        char c = moves[b_starts[0] + b_size];

        for (auto s : b_starts) if (moves[s + b_size] != c) flag = false;

        if (flag) {
            b.push_back(c);
            for (auto s : b_starts) indexes_found[s + b_size] = 1;
            b_size++;
        } 
    }

    first_free = -1;
    for (int i = 0; i < indexes_found.size(); i++) {
        if (indexes_found[i] == 0) {
            first_free = i;
            break;
        }
    }

    for (int i = 0; i < 4; i++) c.push_back(moves[first_free + i]);

    for (int i = first_free; i < moves.size() - 4; i++) {
        if (moves[i] == c[0] && moves[i+1] == c[1] && moves[i+2] == c[2] && moves[i+3] == c[3]) {
            c_starts.push_back(i);
            for (int j = 0; j < 4; j++) indexes_found[i+j] = 1;
        }
    }

    int c_size = 4;

    flag = true;
    while (flag) {

        if (indexes_found[c_size + c_starts[0]] == 1) break;

        char d = moves[c_starts[0] + c_size];

        for (auto s : c_starts) if (moves[s + c_size] != d) flag = false;

        if (flag) {
            c.push_back(d);
            for (auto s : c_starts) indexes_found[s + c_size] = 1;
            c_size++;
        } 
    }

    vector<char> flow;
    int a_matched, b_matched, c_matched, total;
    a_matched = b_matched = c_matched = 0;
    total = a_starts.size() + b_starts.size() + c_starts.size();

    flow.push_back('A');
    a_matched++;

    while (flow.size() < total) {
        int next;
        if (a_matched < a_starts.size()) next = 0;
        if (b_matched < b_starts.size() && b_starts[b_matched] < a_starts[a_matched] || a_matched == a_starts.size()) next = 1;
        if (next == 0 && c_matched < c_starts.size()) {
            if (c_starts[c_matched] < a_starts[a_matched] || a_matched == a_starts.size()) next = 2;
        } 
        else if (next == 1 && c_matched < c_starts.size()) {
            if (c_starts[c_matched] < b_starts[b_matched] || b_matched == b_starts.size()) next = 2;
        }

        switch(next) {

            case 0:
                a_matched++;
                flow.push_back('A');
                break;

            case 1:
                b_matched++;
                flow.push_back('B');
                break;
            
            case 2:
                c_matched++;
                flow.push_back('C');
                break;
        }
    }

    queue<int> q;

    for (int i = 0; i < flow.size(); i++) {
        computer->in.push(flow[i]);
        if (i != flow.size()-1) computer->in.push(',');
    }
    computer->in.push(10);

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 'L' || a[i] == 'R') computer->in.push(a[i]);
        else {
            stack<int> s;
            int n = a[i];
            while (n > 0) {
                s.push(n % 10);
                n /= 10;
            }
            while (s.size() > 0) {
                computer->in.push(s.top() + '0');
                s.pop();
            }
        }
        if (i != a.size()-1) computer->in.push(',');
    }
    computer->in.push(10);

    for (int i = 0; i < b.size(); i++) {
        if (b[i] == 'L' || b[i] == 'R') computer->in.push(b[i]);
        else {
            stack<int> s;
            int n = b[i];
            while (n > 0) {
                s.push(n % 10);
                n /= 10;
            }
            while (s.size() > 0) {
                computer->in.push(s.top() + '0');
                s.pop();
            }
        }
        if (i != b.size()-1) computer->in.push(',');
    }
    computer->in.push(10);

    for (int i = 0; i < c.size(); i++) {
        if (c[i] == 'L' || c[i] == 'R') computer->in.push(c[i]);
        else {
            stack<int> s;
            int n = c[i];
            while (n > 0) {
                s.push(n % 10);
                n /= 10;
            }
            while (s.size() > 0) {
                computer->in.push(s.top() + '0');
                s.pop();
            }
        }
        if (i != c.size()-1) computer->in.push(',');
    }
    computer->in.push(10);

    computer->in.push('n');
    computer->in.push(10);

   computer->simulate();
   cout << computer->lastOutput << endl;
}

int main() {
    part1();
    part2();
}