#include <stdio.h>

int main ()
{

    unsigned int low18Mask = 0x3FFFF;
    unsigned int high14Mask = 0xFFFC0000;;

    unsigned int A = 0xFFFFFFFF;
    unsigned int B = 0xFFFFFFFF;

    A = A & high14Mask;
    B = B & low18Mask;
    unsigned int C = A | B;

    printf ("%x \n", A);
    printf ("%x \n", B);
    printf ("%x \n", C);

    return 0;

}
