#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
#define ROUNDS128128 68

#define SWAP(x, y) (x ^= y, y ^= x, x ^= y)
#define ROTL64(x, r) (((x) << (r)) | (x >> (64 - (r))))
#define ROTR64(x, r) (((x) >> (r)) | (x << (64 - (r))))

#define F64(x) ((ROTL64(x, 1) & ROTL64(x, 8)) ^ ROTL64(x, 2))
#define R64x1(x, y, rk) (y ^= F64(x), y ^= rk, SWAP(x, y))

void Encrypt_Round(u64 Pt[], u64 Ct[], u64 Rk[], int CryptRound){
    Ct[0] = Pt[0], Ct[1] = Pt[1];
    for(int i = 0; i < CryptRound; i += 1){
        R64x1(Ct[1], Ct[0], Rk[i]);
    }
}

void Decrypt_Round(u64 Pt[], u64 Ct[], u64 Rk[], int CryptRound){
    Pt[0] = Ct[0], Pt[1] = Ct[1];
    for(int i = CryptRound - 1; i >= 0; i -= 1){
        R64x1(Pt[0], Pt[1], Rk[i]);
    }
}

void KeySchedule(u64 K[], u64 Rk[]){
    u64 i, B = K[1], A = K[0];
    u64 c = 0xfffffffffffffffcLL, z = 0x7369f885192c0ef5LL;
    for(i = 0; i < 64;){
        Rk[i++] = A; A ^= c ^ (z&1) ^ ROTR64(B,3) ^ ROTR64(B,4); z>>=1;
        Rk[i++] = B; B ^= c ^ (z&1) ^ ROTR64(A,3) ^ ROTR64(A,4); z>>=1;
    }
    Rk[64] = A; A ^= c ^ 1 ^ ROTR64(B,3) ^ ROTR64(B,4);
    Rk[65] = B; B ^= c ^ 0 ^ ROTR64(A,3) ^ ROTR64(A,4);
    Rk[66] = A; Rk[67]=B;
}
