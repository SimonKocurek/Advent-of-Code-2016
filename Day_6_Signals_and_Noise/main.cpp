#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

int main(int argc, char** argv) {
    vector<unordered_map<char, int>> message;
    
    string line;
    if (cin >> line) {
        for (auto i : line) {
            unordered_map<char, int> character_map;
            character_map[i] = 1;
            
            message.push_back(character_map);
        }
    } else {
        return 1;
    }
    
    while (cin >> line) {
        for (int i = 0; i < line.length(); i++) {
            message[i][line[i]]++;
        }
    }
    
    for (auto map : message) {
        int min = INT_MAX;
        char min_char;
        
        for (auto i : map) {
            if (i.second < min) {
                min = i.second;
                min_char = i.first;
            }
        }
        
        cout << min_char;
    }
    
    return 0;
}
