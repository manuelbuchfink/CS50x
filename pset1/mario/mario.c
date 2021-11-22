// include libraries
#include <stdio.h>
#include <cs50.h>

// create main
int main(void)
{  
    int n;
    do
  
    {    
        //get user input
        n = get_int("Height\n");
    }
    // only accept user input 1 to 8
    while (n > 8 || n < 1);
    // print n times \n
    for (int i = 0; i < n; i++)
    {
        //print right alligned pyramid
        for (int j = n - 1 ; j > i; j--)
        {
            printf(" ");
        }
        for (int h = - 1; h < i; h++)
        {
            printf("#");
        }
        // seperate pyramid
        printf("  ");
        //print left alligned pyramid
        for (int l = - 1; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
                
              
                
                
}

