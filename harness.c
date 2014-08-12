#include <stdint.h>
#include <stdio.h>

#include "data.h" // scrambler, base25

const char base25_to_asc[] = "246789BCDEFGHJKMNPRTVWXYZ";

typedef struct {
    uint16_t n_79_64;
    uint32_t n_63_32;
    uint32_t n_31_0;
} cdkey_signature;

void validate_cdkey(const char *key, int32_t *a2, int *a3, cdkey_signature *cdkeysig);
int32_t convert_to_base_5_scramble(const char *key, char *results);
uint32_t base5_to_base2(int32_t four, int five, uint32_t *accum_array, uint32_t *accum_array_, uint32_t char_base5);
void decrypt(uint32_t *big_int);
uint32_t entropy_reducer(int32_t a1, uint32_t *big_int);

int32_t main(int argc, char **argv) {
    int32_t blah, blah2;
    cdkey_signature cdkeysig;
    char cdkey[27];
    cdkey[26] = '\0';
    
    srand(time(NULL));
    int count = 0, i, j;
    for (i = 0; i < 10000000; i++) {
        for (j = 0; j < 26; j++) {
            cdkey[j] = base25_to_asc[rand() % 25];
        }
        validate_cdkey(cdkey, &blah, &blah2, &cdkeysig);
        if (blah == 0x17) {
            printf("found: %s\n", cdkey);
            count++;
        } else {
            //printf("failure: %s: %u\n", cdkey, blah);
        }
    }
    printf("count: %d\n", count);
}

void validate_cdkey(const char *key, int32_t *a2, int *a3, cdkey_signature *cdkeysig)
{
  int32_t v4; // esi@3
  int32_t v5; // ecx@5
  uint16_t n_15_0; // ax@5
  uint16_t n_31_16; // cx@5
  int32_t v8; // eax@5
  int32_t v9; // ecx@5
  uint32_t big_int[4]; // [sp+0h] [bp-44h]@3
  uint8_t base5_52[52]; // [sp+10h] [bp-34h]@3

  if ( key && cdkeysig )
  {
    convert_to_base_5_scramble(key, base5_52);
    big_int[1] = 0;
    big_int[2] = 0;
    v4 = 52;
    big_int[0] = 0;
    big_int[3] = 0;
    do
      base5_to_base2(4, 5, big_int, big_int, base5_52[v4-- - 1]);
    while ( v4 > 0 );
    decrypt(big_int);
    entropy_reducer(v5, (int32_t *)big_int);
    n_15_0 = (uint16_t)(big_int[0]);
    *a2 = big_int[0] >> 10;
    n_31_16 = (uint16_t)(big_int[1]);
    *a3 = (big_int[1] >> 16) | ((n_15_0 & 0x3FF) << 16);
    v8 = big_int[2];
    cdkeysig->n_79_64 = n_31_16;
    v9 = big_int[3];
    cdkeysig->n_63_32 = v8;
    cdkeysig->n_31_0 = v9;
  }
}

int32_t convert_to_base_5_scramble(const char *key, char *results)
{
  uint32_t resultidx2; // esi@1
  uint32_t idx; // edi@1
  uint32_t resultidx1; // ecx@2
  uint32_t quot; // eax@2
  uint16_t rem; // dx@2

  resultidx2 = 33;
  idx = 0;
  do
  {
    resultidx1 = (resultidx2 + 1973) % 52;
    resultidx2 = (resultidx1 + 1973) % 52;
    quot = base25[(uint8_t)key[idx]] / 5;
    rem = base25[(uint8_t)key[idx++]] % 5;
    results[resultidx1] = quot;
    results[resultidx2] = rem;
  }
  while ( idx < 26 );
  return quot;
}


uint32_t base5_to_base2(int32_t four, int five, uint32_t *accum_array, uint32_t *accum_array_, uint32_t char_base5)
{
  int32_t five_; // ebx@1
  int32_t three; // eax@1
  uint32_t char_base5_; // ebp@1
  uint32_t *ptr; // esi@1
  uint32_t *ptr_; // edi@1
  uint32_t v10[2]; // qax@2

  five_ = five;
  three = four - 1;
  char_base5_ = char_base5;
  ptr = &accum_array[three];
  ptr_ = &accum_array_[three];
  do
  {
    *(uint64_t *)v10 = char_base5_ + (uint32_t)five_ * (uint64_t)*ptr;
    *ptr_ = v10[0];
    char_base5_ = v10[1];
    --ptr;
    --ptr_;
    --four;
  }
  while ( four );
  return v10[1];
}

void decrypt(uint32_t *big_int)
{
  uint32_t idx; // esi@1 MAPDST
  int32_t idx16; // edi@1
  char v3; // dl@2 MAPDST
  uint32_t big_int_idx; // ebx@2 MAPDST
  uint8_t nibble[4]; // eax@2
  uint32_t idx2; // ebp@2
  int32_t idx_1; // ebp@5
  uint32_t idx3_; // ecx@5
  int32_t v9; // esi@8
  int32_t v10; // ebx@8
  int32_t idx3; // [sp+10h] [bp-Ch]@5

  idx = 29;
  idx = 29;
  idx16 = 464;
  do
  {
    v3 = 4 * (idx & 7);
    big_int_idx = idx >> 3;
    *(uint32_t *)nibble = ((15 << 4 * (idx & 7)) & big_int[3 - (idx >> 3)]) >> v3;
    v3 = 4 * (idx & 7);
    big_int_idx = idx >> 3;
    idx2 = 29;
    if ( idx16 < 464 )                          // not on first loop iteration
    {
      do
      {
        nibble[0] = *(&scrambler[0][*(&scrambler[0][nibble[0]] + idx16) ^ (uint8_t)(((15 << 4 * (idx2 & 7)) & big_int[3 - (idx2 >> 3)]) >> 4 * (idx2 & 7))]
                    + idx16);
        --idx2;
      }
      while ( (int32_t)idx2 > (int32_t)idx );
    }
    idx_1 = idx - 1;
    idx3_ = idx - 1;
    idx3 = idx - 1;
    if ( ((idx - 1) & 0x80000000u) == 0 )
    {
      do
      {
        nibble[0] = *(&scrambler[0][*(&scrambler[0][nibble[0]] + idx16) ^ (uint8_t)(((15 << 4 * (idx3_ & 7)) & big_int[3 - (idx3_ >> 3)]) >> 4 * (idx3_ & 7))]
                    + idx16);
        idx3_ = idx3-- - 1;
      }
      while ( idx3 >= 0 );
      idx_1 = idx - 1;
    }
    v9 = 3 - big_int_idx;
    v10 = (*(&scrambler[0][nibble[0]] + idx16) & 0xF) << v3;
    idx16 -= 16;
    big_int[v9] = big_int[v9] & ~(15 << v3) | v10;
    idx = idx_1;
    idx = idx_1;
  }
  while ( idx16 >= 0 );
}

