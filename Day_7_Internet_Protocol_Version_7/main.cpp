#include <iostream>
#include <set>

using namespace std;

bool correct_line(string& line) {
    bool correct = false;
    bool outside = true; // outside of "[ ]"
    
    for (int i = 0; i < line.length() - 3; i++) {
        if (line[i] == '[' || line[i] == ']') {
            outside = !outside;
            continue;
        }
        
        // must be different characters
        if (line[i] == line[i+1]) {
            continue;
        }
        
        // is ABBA type
        if (line[i] == line[i+3] && line[i+1] == line[i+2]) {
            if (outside) {
                correct = true;
            } else {
                return false;
            }
        }
    }
    
    return correct;
}

namespace bonus {
    
    // turns ABA into BAB
    void reverse_pair(string& pair) {
        pair[0] = pair[1]; // BBA
        pair[1] = pair[2]; // BAA
        pair[2] = pair[0]; // BAB
    }
    
    // returns true if first pair contains string, else inserts into the second
    bool insert_if_not_in(set<string>& pairs, set<string>& insert_set, string& pair) {
        if (pairs.find(pair) != pairs.end()) {
            return true;
        }

        insert_set.insert(pair);
    }
    
    bool correct_line(string& line) {
        set<string> outside_pairs;
        set<string> inside_pairs;
        
        bool is_outside = true; // outside of "[ ]"

        for (int i = 0; i < line.length() - 2; i++) {
            if (line[i] == '[' || line[i] == ']') {
                is_outside = !is_outside;
                continue;
            }

            // is ABA type
            if (line[i] == line[i+2] && line[i] != line[i+1]) {
                string pair = line.substr(i, 3);
                
                if (is_outside) {
                    if (insert_if_not_in(inside_pairs, outside_pairs, pair)) {
                        return true;
                    }
                } else {
                    reverse_pair(pair);
                    
                    if (insert_if_not_in(outside_pairs, inside_pairs, pair)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}

int main(int argc, char** argv) {
    int count = 0;
    
    string line;
    while (cin >> line) {
        if (bonus::correct_line(line)) {
            count++;
        }
    }
    
    cout << count;
    return 0;
}

