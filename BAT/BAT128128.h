#include <stdio.h>
#include <stdint.h>

typedef uint64_t u64;
#define SWAP(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y))

u64 ROTL(u64 x, int shift){
    return (x << shift) | (x >> (64 - shift));
}

u64 G0(u64 x){
    x ^= (x >> 3) & (x >> 2) & 0x1111111111111111;
    x ^= (x << 3) & (x << 2) & 0x8888888888888888;
    return x;
}

u64 G1(u64 x){
    x ^= (x >> 1) & (x << 1) & 0x4444444444444444;
    x ^= (x << 1) & (x >> 1) & 0x2222222222222222;
    return x;
}

u64 P(u64 x){
    return ROTL(x & 0x00FF00FF00FF00FF, 56) | ROTL(x & 0xFF00FF00FF00FF00, 24);
}

void Round(const u64 Pt[], u64 Ct[], const u64 Rk[], int CryptRound){
    u64 x = Pt[1], y = Pt[0];
    for(int r = 0; r < CryptRound; r++) {
        y ^= P(G0(x) ^ G1(ROTL(x, 4))) ^ Rk[r];
        SWAP(x, y);
    }
    Ct[1] = y, Ct[0] = x;
}

u64 A16x3(u64 x){
    for(int i = 0; i < 3; i++){
        x = ROTL(x, 60);
        u64 t = x >> 56 & 0xF;
        x ^= (((t << 1) | (t >> 3)) << 60) ^ ((t << 3 & 0xF) << 56);
    }
    return x;
}

void KeySchedule(const u64 Mk[], u64 Rk[], int CryptRound, int Dec){
    Rk[1] = Mk[1], Rk[0] = Mk[0];
    for(int r = 0; r < CryptRound - 2; r++)
        Rk[r + 2] = A16x3(Rk[r + 1]) ^ Rk[r] ^ (r + 1);
    if(Dec == 1){
        for(int r = 0; r < (int)(CryptRound / 2); r++)
            SWAP(Rk[r], Rk[CryptRound - r - 1]);
    }
}
