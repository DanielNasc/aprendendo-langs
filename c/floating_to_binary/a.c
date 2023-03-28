#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define print_string(s) printf("%s\n", s);
#define fill_binary_inf(binary) binary[0] = '0'; \
                                for (int i = 1; i <= exponent_size; i++) binary[i] = '1'; \
                                for (int i = exponent_size+1; i < size; i++) binary[i] = '0'; \
                                binary[size] = '\0';

typedef enum { FLOAT, DOUBLE } type;


void double_to_binary(double n, char *binary, type t)
{

    assert(binary != NULL);

    __int8_t size = t == FLOAT ? 32 : 64;
    __int8_t exponent_size = t == FLOAT ? 8 : 11;
    __int8_t mantissa_size = t == FLOAT ? 23 : 52;
    __int8_t integer_size = 0;
    int bias = t == FLOAT ? 127 : 1023;

    // if (sizeof(binary)/sizeof(char) != size + 1) {
    //     printf("binary must be [32|64] + 1 bytes long, but it is %ld bytes long\n", sizeof(binary));
    //     return;
    // }

    // if (t == FLOAT) n = (float) n;  // if the type is float, then convert the double to float

    // binary must be 64 + 1 bytes long

    printf("n: %f\n", n);

    if (n == 0)
    {
        for (int i = 0; i < size; i++) binary[i] = '0';
        binary[size] = '\0';
        return;
    } else if (n == INFINITY)
    {
        fill_binary_inf(binary);
        return;
    } else if (n == -INFINITY)
    {
        fill_binary_inf(binary);
        binary[0] = '1';
        return;
    } else if (isnan(n))
    {
        fill_binary_inf(binary);
        binary[exponent_size+1] = '1';
        return;
    }
    
    char *integer = malloc(sizeof(int) * 8 * sizeof(char));
    char *mantissa = malloc(mantissa_size * sizeof(char));
    char *exponent_binary = malloc(exponent_size+1 * sizeof(char));

    int sign = 0;

    if (n < 0)
    {
        sign = 1;
        n = -n;
    }

    int integer_part = (int) floor(n);
    double fractional_part = n - integer_part;

    // integer part
    for (int i = 0; integer_part != 0 && integer_part != 1 && i < sizeof(int) * 8; i++)
    {
        integer[i] = '0' + (integer_part % 2);
        integer_part /= 2;
        integer_size++;
    }

    if (integer_part == 1) {
        integer[integer_size] = '1';
        integer_size++;
    }

    for (int i = 0; i < integer_size/2; i++)
    {
        char temp = integer[i];
        integer[i] = integer[integer_size - i - 1];
        integer[integer_size - i - 1] = temp;
    }

    printf("integer part: %s\n", integer);

    /*
        mantissa part
        =============

        The fractional portion of the number must also be converted to binary, though the conversion process is much different 
        from what you're used to. The algorithm you'll used is based on performing repeated multiplications by 2, 
        and then checking if the result is >= 1.0. If the result is >= 1.0, then a 1 is recorded for the binary fractional 
        component, and the leading 1 is chopped of the result. If the result is < 1.0, then a 0 is recorded for the binary 
        fractional component, and the result is kept as-is. The recorded builds are built-up left-to-right. The result keeps 
        getting chained along in this way until one of the following is true:

            The result is exactly 1.0
            23 iterations of this process have occurred; i.e. the final converted binary value holds 23 bits

        ref: https://kyledewey.github.io/comp122-fall17/lecture/week_2/floating_point_interconversions.html

    */

    printf("fractional part: %f\n", fractional_part);
    for (int i = 0; i < mantissa_size; i++)
    {
        if (fractional_part == 0) { // if the fractional part is 0, then the rest of the mantissa is 0
            for (int j = i; j < mantissa_size; j++)
            {
                printf("[%d] fractional part: %f -> 0 ::%s ->\t", i+1, fractional_part, mantissa);
                print_string(mantissa);
                mantissa[j] = '0';
            }

            break;
        }

        fractional_part *= 2.0;
        fractional_part = round(fractional_part * 1000000) / 1000000; // round to 6 decimal places to avoid floating point errors
        if (fractional_part >= 1) 
        {
            printf("[%d] fractional part: %f -> 1 ::%s ->\t", i+1, fractional_part, mantissa);
            mantissa[i] = '1';
            fractional_part -= 1.0;
        }
        else
        {
            printf("[%d] fractional part: %f -> 0 ::%s ->\t", i+1, fractional_part, mantissa);
            mantissa[i] = '0';
        }
        print_string(mantissa);
    }
    printf("mantissa part: %s\n", mantissa);

    // exponent part
    int pos = -1;

    for (int i = 0; i < exponent_size; i++) // try to find the first 1 in the integer part
    {
        if (integer[i] == '1')
        {
            pos = i;
            break;
        }
    }

    __uint8_t is_negative = 0;

    if (pos == -1) // if there is no 1 in the integer part, then try to find the first 1 in the mantissa part
    {
        for (int i = 0; i < mantissa_size; i++)
        {
            if (mantissa[i] == '1')
            {
                pos = i;
                is_negative = 1;
                break;
            }
        }
    }

    printf("pos: %d\n", pos);

    int remainder = pos != -1 ? (is_negative ? -1*(pos + 1) : integer_size - 1 - pos) : 0; // if there is no 1 in the integer part and the mantissa part, then the remainder is 0

    int exponent = remainder + bias;

    printf("exponent: %d\n", exponent);

    for (int i = 0; i < exponent_size; i++)
    {
        exponent_binary[exponent_size - 1 - i] = (exponent % 2) + '0'; // convert the exponent to binary
        exponent /= 2;
    }

    printf("exponent binary: %s\n", exponent_binary);

    // mantissa part
    if (is_negative)
    {
        printf("is negative\n");
        for (int i = 0; i < mantissa_size + remainder; i++) // shift the mantissa part to the right
        {
            mantissa[i] = mantissa[i - remainder];
        }

        for (int i = mantissa_size - remainder; i < mantissa_size; i++) { // fill the rest of the mantissa part
            fractional_part *= 2;
            if (fractional_part >= 1)
            {
                mantissa[i] = '1';
                fractional_part -= 1;
            }
            else
            {
                mantissa[i] = '0';
            }
        }
    } else
    {
        for (int i = mantissa_size - 1; i >= remainder; i--) // shift the mantissa part to the left
        {
            mantissa[i] = mantissa[i - remainder];
        }

        for (int i = 0; i < remainder; i++) // put the integer part after the first 1 in the mantissa part
        {
            mantissa[i] = integer[pos + 1 + i];
        }
    }

    printf("mantissa part: %s\n", mantissa);

    // sign bit
    binary[0] = sign + '0';

    // exponent part
    for (int i = 0; i < exponent_size; i++)
    {
        binary[i + 1] = exponent_binary[i]; // put the exponent part in the binary
    }

    // mantissa part
    for (int i = 0; i < mantissa_size; i++)
    {
        binary[i + exponent_size + 1] = mantissa[i]; // put the mantissa part in the binary
    }

    binary[1 + exponent_size + mantissa_size] = '\0';
    
    free(integer);
    free(mantissa);
    free(exponent_binary);

    print_string(binary);
    printf("\n\n");
}

