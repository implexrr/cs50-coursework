#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate avg, set all RGB values to that avg
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create auxiliary array
    RGBTRIPLE aux[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    // Reflect image using auxiliary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            image[i][j] = aux[i][(width - 1) - j];
            image[i][(width - 1) - j] = aux[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create auxiliary array
    RGBTRIPLE aux[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    // Blue images using auxiliary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define target pixels in terms of direction relative the pixel that will be "blurred"
            int north = i - 1;
            int east = j + 1;
            int south = i + 1;
            int west = j - 1;
            int red_sum = aux[i][j].rgbtRed;
            int blue_sum = aux[i][j].rgbtBlue;
            int green_sum = aux[i][j].rgbtGreen;
            float count = 1;

            // If target pixels exist, include them in the average calculation
            if (north >= 0)
            {
                red_sum += aux[north][j].rgbtRed;
                green_sum += aux[north][j].rgbtGreen;
                blue_sum += aux[north][j].rgbtBlue;
                count++;

                if (west >= 0)
                {
                    red_sum += aux[north][west].rgbtRed;
                    green_sum += aux[north][west].rgbtGreen;
                    blue_sum += aux[north][west].rgbtBlue;
                    count++;
                }
                if (east <= width - 1)
                {
                    red_sum += aux[north][east].rgbtRed;
                    green_sum += aux[north][east].rgbtGreen;
                    blue_sum += aux[north][east].rgbtBlue;
                    count++;
                }
            }

            if (south <= height - 1)
            {
                red_sum += aux[south][j].rgbtRed;
                green_sum += aux[south][j].rgbtGreen;
                blue_sum += aux[south][j].rgbtBlue;
                count++;
                if (west >= 0)
                {
                    red_sum += aux[south][west].rgbtRed;
                    green_sum += aux[south][west].rgbtGreen;
                    blue_sum += aux[south][west].rgbtBlue;
                    count++;
                }
                if (east <= width - 1)
                {
                    red_sum += aux[south][east].rgbtRed;
                    green_sum += aux[south][east].rgbtGreen;
                    blue_sum += aux[south][east].rgbtBlue;
                    count++;
                }
            }

            // Necessary because of 1xn images
            if (west >= 0)
            {
                red_sum += aux[i][west].rgbtRed;
                green_sum += aux[i][west].rgbtGreen;
                blue_sum += aux[i][west].rgbtBlue;
                count++;
            }
            if (east <= width - 1)
            {
                red_sum += aux[i][east].rgbtRed;
                green_sum += aux[i][east].rgbtGreen;
                blue_sum += aux[i][east].rgbtBlue;
                count++;
            }
            // Calculate blur-average
            image[i][j].rgbtRed = round(red_sum / count);
            image[i][j].rgbtGreen = round(green_sum / count);
            image[i][j].rgbtBlue = round(blue_sum / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create auxiliary array
    RGBTRIPLE aux[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    // Create "edged" version of image using auxiliary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define target pixels in terms of direction relative the pixel that will be "edged"
            int north = i - 1;
            int east = j + 1;
            int south = i + 1;
            int west = j - 1;
            float gx_red, gx_green, gx_blue, gy_red, gy_green, gy_blue;
            gx_red = gx_green = gx_blue = gy_red = gy_green = gy_blue = 0;

            // If target pixels exist, include them in calculation of "edged" pixel via Sobel's
            if (north >= 0)
            {
                gy_red += -2 * aux[north][j].rgbtRed;
                gy_green += -2 * aux[north][j].rgbtGreen;
                gy_blue += -2 * aux[north][j].rgbtBlue;
                if (west >= 0)
                {
                    gx_red += -1 * aux[north][west].rgbtRed;
                    gx_green += -1 * aux[north][west].rgbtGreen;
                    gx_blue += -1 * aux[north][west].rgbtBlue;
                    gy_red += -1 * aux[north][west].rgbtRed;
                    gy_green += -1 * aux[north][west].rgbtGreen;
                    gy_blue += -1 * aux[north][west].rgbtBlue;
                }
                if (east <= width - 1)
                {
                    gx_red += 1 * aux[north][east].rgbtRed;
                    gx_green += 1 * aux[north][east].rgbtGreen;
                    gx_blue += 1 * aux[north][east].rgbtBlue;
                    gy_red += -1 * aux[north][east].rgbtRed;
                    gy_green += -1 * aux[north][east].rgbtGreen;
                    gy_blue += -1 * aux[north][east].rgbtBlue;
                }
            }

            if (south <= height - 1)
            {
                gy_red += 2 * aux[south][j].rgbtRed;
                gy_green += 2 * aux[south][j].rgbtGreen;
                gy_blue += 2 * aux[south][j].rgbtBlue;
                if (west >= 0)
                {
                    gx_red += -1 * aux[south][west].rgbtRed;
                    gx_green += -1 * aux[south][west].rgbtGreen;
                    gx_blue += -1 * aux[south][west].rgbtBlue;
                    gy_red += 1 * aux[south][west].rgbtRed;
                    gy_green += 1 * aux[south][west].rgbtGreen;
                    gy_blue += 1 * aux[south][west].rgbtBlue;
                }
                if (east <= width - 1)
                {
                    gx_red += 1 * aux[south][east].rgbtRed;
                    gx_green += 1 * aux[south][east].rgbtGreen;
                    gx_blue += 1 * aux[south][east].rgbtBlue;
                    gy_red += 1 * aux[south][east].rgbtRed;
                    gy_green += 1 * aux[south][east].rgbtGreen;
                    gy_blue += 1 * aux[south][east].rgbtBlue;
                }
            }

            // Necessary because of 1xn images
            if (west >= 0)
            {
                gx_red += -2 * aux[i][west].rgbtRed;
                gx_green += -2 * aux[i][west].rgbtGreen;
                gx_blue += -2 * aux[i][west].rgbtBlue;
            }
            if (east <= width - 1)
            {
                gx_red += 2 * aux[i][east].rgbtRed;
                gx_green += 2 * aux[i][east].rgbtGreen;
                gx_blue += 2 * aux[i][east].rgbtBlue;
            }

            // Finish "edged" pixel calculation via Sobel's operator
            float temp_red = sqrt((gx_red * gx_red) + (gy_red * gy_red));
            float temp_green = sqrt((gx_green * gx_green) + (gy_green * gy_green));
            float temp_blue = sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue));

            // Put cap of 255 on new pixel value
            if (temp_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int)(round(temp_red));
            }
            if (temp_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (int)(round(temp_green));
            }
            if (temp_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (int)(round(temp_blue));
            }
        }
    }

    return;
}
