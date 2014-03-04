/*
 *******************************************************************************
 * Finds the total sum of all numbers divisible by 'x' or 'y' for numbers less
 * than 'z'.
 *
 * Two methods are available, a fast one and a slow one.
 * The fast one uses the formula (q*(1+z/q)*(z/2q)) to find the sum of all
 * numbers divisible by 'q' and less than 'z' for 'x', 'y', and 'x*y' and then
 * uses those numbers to find the sum of all numbers divisible by 'x' or 'y' and
 * less than 'z'.
 * The slow one just adds every single number divisible by 'x' or 'y' and then
 * subtracts all numbers divisible by both 'x' and 'y'. (Those numbers were
 * added twice, once for being divisible by 'x' and once for 'y'.)
 *
 * Do whatever you want with this, I guess. No real license.
 *
 * Authored by Isaac Steele
 * Started:        19/2/2014
 * Last Edited:    3/3/2014
 *******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

int sumDivisibleByX( int x, int z );
int sumAllLessThanZ( int x, int z );
int fastSumDivisibleByXorY( int x, int y, int z );
int slowSumDivisibleByXorY( int x, int y, int z );

/*
 * "argc" is a count of how many commandline arguments are passed to the program.
 * "*argv[]" points to an array of commandline arguments. Much like in bash, the
 * first element of that array is the program's name. The array starts at '0',
 * so argv[argc] is a null pointer.
 */
int main( int argc, char *argv[] )
{
    int x, y, z;
    int err = 0;

    if( argc != 4 && argc != 1 )
    {
        //argv[0] should contain the program name, assuming this is true.
        printf("Usage: %s <x> <y> <z>\n"
               "Where <z> is the maximum value (exclusive) and <x> and <y> are the numbers we wish to sum the multiples of.\n", argv[0]);

        err = 1;
    }
    else if( argc == 4 )
    {
        x = atoi( argv[1] );
        y = atoi( argv[2] );
        z = atoi( argv[3] );
    }
    else
    {
        x = 3;
        y = 5;
        z = 1000;
    }

    printf("x = %d\ny = %d\nz = %d\n", x, y, z);

    // Executes if x, y , and z were assigned values.
    if( err == 0 )
    {
        int fastTotal;
        int slowTotal;

        fastTotal = fastSumDivisibleByXorY(x, y, z-1);
        slowTotal = slowSumDivisibleByXorY(x, y, z);

        printf("Using the fast method, the sum is %d.\n", fastTotal);
        printf("Using the slow method, the sum is %d.\n", slowTotal);
        if( fastTotal == slowTotal )
        {
            printf("The fast method and the slow method agree!\n");
            printf("The sum is %d.\n", fastTotal);
        }
    }


    return 0;
}

int sumDivisibleByX( int x, int z )
{
    int sum = 0;
    float n = 0;
    /*
     * The sum of all numbers 0-100 can be found by (1+100)*50. This generalizes
     * to (1+n)*(n/2).
     * There are z/x numbers less than z and divisible by x. If you sum all
     * numbers from 0 to z/x and then multiply by x, you get the sum of all
     * numbers from 0 to z divisible by x.
     * NOTE: This only works if z % x = 0, so first we reduce z until z % x = 0.
     */
    while( z % x > 0)
    {
        z = z - 1;
    }

    n = (float) z / x;

    sum = (int) (x * (1 + n) * (n / 2));

    return sum;
}

int sumAllLessThanZ( int x, int z )
{
    int totalX=0;
    int largestX=x;

    // Adds all numbers less than z divisible by x.
    while(largestX < z)
    {
        totalX += largestX;
        largestX += x;
    }

    return totalX;
}

int fastSumDivisibleByXorY( int x, int y, int z )
{
    int total=0;
    int sumX=0;
    int sumY=0;
    int sumXandY=0;

    /*
     * Since all numbers divisible by both x and y would be summed twice the
     * sum of those numbers must be calculated and subtracted from the combined
     * sums of all multiples off x and all multiples of y.
     */
    sumX = sumDivisibleByX( x, z );
    sumY = sumDivisibleByX( y, z );
    sumXandY = sumDivisibleByX( x*y, z );

    total = sumX + sumY - sumXandY;

    return total;
}

int slowSumDivisibleByXorY( int x, int y, int z )
{
    int total = 0;
    int sumX = 0;
    int sumY = 0;
    int sumXandY = 0;

    /*
     * Since all numbers divisible by both x and y would be summed twice the
     * sum of those numbers must be calculated and subtracted from the combined
     * sums of all multiples of x and all multiples of y.
     */
    sumX = sumAllLessThanZ( x, z );
    sumY = sumAllLessThanZ( y, z );
    sumXandY = sumAllLessThanZ( x*y, z );

    total = sumX + sumY - sumXandY;

    return total;
}