int main()
{
    // tests
    double a = 0.0;
    double b = 1.0;
    double c = 1234.5678;
    double d = -1234.5678;
    double e = 231234.5678;

    print_string("Float tests:");
    char *a_binary = malloc(33 * sizeof(char));
    char *b_binary = malloc(33 * sizeof(char));
    char *c_binary = malloc(33 * sizeof(char));
    char *d_binary = malloc(33 * sizeof(char));
    char *e_binary = malloc(33 * sizeof(char));
    char *inf_binn = malloc(33 * sizeof(char));
    char *nan_binn = malloc(33 * sizeof(char));
    char *ninf_bin = malloc(33 * sizeof(char));

    double_to_binary(a, a_binary, FLOAT);
    double_to_binary(b, b_binary, FLOAT);
    double_to_binary(c, c_binary, FLOAT);
    double_to_binary(d, d_binary, FLOAT);
    double_to_binary(e, e_binary, FLOAT);
    double_to_binary(INFINITY, inf_binn, FLOAT);
    double_to_binary(NAN, nan_binn, FLOAT);
    double_to_binary(-INFINITY, ninf_bin, FLOAT);

    print_string(a_binary);
    print_string(b_binary);
    print_string(c_binary);
    print_string(d_binary);
    print_string(e_binary);
    print_string(inf_binn);
    print_string(nan_binn);
    print_string(ninf_bin);

    assert(strcmp(a_binary, "00000000000000000000000000000000") == 0);
    assert(strcmp(b_binary, "00111111100000000000000000000000") == 0);
    assert(strcmp(c_binary, "01000100100110100101001000101011") == 0);
    assert(strcmp(d_binary, "11000100100110100101001000101011") == 0);
    assert(strcmp(e_binary, "01001000011000011101000010100100") == 0);
    assert(strcmp(inf_binn, "01111111100000000000000000000000") == 0);
    assert(strcmp(nan_binn, "01111111110000000000000000000000") == 0);
    assert(strcmp(ninf_bin, "11111111100000000000000000000000") == 0);

    free(a_binary);
    free(b_binary);
    free(c_binary);
    free(d_binary);
    free(inf_binn);
    free(nan_binn);
    free(ninf_bin);

    print_string("Double tests:");
    a_binary = malloc(65 * sizeof(char));
    b_binary = malloc(65 * sizeof(char));
    c_binary = malloc(65 * sizeof(char));
    d_binary = malloc(65 * sizeof(char));
    e_binary = malloc(65 * sizeof(char));
    inf_binn = malloc(65 * sizeof(char));
    nan_binn = malloc(65 * sizeof(char));
    ninf_bin = malloc(65 * sizeof(char));

    double_to_binary(a, a_binary, DOUBLE);
    double_to_binary(b, b_binary, DOUBLE);
    double_to_binary(c, c_binary, DOUBLE);
    double_to_binary(d, d_binary, DOUBLE);
    double_to_binary(e, e_binary, DOUBLE);
    double_to_binary(INFINITY, inf_binn, DOUBLE);
    double_to_binary(NAN, nan_binn, DOUBLE);
    double_to_binary(-INFINITY, ninf_bin, DOUBLE);

    print_string(a_binary);
    print_string(b_binary);
    print_string(c_binary);
    print_string(d_binary);
    print_string(e_binary);
    print_string(inf_binn);
    print_string(nan_binn);
    print_string(ninf_bin);

    assert(strcmp(a_binary, "0000000000000000000000000000000000000000000000000000000000000000") == 0);
    assert(strcmp(b_binary, "0011111111110000000000000000000000000000000000000000000000000000") == 0);
    assert(strcmp(c_binary, "0100000010010011010010100100010101101101010111001111101010101100") == 0);
    assert(strcmp(d_binary, "1100000010010011010010100100010101101101010111001111101010101100") == 0);
    assert(strcmp(e_binary, "0100000100001100001110100001010010001010110110101011100111110101") == 0);
    assert(strcmp(inf_binn, "0111111111110000000000000000000000000000000000000000000000000000") == 0);
    assert(strcmp(nan_binn, "0111111111111000000000000000000000000000000000000000000000000000") == 0);
    assert(strcmp(ninf_bin, "1111111111110000000000000000000000000000000000000000000000000000") == 0);
}
