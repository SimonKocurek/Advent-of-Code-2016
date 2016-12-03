#include <fstream>
#include <iostream>

// loads values from file into matrix of points
bool read_matrix(int points[3][3], std::ifstream& file) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!(file >> points[i][j])) {
                return false;
            }    
        }
    }

    return true;
}

// checks if triangle on column i is valid
bool valid_triangle(int points[3][3], int i) {
    if (points[0][i] + points[1][i] <= points[2][i]) {
        return false;
    }
    
    if (points[0][i] + points[2][i] <= points[1][i]) {
        return false;
    }
    
    if (points[1][i] + points[2][i] <= points[0][i]) {
        return false;
    }

    return true;
}

// returns the number of valid triangles in matrix
int valid_triangle_count(int points[3][3]) {
    int count = 0;
    
    for (int i = 0; i < 3; i++) {
        if (valid_triangle(points, i)) {
            count++;
        }
    }
    
    return count;
}

// reads input from file and changes count accordingly
void process_input(int& count, int points[3][3]) {
    std::ifstream file;
    file.open("input.txt");
    
    while (read_matrix(points, file)) {
        count = count + valid_triangle_count(points);
    }
    
    file.close();
}

int main(int argc, char** argv) {
    int count = 0;
    // matrix of sides:
    // x1 x2 x3
    // y1 y2 y3
    // z1 z2 z3
    int points[3][3];

    process_input(count, points);

    std::cout << count << '\n';

    return 0;
}
