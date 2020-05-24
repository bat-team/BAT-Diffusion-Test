#include "simon64128.h"

u32 Get_Random_u32(){
    return (u16)rand() ^ ((u32)rand() << 16);
}

u64 Get_Random_u64(){
    return Get_Random_u32() ^ ((u64)Get_Random_u32() << 32);
}

u32 Bit_Flip_u32(u32 x, int position){
    x ^= (u32)1 << position;
    return x;
}

u64 Bit_Flip_u64(u64 x, int position){
    x ^= (u64)1 << position;
    return x;
}

int Check_Bit(int position, int test_rounds){
    int i, test_set = 1000;
    u32 diff_A = 0, diff_B = 0;
    for(i = 0; i < test_set; i++){
        u32 Pt0[2], Pt1[2], Ct0[2], Ct1[2], Mk[4], Rk[ROUNDS64128];
        Pt0[0] = Get_Random_u32(), Pt0[1] = Get_Random_u32();
        Pt1[0] = Pt0[0], Pt1[1] = Pt0[1];
        Mk[0] = Get_Random_u32(), Mk[1] = Get_Random_u32();
        Mk[2] = Get_Random_u32(), Mk[3] = Get_Random_u32();

        KeySchedule(Mk, Rk);
        Encrypt_Round(Pt0, Ct0, Rk, test_rounds);

        if(position < 32){
            Pt1[0] = Bit_Flip_u32(Pt0[0], position);
        }
        else{
            Pt1[1] = Bit_Flip_u32(Pt0[1], position - 32);
        }

        Encrypt_Round(Pt1, Ct1, Rk, test_rounds);

        u32 d_a, d_b;
        d_a = Ct1[0] ^ Ct0[0];
        d_b = Ct1[1] ^ Ct0[1];
        diff_A |= d_a;
        diff_B |= d_b;
    }
    if(diff_A == 0xFFFFFFFF && diff_B == 0xFFFFFFFF){
        return 1;
    }
    return 0;
}

void Fulldiffusion_test(int test_rounds){
    int r;
    for(r = 1; r <= test_rounds; r ++){
        int counter = 0;
        int p = 0;
        for(p = 0; p < 64; p++){
            counter += Check_Bit(p, r);
        }
        printf("Test %2d rounds: with %3d bits achieving full diffusion"
               "\n", r, counter);
    }
}

int main(){
    u32 Pt[2] = {0x20646e75, 0x656b696c}, Ct[2];
    /* Rk0 || Rk1 || Rk2 || Rk3 */
    u32 Mk[4] = {0x03020100, 0x0b0a0908, 0x13121110, 0x1b1a1918};
    u32 Rk[ROUNDS64128];

    printf("Pt: 0x%08X 0x%08X\n", Pt[1], Pt[0]);
    printf("Mk: 0x%08X 0x%08X 0x%08X 0x%08X\n",
            Mk[3],Mk[2],Mk[1],Mk[0]);
    printf("Process Enc\n");
    KeySchedule(Mk, Rk);
    Encrypt_Round(Pt, Ct, Rk, ROUNDS64128);
    printf("Ct: 0x%08X 0x%08X\n", Ct[1], Ct[0]);
    printf("Process Dec\n");
    Decrypt_Round(Ct, Pt, Rk, ROUNDS64128);
    printf("Pt: 0x%08X 0x%08X\n", Pt[1], Pt[0]);
    printf("\n");

    srand(time(NULL));
    Fulldiffusion_test(10);

    return 0;
}
