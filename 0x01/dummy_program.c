#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int varInt = 123456;
    char varString[] = "DefaultString";
    char arrChar[128] = "Long char array right there ->";
    int *ptr2int = &varInt;
    int **ptr2ptr = &ptr2int;
    int ***ptr2ptr2ptr = &ptr2ptr;

    size_t i = 1;
    char entry = 0;
    while ((entry != 'q') && (entry != 'Q')) {
        printf("Refreshed %ld times\nProcess ID: %d\n\n",i, getpid());
        printf("varInt\t\t(%p) = %d\n", &varInt, varInt);
        printf("varString\t(%p) = %s\n", &varString, varString);
        printf("arrChar[128]\t(%p) = %s\n", &arrChar, arrChar);
        printf("\n\n");
        printf("ptr2int\t\t(%p) = %p\n", &ptr2int, ptr2int);
        printf("ptr2ptr\t\t(%p) = %p\n", &ptr2ptr, ptr2ptr);
        printf("ptr2ptr2ptr\t(%p) = %p\n", &ptr2ptr2ptr, ptr2ptr2ptr);
        printf("\n\nPress RETURN to print again, enter q or Q to quit\n");
        i++;
        entry = getchar();
    }
    return 0;
}
