#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <climits>

using namespace std;

struct node {
    string id;
    node* parent;
    vector<node*> children;
};

typedef node* node_p;

node_p createNode(string id) {
    node_p n = new node;
    n->id = id;
    n->parent = NULL;
    return n;
}

map<string, node_p> m;
set<string> s;

void part1() {
	ifstream fin("day06.txt");
    string input;
    vector<string> seglist;
    fin >> input;

    while (!fin.eof()) {
        seglist.push_back(input);
        fin >> input;
    }
    
    vector<tuple<string,string>> orbits;

    for (auto i : seglist) {
        string s1 = i.substr(0, 3);
        string s2 = i.substr(4);
        node_p a, b;

        if (m.find(s1) == m.end()) {
            a = createNode(s1);
            m.insert({s1, a});
        } else {
            a = m[s1];
        }

        if (m.find(s2) == m.end()) {
            b = createNode(s2);
            m.insert({s2, b});
        } else {
            b = m[s2];
        }

        b->parent = a;
        a->children.push_back(b);
    }

    int count = 0;

    for (auto i : m) {
        node_p n = i.second;
        while (n->parent) {
            count++;
            n = n->parent;
        }
    }

    cout << count << endl;

}

int orbitalTransfers(node_p curr) {
    
    s.insert(curr->id);

    if (curr->id == "SAN") return 0;

    int min;

    if (curr->parent && s.find(curr->parent->id) == s.end()) min = orbitalTransfers(curr->parent);
    else min = INT_MAX/2;

    for (auto i : curr->children) {
        if (s.find(i->id) == s.end()) {
            int candidate = orbitalTransfers(i);
            if (candidate < min) min = candidate;
        }
    }

    return 1 + min;
}

void part2() {
    cout << orbitalTransfers(m["YOU"]) - 2 << endl;
}

int main() {
    part1();
    part2();
}
