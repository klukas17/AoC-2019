#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <tuple>
#include <map>

using namespace std;

class Material {
    public:
        string name;
        int quantity;
        vector<tuple<string, int>> ingredients;
        Material(string name, int quantity) {
            this->name = name;
            this->quantity = quantity;
        }
};

map<string, Material*> materials_map;
map<string, int> stock;
long long ores = 0;

void count_ores(string material) {
    Material* m = materials_map[material];
    for (auto ingredient : m->ingredients) {
        int amount = get<1>(ingredient);
        string rock = get<0>(ingredient);

        if (rock == "ORE") ores += amount;

        else {
            while (stock[rock] < amount) {
                count_ores(rock);
                stock[rock] += materials_map[rock]->quantity;
            }
            stock[rock] -= amount;
        }
    }
}

void part1() {
    ifstream fin("day14.txt");
    string input;
    vector<string> in;

    while (!fin.eof()) {
        getline(fin, input);
        in.push_back(input);
    }

    regex r1(R"((\d+ [A-Z]+(?:, \d+ [A-Z]+)*) => (\d+ [A-Z]+))");
    regex r2(R"((\d+ [A-z]+)(?:, )?(\d+ [A-Z]+(?:, \d+ [A-Z]+)*)?)");
    regex r3(R"((\d+) ([A-Z]+))");
    cmatch match;

    for (int i = 0; i < in.size(); i++) {
        regex_match(const_cast<char*>(in[i].c_str()), match, r1);
        string result = match[match.size()-1];
        string ingredients_match = match[1];

        vector<string> ingredients;

        bool flag = true;
        while (flag) {
            regex_match(const_cast<char*>(ingredients_match.c_str()), match, r2);
            if (match.size() < 3) flag = false;
            ingredients.push_back(match[1]);
            ingredients_match = match[2];
        }
        ingredients.pop_back();

        regex_match(const_cast<char*>(result.c_str()), match, r3);
        Material* mat = new Material(match[2], stoi(match[1]));

        materials_map[match[2]] = mat;
        stock[match[2]] = 0;

        for (auto i : ingredients) {
            regex_match(const_cast<char*>(i.c_str()), match, r3);
            mat->ingredients.push_back(tuple<string, int>(match[2], stoi(match[1])));
        }
    }

    count_ores("FUEL");

    cout << ores << endl;
}

void part2() {
    int fuel = 1;
    while (ores <= 1000000000000) {
        count_ores("FUEL");
        if (ores <= 1000000000000) fuel++;
    }
    cout << fuel << endl;
}

int main() {
    part1();
    part2();
}