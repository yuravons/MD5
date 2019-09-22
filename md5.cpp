#include "md5.h"

ui MD5::F(ui B, ui C, ui D) {
    return (B & C) | (~B & D);
}

ui MD5::G(ui B, ui C, ui D) {
    return (B & D) | (C & ~D);
}

ui MD5::H(ui B, ui C, ui D) {
    return B ^ C ^ D;
}

ui MD5::I(ui B, ui C, ui D) {
    return C ^ (B | ~D);
}

ui MD5::rotate_left(ui value, ui count) {
    return (value << count) | (value >> (32 - count));
}

void MD5::FF(ui& A, ui B, ui C, ui D, ui x, ui count, ui t) {
    A = rotate_left(A + F(B, C, D) + x + t, count) + B;
}

void MD5::GG(ui& A, ui B, ui C, ui D, ui x, ui count, ui t) {
    A = rotate_left(A + G(B, C, D) + x + t, count) + B;
}

void MD5::HH(ui& A, ui B, ui C, ui D, ui x, ui count, ui t) {
    A = rotate_left(A + H(B, C, D) + x + t, count) + B;
}

void MD5::II(ui& A, ui B, ui C, ui D, ui x, ui count, ui t) {
    A = rotate_left(A + I(B, C, D) + x + t, count) + B;
}

std::string MD5::result() const
{
    char buf[33];
    for (int i = 0; i < 16; i++)
        sprintf(buf + i * 2, "%02x", results[i]);
    buf[32] = 0;

    return std::string(buf);
}

MD5::MD5(string text)
{
    update((const unsigned char*)text.c_str(), text.length());
    convert_128();
}

