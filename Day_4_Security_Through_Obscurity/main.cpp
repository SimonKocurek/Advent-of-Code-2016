#include "main.h"
#include "Room.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    int result = 0;
    
    read_file("input.txt", result);
    
    std::cout << result;
    return 0;
}

void read_file(const std::string& file_name, int& result) {
    std::ifstream file;
    file.open(file_name);
    
    std::string line;
    while (file >> line) {
        process_line(line, result);
    }
    
    file.close();
}

void process_line(std::string& line, int& result) {
    Room room(line);
    if (room.is_room()) {
        result = result + room.get_sector_id();
    }
}
