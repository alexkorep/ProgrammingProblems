#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STEPS 1000000
#define MODULO 1000000007
int ones[MAX_STEPS + 1] = {0};

int f1 = 1;
int f2 = 0;
int oldLimit = 1;

int calcOnes(int val) {
    int result = 0;
    while (val) {
        if (val & 0x1) {
            ++result;
        }
        val = val >> 1;
    }
    return result;
}

void buildFs(int limit) {
    int f1new = 0;
    int f2new = 0;
    int i;

    if (oldLimit >= limit) {
        return;
    }

    for (i = oldLimit + 1; i <= limit; ++i) {
        f1new = f1+f2;
        f2new = f1;
        f1 = f1new % MODULO;
        f2 = f2new % MODULO;
        
        ones[i] = calcOnes((f1 + f2) % MODULO);
    }
    oldLimit = limit;
}


int main() {
    int t = 0;
    int a = 0;
    int b = 0;
    ones[1] = 1;

    //buildFs(MAX_STEPS);

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &a, &b);
        buildFs(a);
        printf(ones[a] == b ? "CORRECT\n" : "INCORRECT\n");
    }

    return 0;
}
