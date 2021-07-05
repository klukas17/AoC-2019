#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <climits>
#include <vector>
#include <map>

using namespace std;

void part1() {
    ifstream fin("day03.txt");
    string trail1, trail2, segment;
    
    set<tuple<int, int>> v1, v2;
    fin >> trail1;
    fin >> trail2;

    stringstream stream(trail1);
    vector<string> seglist1;

    while(getline(stream, segment, ',')) {
        seglist1.push_back(segment);
    }

    stream.str("");
    stream.clear();

    stream.str(trail2);
    vector<string> seglist2;

    while(getline(stream, segment, ',')) {
        seglist2.push_back(segment);
    }

    int x = 0, y = 0;
    for (string s : seglist1) {
        char c = s.at(0);
        int d = stoi(s.substr(1));
        switch(c) {

            case 'U':
                while (d > 0) {
                    y++;
                    d--;
                    v1.insert(tuple<int, int>{x,y});
                }
                break;

            case 'D':
                while (d > 0) {
                    y--;
                    d--;
                    v1.insert(tuple<int, int>{x,y});
                }
                break;

            case 'L':
                while (d > 0) {
                    x--;
                    d--;
                    v1.insert(tuple<int, int>{x,y});
                }
                break;

            case 'R':
                while (d > 0) {
                    x++;
                    d--;
                    v1.insert(tuple<int, int>{x,y});
                }
                break;

        }
    }

    x = y = 0;
    for (string s : seglist2) {
        char c = s.at(0);
        int d = stoi(s.substr(1));
        switch(c) {

            case 'U':
                while (d > 0) {
                    y++;
                    d--;
                    v2.insert(tuple<int, int>{x,y});
                }
                break;

            case 'D':
                while (d > 0) {
                    y--;
                    d--;
                    v2.insert(tuple<int, int>{x,y});
                }
                break;

            case 'L':
                while (d > 0) {
                    x--;
                    d--;
                    v2.insert(tuple<int, int>{x,y});
                }
                break;

            case 'R':
                while (d > 0) {
                    x++;
                    d--;
                    v2.insert(tuple<int, int>{x,y});
                }
                break;

        }
    }

    set<tuple<int,int>> intersect;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(intersect, intersect.begin()));

    int min = INT_MAX, dist;

    for (auto i : intersect) {
        dist = abs(get<0>(i)) + abs(get<1>(i));
        if (dist < min) min = dist;
    }

    cout << min  << endl;

}

void part2() {
    ifstream fin("day03.txt");
    string trail1, trail2, segment;
    
    set<tuple<int, int>> v1, v2;
    fin >> trail1;
    fin >> trail2;

    stringstream stream(trail1);
    vector<string> seglist1;

    while(getline(stream, segment, ',')) {
        seglist1.push_back(segment);
    }

    stream.str("");
    stream.clear();

    stream.str(trail2);
    vector<string> seglist2;

    while(getline(stream, segment, ',')) {
        seglist2.push_back(segment);
    }

    map<tuple<int,int>, int> m1;

    int x = 0, y = 0, t = 0;
    for (string s : seglist1) {
        char c = s.at(0);
        int d = stoi(s.substr(1));
        switch(c) {

            case 'U':
                while (d > 0) {
                    y++;
                    d--;
                    t++;
                    v1.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m1.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m1.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'D':
                while (d > 0) {
                    y--;
                    d--;
                    t++;
                    v1.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m1.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m1.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'L':
                while (d > 0) {
                    x--;
                    d--;
                    t++;
                    v1.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m1.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m1.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'R':
                while (d > 0) {
                    x++;
                    d--;
                    t++;
                    v1.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m1.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m1.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

        }
    }

    map<tuple<int,int>, int> m2;

    x = y = t = 0;
    for (string s : seglist2) {
        char c = s.at(0);
        int d = stoi(s.substr(1));
        switch(c) {

            case 'U':
                while (d > 0) {
                    y++;
                    d--;
                    t++;
                    v2.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m2.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m2.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'D':
                while (d > 0) {
                    y--;
                    d--;
                    t++;
                    v2.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m2.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m2.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'L':
                while (d > 0) {
                    x--;
                    d--;
                    t++;
                    v2.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m2.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m2.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

            case 'R':
                while (d > 0) {
                    x++;
                    d--;
                    t++;
                    v2.insert(tuple<int, int>{x,y});
                    try {
                        auto a = m2.at(tuple<int,int>{x,y});
                    } catch (exception e) {
                        m2.insert({tuple<int,int>{x,y}, t});
                    }
                }
                break;

        }
    }

    set<tuple<int,int>> intersect;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(intersect, intersect.begin()));

    int min = INT_MAX, dist;

    //for (auto &i : m1) cout << get<0>(i.first) << ", " << get<1>(i.first) << " -> " << i.second << endl;

    for (auto i : intersect) {
        dist = m1.at(i) + m2.at(i);
        if (dist < min) min = dist;
    }

    cout << min  << endl;

}

int main() {
    part1();
    part2();
}