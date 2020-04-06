#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

int main (int argCount, char *args [])
{
    enum Mode { Geo2Mercator = 1, Mercator2Geo } mode = Geo2Mercator;
    double lat = 1.0e4, lon = 1.0e4;

    printf ("Lat/Lon <=> Mercator converter tool\n");

    if (argCount < 2)
    {
        printf ("\n\nUSAGE:\n\tmt -lat:<lat> -lon<lon> -m<mode>\n\nwhere mode us 1 - geo to mercator, 2 - mercator to geo\n");
        exit (0);
    }

    for (int i = 1; i < argCount; ++ i)
    {
        char *arg = args [i];

        if (arg [0] == '-' || arg [0] == '/')
        {
            if (strnicmp (arg + 1, "lat:", 4) == 0)
                lat = atof (arg + 5);
            else if (strnicmp (arg + 1, "lon:", 4) == 0)
                lon = atof (arg + 5);
            else if (strnicmp (arg + 1, "m:", 2) == 0)
                mode = (Mode) atoi (arg + 3);
        }
        else
        {
            printf ("Invalid argument - %s\n", arg);
        }
    }

    switch (mode)
    {
        case Mode::Geo2Mercator:
            printf ("Converting %f deg to Mercator...", lat);

            lat *= (PI / 180.0);
            lat  = log (tan (lat * 0.5 + PI * 0.25));
            
            printf ("%.8f\n", lat);
            
            if (lon < 1.0e3)
                printf ("Converting %f deg to Mercator...%.8f\n", lon, lon * PI / 180.0);

            break;

        case Mode::Mercator2Geo:
            printf ("Converting %f to geo latitude...", lat);

            lat = 2.0 * (atan (exp (lat)) - PI * 0.25);
            
            printf ("%f.8\n", lat * 180.0 / PI);
            
            if (lon < 1.0e3)
                printf ("Converting %f deg to geo longitude...%.8f\n", lon, lon / PI * 180.0);

            break;

        default:
            printf ("Unknown mode %d\n", (int) mode);
    }

    exit (0);
}