#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
#define ROUNDS64128 44

#define SWAP(x, y) (x ^= y, y ^= x, x ^= y)
#define ROTL32(x, r) (((x) << (r)) | (x >> (32 - (r))))
#define ROTR32(x, r) (((x) >> (r)) | (x << (32 - (r))))

#define F32(x) ((ROTL32(x, 1) & ROTL32(x, 8)) ^ ROTL32(x, 2))
#define R32x1(x, y, rk) (y ^= F32(x), y ^= rk, SWAP(x, y))

void Encrypt_Round(u32 Pt[], u32 Ct[], u32 Rk[], int CryptRound){
    Ct[0] = Pt[0], Ct[1] = Pt[1];
    for(int i = 0; i < CryptRound; i += 1){
        R32x1(Ct[1], Ct[0], Rk[i]);
    }
}

void Decrypt_Round(u32 Pt[], u32 Ct[], u32 Rk[], int CryptRound){
    Pt[0] = Ct[0], Pt[1] = Ct[1];
    for(int i = CryptRound - 1; i >= 0; i -= 1){
        R32x1(Pt[0], Pt[1], Rk[i]);
    }
}

void KeySchedule(u32 K[], u32 Rk[]){
    u32 i, c = 0xfffffffc;
    u64 z = 0xfc2ce51207a635dbLL;
    Rk[0] = K[0];
    Rk[1] = K[1];
    Rk[2] = K[2];
    Rk[3] = K[3];
    for(i = 4; i < ROUNDS64128; i++){
        Rk[i] = c ^ (z & 1) ^ Rk[i-4] ^ \
            ROTR32(Rk[i-1], 3) ^ Rk[i-3] ^ ROTR32(Rk[i-1], 4) ^ \
            ROTR32(Rk[i-3], 1);
            z >>= 1;
    }
}
