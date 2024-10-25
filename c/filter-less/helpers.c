#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            float avg = (image[i][a].rgbtRed + image[i][a].rgbtGreen + image[i][a].rgbtBlue) / 3.00;
            int ave = round(avg);
            image[i][a].rgbtRed = ave;
            image[i][a].rgbtGreen = ave;
            image[i][a].rgbtBlue = ave;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {

            float sepiaRed = 0.393 * image[i][a].rgbtRed + 0.769 * image[i][a].rgbtGreen + 0.189 * image[i][a].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][a].rgbtRed + 0.686 * image[i][a].rgbtGreen + 0.168 * image[i][a].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][a].rgbtRed + 0.534 * image[i][a].rgbtGreen + 0.131 * image[i][a].rgbtBlue;
            int red = round(sepiaRed);
            if (red > 255)
            {
                red = 255;
            }
            int green = round(sepiaGreen);
            if (green > 255)
            {
                green = 255;
            }
            int blue = round(sepiaBlue);
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][a].rgbtRed = red;
            image[i][a].rgbtGreen = green;
            image[i][a].rgbtBlue = blue;


        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < (width / 2); a++)
        {
            int red = image[i][a].rgbtRed;
            int green = image[i][a].rgbtGreen;
            int blue = image[i][a].rgbtBlue;
            image[i][a].rgbtRed = image[i][width - a - 1].rgbtRed;
            image[i][a].rgbtGreen =  image[i][width - a - 1].rgbtGreen;
            image[i][a].rgbtBlue = image[i][width - a - 1].rgbtBlue;

            image[i][width - a - 1].rgbtRed = red;
            image[i][width - a - 1].rgbtGreen = green;
            image[i][width - a - 1].rgbtBlue = blue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of original image
    int h = height;
    int w = width;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            temp[i][a] = image[i][a];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            // blur middle pixels
            if (i > 0 && a > 0 && i < h - 1 && a < w - 1)
            {
                float red = (temp[i][a].rgbtRed + temp[i - 1][a - 1].rgbtRed + temp[i - 1][a].rgbtRed + temp[i - 1][a + 1].rgbtRed + temp[i][a - 1].rgbtRed + temp[i][a + 1].rgbtRed + temp[i + 1][a - 1].rgbtRed + temp[i + 1][a].rgbtRed + temp[i + 1][a + 1].rgbtRed)/9.00;
                float green = (temp[i][a].rgbtGreen + temp[i - 1][a - 1].rgbtGreen + temp[i - 1][a].rgbtGreen + temp[i - 1][a + 1].rgbtGreen + temp[i][a - 1].rgbtGreen + temp[i][a + 1].rgbtGreen + temp[i + 1][a - 1].rgbtGreen + temp[i + 1][a].rgbtGreen + temp[i + 1][a + 1].rgbtGreen)/9.00;
                float blue = (temp[i][a].rgbtBlue + temp[i - 1][a - 1].rgbtBlue + temp[i - 1][a].rgbtBlue + temp[i - 1][a + 1].rgbtBlue + temp[i][a - 1].rgbtBlue + temp[i][a + 1].rgbtBlue + temp[i + 1][a - 1].rgbtBlue + temp[i + 1][a].rgbtBlue + temp[i + 1][a + 1].rgbtBlue)/9.00;

                int avgr = round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;
            }
            // blur edges
            else if (i == 0 && a != 0)
            {
                float red = (temp[i][a].rgbtRed + temp[i][a - 1].rgbtRed + temp[i][a + 1].rgbtRed + temp[i + 1][a - 1].rgbtRed + temp[i + 1][a + 1].rgbtRed + temp[i + 1][a].rgbtRed) / 6.00;
                float green = (temp[i][a].rgbtGreen + temp[i][a - 1].rgbtGreen + temp[i][a + 1].rgbtGreen + temp[i + 1][a - 1].rgbtGreen + temp[i + 1][a + 1].rgbtGreen + temp[i + 1][a].rgbtGreen) / 6.00;
                float blue = (temp[i][a].rgbtBlue + temp[i][a - 1].rgbtBlue + temp[i][a + 1].rgbtBlue + temp[i + 1][a - 1].rgbtBlue + temp[i + 1][a + 1].rgbtBlue + temp[i + 1][a].rgbtBlue) / 6.00;
                int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;

            }
            else if (i == (height - 1) && a != 0)
            {
                float red = (temp[i][a].rgbtRed + temp[i][a - 1].rgbtRed + temp[i][a + 1].rgbtRed + temp[i - 1][a - 1].rgbtRed + temp[i - 1][a + 1].rgbtRed + temp[i - 1][a].rgbtRed)/6.00;
                float green = (temp[i][a].rgbtGreen + temp[i][a - 1].rgbtGreen + temp[i][a + 1].rgbtGreen + temp[i - 1][a - 1].rgbtGreen + temp[i - 1][a + 1].rgbtGreen + temp[i - 1][a].rgbtGreen)/6.00;
                float blue = (temp[i][a].rgbtBlue + temp[i][a - 1].rgbtBlue + temp[i][a + 1].rgbtBlue + temp[i - 1][a - 1].rgbtBlue + temp[i - 1][a + 1].rgbtBlue + temp[i - 1][a].rgbtBlue)/6.00;
                int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;

            }
             else if (i != 0 && a == (width - 1))
            {
                float red = (temp[i][a].rgbtRed + temp[i - 1][a].rgbtRed + temp[i + 1][a].rgbtRed + temp[i - 1][a - 1].rgbtRed + temp[i + 1][a - 1].rgbtRed + temp[i][a - 1].rgbtRed)/6.00;
                float green = (temp[i][a].rgbtGreen + temp[i - 1][a].rgbtGreen + temp[i + 1][a].rgbtGreen + temp[i - 1][a - 1].rgbtGreen + temp[i + 1][a - 1].rgbtGreen + temp[i][a - 1].rgbtGreen)/6.00;
                float blue = (temp[i][a].rgbtBlue + temp[i - 1][a].rgbtBlue + temp[i + 1][a].rgbtBlue + temp[i - 1][a - 1].rgbtBlue + temp[i + 1][a - 1].rgbtBlue + temp[i][a - 1].rgbtBlue)/6.00;
                int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;

            }
            else if (i != 0 && a == 0)
            {
                float red = (temp[i][a].rgbtRed + temp[i - 1][a].rgbtRed + temp[i + 1][a].rgbtRed + temp[i - 1][a + 1].rgbtRed + temp[i + 1][a + 1].rgbtRed + temp[i][a + 1].rgbtRed)/6.00;
                float green = (temp[i][a].rgbtGreen + temp[i - 1][a].rgbtGreen + temp[i + 1][a].rgbtGreen + temp[i - 1][a + 1].rgbtGreen + temp[i + 1][a + 1].rgbtGreen + temp[i][a + 1].rgbtGreen)/6.00;
                float blue = (temp[i][a].rgbtBlue + temp[i - 1][a].rgbtBlue + temp[i + 1][a].rgbtBlue + temp[i - 1][a + 1].rgbtBlue + temp[i + 1][a + 1].rgbtBlue + temp[i][a + 1].rgbtBlue)/6.00;
                int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;

            }
            // blur corner
             if (i == 0 && a == 0)
            {
                float red = (temp[i][a].rgbtRed + temp[i + 1][a].rgbtRed + temp[i][a + 1].rgbtRed + temp[i + 1][a + 1].rgbtRed) / 4.00;
                float green = (temp[i][a].rgbtGreen + temp[i + 1][a].rgbtGreen + temp[i][a + 1].rgbtGreen + temp[i + 1][a + 1].rgbtGreen) / 4.00;
                float blue = (temp[i][a].rgbtBlue + temp[i + 1][a].rgbtBlue + temp[i][a + 1].rgbtBlue + temp[i + 1][a + 1].rgbtBlue) / 4.00;
               int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;
            }
            else if (i == (height - 1) && a == 0)
            {
                float red = (temp[i][a].rgbtRed + temp[i - 1][a].rgbtRed + temp[i][a + 1].rgbtRed + temp[i - 1][a + 1].rgbtRed) / 4.00;
                float green = (temp[i][a].rgbtGreen + temp[i - 1][a].rgbtGreen + temp[i][a + 1].rgbtGreen + temp[i - 1][a + 1].rgbtGreen) / 4.00;
                float blue = (temp[i][a].rgbtBlue + temp[i - 1][a].rgbtBlue + temp[i][a + 1].rgbtBlue + temp[i - 1][a + 1].rgbtBlue) / 4.00;
              int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;
            }
             else if (i == (height - 1) && a == (width - 1))
            {
                float red = (temp[i][a].rgbtRed + temp[i - 1][a].rgbtRed + temp[i][a - 1].rgbtRed + temp[i - 1][a - 1].rgbtRed) / 4.00;
                float green = (temp[i][a].rgbtGreen + temp[i - 1][a].rgbtGreen + temp[i][a - 1].rgbtGreen + temp[i - 1][a - 1].rgbtGreen) / 4.00;
                float blue = (temp[i][a].rgbtBlue + temp[i - 1][a].rgbtBlue + temp[i][a - 1].rgbtBlue + temp[i - 1][a - 1].rgbtBlue) / 4.00;
              int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;
            }
            else if (i == 0 && a == (width - 1))
            {
                float red = (temp[i][a].rgbtRed + temp[i + 1][a].rgbtRed + temp[i][a - 1].rgbtRed + temp[i + 1][a - 1].rgbtRed) / 4.00;
                float green = (temp[i][a].rgbtGreen + temp[i + 1][a].rgbtGreen + temp[i][a - 1].rgbtGreen + temp[i + 1][a - 1].rgbtGreen) / 4.00;
                float blue = (temp[i][a].rgbtBlue + temp[i + 1][a].rgbtBlue + temp[i][a - 1].rgbtBlue + temp[i + 1][a - 1].rgbtBlue) / 4.00;
                int avgr =round(red);
                int avgg = round(green);
                int avgb = round(blue);
                image[i][a].rgbtRed = avgr;
                image[i][a].rgbtGreen = avgg;
                image[i][a].rgbtBlue = avgb;
            }

        }
    }
    return;
}

