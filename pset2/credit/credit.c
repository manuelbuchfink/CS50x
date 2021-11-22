#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    //user input
    string number = get_string("Number: ");
    
    //converting string to longlong for checksum
    char value[strlen(number)];
    char *eptr;
    
    long long cardnumber;
    strcpy(value, number);
    
    cardnumber = strtoll(value, &eptr, 10);

// check sum
    int counter = 0;

    while (cardnumber > 0)
    {
        cardnumber = cardnumber / 10;
        counter++;
    }

// Array of card number
    
    int cardnumberArr[counter];
    for (int i = 0; i < counter; i++)
    {
        cardnumberArr[counter - i - 1] = cardnumber % 10;
        cardnumber = cardnumber / 10;
    }
// multiplying every other number
    for (int i = 1; i < counter; i += 2)
    {
        cardnumberArr[i] = cardnumberArr[i] * 2;
    }

    int oddNumber = 0;
    int temp;

    for (int i = 0; i < counter; i++)
    {
        temp = (cardnumberArr[i] % 10) + (cardnumberArr[i] / 10 % 10);
        oddNumber = oddNumber + temp;
    }
    // if checksum is ok continue
    if (oddNumber % 10 == 0)
    {
        //comparing Cardnumbers as string  with ascii value of numbers
        if (strlen(number) == 15)
        {
            if (number[0] == 51)
            {
                if (number[1] == 52 || number[1] == 55)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        //checking fo Master Card
        else if (strlen(number) == 16 && number[0] == 53)
        {
            if (number[1] < 54 && number[1] > 48)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }   
        //checking for VISA
        else if (strlen(number) == 13 || strlen(number) == 16)
        {
            if (number[0] == 52 && number[strlen(number) - 1] != 51)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }    
        else
        {
            printf("INVALID\n");
        }
    }
}