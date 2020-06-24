#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "ppmFile.h"

void vertPass ( Image *img, Image *out, float Avg, int radius )
{
    # pragma omp parallel
    # pragma omp for
    for ( int j = 0; j < ImageHeight( img ); j++ )
    {
        float hSum[] = {0.0, 0.0, 0.0};
        float iAvg[] = {0.0, 0.0, 0.0};

        for ( int x = 0; x < radius; x++ )
        {
            hSum[0] += ImageGetPixel( img, x, j, 0); // Red
            hSum[1] += ImageGetPixel( img, x, j, 1); // Green
            hSum[2] += ImageGetPixel( img, x, j, 2); // Blue
        }
        iAvg[0] = hSum[0] * Avg;
        iAvg[1] = hSum[1] * Avg;
        iAvg[2] = hSum[2] * Avg;
        for ( int i = 0; i < ImageWidth(img); i++ )
        {
            if (i - radius / 2 >= 0 && ( i + 1 + radius / 2 ) < ImageWidth(img))
            {
                hSum[0] -= ImageGetPixel( img, i - radius / 2, j, 0 ); // Red
                hSum[1] -= ImageGetPixel( img, i - radius / 2, j, 1 ); // Green
                hSum[2] -= ImageGetPixel( img, i - radius / 2, j, 2 ); // Blue

                hSum[0] += ImageGetPixel( img, i + 1 + radius / 2, j, 0 ); // Red
                hSum[1] += ImageGetPixel( img, i + 1 + radius / 2, j, 1 ); // Green
                hSum[2] += ImageGetPixel( img, i + 1 + radius / 2, j, 2 ); // Blue

                iAvg[0] = hSum[0] * Avg;
                iAvg[1] = hSum[1] * Avg;
                iAvg[2] = hSum[2] * Avg;
            }
            ImageSetPixel( out, i, j, 0, (int) iAvg[0] ); // Red
            ImageSetPixel( out, i, j, 1, (int) iAvg[1] ); // Green
            ImageSetPixel( out, i, j, 2, (int) iAvg[2] ); // Blue
        }
    }
}
void horPass ( Image *img, Image *out, float Avg, int radius )
{
    # pragma omp parallel
    # pragma omp for
    for ( int i = 0; i < ImageWidth( img ); i++ )
    {
        float tSum[] = { 0.0, 0.0, 0.0 };
        float iAvg[] = { 0.0, 0.0, 0.0 };
        for ( int y = 0; y < radius; y++ )
        {
            tSum[0] += ImageGetPixel( img, i, y, 0); // Red
            tSum[1] += ImageGetPixel( img, i, y, 1); // Green
            tSum[2] += ImageGetPixel( img, i, y, 2); // Blue
        }
        iAvg[0] = tSum[0] * Avg;
        iAvg[1] = tSum[1] * Avg;
        iAvg[2] = tSum[2] * Avg;
        for ( int j = 0; j < ImageHeight( img ); j++ )
        {
            if (j - radius / 2 >= 0 && j + 1 + radius / 2 < ImageHeight( img ))
            {
                tSum[0] -= ImageGetPixel( img, i , j - radius / 2, 0 ); // Red
                tSum[1] -= ImageGetPixel( img, i , j - radius / 2, 1 ); // Green
                tSum[2] -= ImageGetPixel( img, i , j - radius / 2, 2 ); // Blue

                tSum[0] += ImageGetPixel( img, i, j + 1 + radius / 2, 0 ); // Red
                tSum[1] += ImageGetPixel( img, i, j + 1 + radius / 2, 1 ); // Green
                tSum[2] += ImageGetPixel( img, i, j + 1 + radius / 2, 2 ); // Blue

                iAvg[0] = tSum[0] * Avg;
                iAvg[1] = tSum[1] * Avg;
                iAvg[2] = tSum[2] * Avg;
            }
            ImageSetPixel( out, i, j, 0, (int) iAvg[0] ); // Red
            ImageSetPixel( out, i, j, 1, (int) iAvg[1] ); // Green
            ImageSetPixel( out, i, j, 2, (int) iAvg[2] ); // Blue
        }
    }
}

int main ( int argc, char *argv[] )
{
    if ( argc != 4 )
        printf ( "Usage is ./hw4 r <inputfile>.ppm <outputfile>.ppm\n" );

    Image *img, *pass1, *pass2;
    img = ImageRead( argv[2] );

    int radius = atoi( argv[1] );
    if ( radius % 2 == 0 ) radius++;

    float Avg = (float)1/radius;
    pass1 = ImageCreate( ImageWidth(img), ImageHeight(img) );
    pass2 = ImageCreate( ImageWidth(img), ImageHeight(img) );


    // Do pass 1 and pass 2 in series to avoid accessing values before they have set.
    vertPass( img, pass1, Avg, radius );
    horPass( pass1, pass2, Avg, radius );
   
    ImageWrite( pass2, argv[3] );

    return 0;
}
