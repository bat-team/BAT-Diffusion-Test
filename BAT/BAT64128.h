#include <stdio.h>
#include <stdint.h>

typedef uint32_t u32;
#define SWAP(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y))

u32 ROTL(u32 x, int shift){
    return (x << shift) | (x >> (32 - shift));
}

u32 G0(u32 x){
    x ^= (x >> 3) & (x >> 2) & 0x11111111;
    x ^= (x << 3) & (x << 2) & 0x88888888;
    return x;
}

u32 G1(u32 x){
    x ^= (x >> 1) & (x << 1) & 0x44444444;
    x ^= (x << 1) & (x >> 1) & 0x22222222;
    return x;
}

u32 P(u32 x){
    return ROTL(x & 0x0F0F0F0F, 28) | ROTL(x & 0xF0F0F0F0, 12);
}

void Round(const u32 Pt[], u32 Ct[], const u32 Rk[], int CryptRound){
    u32 x = Pt[1], y = Pt[0];
    for(int r = 0; r < CryptRound; r++) {
        y ^= P(G0(x) ^ G1(ROTL(x, 4))) ^ Rk[r];
        SWAP(x, y);
    }
    Ct[1] = y, Ct[0] = x;
}

u32 A8x3(u32 x){
    for(int i = 0; i < 3; i++){
        x = ROTL(x, 28);
        u32 t = x >> 24 & 0xF;
        x ^= (((t << 1) | (t >> 3)) << 28) ^ ((t << 3 & 0xF) << 24);
    }
    return x;
}

void KeySchedule(const u32 Mk[], u32 Rk[], int CryptRound, int Dec){
    Rk[3] = Mk[3], Rk[2] = Mk[2], Rk[1] = Mk[1], Rk[0] = Mk[0];
    for(int r = 0; r < CryptRound - 4; r++)
        Rk[r + 4] = A8x3(Rk[r + 3]) ^ Rk[r] ^ (r + 1);
    if(Dec == 1){
        for(int r = 0; r < (int)(CryptRound / 2); r++)
            SWAP(Rk[r], Rk[CryptRound - r - 1]);
    }
}
