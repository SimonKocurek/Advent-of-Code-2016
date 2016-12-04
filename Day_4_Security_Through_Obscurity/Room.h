#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>

class Room {
public:
    Room(std::string& line);
    Room(const Room& orig);
    virtual ~Room();
    
    typedef struct {
        char character;
        int occurances;
    } Letter;
    
    bool is_room();
    int get_sector_id();
    
private:
    std::string* name;
    int sector_id;
    std::string* checksum;
    
    std::vector<Letter>* letter_frequency();
};

#endif
