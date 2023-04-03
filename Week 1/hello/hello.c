#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define TAM_MAX 80

char first[TAM_MAX], last[TAM_MAX];

int main (void)
{
    printf("What's your first name? ");
    scanf("%s", &first);
    printf("What's your last name? ");
    scanf("%s", &last);
    printf("Hello, %s %s! \n", first, last);
}