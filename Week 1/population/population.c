#include <stdlib.h>
#include <stdio.h>

#define MIN_LLAMAS 9

int get_start(void);
int get_ending(int start_size);
void flush_buffer(void);

int main(void)
{
    int years = 0;
    int start_size = get_start();
    int end_size = get_ending(start_size);

    // Calculate and print data
    while(start_size < end_size)
    {
        start_size = start_size + (start_size/3) - (start_size/4);
        years++;
    }
    
    printf("Years: %d", years);
}

int get_start(void)
{
    int start_size;
    do
    {
        printf("Start size: ");
        scanf("%d", &start_size);

        // Custom function to clear buffer without CS50's library
        flush_buffer(); 

    } while (start_size < MIN_LLAMAS);
    return start_size;
}

int get_ending(int start_size)
{
    int end_size;
    do
    {
        printf("End size: ");
        scanf("%d", &end_size);

        // Custom function to clear buffer without CS50's library
        flush_buffer(); 

    } while (end_size < start_size);
    return end_size;
}

void flush_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    { 
        // Wait for buffer to clear
    }
}