#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // calculating average RGB value
            average = round((image[j][i].rgbtRed + image[j][i].rgbtGreen + image[j][i].rgbtBlue) / 3.0);

            //applying RGB average to each color
            image[j][i].rgbtRed = average;
            image[j][i].rgbtGreen = average;
            image[j][i].rgbtBlue = average;
        }
    }
}
//declaring function that keeps RGB in the Boundarys
int bound(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    else if (RGB < 0)
    {
        RGB = 0;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating sepia values
            int sepiaRed = bound(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));

            int sepiaGreen = bound(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));

            int sepiaBlue = bound(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));

            //applying sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //getting a temp storage or "empty glass"
    int tmp[3];
    for (int j = 0; j < width / 2; j++)
    {
        //looping ober half of the width
        for (int i = 0; i < height; i++)
        {
            //assigning the left half of the pic to the empty glass
            tmp[0] = image[i][j].rgbtRed;
            tmp[1] = image[i][j].rgbtGreen;
            tmp[2] = image[i][j].rgbtBlue;

            //assigning the right half to the left
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            //assigning the left half which was stored on the empty glass to the right half
            image[i][width - j - 1].rgbtRed = tmp[0];
            image[i][width - j - 1].rgbtGreen = tmp[1];
            image[i][width - j - 1].rgbtBlue = tmp[2];
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float counter;
    int sumRed;
    int sumGreen;
    int sumBlue;
    RGBTRIPLE temp[height][width];

    //looping over every pixel
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            //"re-"setting the values to 0 !!Improtant!!
            counter = 0;
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;

            //looping over every adjacent pixel
            for (int a = -1; a < 2; a++)
            {
                //checking if out of bounds
                if (i + a  < 0 || i + a >= height)
                {
                    continue;
                }
                for (int b = -1; b < 2; b++)
                {
                    if (j + b < 0 || j + b >= width)
                    {
                        continue;
                    }

                    //summing up all values of adjacent pixels
                    sumRed += image[i + a][j + b].rgbtRed;
                    sumGreen += image[i + a][j + b].rgbtGreen;
                    sumBlue += image[i + a][j + b].rgbtBlue;

                    //++ing counter for average calculation
                    counter++;
                }
            }

            //assigning the new values to "empty glass"
            tmp[i][j].rgbtRed = round(sumRed / counter * 1.0);
            tmp[i][j].rgbtGreen = round(sumGreen / counter * 1.0);
            tmp[i][j].rgbtBlue = round(sumBlue / counter * 1.0);
        }
    }
    //swapping normal with blurred pixels out of the "empty glass"
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}