#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    char *input = argv[1];
    FILE *card = fopen(input, "r");
    FILE *new_file = NULL;
    BYTE buffer[512];
    int counter = 0;

    // ###.jpeg
    char name[8];

    // only 1 argc
    if (argc < 2 || argc > 2)
    {
        printf("usage ./recover image\n");
        return 1;
    }

    if (card == NULL)
    {
        fprintf(card, "Cannot open file %s", input);
        return 2;
    }

    while (true)
    {
        //break if end of card
        if (feof(card))
        {
            break;
        }

        //true while start of jpeg file
        bool header = buffer[0] == 0xff && buffer[1] == 0xd8 &&
                      buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        //image counter++; closing previous jpeg
        if (header && new_file !=  NULL)
        {
            fclose(new_file);
            counter++;
        }
        //opening new jpeg
        if (header)
        {
            sprintf(name, "%03i.jpg", counter);
            new_file = fopen(name, "w");
        }
        // copying into new jpeg from buffer
        if (new_file != NULL)
        {
            //reading into buffer
            int read = fread(buffer, sizeof(BYTE), 512, card);
            fwrite(buffer, sizeof(BYTE), read, new_file);
        }
    }
}


