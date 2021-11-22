#include <cs50.h>
#include <stdio.h>

int main()
{
    long long cardNumber;

// get a card number from the user
    do
    {
        printf("Your card number please: ");
        //scanf("%lld", &cardNumber);
        cardNumber = get_long_long();
    }
    while (cardNumber < 0);

//check the length of the card
    int counter = 0;
    long long cardnumber
    while (cardnumber > 0)
    {
        cardnumber = cardnumber / 10;
        counter++;
    }

    if (counter != 15 && counter != 16 && counter != 13)
    {
        printf("INVALID\n");
    }

// Array of card number
    cardnumber = cardnumber;
    int cardnumberArr[counter], cardnumberArrNeo[counter], i;
    for (i=0; i<counter; i++)
    {
        cardnumberArr[counter-i-1] = cardnumber % 10;
        cardnumberArr[counter-i-1] = cardnumberArr[counter-i-1];
        cardnumber = cardnumber / 10;
    }

    for (int i = 1; i < counter; i+=2)
    {
        cardnumberArr[i] = cardnumberArr[i] * 2;
    }

    int oddNumber = 0;
    int temp;

    for (int i = 0; i < counter; i++)
    {
        temp = (cardnumberArr[i] % 10) + (cardnumberArr[i]/10 % 10);
        oddNumber = oddNumber + temp;
    }

    if (oddNumber % 10 == 0)
    {
// Check the type of the card
        if ( ((cardNumberArr[0] == 3 && cardNumberArr[1] == 4) || (cardNumberArr[0] == 3 && cardNumberArr[1] == 7)) && counter == 15 )
        {
            printf("AMEX\n");
        }
        else if (cardNumberArr[0] == 5 && cardNumberArr[1] >= 1 && cardNumberArr[1] <= 5 && counter == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (cardNumberArr[0] == 4 && (counter == 13 || counter == 16 ))
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

    return 0;
}