#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <math.h>

using namespace std;

class Comet {
    public:
        int x;
        int y;
        int loc_x;
        int loc_y;
        float dist;
        float tan;
        Comet* brother;
        Comet* next;
        Comet(int x, int y, int loc_x, int loc_y) {
            this->loc_x = loc_x;
            this->loc_y = loc_y;
            this->x = x;
            this->y = y;
            this->dist = sqrt(x*x + y*y);
            this->tan = y * 1.0 / x;
            this->brother = nullptr;
            this->next = nullptr;
        }
};

int x_max, y_max;
vector<int> v;
int x_pos, y_pos;

int get(int x, int y) {return v[x * x_max + y];}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void part1() {
    ifstream fin("day10.txt");
    string input;
    vector<string> seglist;

    do {
        fin >> input;
        seglist.push_back(input);
    } while (!fin.eof());

    x_max = seglist[0].length();
    y_max = seglist.size();

    for (int y = 0; y < seglist.size(); y++) {
        for (int x = 0; x < seglist[0].length(); x++) {
            v.push_back(seglist[y][x] == '#');
        }       
    }

    int max = 0;

    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            if (get(i, j) != 1) continue;
            int matches = 0;

            for (int dx = -x_max; dx <= x_max; dx++) {
            	for (int dy = -y_max; dy <= y_max; dy++) {
            		if (gcd(abs(dx), abs(dy)) != 1) continue;
            		int x_curr = i, y_curr = j, found = 0;
                    while (x_curr >= 0 && x_curr < x_max && y_curr >= 0 && y_curr < y_max && !found) {
                        x_curr += dx;
                        y_curr += dy;
                        if (!(x_curr >= 0 && x_curr < x_max && y_curr >= 0 && y_curr < y_max)) break;
                        if (get(x_curr, y_curr) == 1) found = 1;
                    }
                    if (found) matches++;
            	}
            }

            if (matches > max) {
                max = matches;
                x_pos = j;
                y_pos = i;
            }
        }
    }

    cout << max << endl;
}

Comet* quadrant[4]{nullptr, nullptr, nullptr, nullptr};
Comet* axis[4]{nullptr, nullptr, nullptr, nullptr};

void insert_in_axis(Comet* comet, int card) {
    Comet* ax = axis[card];
    if (!ax) axis[card] = comet;
    else {
        Comet* curr_comet = ax;
        Comet* prev_comet = nullptr;
        while (curr_comet && curr_comet->dist < comet->dist) {
            prev_comet = curr_comet;
            curr_comet = curr_comet->brother;
        }
        if (curr_comet && prev_comet) {
            prev_comet->brother = comet;
            comet->brother = curr_comet;
        }
        else if (curr_comet && !prev_comet) {
            comet->brother = curr_comet;
            axis[card] = comet;
        }
        else if (!curr_comet && prev_comet) {
            prev_comet->brother = comet;
        }
    }
}

void insert_in_quadrant(Comet* comet, int card) {
    Comet* quad = quadrant[card];
    if (!quad) quadrant[card] = comet;
    else {
        Comet* curr_comet = quad;
        Comet* prev_comet = nullptr;
        while (curr_comet && curr_comet->tan < comet->tan) {
            prev_comet = curr_comet;
            curr_comet = curr_comet->next;
        }
        if (curr_comet && curr_comet->tan == comet->tan) {
            Comet* prev = prev_comet;
            prev_comet = nullptr;
            while (curr_comet && curr_comet->dist < comet->dist) {
                prev_comet = curr_comet;
                curr_comet = curr_comet->brother;
            }
            if (curr_comet && prev_comet) {
                prev_comet->brother = comet;
                comet->brother = curr_comet;
            }
            else if (curr_comet && !prev_comet) {
                comet->brother = curr_comet;
                comet->next = curr_comet->next;
                curr_comet->next = nullptr;
                if (prev) prev->next = comet;
                else quadrant[card] = comet;
            }
            else if (!curr_comet && prev_comet) {
                prev_comet->brother = comet;
            }
        }
        else if (curr_comet && prev_comet) {
            prev_comet->next = comet;
            comet->next = curr_comet;
        }
        else if (curr_comet && !prev_comet) {
            comet->next = curr_comet;
            quadrant[card] = comet;
        }
        else if (!curr_comet && prev_comet) {
            prev_comet->next = comet;
        }
    }
}

void part2() {

    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            if (get(i,j) != 1) continue;
            if (j == x_pos && i == y_pos) continue;

            int dx = j - x_pos, dy = i - y_pos;

            Comet* new_comet = new Comet(dx, dy, j, i);

            /* cout << endl 
                 << new_comet->x << " "
                 << new_comet->y << " "
                 << new_comet->dist << " "
                 << new_comet->tan << " "
                 << new_comet->brother << " "
                 << new_comet->next << endl; */

            if (dx > 0 && dy < 0) {
                insert_in_quadrant(new_comet, 0);
            } else if (dx > 0 && dy > 0) {
                insert_in_quadrant(new_comet, 1);
            } else if (dx < 0 && dy > 0) {
                insert_in_quadrant(new_comet, 2);
            } else if (dx < 0 && dy < 0) {
                insert_in_quadrant(new_comet, 3);
            } else if (dx == 0 && dy < 0) {
                insert_in_axis(new_comet, 0);
            } else if (dx > 0 && dy == 0) {
                insert_in_axis(new_comet, 1);
            } else if (dx == 0 && dy > 0) {
                insert_in_axis(new_comet, 2);
            } else if (dx < 0 && dy == 0) {
                insert_in_axis(new_comet, 3);
            }
        }
    }

    Comet* prev = quadrant[3];
    while (prev->next) prev = prev->next;

    for (int i = 0; i < 4; i++) axis[i]->next = quadrant[i];

    for (int i = 0; i < 4; i++) {
        Comet* c = quadrant[i];
        while (c->next) c = c->next;
        c->next = axis[(i+1)%4];
    }

    Comet* comet = axis[0];

    int x_destroyed, y_destroyed;

    for (int i = 0; i < 200; i++) {
        x_destroyed = comet->loc_x;
        y_destroyed = comet->loc_y;
        if (comet->brother) {
            Comet* brother = comet->brother;
            prev->next = brother;
            brother->next = comet->next;
            free(comet);
            prev = brother;
            comet = brother->next;
        } else {
            prev->next = comet->next;
            free(comet);
            comet = prev->next;
        }
    }

    cout << 100 * x_destroyed + y_destroyed << endl;
}

int main() {
    part1();
    part2();
}
