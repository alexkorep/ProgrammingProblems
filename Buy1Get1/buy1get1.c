#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 202
int main(void) {
    int t = 0;
    char c = 0;
    char s[MAX_STR_LEN + 1] = {0};
    char* pos = 0;
    char counts['z' - 'A' + 1] = {0};
    int result = 0;

    scanf("%d",&t);

    while (t--) {
        scanf("%s",&s, MAX_STR_LEN);

        memset(counts, 0, sizeof(counts));

        pos = s;
        while (*pos) {
            ++counts[*pos - 'A'];
            ++pos;
        }

        result = 0;
        for (c = 'A'; c <= 'z'; ++c) {
            result += (counts[c - 'A'] + 1)/2;
        }

        printf("%d\n", result);
    }
    return 0;
}
