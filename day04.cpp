#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void part1() {
    int lower_bound = 265275;
    int higher_bound = 781584;
    int match = 0;

    for (int candidate = lower_bound; candidate <= higher_bound; candidate++) {

        if (candidate < 100000 || candidate > 999999) continue;

        bool flag = false;
        int num = candidate;
        while (num > 0) {
            int digit1 = num % 10;
            int digit2 = (num/10) % 10;
            num /= 10;
            if (digit1 == digit2) {
                flag = true;
                break;
            }
        }
        if (!flag) continue;

        flag = true;
        num = candidate;
        while (num > 0) {
            int digit1 = num % 10;
            int digit2 = (num/10) % 10;
            num /= 10;
            if (digit1 < digit2) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;

        match++;
    }

    cout << match << endl;
}

void part2() {
    int lower_bound = 265275;
    int higher_bound = 781584;
    int match = 0;

    for (int candidate = lower_bound; candidate <= higher_bound; candidate++) {

        if (candidate == 265333) {
            int a = 0;
        }

        if (candidate < 100000 || candidate > 999999) continue;

        bool flag = false;
        int num = candidate;
        while (num > 0) {
            int digit1 = num % 10;
            int digit2 = (num/10) % 10;
            int digit3 = (num/100) % 10;
            num /= 10;
            if (digit1 == digit2) {
                if (digit3 != digit2) {
                    flag = true;
                    break;
                }
                else {
                    num /= 10;
                    do {
                        digit3 = (num/10) % 10;
                        num /= 10;
                    } while (digit3 == digit2);
                }
            }
        }
        if (!flag) continue;

        flag = true;
        num = candidate;
        while (num > 0) {
            int digit1 = num % 10;
            int digit2 = (num/10) % 10;
            num /= 10;
            if (digit1 < digit2) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;

        match++;
    }

    cout << match << endl;
}

int main() {
    part1();
    part2();
}