void MD5::compression(const uc block[64])
{
    ui A = registers[0], B = registers[1], C = registers[2], D = registers[3], x[16];
    for (unsigned int i = 0, j = 0; j < 64; i++, j += 4)
        x[i] = ((ui)block[j]) | (((ui)block[j + 1]) << 8) | (((ui)block[j + 2]) << 16) | (((ui)block[j + 3]) << 24);
    int i = 0;
    /* RounD 1 */
    FF(A, B, C, D, x[0], 7, T[i++]);
    FF(D, A, B, C, x[1], 12, T[i++]);
    FF(C, D, A, B, x[2], 17, T[i++]);
    FF(B, C, D, A, x[3], 22, T[i++]);
    FF(A, B, C, D, x[4], 7, T[i++]);
    FF(D, A, B, C, x[5], 12, T[i++]);
    FF(C, D, A, B, x[6], 17, T[i++]);
    FF(B, C, D, A, x[7], 22, T[i++]);
    FF(A, B, C, D, x[8], 7, T[i++]);
    FF(D, A, B, C, x[9], 12, T[i++]);
    FF(C, D, A, B, x[10], 17, T[i++]);
    FF(B, C, D, A, x[11], 22, T[i++]);
    FF(A, B, C, D, x[12], 7, T[i++]);
    FF(D, A, B, C, x[13], 12, T[i++]);
    FF(C, D, A, B, x[14], 17, T[i++]);
    FF(B, C, D, A, x[15], 22, T[i++]);

    /* RounD 2 */
    GG(A, B, C, D, x[1], 5, T[i++]);
    GG(D, A, B, C, x[6], 9, T[i++]);
    GG(C, D, A, B, x[11], 14, T[i++]);
    GG(B, C, D, A, x[0], 20, T[i++]);
    GG(A, B, C, D, x[5], 5, T[i++]);
    GG(D, A, B, C, x[10], 9, T[i++]);
    GG(C, D, A, B, x[15], 14, T[i++]);
    GG(B, C, D, A, x[4], 20, T[i++]);
    GG(A, B, C, D, x[9], 5, T[i++]);
    GG(D, A, B, C, x[14], 9, T[i++]);
    GG(C, D, A, B, x[3], 14, T[i++]);
    GG(B, C, D, A, x[8], 20, T[i++]);
    GG(A, B, C, D, x[13], 5, T[i++]);
    GG(D, A, B, C, x[2], 9, T[i++]);
    GG(C, D, A, B, x[7], 14, T[i++]);
    GG(B, C, D, A, x[12], 20, T[i++]);

    /* RounD 3 */
    HH(A, B, C, D, x[5], 4, T[i++]);
    HH(D, A, B, C, x[8], 11, T[i++]);
    HH(C, D, A, B, x[11], 16, T[i++]);
    HH(B, C, D, A, x[14], 23, T[i++]);
    HH(A, B, C, D, x[1], 4, T[i++]);
    HH(D, A, B, C, x[4], 11, T[i++]);
    HH(C, D, A, B, x[7], 16, T[i++]);
    HH(B, C, D, A, x[10], 23, T[i++]);
    HH(A, B, C, D, x[13], 4, T[i++]);
    HH(D, A, B, C, x[0], 11, T[i++]);
    HH(C, D, A, B, x[3], 16, T[i++]);
    HH(B, C, D, A, x[6], 23, T[i++]);
    HH(A, B, C, D, x[9], 4, T[i++]);
    HH(D, A, B, C, x[12], 11, T[i++]);
    HH(C, D, A, B, x[15], 16, T[i++]);
    HH(B, C, D, A, x[2], 23, T[i++]);

    /* RounD 4 */
    II(A, B, C, D, x[0], 6, T[i++]);
    II(D, A, B, C, x[7], 10, T[i++]);
    II(C, D, A, B, x[14], 15, T[i++]);
    II(B, C, D, A, x[5], 21, T[i++]);
    II(A, B, C, D, x[12], 6, T[i++]);
    II(D, A, B, C, x[3], 10, T[i++]);
    II(C, D, A, B, x[10], 15, T[i++]);
    II(B, C, D, A, x[1], 21, T[i++]);
    II(A, B, C, D, x[8], 6, T[i++]);
    II(D, A, B, C, x[15], 10, T[i++]);
    II(C, D, A, B, x[6], 15, T[i++]);
    II(B, C, D, A, x[13], 21, T[i++]);
    II(A, B, C, D, x[4], 6, T[i++]);
    II(D, A, B, C, x[11], 10, T[i++]);
    II(C, D, A, B, x[2], 15, T[i++]);
    II(B, C, D, A, x[9], 21, T[i++]);

    registers[0] += A;
    registers[1] += B;
    registers[2] += C;
    registers[3] += D;

    memset(x, 0, sizeof x);
}

void MD5::update(const unsigned char input[], ui length)
{
    ui index = counter[0] / 8 % 64;

    if ((counter[0] += (length << 3)) < (length << 3))
        counter[1]++;
    counter[1] += (length >> 29);
    ui firstpart = 64 - index;

    ui i;
    if (length >= firstpart)
    {
        memcpy(&tmp_buf[index], input, firstpart);
        compression(tmp_buf);
        for (i = firstpart; i + 64 <= length; i += 64)
            compression(&input[i]);

        index = 0;
    }
    else
        i = 0;
    memcpy(&tmp_buf[index], &input[i], length - i);
}

MD5& MD5::convert_128()
{
    static unsigned char padding[64] = {
      0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    unsigned char bits[8];

    for (ui i = 0, j = 0; j < 8; i++, j += 4) {
        bits[j] = counter[i] & 0xff;
        bits[j + 1] = (counter[i] >> 8) & 0xff;
        bits[j + 2] = (counter[i] >> 16) & 0xff;
        bits[j + 3] = (counter[i] >> 24) & 0xff;
    }

    ui index = counter[0] / 8 % 64;
    ui padLen = (index < 56) ? (56 - index) : (120 - index);
    update(padding, padLen);

    update(bits, 8);

    for (ui i = 0, j = 0; j < 16; i++, j += 4) {
        results[j] = registers[i] & 0xff;
        results[j + 1] = (registers[i] >> 8) & 0xff;
        results[j + 2] = (registers[i] >> 16) & 0xff;
        results[j + 3] = (registers[i] >> 24) & 0xff;
    }

    return *this;
}
