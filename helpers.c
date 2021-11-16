#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen) / 3.0);
            //take average of the color values to convert them to grayscale
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        int k = width - 1;

        for (int j = 0; j < round((width / 2)); j++)
        {   
            //swap pixels that are at right side of the image with left pixels
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;

            k--;
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int divider = 0;
    int dividend_red = 0;
    int dividend_blue = 0;
    int dividend_green = 0;
    //define an empty array to use it for the calculation
    RGBTRIPLE filtered[height][width];


    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            divider = 0;
            dividend_red = 0;
            dividend_blue = 0;
            dividend_green = 0;
            //form a 3x3 array and sum their color values
            for (int k = i - 1; k < i + 2; k++)
            {
                if (k >= 0 && k < height)
                {
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        if (l >= 0 && l < width)
                        {
                            //cumulate each color value on dividend and keep a counter for divider   
	                        dividend_red += image[k][l].rgbtRed;
                            dividend_blue += image[k][l].rgbtBlue;
                            dividend_green += image[k][l].rgbtGreen;
                            divider++;
                        }
                    }
                }

            }

            //find the average of the 3x3 array and assign this value to each relates pixel color
            filtered[i][j].rgbtRed = round((float)dividend_red / divider);
            filtered[i][j].rgbtBlue = round((float)dividend_blue / divider);
            filtered[i][j].rgbtGreen = round((float)dividend_green / divider);

        }
    }

    //change the original pixels with the blurred ones
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtRed = filtered[i][j].rgbtRed;
            image[i][j].rgbtBlue = filtered[i][j].rgbtBlue;
            image[i][j].rgbtGreen = filtered[i][j].rgbtGreen;

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //defining Gx and Gy arrays
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    //define a empty array to use it for calculation later
    RGBTRIPLE filter[height][width];

    int finalRed = 0;
    int finalBlue = 0;
    int finalGreen = 0;
    
    int m = 0;
    int n = 0;

    int xred = 0;
    int xblue = 0;
    int xgreen = 0;
    int yred = 0;
    int yblue = 0;
    int ygreen = 0;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            //reset all variables here to calculate them for the new pixel
            finalRed = 0;
            finalBlue = 0;
            finalGreen = 0;

            xred = 0;
            xblue = 0;
            xgreen = 0;
            yred = 0;
            yblue = 0;
            ygreen = 0;
            m = 0;
            n = 0;
            //calculate Gx and Gy values according to the pixel location
            for (int k = i - 1; k < i + 2; k++)
            {
                if (k >= 0 && k < height)
                {

                    for (int l = j - 1; l < j + 2; l++)
                    {
                        if (l >= 0 && l < width)
                        {
                            //if the pixel is at left corner
                            if (i == 0 && j == 0)
                            {
                                if (n > 2 || n == 0)
                                {
                                    m++;
                                    n = 1;
                                }

                                if (m > 2 || m == 0)
                                {
                                    m = 1;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;

                            }
                            //if the pixel is at bottom left corner
                            else if (j == 0 && i == height - 1)
                            {
                                if (n == 0)
                                {
                                    n = 1;
                                }
                                if (n > 2)
                                {
                                    n = 1;
                                    m++;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }
                            //if the pixel is at bottom right corner
                            else if (i == height - 1 && j == width - 1)
                            {

                                if (n > 1)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m > 1)
                                {
                                    m = 0;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }
                            //if the pixel is at top right corner
                            else if (i == 0 && j == width - 1)
                            {
                                if (m == 0)
                                {
                                    m = 1;
                                }

                                if (n > 1)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m > 2)
                                {
                                    m = 1;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;


                            }

                            //right edge
                            else if (j == width - 1)
                            {

                                if (n > 1)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m > 2)
                                {
                                    m = 0;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }

                            //left edge

                            else if (j == 0)
                            {
                                if (n == 0)
                                {
                                    n = 1;
                                }

                                if (n > 2)
                                {
                                    m++;
                                    n = 1;
                                }

                                if (m > 2)
                                {
                                    m = 0;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }

                            //bottom edge
                            else if (i == height - 1)
                            {
                                if (n > 2)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m > 1)
                                {
                                    m = 0;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }

                            //top edge
                            else if (i == 0)
                            {
                                if (n > 2)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m == 0 || m > 2)
                                {
                                    m = 1;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];

                                n++;
                            }
                            //middle pixels
                            else
                            {
                                if (n > 2)
                                {
                                    m++;
                                    n = 0;
                                }

                                if (m > 2)
                                {
                                    m = 0;
                                }
                                //calculate Gx and Gy values for each color
                                xred += image[k][l].rgbtRed * Gx[m][n];
                                xblue += image[k][l].rgbtBlue * Gx[m][n];
                                xgreen += image[k][l].rgbtGreen * Gx[m][n];

                                yred += image[k][l].rgbtRed * Gy[m][n];
                                yblue += image[k][l].rgbtBlue * Gy[m][n];
                                ygreen += image[k][l].rgbtGreen * Gy[m][n];
                                n++;
                            }
                        }
                    }
                }
            }
            //apply the Sobel filter algorithm
            finalRed = (int) round(sqrt((xred * xred) + (yred * yred)));
            finalBlue = (int) round(sqrt((xblue * xblue) + (yblue * yblue)));
            finalGreen = (int) round(sqrt((xgreen * xgreen) + (ygreen * ygreen)));
            //capp the value at 255
            if (finalRed > 255)
            {
                finalRed = 255;
            }

            if (finalBlue > 255)
            {
                finalBlue = 255;
            }

            if (finalGreen > 255)
            {
                finalGreen = 255;
            }
            //assign the capped value to the related pixel
            filter[i][j].rgbtRed = finalRed;
            filter[i][j].rgbtBlue = finalBlue;
            filter[i][j].rgbtGreen = finalGreen;

        }
    }

    //change original pixels with the edge filtered ones
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            image[i][j] = filter[i][j];
        }
    }

    return;
}
