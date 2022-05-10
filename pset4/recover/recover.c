#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{

// Check to see if user put in correct number of CLI
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open forensic image
    FILE *raw_file = fopen(argv[1], "r");

    // Check that forensic image isn't some garbage file
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create buffer with the same size of a "FAT" block within a standard JPEG image.
    BYTE buffer[BLOCK_SIZE];

    // Create buffer for filename of form ###.jpg
    char filename[4];

    int jpeg_count = 0;

    // Iterate through forensic image until fread reaches EOF
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // If first 4 bytes of block indicate start of JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Rename filename to corresponding JPEG counter (###.jpg)
            sprintf(filename, "%03i.jpg", jpeg_count);

            // Open JPEG
            FILE *img = fopen(filename, "w");

            // Write buffer into JPEG
            fwrite(buffer, sizeof(buffer), 1, img);

            // Close pointer to header block
            fclose(img);
            jpeg_count ++;
        }

        // If block is the start of a jpeg
        else
        {
            // Either this is before the first jpeg (in which case do nothing) or its after (in which case, create a pointer and continue writing to current jpeg)
            if (jpeg_count > 0)
            {
                FILE *img2 = fopen(filename, "a");
                fwrite(buffer, sizeof(buffer), 1, img2);
                fclose(img2);
            }
        }
    }

    // Close forensic image
    fclose(raw_file);
}