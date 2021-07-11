#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> seglist;

int simulate(int input1, int input2) {

    int out = 0, index = 0;
    queue<int> input;
    input.push(input1);
    input.push(input2);
    int input_index = 0;
    bool flag = true;
    vector<int> temporary(seglist);

    while (flag) {

        int arg1, arg2, arg3;

        int instruction = temporary[index];
        int opcode = instruction % 100;
        instruction /= 100;
        int mode1 = instruction % 10;
        instruction /= 10;
        int mode2 = instruction % 10;
        instruction /= 10;
        int mode3 = instruction % 10;

        if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8) {
            if (mode1 == 0) arg1 = temporary[temporary[index+1]];
            else arg1 = temporary[index+1];

            if (mode2 == 0) arg2 = temporary[temporary[index+2]];
            else arg2 = temporary[index+2]; 
        }

        switch(opcode) {
            case 1:
                arg3 = arg1 + arg2;
                if (mode3 == 0) temporary[temporary[index+3]] = arg3;
                else temporary[index+3] = arg3;
                index += 4;
                break;

            case 2:
                arg3 = arg1 * arg2;
                if (mode3 == 0) temporary[temporary[index+3]] = arg3;
                else temporary[index+3] = arg3;
                index += 4;
                break;

            case 3:
                if (mode1 == 0) temporary[temporary[index+1]] = input.front();
                else temporary[index+1] = input.front();
                input.pop();
                index += 2;
                break;

            case 4:
                if (mode1 == 0) out = temporary[temporary[index+1]];
                else out = temporary[index+1];
                index += 2;
                break;
                
            case 5:
            	if (arg1 != 0) index = arg2;
            	else index += 3;
            	break;
            	
            case 6:
            	if (arg1 == 0) index = arg2;
            	else index += 3;
            	break;
            	
            case 7:
                arg3 = temporary[index+3];
            	temporary[arg3] = arg1 < arg2;
            	index += 4;
            	break;
            	
            case 8:
                arg3 = temporary[index+3];
            	temporary[arg3] = arg1 == arg2;
            	index += 4;
            	break;

            case 99:
                flag = false;
                break;
        }
    }

    return out;
}

void part1() {
    ifstream fin("day07.txt");
    string input;
    fin >> input;

    stringstream stream(input);
    string segment;

    while(getline(stream, segment, ',')) {
        seglist.push_back(stoi(segment));
    }

    int max_output = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == j) continue;
            for (int k = 0; k < 5; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 5; l++) {
                    if (l == i || l == j || l == k) continue;
                    for (int m = 0; m < 5; m++) {
                        if (m == i || m == j || m == k || m == l) continue;
                        //cout << i << " " << j << " " << k << " " << l << " " << m << endl;
                        int args[] = {i,j,k,l,m};
                        int input = 0;
                        int output;
                        for (int n = 0; n < 5; n++) {
                            output = simulate(args[n], input);
                            input = output;
                        }
                        if (output > max_output) max_output = output;
                    }
                }
            }
        }
    }

    cout << max_output << endl;
}

vector<int> temp[5];
int local_index[5];
queue<int> input[5];
int terminated[5];
int output[5];

void reset_args() {
    for (int i = 0; i < 5; i++) {
        vector<int> empty(seglist);
        temp[i].swap(empty);
        local_index[i] = 0;
        queue<int> e;
        input[i].swap(e);
        terminated[i] = 0;
        output[i] = 0;
    }
}

int sum_terminated() {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        if (terminated[i] == 1) result++;
    }
    return result;
}

void simulate_loop(int card) {

    while (true) {
        int arg1, arg2, arg3;
        int instruction = temp[card][local_index[card]];
        int opcode = instruction % 100;
        instruction /= 100;
        int mode1 = instruction % 10;
        instruction /= 10;
        int mode2 = instruction % 10;
        instruction /= 10;
        int mode3 = instruction % 10;

        if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8) {
            
            if (mode1 == 0) arg1 = temp[card][temp[card][local_index[card]+1]];
            else arg1 = temp[card][local_index[card]+1];

            if (mode2 == 0) arg2 = temp[card][temp[card][local_index[card]+2]];
            else arg2 = temp[card][local_index[card]+2];
        } 

        switch(opcode) {
            case 1:
                arg3 = arg1 + arg2;
                if (mode3 == 0) temp[card][temp[card][local_index[card]+3]] = arg3;
                else temp[card][local_index[local_index[card]+3]] = arg3;
                local_index[card] += 4;
                break;

            case 2:
                arg3 = arg1 * arg2;
                if (mode3 == 0) temp[card][temp[card][local_index[card]+3]] = arg3;
                else temp[card][local_index[local_index[card]+3]] = arg3;
                local_index[card] += 4;
                break;

            case 3:            
                if (mode1 == 0) temp[card][temp[card][local_index[card]+1]] = input[card].front();
                else temp[card][local_index[card]+1] = input[card].front();
                input[card].pop();
                local_index[card] += 2;
                break;

            case 4:
                if (mode1 == 0) output[card] = temp[card][temp[card][local_index[card]+1]];
                else output[card] = temp[card][local_index[card]+1];
                local_index[card] += 2;
                input[(card+1)%5].push(output[card]);
                return;

            case 5:
                if (arg1 != 0) local_index[card] = arg2;
                else local_index[card] += 3;
                break;

            case 6:
                if (arg1 == 0) local_index[card] = arg2;
                else local_index[card] += 3;
                break;

            case 7:
                arg3 = temp[card][local_index[card]+3];
                temp[card][arg3] = arg1 < arg2;
                local_index[card] += 4;
                break;

            case 8:
                arg3 = temp[card][local_index[card]+3];
                temp[card][arg3] = arg1 == arg2;
                local_index[card] += 4;
                break;

            case 99:
                terminated[card] = 1;
                return;
            
        }
    }
    

}

void part2() {

    int max_output = 0;

    for (int i = 5; i < 10; i++) {
        for (int j = 5; j < 10; j++) {
            if (i == j) continue;
            for (int k = 5; k < 10; k++) {
                if (k == i || k == j) continue;
                for (int l = 5; l < 10; l++) {
                    if (l == i || l == j || l == k) continue;
                    for (int m = 5; m < 10; m++) {
                        if (m == i || m == j || m == k || m == l) continue;
                        //cout << i << " " << j << " " << k << " " << l << " " << m << endl;
                        reset_args();
                        int args[5] = {i,j,k,l,m};
                        for (int i = 0; i < 5; i++) {
                            input[i].push(args[i]);
                        }
                        input[0].push(0);
                        int current_node = 0;
                        while (sum_terminated() < 5) {
                            simulate_loop(current_node);
                            current_node++;
                            current_node %= 5;
                        }

                        if (output[4] > max_output) max_output = output[4];
                    }
                }
            }
        }
    }

    cout << max_output << endl;
}

int main() {
    part1();
    part2();
}