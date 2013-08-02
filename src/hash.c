#include "hash.h"

#include <stdio.h>
static Integer32 constant[] = {
    0X428A2F98,
    0X71374491,
    0XB5C0FBCF,
    0XE9B5DBA5,
    0X3956C25B,
    0X59F111F1,
    0X923F82A4,
    0XAB1C5ED5,
    0XD807AA98,
    0X12835B01,
    0X243185BE,
    0X550C7DC3,
    0X72BE5D74,
    0X80DEB1FE,
    0X9BDC06A7,
    0XC19BF174,
    0XE49B69C1,
    0XEFBE4786,
    0X0FC19DC6,
    0X240CA1CC,
    0X2DE92C6F,
    0X4A7484AA,
    0X5CB0A9DC,
    0X76F988DA,
    0X983E5152,
    0XA831C66D,
    0XB00327C8,
    0XBF597FC7,
    0XC6E00BF3,
    0XD5A79147,
    0X06CA6351,
    0X14292967,
    0X27B70A85,
    0X2E1B2138,
    0X4D2C6DFC,
    0X53380D13,
    0X650A7354,
    0X766A0ABB,
    0X81C2C92E,
    0X92722C85,
    0XA2BFE8A1,
    0XA81A664B,
    0XC24B8B70,
    0XC76C51A3,
    0XD192E819,
    0XD6990624,
    0XF40E3585,
    0X106AA070,
    0X19A4C116,
    0X1E376C08,
    0X2748774C,
    0X34B0BCB5,
    0X391C0CB3,
    0X4ED8AA4A,
    0X5B9CCA4F,
    0X682E6FF3,
    0X748F82EE,
    0X78A5636F,
    0X84C87814,
    0X8CC70208,
    0X90BEFFFA,
    0XA4506CEB,
    0XBEF9A3F7,
    0XC67178F2
};

static Integer32 RotateWord(Integer32 value, Integer8 count) {
    return value >> count | value << 32 - count;
}

static Integer32 DecodeWord(Byte *message, Integer32 index) {
    Byte *byte = message + sizeof(Integer32) * index;
    Integer32 value[] = {byte[0], byte[1], byte[2], byte[3]};
    return value[0] << 24 | value[1] << 16 | value[2] << 8 | value[3];
}

static void UpdateHash(Integer32 *hash, Byte *block) {
    Integer32 schedule[64] = {
        DecodeWord(block, 0),
        DecodeWord(block, 1),
        DecodeWord(block, 2),
        DecodeWord(block, 3),
        DecodeWord(block, 4),
        DecodeWord(block, 5),
        DecodeWord(block, 6),
        DecodeWord(block, 7),
        DecodeWord(block, 8),
        DecodeWord(block, 9),
        DecodeWord(block, 10),
        DecodeWord(block, 11),
        DecodeWord(block, 12),
        DecodeWord(block, 13),
        DecodeWord(block, 14),
        DecodeWord(block, 15)
    };
    for (Integer8 index = 16; index < 64; index += 1) {
        Integer32 lower = schedule[index - 15];
        Integer32 upper = schedule[index - 2];
        Integer32 sigma_0 = RotateWord(lower, 7) ^ RotateWord(lower, 18) ^ (lower >> 3);
        Integer32 sigma_1 = RotateWord(upper, 17) ^ RotateWord(upper, 19) ^ (upper >> 10);
        schedule[index] = schedule[index - 16] + sigma_0 + schedule[index - 7] + sigma_1;
    }
    Integer32 a = hash[0];
    Integer32 b = hash[1];
    Integer32 c = hash[2];
    Integer32 d = hash[3];
    Integer32 e = hash[4];
    Integer32 f = hash[5];
    Integer32 g = hash[6];
    Integer32 h = hash[7];
    for (Integer8 index = 0; index < 64; index += 1) {
        Integer32 sum_1 = RotateWord(e, 6) ^ RotateWord(e, 11) ^ RotateWord(e, 25);
        Integer32 sum_0 = RotateWord(a, 2) ^ RotateWord(a, 13) ^ RotateWord(a, 22);
        Integer32 choose = (e & f) ^ (~e & g);
        Integer32 majority = (a & b) ^ (a & c) ^ (b & c);
        Integer32 temp_1 = h + sum_1 + choose + constant[index] + schedule[index];
        Integer32 temp_2 = sum_0 + majority;
        h = g;
        g = f;
        f = e;
        e = d + temp_1;
        d = c;
        c = b;
        b = a;
        a = temp_1 + temp_2;
    }
    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}

static void InitPadding(Byte *padding, Byte *block, Integer32 length, Integer64 bits) {
    MemoryCopy(block, padding, length);
    padding[length] = 0X80;
    padding[56] = bits >> 56;
    padding[57] = bits >> 48 & 0XFF;
    padding[58] = bits >> 40 & 0XFF;
    padding[59] = bits >> 32 & 0XFF;
    padding[60] = bits >> 24 & 0XFF;
    padding[61] = bits >> 16 & 0XFF;
    padding[62] = bits >> 8 & 0XFF;
    padding[63] = bits & 0XFF;
}

Bool HashEqualSHA256(Byte *message, Integer32 length, Byte *sample) {
    Integer32 hash[] = {0X6A09E667, 0XBB67AE85, 0X3C6EF372, 0XA54FF53A, 0X510E527F, 0X9B05688C, 0X1F83D9AB, 0X5BE0CD19};
    Byte padding[64] = {0X00};
    InitPadding(padding, message, length, length * 8);
    UpdateHash(hash, padding);
    return hash[0] == DecodeWord(sample, 0) &&
           hash[1] == DecodeWord(sample, 1) &&
           hash[2] == DecodeWord(sample, 2) &&
           hash[3] == DecodeWord(sample, 3) &&
           hash[4] == DecodeWord(sample, 4) &&
           hash[5] == DecodeWord(sample, 5) &&
           hash[6] == DecodeWord(sample, 6) &&
           hash[7] == DecodeWord(sample, 7);
}
