/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){
        return !y;
    }
    if(!y){
        return 0;
    }
    return !((x^y)>>31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a, b, c, d, e;
    int mask16 = (0xFF << 8) | 0xFF;

    a = v > mask16;
    v = v >> (a << 4);

    b = v > 0xFF;
    v = v >> (b << 3);

    c = v > 0xF;
    v = v >> (c << 2);

    d = v > 0x3;
    v = v >> (d << 1);

    e = v > 0x1;

    return (a << 4) |
           (b << 3) |
           (c << 2) |
           (d << 1) |
           e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
     int ns = n << 3;
    int ms = m << 3;

    int nb = (x >> ns) & 0xFF;
    int mb = (x >> ms) & 0xFF;

    int diff = nb ^ mb;

    return x ^ ((diff << ns) | (diff << ms));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    int i = 32;

    while (i) {
        result = (result << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }

    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask;

    mask = ~(((1 << 31) >> n) << 1);

    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;
    int count = 0;
    int t;

    t = !(y >> 16) << 4;
    count = count + t;
    y = y << t;

    t = !(y >> 24) << 3;
    count = count + t;
    y = y << t;

    t = !(y >> 28) << 2;
    count = count + t;
    y = y << t;

    t = !(y >> 30) << 1;
    count = count + t;
    y = y << t;

    t = !(y >> 31);
    count = count + t;
    y = y << t;

    count = count + !y;

    return count;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned sign;
    unsigned exp;
    unsigned frac;
    unsigned sig;
    unsigned rem;
    unsigned half;
    int e = 31;
    int shift;

    if (x == 0)
        return 0;

    sign = ux & 0x80000000;

    if (sign)
        ux = -ux;

    while (!(ux >> e))
        e = e - 1;

    exp = e + 127;

    if (e <= 23) {
        frac = (ux << (23 - e)) & 0x7FFFFF;
    }
    else {
        shift = e - 23;

        sig = ux >> shift;
        rem = ux & ((1 << shift) - 1);
        half = 1 << (shift - 1);

        if (rem > half)
            sig = sig + 1;
        else if (rem == half) {
            if (sig & 1)
                sig = sig + 1;
        }

        if (sig >> 24) {
            exp = exp + 1;
            sig = sig >> 1;
        }

        frac = sig & 0x7FFFFF;
    }

    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;

    /* NaN 或无穷大 */
    if (exp == 0x7F800000)
        return uf;

    /* 0 或非规格化数 */
    if (exp == 0)
        return sign | (frac << 1);

    /* 规格化数：指数 + 1 */
    exp = exp + 0x00800000;

    /* 溢出到无穷大 */
    if (exp == 0x7F800000)
        return sign | exp;

    return sign | exp | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    unsigned exp;
    unsigned hi;
    unsigned value;
    int e;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7FF;

    /* NaN / infinity */
    if (exp >= 0x7FF)
    return 0x80000000;

    e = exp - 1023;

    /* 绝对值小于 1，向 0 截断 */
    if (e < 0)
        return 0;

    /* 超出 32 位 int 范围 */
    if (e > 30)
        return 0x80000000;

    /*
     * double 的有效数字是：
     * 1.fraction
     *
     * uf2 低 20 位 = fraction 的高 20 位
     * 再补上隐藏的 leading 1
     */
    hi = (uf2 & 0xFFFFF) | 0x100000;

    if (e <= 20) {
        value = hi >> (20 - e);
    }
    else {
        value = (hi << (e - 20)) |
                (uf1 >> (52 - e));
    }

    if (sign)
        return -value;

    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;

    if (x < -126)
        return 1 << (x + 149);

    if (x <= 127)
        return (x + 127) << 23;

    return 0x7F800000;
}
