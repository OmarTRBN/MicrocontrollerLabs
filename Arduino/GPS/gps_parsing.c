#include <stdio.h>

int main()
{
    const char *nmea = "$GPRMC,185242.00,A,4057.51881,N,02905.26289,E,0.420,,221223,,,D*73\n"
                       "$GPVTG,,T,,M,0.420,N,0.777,K,D*27\n"
                       "$GPGGA,185242.00,4057.51881,N,02905.26289,E,2,06,1.37,12.1,M,37.6,M,,0000*6E\n"
                       "$GPGSA,A,3,29,25,28,31,05,26,,,,,,,4.33,1.37,4.10*03\n"
                       "$GPGSV,3,1,12,05,35,067,09,12,04,139,08,16,15,314,06,18,67,228,09*7D\n"
                       "$GPGSV,3,2,12,20,11,038,,23,17,171,12,25,36,149,34,26,40,307,22*7C\n"
                       "$GPGSV,3,3,12,28,25,237,10,29,61,053,30,31,30,264,22,40,36,143,33*7F\n"
                       "$GPGLL,4057.51881,N,02905.26289,E,185242.00,A,D*6E\n";

    int depola = 0, counter;
    int saat, dakika, saniye, boylam, enlem, enlemrad, enlemcm, boylamcm;
    char simdiki, depo[70], onceki;

    onceki = nmea[0];

    for (int i = 0; nmea[i] != '\0'; i++)
    {
        simdiki = nmea[i];

        if (depola == 0)
        {
            if (onceki == 'M' && simdiki == 'C')
            {
                counter = 0;
                depola = 1;
            }
            else
            {
                onceki = simdiki;
            }
        }
        else
        {
            depo[counter] = simdiki;
            counter++;
            if (counter == 47)
            {
                saat = 3 + 10 * (depo[1] - 48) + (depo[2] - 48);
                dakika = 10 * (depo[3] - 48) + (depo[4] - 48);
                saniye = 10 * (depo[5] - 48) + (depo[6] - 48);

                enlem = 600 * (depo[13] - 48) + 60 * (depo[14] - 48) + (depo[15] - 48) + 0.1 * (depo[15] - 48);
                enlemrad = enlem * 3.1415 / 1800.0;
                enlemcm = enlem * 1.852;

                boylamcm = (6000 * (depo[26] - 48) + 600 * (depo[27] - 48) + 60 * (depo[28] - 48) + (depo[29] - 48)) * 1.852 * cos(enlemrad);
            }
            onceki = simdiki;
        }
    }

    printf("%d\t", saat);
    printf("%d\t", dakika);
    printf("%d\n", saniye);
    printf("Enlem: %d m\n", enlemcm);
    printf("Enlemrad: %d rad\n", enlemrad);
    printf("Boylam: %d m\n", boylamcm);

    return 0;
}
