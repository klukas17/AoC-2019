#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

long long gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

class Moon {
    public:
        int pos_x;
        int pos_y;
        int pos_z;
        int vel_x;
        int vel_y;
        int vel_z;

        Moon(int x, int y, int z) {
            pos_x = x;
            pos_y = y;
            pos_z = z;
            vel_x = 0;
            vel_y = 0;
            vel_z = 0;
        }
};

void part1() {
    ifstream fin("day12.txt");
    string input;
    vector<string> in;

    do {
        getline(fin, input);
        in.push_back(input);
    } while (!fin.eof());

    vector<Moon*> moons;
    regex r(R"(<x=(-?\d+), y=(-?\d+), z=(-?\d+)>)");
    cmatch match;

    for (int i = 0; i < in.size(); i++) {
        regex_match(const_cast<char*>(in[i].c_str()), match, r);
        Moon* moon = new Moon(stoi(match.str(1)), stoi(match.str(2)), stoi(match.str(3)));
        moons.push_back(moon);
    }

    for (int i = 0; i < 1000; i++) {

        for (int j = 0; j < moons.size(); j++) {
            for (int k = 0; k < moons.size(); k++) {
                if (j == k) continue;

                if (moons[j]->pos_x > moons[k]->pos_x) moons[j]->vel_x--;
                else if (moons[j]->pos_x < moons[k]->pos_x) moons[j]->vel_x++;

                if (moons[j]->pos_y > moons[k]->pos_y) moons[j]->vel_y--;
                else if (moons[j]->pos_y < moons[k]->pos_y) moons[j]->vel_y++;

                if (moons[j]->pos_z > moons[k]->pos_z) moons[j]->vel_z--;
                else if (moons[j]->pos_z < moons[k]->pos_z) moons[j]->vel_z++;
            }
        }

        for (auto m : moons) {
            m->pos_x += m->vel_x;
            m->pos_y += m->vel_y;
            m->pos_z += m->vel_z;
        }
    }

    int energy = 0;

    for (auto m : moons) {
        int abs_pos = abs(m->pos_x) + abs(m->pos_y) + abs(m->pos_z);
        int abs_vel = abs(m->vel_x) + abs(m->vel_y) + abs(m->vel_z);
        energy += abs_pos * abs_vel;
    }

    cout << energy << endl;
}

void part2() {
    ifstream fin("day12.txt");
    string input;
    vector<string> in;

    do {
        getline(fin, input);
        in.push_back(input);
    } while (!fin.eof());

    vector<Moon*> moons;
    vector<int> init_x;
    vector<int> init_y;
    vector<int> init_z;
    regex r(R"(<x=(-?\d+), y=(-?\d+), z=(-?\d+)>)");
    cmatch match;

    for (int i = 0; i < in.size(); i++) {
        regex_match(const_cast<char*>(in[i].c_str()), match, r);
        Moon* moon = new Moon(stoi(match.str(1)), stoi(match.str(2)), stoi(match.str(3)));
        init_x.push_back(stoi(match.str(1)));
        init_y.push_back(stoi(match.str(2)));
        init_z.push_back(stoi(match.str(3)));
        moons.push_back(moon);
    }

    int x_found = 0, y_found = 0, z_found = 0;
    long long x_time = 0, y_time = 0, z_time = 0;

    while (x_found == 0) {
        for (int j = 0; j < moons.size(); j++) {
            for (int k = 0; k < moons.size(); k++) {
                if (j == k) continue;

                if (moons[j]->pos_x > moons[k]->pos_x) moons[j]->vel_x--;
                else if (moons[j]->pos_x < moons[k]->pos_x) moons[j]->vel_x++;
            }
        }

        for (auto m : moons) {
            m->pos_x += m->vel_x;
        }

        x_time++;
        
        int flag = true;
        for (int i = 0; i < moons.size(); i++) {
            if (moons[i]->pos_x != init_x[i] || moons[i]->vel_x != 0) {
                flag = false;
                break;
            }
        }
        if (flag) x_found = true;
    }

    while (y_found == 0) {
        for (int j = 0; j < moons.size(); j++) {
            for (int k = 0; k < moons.size(); k++) {
                if (j == k) continue;

                if (moons[j]->pos_y > moons[k]->pos_y) moons[j]->vel_y--;
                else if (moons[j]->pos_y < moons[k]->pos_y) moons[j]->vel_y++;
            }
        }

        for (auto m : moons) {
            m->pos_y += m->vel_y;
        }

        y_time++;
        
        int flag = true;
        for (int i = 0; i < moons.size(); i++) {
            if (moons[i]->pos_y != init_y[i] || moons[i]->vel_y != 0) {
                flag = false;
                break;
            }
        }
        if (flag) y_found = true;
    }

    while (z_found == 0) {
        for (int j = 0; j < moons.size(); j++) {
            for (int k = 0; k < moons.size(); k++) {
                if (j == k) continue;

                if (moons[j]->pos_z > moons[k]->pos_z) moons[j]->vel_z--;
                else if (moons[j]->pos_z < moons[k]->pos_z) moons[j]->vel_z++;
            }
        }

        for (auto m : moons) {
            m->pos_z += m->vel_z;
        }

        z_time++;
        
        int flag = true;
        for (int i = 0; i < moons.size(); i++) {
            if (moons[i]->pos_z != init_z[i] || moons[i]->vel_z != 0) {
                flag = false;
                break;
            }
        }
        if (flag) z_found = true;
    }

    long long time;
    time = (x_time * y_time) / gcd(x_time, y_time);
    time = (time * z_time) / gcd(time, z_time);

    cout << time << endl;
}

int main() {
    part1();
    part2();
}