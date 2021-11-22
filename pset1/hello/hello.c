// include libraries
#include <stdio.h>
#include <cs50.h>

// create main
int main(void)
{
    string  Name = get_string("What's your Name?\n");
    
    printf("hello, %s\n", Name);
}