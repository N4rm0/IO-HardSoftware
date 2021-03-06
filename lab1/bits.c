/* 
 * CSE 351 HW1 (Data Lab )
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   Use the dlc compiler to check that your solutions conform
 *   to the coding rules.
 */


#endif
// declaration to avoid annoying warning
int printf(const char *, ...);

// Rating: 1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 * and the rest set to 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int pattern1 = 0x49;
  int pattern2 = 0x02;
  return pattern1 | (pattern2 << 8) | (pattern1 << 12) | (pattern2 << 20) | (pattern1 << 24); 
}
// Rating: 2
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {

  // the idea is to see if the n-1 bits are enough to fill the number.
  // if the number x is negative, we take its complementary to get a positive number
  int is_negative;
  int mask;
  int minus_one = ((1 << 31) >> 31);
  int result;
  // test if number is positive or negative
  is_negative = x >> 31; // either 0x00...00 or 0xff..ff

  // consider only the last n-1 bits
  // take advantage minus one is the 0xff mask
  mask = minus_one << (n+minus_one);
  // perform if operation (x<0)? ~x& mask : x&mask
  result = (is_negative & (mask & ~x)) + ((~is_negative) & (mask & x));

  //printf("x=%d n=%d (negative %d) mask=%x result=%d\n",x,n,is_negative,mask,!result);
  // result == 0 ?  ok: ko
  return !result;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  // taken from previous exercice
  int is_positive = ((~x) >> 31) ; // either 0x00..00 or 0xff..ff
  int is_not_zero = ((!!x) << 31)>>31 ;
  return (is_not_zero & ((~is_positive) + (is_positive & 1)));
}
/* 
 * getbyte - extract byte n from word x
 *   bytes numbered from 0 (lsb) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // just shift bits to get the mask
  int byte_mask = 0xFF;
  // perform 8*n, since 8=2^3 use bitshift to compute powers of 2
  return byte_mask & (x >> (n << 3));
}

// Rating: 3
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  // n=0 is a o_O case
  // case x > 0 => easy case, logicShift is done by >>
  // case x < 0 => 
  //            case n > 0 do shift and use mask 0x00..FF to discard n bits
  //            case n = 0 do shift of 0 and use mask 0xFF..FF to keep all bits
  
  int minus_one = ~0;
  int zero_or_minus_one = (x >> 31); // either 0x00..00 or 0xff..ff
  // somehow I am lost in this mess!!
  int is_n_zero = ((!n) << 31) >> 31; // if n=0  0xFF..FF else 0x00
  int mask =  is_n_zero + ((~is_n_zero) & (~((1 << 31) >> (n + minus_one))));
  int positive_case = (zero_or_minus_one ^ minus_one) & (x >> n);
  int negative_case = (zero_or_minus_one ^ 0) & ((x >> n) & mask);
  return positive_case + negative_case;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // interesting case is when both x and y are negative or positive, other case is irrelevant
  int compute_x_y = x + y;
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int not_same_sign = sign_x ^ sign_y;
  // test sign has changed (test 1st bit) with XOR
  // change => 0xFF..FF
  // no change => 0x00..00
  int not_change = (compute_x_y ^ sign_x ) >> 31;

  //printf("x=%d[%x] y=%d[%x] sign_x=%x sign_y=%x not_same_sign=%x not_change=%x\n",x,x,y,y,sign_x,sign_y,not_same_sign,not_change);
  
  return (not_same_sign & 1) + (~not_same_sign & ((not_change & 0) + (~not_change & 1) ));
}
// Rating: 4
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int invx = ~x;                  //if x==0, then -1
  int negx = invx + 1;                //if x==0, then 0
  return ((~negx & invx)>>31) & 1; 
}
// Extra Credit: Rating: 3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // transform x to 0x00 or 0xFF..FF
  int boolean_x = ((!!x) <<31) >>31;
  return (boolean_x & y) + (~boolean_x & z);
}
// Extra Credit: Rating: 4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  // check that only 1 bit is set to 1
  // x & x-1 does the trick
  // check also x is not negative or null
  int x_negative = x >> 31; // 0x00 if positive, 0xFF..FF otherwise
  int x_null = ((!x) << 31) >> 31;  // 0xFF..FF if null
  int negative_or_null = x_null | x_negative;
  int minus_1 = ~0;
  int divide_by_two = !(x & (x + minus_1)); // 0 if divisable by 2
  //  printf("x_negative=%x x_null=%x negative_or_null=%x divide_by_two=%x\n",x_negative,x_null,negative_or_null,divide_by_two);
  return (negative_or_null & 0) + (~negative_or_null & divide_by_two);
}