uint32_t entropy_reducer(int32_t a1, uint32_t *big_int)
{
  uint32_t bit1; // eax@1
  uint32_t old; // esi@1
  char bit1idx; // cl@2
  uint32_t n_i; // ebx@2
  int32_t picker; // edi@2
  uint32_t v7; // eax@2
  char bit2; // cl@4
  uint32_t v9; // ebx@4
  int32_t v10; // edi@4
  uint32_t v11; // eax@4
  char bit3; // cl@6
  uint32_t v13; // ebx@6
  int32_t v14; // edi@6
  uint32_t v15; // eax@6
  char bit4; // cl@8
  uint32_t v17; // ebx@8
  int32_t v18; // edi@8
  uint32_t v19; // eax@8
  char v20; // cl@10
  uint32_t v21; // ebx@10
  int32_t v22; // edi@10
  uint32_t v23; // eax@10
  char v24; // cl@12
  uint32_t v25; // ebx@12
  int32_t v26; // edi@12

  uint32_t old_120[4];
  old_120[0] = big_int[0];
  old_120[1] = big_int[1];
  old_120[2] = big_int[2];
  old_120[3] = big_int[3];

  bit1 = 0;
  old = 2;
  do
  {
    bit1idx = bit1 & 0x1F;
    n_i = old_120[3 - (bit1 >> 5)];
    picker = 1 << (bit1 & 0x1F);
    v7 = bit1 + 11;
    big_int[3 - ((old - 2) >> 5)] = big_int[3 - ((old - 2) >> 5)] & ~(1 << ((old - 2) & 0x1F)) | ((((picker & n_i) >> bit1idx) & 1) << ((old - 2) & 0x1F));
    if ( v7 >= 120 ) // 47d57d
      v7 = v7 - 120 + (((v7 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    bit2 = v7 & 0x1F;
    v9 = old_120[3 - (v7 >> 5)];
    v10 = 1 << (v7 & 0x1F);
    v11 = v7 + 11;
    big_int[3 - ((old - 1) >> 5)] = big_int[3 - ((old - 1) >> 5)] & ~(1 << ((old - 1) & 0x1F)) | ((((v10 & v9) >> bit2) & 1) << ((old - 1) & 0x1F));
    if ( v11 >= 120 ) // 47d5e7
      v11 = v11 - 120 + (((v11 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    bit3 = v11 & 0x1F;
    v13 = old_120[3 - (v11 >> 5)];
    v14 = 1 << (v11 & 0x1F);
    v15 = v11 + 11;
    big_int[3 - (old >> 5)] = big_int[3 - (old >> 5)] & ~(1 << (old & 0x1F)) | ((((v14 & v13) >> bit3) & 1) << (old & 0x1F));
    if ( v15 >= 120 ) // 47d650
      v15 = v15 - 120 + (((v15 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    bit4 = v15 & 0x1F;
    v17 = old_120[3 - (v15 >> 5)];
    v18 = 1 << (v15 & 0x1F);
    v19 = v15 + 11;
    big_int[3 - ((old + 1) >> 5)] = big_int[3 - ((old + 1) >> 5)] & ~(1 << ((old + 1) & 0x1F)) | ((((v18 & v17) >> bit4) & 1) << ((old + 1) & 0x1F));
    if ( v19 >= 120 ) // 47d6ba
      v19 = v19 - 120 + (((v19 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    v20 = v19 & 0x1F;
    v21 = old_120[3 - (v19 >> 5)];
    v22 = 1 << (v19 & 0x1F);
    v23 = v19 + 11;
    big_int[3 - ((old + 2) >> 5)] = big_int[3 - ((old + 2) >> 5)] & ~(1 << ((old + 2) & 0x1F)) | ((((v22 & v21) >> v20) & 1) << ((old + 2) & 0x1F));
    if ( v23 >= 120 ) // 47d724
      v23 = v23 - 120 + (((v23 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    v24 = v23 & 0x1F;
    v25 = old_120[3 - (v23 >> 5)];
    v26 = 1 << (v23 & 0x1F);
    bit1 = v23 + 11;
    big_int[3 - ((old + 3) >> 5)] = big_int[3 - ((old + 3) >> 5)] & ~(1 << ((old + 3) & 0x1F)) | ((((v26 & v25) >> v24) & 1) << ((old + 3) & 0x1F));
    if ( bit1 >= 120 ) // 47d78e
      bit1 = bit1 - 120 + (((bit1 - 120) & 0x80000000u) != 0 ? 0xB : 0);
    old += 6;
  }
  while ( old - 2 < 120 );
  return bit1;
}
