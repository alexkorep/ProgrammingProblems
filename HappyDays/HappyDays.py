"""
http://www.codechef.com/problems/HAPPY

Johnny has a pool in his garden. There are several islands in the pool. 
Some islands are connected by bridges. Any bridge can be removed. Every day 
Johnny removes some bridges so that there is only one way from any island to 
any other. In the evening he returns removed bridges to their places. Also he 
has some favorite bridges which he never removes. Johnny will be happy if he is 
able to make a configuration of bridges on the given day which he has never 
made before. You have to count the amount of days he will be happy. Of course, 
if the favorite bridges themselves don't satisfy the happiness condition Johnny 
will not be happy for even single day.

Input

The first line of input file contains number t - the number of test cases. Then
the description of each test case follows. The first line of each test case 
contains number n - the number of islands. Islands are numbered with integers 
from 1 to n. Then n lines follow each containing n characters defining the 
connectivity matrix of those islands. Character in column x of line y will be 
'1' if the islands with numbers x and y are connected and '0' otherwise. The 
next line is number p - the number of favorite bridges. The next p lines 
contain the pairs of islands that are connected by favorite bridges.
Output

For each test case print the number of days Johnny will be happy in this 
situation.

Constraints

1 <= t <= 5
2 <= n <= 30
1 <= p <= min(6, n-1)
Example

Input:
1
4
0111
1011
1101
1110
2
1 2
3 4

Output:
4

"""


'''
matrix of bridges will be kept in the following format:
cell format:
0 - no bridges here
1 - bridge is there
2 - favorite bridge
'''


def get_combinations(matrix, row, numberOfEnds):
    """Calculates number of combinations for the given matrix
    
    |matrix| - the matrix
    |row| - row to use, we are looking how many ways do we have to leave 1 or 2
        bridges at this row. Then we multiply number of ways by the value
        returned by get_combinations(matrix, row + 1, numberOfEnds),
        where numberOfEnds is incremented if we have 1 bridge here or is the 
        same if we have 2 bridges here.
    |numberOfEnds| - number of rows we already had with 1 bridge (it's the end
        island, obviously we can have 2 ends only)
    """
    
    numberOfFavorites = 0   # number of favorite bridges in this row
    numberOfBridges = 0     # total number of bridges in this row
    for p in matrix[row]:
        if p == 2:
            numberOfFavorites += 1
            
        if p:
            numberOfBridges += 1
    
    # This row doesn't allow to make a happy combination
    if numberOfFavorites > 2 or numberOfBridges == 0:
        return 0
    
    # Number of combinations with 1 bridge
    if numberOfFavorites == 0:
        oneBridgeCombinations = numberOfBridges
        twoBridgeCombinations = numberOfBridges*(numberOfBridges - 1)/2
    elif numberOfFavorites == 1:
        oneBridgeCombinations = 1
        twoBridgeCombinations = numberOfBridges - 1
    else:
        oneBridgeCombinations = 0
        twoBridgeCombinations = 1
        
    if numberOfEnds == 2:
        oneBridgeCombinations = 0

    print("%d: %d - %d\n" % (row, 
                             oneBridgeCombinations, 
                             twoBridgeCombinations))
    
    if row == len(matrix) - 1:
        return oneBridgeCombinations + twoBridgeCombinations
    else:
        return oneBridgeCombinations * \
                get_combinations(matrix, row + 1, numberOfEnds + 1) + \
            twoBridgeCombinations * \
                get_combinations(matrix, row + 1, numberOfEnds)

def read_data():
    '''Reads input from stdin and returns the matrix of bridges'''
    n = int(input())
    # read connectivity matrix
    
    matrix = []
    for i in range(n):
        string = input()
        row = []
        for s in string:
            row.append(int(s))
        matrix.append(row) 
    
    # read favorite bridges
    nFavorite = int(input())
    for i in range(nFavorite):
        row = input().split()
        matrix[int(row[0]) - 1][int(row[1]) - 1] = 2 #mark this cell as favorite

    return matrix

###############################################################################

T = int(input())

for t in range(T):
    matrix = read_data()
    
    print(get_combinations(matrix, 0, 0))
