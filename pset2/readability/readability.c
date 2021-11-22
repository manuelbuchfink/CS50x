#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

int main(void)
{
    //get Text from user
    string s = get_string("Text: ");
    //counting letters l
    float l = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            l++;
        }
    }
    //counting words w
    float w = 1;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 32)
        {
            w++;

        }

    }
    //counting Sentences
    float Sentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            Sentences++;
        }
    }
    //computing L and S for the Grading formula
    float L = (l / w * 100);
    float S = (Sentences / w * 100);
    float Grade = 0.0588 * L - 0.296 * S - 15.8;
    //Printing different outputs depending on the Grade
    if (Grade < 0)
    {
        printf("Before Grade 1\n");

    }
    else if (Grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(Grade));
    }
}