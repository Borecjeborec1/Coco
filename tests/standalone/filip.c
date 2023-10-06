#include <stdio.h>
int main()
{
    char name[21]; // 20 chars plus the null-terminator
    printf("What's your name? ");
    scanf_s("%20s", name);
    printf("%s", name);
    return 0;
}