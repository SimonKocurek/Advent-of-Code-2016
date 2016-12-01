#include <iostream>
#include <unordered_map>

typedef struct {
    int x,y;
} point;

/**
 * Extracts integer from string in format "L1234,", or "R123"
 */
int extract_int(std::string* str) {
    int str_end = str->length();
    if ((*str)[str->length() - 1] == ',') {
        str_end--;
    }

    *str = str->substr(1, str_end - 1);
    return atoi(str->c_str());
}

/**
 * changes direction based on input character, L means 90 degrees left, R 90 
 * degrees right
 */
void change_direction(char direction, int& direction_id) {
    if (direction == 'L') {
        direction_id = direction_id - 1;
        
        if (direction_id < 0) {
            direction_id = 3;
        }
        
        return;
    }
    
    if (direction == 'R') {
        direction_id = (direction_id + 1) % 4;
        return;
    }
}

int main(int argc, char** argv) {
    point location = {0,0};
    
    // vector used for movement
    point directions[4] = {{0,1},{-1,0},{0,-1},{1,0}};
    int direction_id = 3;
    
    // map of visited points
    std::unordered_map<int, std::unordered_map<int, bool>> visited;
    bool twice_visited = false;
    
    std::string instruction; 
    while (!twice_visited && std::cin >> instruction) {
        char direction = instruction[0];
        change_direction(direction, direction_id);
        
        int movement = extract_int(&instruction);
        
        // move to each field and check/ record if you have already visited the 
        // point
        for (int i = 0; i < movement; i++) {
            if ((visited[location.x])[location.y]) {
                twice_visited = true;
                break;
            }
            (visited[location.x])[location.y] = true;
        
            location.x += directions[direction_id].x;
            location.y += directions[direction_id].y;
        }
    }
    
    std::cout << std::abs(location.x) + std::abs(location.y) << '\n';
    
    return 0;
}
