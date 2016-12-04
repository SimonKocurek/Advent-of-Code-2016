#include "Room.h"
#include <ctype.h>
#include <algorithm>
#include <unordered_map>

Room::Room(std::string& line) {
    int cursor = 0;
    
    // stop at first digit
    for (; cursor < line.length() ; cursor++) {
        if (isdigit(line[cursor])) {
            break;
        }
    }
    
    // copy the name without the last dash
    name = new std::string(line.substr(0, cursor - 1));
    // parse next 3 digits
    sector_id = std::stoi(line.substr(cursor, 3));
    // copy 5 characters inside []
    checksum = new std::string(line.substr(cursor + 4, 5));
}

Room::~Room() {
    delete name;
    delete checksum;
}

bool is_frequent(char c, std::vector<Room::Letter>* frequency) {
    for (int i = 0; i < 5; i++) {
        if ((*frequency)[i].character == c) {
            return true;
        }
    }
    
    return false;
}

bool Room::is_room() {
    std::vector<Room::Letter>* frequency = letter_frequency();
    
    bool result = true;
    for (int i = 0; i < checksum->length(); i++) {
        if (!is_frequent((*checksum)[i], frequency)) {
            result = false;
            break;
        }
    }
    
    delete frequency;
    return result;
}

void calculate_occurance_of_letters(std::unordered_map<char, int>& map, std::string* name) {
    for (int i = 0; i < name->length(); i++) {
        char letter = (*name)[i];
        
        if (letter == '-') {
            continue;
        }
        
        map[letter]++;
    }
}

bool sort_function (Room::Letter i, Room::Letter j) {
    if (j.occurances == i.occurances) {
        return j.character > i.character;
    }
    
    return (j.occurances < i.occurances); 
}

std::vector<Room::Letter>* Room::letter_frequency() {
    std::unordered_map<char, int> map;
    calculate_occurance_of_letters(map, name);
    
    std::vector<Letter>* frequency = new std::vector<Letter>();
    
    // fill the vector with each frequency pair, so that the most common letters
    // are first
    for (auto i = map.begin(); i != map.end(); i++) {
        frequency->push_back({i->first,  i->second});
    }

    // sort so the 5 most frequent numbers are first in the vector
    std::sort(frequency->begin(), frequency->end(), sort_function);
    
    return frequency;
}

int Room::get_sector_id() {
    return sector_id;
}
