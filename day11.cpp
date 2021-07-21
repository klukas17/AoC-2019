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
                        if (out.size() == 2) return;
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
                        halted = 1;
                        return;
                }
            }
        }
};

class Node {
    public:

        int x_coordinate;
        int y_coordinate;
        int color;
        Node* left_node;
        Node* right_node;

        Node(int x, int y, int t) {
            x_coordinate = x;
            y_coordinate = y;
            color = t;
            left_node = nullptr;
            right_node = nullptr;
        }
};

class NodeIterator {
    public:

        stack<Node*> s;

        NodeIterator(Node* root) {
            s.push(root);
        }

        bool has_next() {
            if (s.size() > 0) return true;
            else return false;
        }

        Node* next() {
            Node* ret_node = s.top();
            s.pop();
            if (ret_node->left_node) s.push(ret_node->left_node);
            if (ret_node->right_node) s.push(ret_node->right_node);
            return ret_node;
        }
};

class CoordinateSystem {
    public:

        Node* root;
        int num;

        CoordinateSystem(int start) {
            root = new Node(0, 0, start);
            num = 1;
        }

        Node* get_node(int x, int y) {
            return get(root, x, y);
        }

        Node* get(Node* curr, int x, int y) {
            if (!curr) return nullptr;
            if (curr->x_coordinate == x && curr->y_coordinate == y) return curr;
            if (curr->x_coordinate > x || curr->x_coordinate == x && curr->y_coordinate > y) return get(curr->left_node, x, y);
            return get(curr->right_node, x, y);
        }

        Node* insert_node(int x, int y, int t) {
            return insert(root, x, y, t);
        }

        Node* insert(Node* curr, int x, int y, int t) {
            if (curr->x_coordinate == x && curr->y_coordinate == y) return nullptr;
            else if (curr->left_node && (curr->x_coordinate > x || curr->x_coordinate == x && curr->y_coordinate > y))
                return insert(curr->left_node, x, y, t);
            else if (!curr->left_node && (curr->x_coordinate > x || curr->x_coordinate == x && curr->y_coordinate > y)) {
                curr->left_node = new Node(x, y, t);
                num++;
                return curr->left_node;
            }
            else if (curr->right_node && (curr->x_coordinate < x || curr->x_coordinate == x && curr->y_coordinate < y))
                return insert(curr->right_node, x, y, t);
            else if (!curr->right_node && (curr->x_coordinate < x || curr->x_coordinate == x && curr->y_coordinate < y)) {
                curr->right_node = new Node(x, y, t);
                num++;
                return curr->right_node;
            }
            return nullptr;
        }

        int get_limit(Node* curr, int coordinate, int extreme) {

            if (curr->left_node && curr->right_node) {
                int left_child = get_limit(curr->left_node, coordinate, extreme);
                int right_child = get_limit(curr->right_node, coordinate, extreme);
                if (coordinate == 0 && extreme == 0) {
                    int candidate = (left_child < right_child) ? left_child : right_child;
                    return (curr->x_coordinate < candidate) ? curr->x_coordinate : candidate;
                } 
                else if (coordinate == 0 && extreme == 1) {
                    int candidate = (left_child > right_child) ? left_child : right_child;
                    return (curr->x_coordinate > candidate) ? curr->x_coordinate : candidate;
                }
                else if (coordinate == 1 && extreme == 0) {
                    int candidate = (left_child < right_child) ? left_child : right_child;
                    return (curr->y_coordinate < candidate) ? curr->y_coordinate : candidate;
                }
                else if (coordinate == 1 && extreme == 1) {
                    int candidate = (left_child > right_child) ? left_child : right_child;
                    return (curr->y_coordinate > candidate) ? curr->y_coordinate : candidate;
                }
            }

            else if (curr->left_node && !curr->right_node) {
                int child = get_limit(curr->left_node, coordinate, extreme);
                if (coordinate == 0 && extreme == 0) {
                    return (curr->x_coordinate < child) ? curr->x_coordinate : child;
                } 
                else if (coordinate == 0 && extreme == 1) {
                    return (curr->x_coordinate > child) ? curr->x_coordinate : child;
                }
                else if (coordinate == 1 && extreme == 0) {
                    return (curr->y_coordinate < child) ? curr->y_coordinate : child;
                }
                else if (coordinate == 1 && extreme == 1) {
                    return (curr->y_coordinate > child) ? curr->y_coordinate : child;
                }
            }

            else if (!curr->left_node && curr->right_node) {
                int child = get_limit(curr->right_node, coordinate, extreme);
                if (coordinate == 0 && extreme == 0) {
                    return (curr->x_coordinate < child) ? curr->x_coordinate : child;
                } 
                else if (coordinate == 0 && extreme == 1) {
                    return (curr->x_coordinate > child) ? curr->x_coordinate : child;
                }
                else if (coordinate == 1 && extreme == 0) {
                    return (curr->y_coordinate < child) ? curr->y_coordinate : child;
                }
                else if (coordinate == 1 && extreme == 1) {
                    return (curr->y_coordinate > child) ? curr->y_coordinate : child;
                }
            }

            else {
                if (coordinate == 0) return curr->x_coordinate;
                else return curr->y_coordinate;
            }

            return 0;
        }
};

