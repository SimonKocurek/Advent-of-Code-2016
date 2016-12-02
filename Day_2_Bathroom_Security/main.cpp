#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>

typedef struct {
    int x,y;
} point;

void read_instruction(char instruction, point& location) {
    point previous_location = {location.x, location.y};
    
    switch(instruction) {
        case 'U': location.y--; break;
        case 'D': location.y++; break;
        case 'L': location.x--; break;
        case 'R': location.x++; break;
    }
    
    // distance from the middle
    if (std::abs(2 -location.x) + std::abs(2 -location.y) > 2) {
        location = previous_location;
    }
}

void read_line(std::string& line, point& location) {
    std::istringstream line_reader(line);

    char instruction;
    while (line_reader >> instruction) {
        read_instruction(instruction, location);
    }
}

void print_result(std::vector<char>& result) {
    for (auto i = result.begin(); i != result.end(); i++) {
        std::cout << *i;
    }
}

int main(int argc, char** argv) {
    point location = {0,2};
    const char numbers[5][5] = {
        {0,   0, '1', 0,  0 },
        {0,  '2','3','4', 0 },
        {'5','6','7','8','9'},
        {0,  'A','B','C', 0 },
        {0,   0, 'D', 0,  0 }
    };
    
    std::vector<char> result;
    std::string line;
    while(std::cin >> line) {
        read_line(line, location);
        
        result.push_back(numbers[location.y][location.x]);
    }
    
    print_result(result);
    
    return 0;
}
