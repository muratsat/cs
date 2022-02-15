/* 
this is a program that counts the number of 
1-bits in a 32-bit number 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// a function to measure 
// time usage of a particular function
void timer(unsigned (*func)(unsigned)) {
    clock_t start = clock();

    const unsigned ITERATIONS = 100000000;
    unsigned t =  func(ITERATIONS);

    clock_t end = clock();

    printf(" %lfs \n", (double(end - start))/CLOCKS_PER_SEC);
}

// accumulators 1-4 are functions that count 
// the number of ones in binary in all numbers
// from 0 to ITERATIONS in timer function

unsigned accumulator1(unsigned count) {
    printf("1: ");
    unsigned sum = 0;

    for(unsigned x = 0; x < count; x++){
        for(size_t i = 0; i < 32; i++){
            if((x & (1 << i)) != 0)
                sum++;
        }
    }

    return sum;
}

unsigned accumulator2(unsigned count) {
    printf("2: ");
    unsigned sum = 0;

    for(unsigned x = 0; x < count; x++){
        for(size_t i = x; i != 0; i >>= 1){
            sum += i & 1;
        }
    }

    return sum;
}

unsigned accumulator3(unsigned count) {
    printf("3: ");
    unsigned sum = 0;

    for(unsigned x = 0; x < count; x++){
        for(size_t i = x; i != 0; i &= i-1){
            sum++;
        }
    }

    return sum;
}

unsigned accumulator4(unsigned count) {
    printf("4: ");
    unsigned sum = 0;

    for(unsigned x = 0; x < count; x++) {

        unsigned
        i = ((x & 0xAAAAAAAA) >>  1) + (x & 0x55555555);
        i = ((i & 0xCCCCCCCC) >>  2) + (i & 0x33333333);
        i = ((i & 0xF0F0F0F0) >>  4) + (i & 0x0F0F0F0F);
        i = ((i & 0xFF00FF00) >>  8) + (i & 0x00FF00FF);
        i = ((i & 0xFFFF0000) >> 16) + (i & 0x0000FFFF);

        sum += i;
    }

    return sum;
}

unsigned accumulator5(unsigned count) {
    printf("5: ");
    unsigned sum = 0;

    for(unsigned x = 0; x < count; x++) {
        unsigned
        i = ((x >>  1) & 0x55555555) + (x & 0x55555555);
        i = ((i >>  2) & 0x33333333) + (i & 0x33333333);
        i = ((i >>  4) & 0x0F0F0F0F) + (i & 0x0F0F0F0F);
        i = ((i >>  8) & 0x00FF00FF) + (i & 0x00FF00FF);
        i = ((i >> 16) & 0x0000FFFF) + (i & 0x0000FFFF);

        sum += i;
    }

    return sum;
}

/*
    An example for x = 0b10110100 = 180 

x = 10 11 01 00

    10|11|01|00     x
     1|01|10|10     x >> 1
    01|01|01|01     0x55
    01|01|00|00     (x >> 1) & 0x55
    00|01|01|00     x & 0x55
    01|10|01|00     ((x >> 1) & 0x55) + x & 0x55 = i

    01 10|01 00     i
       01|10 01     i >> 2
    00 11|00 11     0x33
    00 01|00 01     (i >> 2) & 0x33
    00 10|00 00     i & 0x33
    00 11|00 01     ((i >> 2) & 0x33) + (i & 0x33) = i

    00 11 00 01     i
          00 11     i >> 4
    00 00 11 11     0x0F
    00 00 00 11     (i >> 4) & 0x0F
    00 00 00 01     i & 0x0F
    00 00 01 00     ((i >> 4) & 0x0F) + (i & 0x33)
*/


int main(){
    timer(accumulator1);
    timer(accumulator2);
    timer(accumulator3);
    timer(accumulator4);
    timer(accumulator5);

/*
time results on my laptop:
1:  2.745822s 
2:  1.310582s 
3:  0.728901s 
4:  0.234546s 
5:  0.237523s
*/

    return 0;
}