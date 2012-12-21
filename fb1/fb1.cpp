#include <iostream>
#include <vector>

unsigned int N = 0; // max size
unsigned int K = 0; // # of pegs
std::vector<unsigned int> status;
std::vector<unsigned int> output;
std::vector<unsigned int> moveFrom;
std::vector<unsigned int> moveTo;


bool canMoveHere(unsigned int size, unsigned int pos) {
    for (unsigned int i = N; i > size; --i) {
        if (status[i] == pos) {
            return false;
        }
    }
    return true;
}

unsigned int findBestPosToMove(unsigned int size, 
                               unsigned int prohibited1, 
                               unsigned int prohibited2) {
    unsigned int pos2 = 0;
    if (output[size] != prohibited1 && output[size] != prohibited2 && 
        canMoveHere(size, output[size])) 
    {
        pos2 = output[size];
    }
    
    if (!pos2) {
        for (unsigned int i = 1; i <= K; ++i) {
            if (i != prohibited1 && i != prohibited2 && canMoveHere(size, i)) {
                pos2 = i;
                break;
            }
        }
    }
    return pos2;
}

void move(unsigned int size, unsigned int end) {
    unsigned int start = status[size];
    // find size which is on the same pos as s
    unsigned int size2 = 0;
    for (unsigned int i = size - 1; i >= 1; --i) {
        if (status[i] == start) {
            size2 = i;
            break;
        }
    }
    
    if (size2 != 0) {
        // find another destination pos != start and != end
        // Preferrably destination should be equal to output[size2]
        unsigned int pos2 = findBestPosToMove(size2, start, end);
        move(size2, pos2);
    }
    
    moveFrom.push_back(status[size]);
    moveTo.push_back(end);
    status[size] = end;
}

int main() {
    std::cin >> N;
    std::cin >> K;
    
    status.resize(N + 1);
    for (unsigned int i = 1; i <= N; ++i) {
        std::cin >> status[i];
    }
    
    output.resize(N + 1);
    for (unsigned int i = 1; i <= N; ++i) {
        std::cin >> output[i];
    }
    
    for (unsigned int i = N; i >= 1; --i) {
        if (status[i] != output[i]) {
            move(i, output[i]);
        }
    }
    
    std::cout << moveFrom.size() << std::endl;
    for (unsigned int i = 0; i < moveFrom.size(); ++i) {
        std::cout << moveFrom[i] << " " << moveTo[i] << std::endl;
    }
}