class Robot {
    public:

        int x;
        int y;
        int direction;
        int text;
        IntcodeComputer* brain;
        CoordinateSystem* map;

        Robot(int start) {
            x = 0;
            y = 0;
            direction = UP;
            text = start;
            brain = new IntcodeComputer();
            map = new CoordinateSystem(start);
        }

        enum Direction {
            UP = 0, 
            RIGHT = 1,
            DOWN = 2,
            LEFT = 3
        };

        void color() {
            ifstream fin("day11.txt");
            string input;
            fin >> input;

            stringstream stream(input);
            string segment;

            int curr = 0;
            while(getline(stream, segment, ',')) {
                brain->seglist[curr] = stoll(segment);
                curr++;
            }

            while (brain->halted == 0) {
                Node* curr = map->get_node(x, y);
                if (!curr) curr = map->insert_node(x, y, 0);
                brain->in.push(curr->color);
                brain->simulate();
                
                if (brain->halted == 0) {
                    int arg1 = brain->out.front();
                    brain->out.pop();
                    int arg2 = brain->out.front();
                    brain->out.pop();
                
                    curr->color = arg1;

                    switch(direction) {

                        case UP:
                            if (arg2 == 0) direction = LEFT;
                            else if (arg2 == 1) direction = RIGHT;
                            break;

                        case RIGHT:
                            if (arg2 == 0) direction = UP;
                            else if (arg2 == 1) direction = DOWN;
                            break;

                        case DOWN:
                            if (arg2 == 0) direction = RIGHT;
                            else if (arg2 == 1) direction = LEFT;
                            break;

                        case LEFT:
                            if (arg2 == 0) direction = DOWN;
                            else if (arg2 == 1) direction = UP;
                            break;
                    }

                    switch(direction) {

                        case UP:
                            y++;
                            break;

                        case RIGHT:
                            x++;
                            break;

                        case DOWN:
                            y--;
                            break;

                        case LEFT:
                            x--;
                            break;
                    }
                }
            }
            if (text) read_registration_identifier();
        }

        void read_registration_identifier() {
            int min_x, max_x, min_y, max_y;
            min_x = map->get_limit(map->root, 0, 0);
            max_x = map->get_limit(map->root, 0, 1);
            min_y = map->get_limit(map->root, 1, 0);
            max_y = map->get_limit(map->root, 1, 1);

            int dx = max_x - min_x + 1;
            int dy = max_y - min_y + 1;

            vector<vector<int>> registration;
            for (int i = 0; i < dy; i++) {
                vector<int> v;
                for (int j = 0; j < dx; j++) {
                    v.push_back(0);
                }
                registration.push_back(v);
            }

            NodeIterator* it = new NodeIterator(map->root);
            while (it->has_next()) {
                Node* node = it->next();
                registration[-node->y_coordinate-max_y][node->x_coordinate-min_x] = node->color;
            }

            for (int i = 0; i < registration.size(); i++) {
                vector<int> v = registration[i];
                for (int j = 0; j < v.size(); j++) {
                    if (v[j] == 1) cout << "*";
                    else cout << " ";
                }
                cout << endl;
            }
        }
};

void part1() {
    Robot* robot = new Robot(0);
    robot->color();
    cout << robot->map->num << endl;
}

void part2() {
    Robot* robot = new Robot(1);
    robot->color();
}

int main() {
    part1();
    part2();
}