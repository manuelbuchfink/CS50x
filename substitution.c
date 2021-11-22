#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

//prompting user for command line input
int main(int argc, string argv[])
{
    //Only allowing two command line arguments
    if (argc > 2)
    {
        printf("Only a single key allowed.\n");
        return 1;
    }
    else if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Only allowing a key of len 26
    int str_len  = strlen(argv[1]);
    if (str_len != 26)
    {
        printf("Key has to be 26 characters long.\n");
        return 1;
    }
    //checking if key only contains abc chars
    int sum = 0;
    for (int i = 0; i < str_len; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key has to only contain Alphabetical characters.\n");
            return 1;
        }
        // summing up all chars in the key
        sum += toupper(argv[1][i]);
    }
    // comparing the sum to the total value of ABC chars summed up
    if (sum != 2015)
    {
        printf("Key has to only contain each letter once.\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        int x = 0;
        char encrypt[x];
        printf("ciphertext: ");
        for (int i = 0, size = strlen(plaintext); i < size; i++)
        {
            x++;
            //creating an Index starting with A from 0
            if (isupper(plaintext[i]))
            {
                //assigning the key from command line to the encrypt array
                encrypt[i] = toupper(argv[1][plaintext[i] - 65]);
            }
            else if (islower(plaintext[i]))
            {
                encrypt[i] = tolower(argv[1][plaintext[i] - 97]);
            }
            else
            {
                //leaving non alphabetical characters unaffected
                encrypt[i] = plaintext[i];
            }
            printf("%c", encrypt[i]);
        }
        printf("\n");
        return 0;
    }
}