#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define CARD_MOD 10
#define MAX_LENGTH 9 
#define MIN_VALUE 10000
#define AMEX_NUM 37
#define MC_NUM 22
#define MC_MIN 51
#define MC_MAX 55
#define VS_MIN 40
#define VS_MAX 49
#define INVALID 0
#define AMEX 1
#define MASTERCARD 2
#define VISA 3

long long get_card(void);
int checksum_card(long long card);
int check_card(int mod, long long card);
void flush_buffer(void);

int main(void)
{
    // User input and validation
    long long card = get_card();
    int mod = checksum_card(card);
    int op = check_card(mod, card);

    // Print results
    switch (op)
    {
        case AMEX:
            printf("AMEX\n");
            break;

        case MASTERCARD:
            printf("MASTERCARD\n");
            break;

        case VISA:
            printf("VISA\n");
            break;
        
        default:
            printf("INVALID\n");
            break;
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

long long get_card(void)
{
    long long card; 
    do
    {
        printf("Number: ");
        scanf("%lld", &card);

        // Custom function to clear buffer without CS50's library
        flush_buffer(); 

    } while (card < MIN_VALUE);
    return card;
}

int checksum_card(long long card)
{
    int op = 0, mod = 0; 
    long long sum_a = 0, sum_b = 0, sum_temp_b = 0;
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        sum_a = sum_a + fmod((card/pow(CARD_MOD,i*2)), CARD_MOD);

        // Make modulo of first sum if needed.
        sum_temp_b = (int)(fmod((card/pow(CARD_MOD,(i*2)+1)), CARD_MOD));
        sum_temp_b *= 2;
        if (sum_temp_b >= CARD_MOD)
        {
            sum_temp_b = fmod(sum_temp_b,CARD_MOD) + sum_temp_b/CARD_MOD;
        }
        sum_b = sum_b + sum_temp_b;
    }
    return mod = (sum_a + sum_b) % CARD_MOD;
}

int check_card(int mod, long long card)
{
    int op = 0;
    if (mod == 0)
    {
        while (card >= 100) 
        {
            card /= 10;
        }

        if (card == AMEX_NUM)
        {
            return op = AMEX;
        }

        else if (card == MC_NUM || (MC_MIN <= card && card <= MC_MAX))
        {
            return op = MASTERCARD;
        }

        else if (VS_MIN <= card && card <= VS_MAX)
        {
            return op = VISA;
        }
        
        else
        {
            return op = INVALID;
        }   
    }
}
