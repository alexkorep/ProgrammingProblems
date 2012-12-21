/*
There are K pegs. Each peg can hold discs in decreasing order of radius when looked from bottom to top of the peg. There are N discs which have radius 1 to N; Given the initial configuration of the pegs and the final configuration of the pegs, output the moves required to transform from the initial to final configuration. You are required to do the transformations in minimal number of moves. 

A move consists of picking the topmost disc of any one of the pegs and placing it on top of anyother peg. At anypoint of time, the decreasing radius property of all the pegs must be maintained. 

Constraints: 
1<= N<=8 
3<= K<=5 

Input Format: 
N K 
2nd line contains N integers. Each integer in the second line is in the range 1 to K where the i-th integer denotes the peg to which disc of radius i is present in the initial configuration. 3rd line denotes the final configuration in a format similar to the initial configuration. 

Output Format: 
The first line contains M - The minimal number of moves required to complete the transformation. The following M lines describe a move, by a peg number to pick from and a peg number to place on. If there are more than one solutions, it's sufficient to output any one of them. You can assume, there is always a solution with less than 7 moves and the initial confirguration will not be same as the final one. 


Sample Input #00: 
2 3 
1 1 
2 2  
Sample Output #00: 
3 
1 3 
1 2 
3 2 

Sample Input #01: 
6 4 
4 2 4 3 1 1 
1 1 1 1 1 1 
Sample Output #01: 
5
3 1 
4 3 
4 1 
2 1 
3 1 

*/

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