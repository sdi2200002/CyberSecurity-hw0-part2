/*File: mertsumd.c */
#include <stdio.h>
#define MAXEXP 8

int main()
{
    int k, i, max, power, n, temp, factor, next, count, mertens, zp, sum, term, an, dn;
    k = 1;
    max = 1;
    mertens = 0;
    zp = 0;
    for (k = 1 ; k <= MAXEXP ; k++) {                                                                                                                         /* max = 10^MAXEXP */
         max *= 10;
    }
    for (n = 1 ; n <= max + 9 ; n++) {
         count = 0;
         if (n % 4 == 0 || n % 9 == 0) {                                              /* if 2^2 or 3^3 divisors of n, n is not free-squered, the result of mobius fanction is 0  */
             power = 1;
             for (i = 1 ; i <= MAXEXP ; i++){
                  power *= 10;
                  if (n >=  power - 9 && n <= power + 9 ) {                                          /* print mertens fanction result if 10^k-9 <= n <=10^k+9 , 1 <= k <= MAXEXP */
                      printf("M(%d) = %d\n", n, mertens);
                  }
                  if (n == power + 9 && i != MAXEXP) {                                                                           /* print dots after M(10^k+9) , 1 <= k < MAXEXP */
                      printf("..........\n");
                  }
             }
             if (mertens == 0) {                                                                        /* if mertens fanction result is 0, n is a zero point of mertens faction */
                 zp ++;
             }
             continue;                                                                                                                               /* continue for next number */
         }
         temp = n;
         if (temp % 2 == 0) {                                                    /* checking if 2 is a factor of n, we already checked if a power of 2 is a factor by checking 4 */
             count ++;
             temp /= 2;
         }
         if (temp % 3 == 0) {                                                    /* checking if 3 is a factor of n, we already checked if a power of 3 is a factor by checking 9 */
             count ++;
             temp /= 3;
         }
         factor = 5;
         next = 0;
         while (factor * factor <= temp) {                            /* searching for factors until the squere root of the number, after that only n can be a factor of its own */
                if (temp % factor == 0) {
                    count ++;
                    temp /= factor;
                    if (temp % factor == 0) {                              /* if factor divides n more than one times, n is not free-squered, the result of mobius fanction is 0 */
                        next = 1;
                        break;                                                                                                                                   /* stop "while" */
                    }
                }
                if (factor % 6 == 5) {
                    factor += 2;                                                                                        /* skip next "factor" because it is a multiple of 2 or 3 */
                }
                else {
                      factor += 4;                                                                              /* skip next 3 "factors" because they are multiples of 2, 3 or 5 */
                }
         }
         if (next == 0) {                                                                                /* not checking numbers if "next" is 1 because they are not squere-free */
             if (temp != 1) {                                                                                                     /* if "temp" is not 1 then it is a factor of n */
                 count ++;
             }
             if (count % 2 == 0) {                                                                      /* if the sum of the factors is even, the result of mobius fanction is 1 */
                 mertens ++;
             }
             else {                                                                                     /* if the sum of the factors is odd, the result of mobius fanction is -1 */
                   mertens --;
             }
         }
         power = 1;
         for (i = 1 ; i <= MAXEXP ; i++){
              power *= 10;
              if (n >= power - 9 && n  <= power + 9) {                                                     /* mertens fanction result if 10^k-9 <= n <=10^k+9 , 1 <= k <= MAXEXP */
                  printf("M(%d) = %d\n", n, mertens);
              }
              if (n == power + 9 && i != MAXEXP) {                                                                               /* print dots after M(10^k+9) , 1 <= k < MAXEXP */
                  printf("..........\n");
              }
         }
         if (mertens == 0) {                                                                            /* if mertens fanction result is 0, n is a zero point of mertens faction */
             zp ++;
         }
    }
    printf("\nFound %d zero points of Mertens function\n", zp);
    printf("\nChecking numbers in the range [2,%d]\n", zp*1000);

    an = 0;
    dn = 0;
    for (n = 2 ; n <= zp*1000 ; n++) {
         sum = 1;
         temp = n;
         factor = 2;
         while (factor * factor <= temp) {                            /* searching for factors until the squere root of the number, after that only n can be a factor of its own */
                term = 1;
                while (temp % factor == 0) {                   /* for each factor we make a term (1 + factor + factor^2 ... + factor^k) k is how many times a factor is repeated */
                       term = factor * term + 1;
                       temp /= factor;
                }
                sum *= term;                                                                                                                 /* sum = (term1 * term2 *...* termx */
                if (factor == 2) {
                    factor = 3;
                }
                else if (factor == 3) {
                         factor = 5;                                                                                                     /* skip 4 because it is a multiple of 2 */
                }
                else if (factor % 6 == 5) {
                         factor += 2;                                                                                     /* skip next factor because it is a multiple of 2 or 3 */
                }
                else {
                      factor += 4;                                                                                /* skip next 3 factors because they are multiples of 2. 3 or 5 */
                }
         }
         if (temp != 1) {                                                                                                           /* if temp is not 1 then it is a factor of n */
             sum *= (1 + temp);
         }
         if (sum - n == n) {                                                                                                             /* sum includes n so it gets abstracted */
             printf("\nFound perfect number: %d\n", n);                                                                                              /* if sum-n=n, n is perfect */
         }
         else if (sum - n < n) {                                                                                                         /* sum includes n so it gets abstracted */
                  dn++;                                                                                                                            /* if sum-n<n, n is deficient */
         }
         else {
               an++;                                                                                                                                /* if sum-n>n, n is abundant */
         }
    }
    printf("\nFound %d deficient numbers\n", dn);
    printf("\nFound %d abundant numbers\n\n", an);
}

