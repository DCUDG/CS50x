#include <stdlib.h>
#include <stdio.h>

#define MIN_SIZE 0
#define MAX_SIZE 9

int get_size(void);
void print_size(int size);
void print_spaces(int i);
void print_hashes(int i);
void flush_buffer(void);

int main(void)
{
    int c = get_size();
    print_size(c);
}

int get_size(void)
{
    float size;
    int size_int;
    do
    {
        printf("Height: ");
        scanf("%f", &size);

        // Custom function to clear buffer without CS50's library
        flush_buffer();

        size_int = size;
    } while (size < MIN_SIZE || size > MAX_SIZE || size != size_int);
    return size_int;
}

void print_size(int size)
{
    for (int i = 0; i < size; i++)
    {
        print_spaces(size - i);
        print_hashes(i);
        printf("  ");
        print_hashes(i);
        printf("\n");
    }
}

void flush_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Wait for buffer to clear
    }
}

void print_spaces(int i)
{
    for (int j = 0; j < i; j++)
    {
        printf(" ");
    }
}

void print_hashes(int i)
{
    for (int j = 0; j < i; j++)
    {
        printf("#");
    }
}