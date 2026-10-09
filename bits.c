/* 
 * CS:APP Data Lab 
 * 
 * Yubo Zhou - 25803050041
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

You will provide your solution to the Data Lab by
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return (0x01) << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return (~(x & y) & ~(~x & ~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int msk = (x >> 31);

  return (msk & ((~x) + 0x01));
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  return ((x & ~((0xFF) << (dst << 3))) | (((x >> (src << 3)) & (0xFF)) << (dst << 3)));
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int not_n = !n;
  n = n | (not_n << 5);
  int neg_n = ((~n) + 0x01);
  int msk = (0x01 << (32 + neg_n)) + (~0x00);
  int msk_ifn0 = ((~not_n) + 0x01);
  return ((x >> n) & msk) | (msk_ifn0 & (x << (32 + neg_n)));

}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int msk = (0x0F) | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int low = (x & msk) << 4;
  return ((x >> 4) & msk) | low;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int lowbit = (~x) & (x + 0x01);
  x = x | lowbit;
  return (~x) & (x + 0x01);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int sum = 0x00;
  // xor : ~((x & y) | (~x & ~y)) = (~(x & y)) & (x | y)
  int xor_x = 0x00, xor_y = 0x00;
  xor_x = x, xor_y = x >> 16;
  x = (~(xor_x & xor_y)) & (xor_x | xor_y);
  xor_x = x, xor_y = x >> 8;
  x = (~(xor_x & xor_y)) & (xor_x | xor_y);
  sum = sum + x;
  sum = sum + (x >> 1);
  sum = sum + (x >> 2);
  sum = sum + (x >> 3);
  sum = sum + (x >> 4);
  sum = sum + (x >> 5);
  sum = sum + (x >> 6);
  sum = sum + (x >> 7);
  
  sum = sum + !((x & (0x01 << 31)));
  return sum & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  n = n & 0x1F;
  n = n | ((!n) << 5);
  int neg_n = ((~n) + 0x01);
  int msk = (0x01 << (32 + neg_n)) + (~0x00);
  return ((x >> n) & (msk)) | (x << (32 + neg_n));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int neg_one = ~0x00;
  int delta = (x >> n) & 0x01;
  delta = delta + neg_one;
  x = x + ((0x01 << n) >> 1) + delta;

  int msk = (0x01 << n) + neg_one;
  return x & (~msk);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int is_x_neg = (x >> 31) & 1;
  int is_y_neg = (y >> 31) & 1;
  int is_x_pos = !is_x_neg;
  int is_y_pos = !is_y_neg;
  int delta = x + ((~y) + 0x01);
  int raw_gr = !(delta >> 31);
  int gr = ((is_x_pos & is_y_neg) | (((is_x_pos & is_y_pos) | (is_x_neg & is_y_neg)) & raw_gr));
  int avg = (x >> 1) + (y >> 1);
  int c = ((x & 1) + (y & 1) + gr) >> 1;
  return avg + c;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int is_a_neg = (a >> 31) & 1;
  int is_b_neg = (b >> 31) & 1;
  int is_X_neg = (x >> 31) & 1;
  int is_a_pos = !is_a_neg;
  int is_b_pos = !is_b_neg;
  int is_X_pos = !is_X_neg;

  // ax : a <= x
  int xx = x, yy = a;
  int is_x_neg = is_X_neg;
  int is_y_neg = is_a_neg;
  int is_x_pos = is_X_pos;
  int is_y_pos = is_a_pos;
  int delta = xx + ((~yy) + 0x01);
  int raw_gr = !(delta >> 31);
  int ax = ((is_x_pos & is_y_neg) | (((is_x_pos & is_y_pos) | (is_x_neg & is_y_neg)) & raw_gr));
  
  // xb : x <= b
  xx = b, yy = x;
  is_x_neg = is_b_neg;
  is_y_neg = is_X_neg;
  is_x_pos = is_b_pos;
  is_y_pos = is_X_pos;
  delta = xx + ((~yy) + 0x01);
  raw_gr = !(delta >> 31);
  int xb = ((is_x_pos & is_y_neg) | (((is_x_pos & is_y_pos) | (is_x_neg & is_y_neg)) & raw_gr));
  
  // bx : b <= x
  xx = x, yy = b;
  is_x_neg = is_X_neg;
  is_y_neg = is_b_neg;
  is_x_pos = is_X_pos;
  is_y_pos = is_b_pos;
  delta = xx + ((~yy) + 0x01);
  raw_gr = !(delta >> 31);
  int bx = ((is_x_pos & is_y_neg) | (((is_x_pos & is_y_pos) | (is_x_neg & is_y_neg)) & raw_gr));
  
  // xa : x <= a
  xx = a, yy = x;
  is_x_neg = is_a_neg;
  is_y_neg = is_X_neg;
  is_x_pos = is_a_pos;
  is_y_pos = is_X_pos;
  delta = xx + ((~yy) + 0x01);
  raw_gr = !(delta >> 31);
  int xa = ((is_x_pos & is_y_neg) | (((is_x_pos & is_y_pos) | (is_x_neg & is_y_neg)) & raw_gr));
  
  return ((ax & xb) | (bx & xa));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  // consts
  int INT_MIN = 1 << 31;
  int INT_MAX = ~INT_MIN;

  // make positive
  int is_neg_msk = (x >> 31);
  int is_pos_msk = ~is_neg_msk;
  int xx = (is_neg_msk & ((~x) + 0x01)) | (is_pos_msk & x);

  // 0x19999999 is the greatest number that can be multiply
  // if x > 0x19999999, return INT_MAX, else, *5;
  int thr = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | (0x9A);
  int delta = xx + ((~thr) + 0x01);
  int msk_le = delta >> 31;
  int ge = !msk_le;
  int msk_ge = (~ge) + 0x01;

  // restore
  return (msk_ge & ((is_neg_msk & INT_MIN) | (is_pos_msk & INT_MAX))) | (msk_le & (x + (x << 2)));
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int lx = x & 0xFF;
  int ly = y & 0xFF;
  int lz = z & 0xFF;
  int carry = (lx + ly + lz) >> 8;
  int xx = x >> 8;
  int yy = y >> 8;
  int zz = z >> 8;
  int res = xx + yy + zz + carry;
  res = res >> 23;
  int is_neg_msk = (res >> 31);
  int is_pos_msk = ~is_neg_msk;
  int is_full_one = !(res + 1);
  int is_full_zero = !res;
  int is_good_msk = (~(is_full_one | is_full_zero) + 1);

  int is_pos_overflow_msk = is_pos_msk & (~is_good_msk);
  int is_neg_overflow_msk = is_neg_msk & (~is_good_msk);

  return (is_good_msk & 0) | (is_pos_overflow_msk & 1) | (is_neg_overflow_msk);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned S = uf >> 31;
  unsigned E = (uf >> 23) & 0x000000FF;
  unsigned M = uf & 0x007FFFFF;
  if (E == 0x00000000) {
    unsigned num = M + (M >> 1);
    if ((num & 0x00000001) & (M & 0x00000001)) {
      num = num + 1;
    }
    return num | (S << 31);
  } else if (E == 0x000000FF) {
    return uf;
  }
  unsigned num = M;
  num = num | (0x00800000);
  unsigned lst_bit = num & 1;
  num = num + (num >> 1);
  if (num & lst_bit) {
    num = num + 1;
  } 
  unsigned res = (S << 31) | (E << 23);
  if (num & 0x01000000) {
    lst_bit = num & 1;
    num = (num >> 1);
    if (num & lst_bit) {
      num = num + 1;
    }
    res = res + 0x00800000;
    if (((res >> 23) & 0x000000FF) == 0x000000FF) {
      return res & 0xFF800000;
    }
  }
  res = res + (num & 0x007FFFFF);
  return res;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned S = uf >> 31;
  unsigned E = (uf >> 23) & 0x000000FF;
  unsigned M = uf & 0x007FFFFF;
  if (E == 0x00000000) {
    return S << 31;
  }
  if (E == 0x000000FF) {
    return uf;
  }
  if (E >= 150U) {
    return uf;
  }
  if (E <= 125U) {
    return S << 31;
  }
  unsigned decimal = 0x00000000;
  unsigned num = M | 0x00800000;
  int bit = 23 - (E - 127);
  for (int i = 0; i < bit; i++) {
    decimal = decimal | ((num & (1U << i)) << (24 - bit));
    num = num & ~(1U << i);
  }
  if (bit == 24) {
    if (decimal <= 0x00800000) {
      return S << 31;
    } else {
      return (S << 31) | (127U << 23);
    }
  }
  if (decimal < 0x00800000 || (decimal == 0x00800000 && !((num >> bit) & 1U))) {
    num ^= 0x00800000;
    return (S << 31) | (E << 23) | num;
  } else {
    num = num + (1U << bit);
    unsigned res = (S << 31) | (E << 23);
    if (num & (0x01000000)) {
      res = res + 0x00800000;
      num = num >> 1;
    }
    return res | (num & 0x007FFFFF);
  }
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned absx = x > 0 ? x : -x;
  if (absx == 0) {
    return 0x00000000;
  }
  unsigned ux = x;
  unsigned res = ux & 0x80000000;

  for (unsigned i = 31; i >= 0; i--) {
    if ((absx >> i) & 1) {
      unsigned num = absx & ((1U << i) - 1U);
      if (i > 23) {
        int remainder = num & ((1U << (i - 23)) - 1U);
        num = num >> (i - 23);
        if (remainder > (1U << (i - 24)) || (remainder == (1U << (i - 24)) && (num & 1))) {
          num++;
          if ((num >> 23) & 1) {
            i++;
            num = num ^ (1U << 23);
            num = num >> 1;
          }
        }
      } else {
        num = num << (23 - i);
      }
      return res | ((i + 127U) << 23) | (num);
    }
  }
  return 0x00000000;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int num = x;
  int msk = 0x00;

  msk = 0x55;
  msk = msk | (msk << 8);
  msk = msk | (msk << 16);
  num = (num & msk) + ((num >> 1) & msk);

  msk = 0x33;
  msk = msk | (msk << 8);
  msk = msk | (msk << 16);
  num = (num & msk) + ((num >> 2) & msk);

  msk = 0x0F;
  msk = msk | (msk << 8);
  msk = msk | (msk << 16);
  num = (num & msk) + ((num >> 4) & msk);

  msk = 0xFF;
  msk = msk | (msk << 16);
  num = (num & msk) + ((num >> 8) & msk);

  msk = 0xFF;
  msk = msk | (msk << 8);
  num = (num & msk) + ((num >> 16) & msk);

  return num;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int tmp = 0x00;
  int msk = 0x00;
  
  tmp = x >> 16;
  msk = (0xFF << 8) | (0xFF);
  x = (x << 16) | (tmp & msk);

  tmp = x >> 8;
  msk = msk ^ (msk << 8);
  x = ((x & msk) << 8) | (tmp & msk);

  tmp = x >> 4;
  msk = msk ^ (msk << 4);
  x = ((x & msk) << 4) | (tmp & msk);

  tmp = x >> 2;
  msk = msk ^ (msk << 2);
  x = ((x & msk) << 2) | (tmp & msk);

  tmp = x >> 1;
  msk = msk ^ (msk << 1);
  x = ((x & msk) << 1) | (tmp & msk);

  return x;
}
