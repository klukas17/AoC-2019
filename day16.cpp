#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Generator {
    public:
        int base;
        int curr;

        Generator(int base) {
            this->base = base;
            this->curr = 0;
        }
        ~Generator() {}

        int next() {
            curr++;
            curr %= 4 * base;
            int ret_val;

            if (curr < base) ret_val = 0;
            else if (curr < 2 * base) ret_val = 1;
            else if (curr < 3 * base) ret_val = 0;
            else ret_val = -1;

            return ret_val;
        }
};

void part1() {
    ifstream fin("day16.txt");
    string input;
    getline(fin, input);
    
    vector<int> sequence;
    for (int i = 0; i < input.size(); i++) {
        sequence.push_back(input.at(i) - '0');
    }

    for (int _ = 0; _ < 100; _++) {

        vector<int> new_sequence;
        for (int i = 0; i < sequence.size(); i++) {
            int result = 0;

            Generator* g = new Generator(i+1);
            for (int j = 0; j < sequence.size(); j++) {
                result += sequence[j] * g->next();
            }
            
            delete g;
            new_sequence.push_back(abs(result) % 10);
        }

        sequence = new_sequence;
    }

    for (int i = 0; i < 8; i++) cout << sequence[i];
    cout << endl;
}

void part2() {
    ifstream fin("day16.txt");
    string input;
    getline(fin, input);
    
    vector<int> pattern;
    for (int i = 0; i < input.size(); i++) {
        pattern.push_back(input.at(i) - '0');
    }

    vector<int> sequence;

    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < pattern.size(); j++) {
            sequence.push_back(pattern[j]);
        }
    }

    int offset = 0;
    for (int i = 6; i >= 0; i--) {
        int x = 1;
        int j = i;
        while (j < 6) {
            x *= 10;
            j++;
        }
        offset += sequence[i] * x;
    }

    vector<int> s;
    for (int i = offset; i < sequence.size(); i++) {
        s.push_back(sequence[i]);
    }

    for (int _ = 0; _ < 100; _++) {
        int num = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            num += s[i];
            s[i] = num %= 10;
        }
    }

    for (int i = 0; i < 8; i++) cout << s[i];
    cout << endl;
}

int main() {
    part1();
    part2();
}