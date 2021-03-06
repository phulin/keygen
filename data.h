uint8_t base25[] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF,   0, 0xFF,   1, 0xFF,   2,   3,   4,   5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF,   6,   7,   8,   9, 0xA, 0xB, 0xC, 0xFF, 0xD, 0xE, 0xFF, 0xF, 0x10, 0xFF,
 0x11, 0xFF, 0x12, 0xFF, 0x13, 0xFF, 0x14, 0x15, 0x16, 0x17, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF,   6,   7,   8,   9, 0xA, 0xB, 0xC, 0xFF, 0xD, 0xE, 0xFF, 0xF, 0x10, 0xFF,
 0x11, 0xFF, 0x12, 0xFF, 0x13, 0xFF, 0x14, 0x15, 0x16, 0x17, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

uint8_t scrambler[30][16] = {
   9,   4,   7, 0xF, 0xD, 0xA,   3, 0xB,   1,   2, 0xC,   8,   6, 0xE,   5,   0,
   9, 0xB,   5,   4,   8, 0xF,   1, 0xE,   7,   0,   3,   2, 0xA,   6, 0xD, 0xC,
 0xC, 0xE,   1,   4,   9, 0xF, 0xA, 0xB, 0xD,   6,   0,   8,   7,   2,   5,   3,
 0xB,   2,   5, 0xE, 0xD,   3,   9,   0,   1, 0xF,   7, 0xC, 0xA,   6,   4,   8,
   6,   2,   4,   5, 0xB,   8, 0xC, 0xE, 0xD, 0xF,   7,   1, 0xA,   0,   3,   9,
   5,   4, 0xE, 0xC,   7,   6, 0xD, 0xA, 0xF,   2,   9,   1,   0, 0xB,   8,   3,
 0xC,   7,   8, 0xF, 0xB,   0,   5,   9, 0xD, 0xA,   6, 0xE,   2,   4,   3,   1,
   3, 0xA, 0xE,   8,   1, 0xB,   5,   4,   2, 0xF, 0xD, 0xC,   6,   7,   9,   0,
 0xC, 0xD,   1, 0xF,   8, 0xE,   5, 0xB,   3, 0xA,   9,   0,   7,   2,   4,   6,
 0xD, 0xA,   7, 0xE,   1,   6, 0xB,   8, 0xF, 0xC,   5,   2,   3,   0,   4,   9,
   3, 0xE,   7,   5, 0xB, 0xF,   8, 0xC,   1, 0xA,   4, 0xD,   0,   6,   9,   2,
 0xB,   6,   9,   4,   1,   8, 0xA, 0xD,   7, 0xE,   0, 0xC, 0xF,   2,   3,   5,
 0xC,   7,   8, 0xD,   3, 0xB,   0, 0xE,   6, 0xF,   9,   4, 0xA,   1,   5,   2,
 0xC,   6, 0xD,   9, 0xB,   0,   1,   2, 0xF,   7,   3,   4, 0xA, 0xE,   8,   5,
   3,   6,   1,   5, 0xB, 0xC,   8,   0, 0xF, 0xE,   9,   4,   7, 0xA, 0xD,   2,
 0xA,   7, 0xB, 0xF,   2,   8,   0, 0xD, 0xE, 0xC,   1,   6,   9,   3,   5,   4,
 0xA, 0xB, 0xD,   4,   3,   8,   5,   9,   1,   0, 0xF, 0xC,   7, 0xE,   2,   6,
 0xB,   4, 0xD, 0xF,   1,   6,   3, 0xE,   7, 0xA, 0xC,   8,   9,   2,   5,   0,
   9,   6,   7,   0,   1, 0xA, 0xD,   2,   3, 0xE, 0xF, 0xC,   5, 0xB,   4,   8,
 0xD, 0xE,   5,   6,   1,   9,   8, 0xC,   2, 0xF,   3,   7, 0xB,   4,   0, 0xA,
   9, 0xF,   4,   0,   1,   6, 0xA, 0xE,   2,   3,   7, 0xD,   5, 0xB,   8, 0xC,
   3, 0xE,   1, 0xA,   2, 0xC,   8,   4, 0xB,   7, 0xD,   0, 0xF,   6,   9,   5,
   7,   2, 0xC,   6, 0xA,   8, 0xB,   0, 0xF,   4,   3, 0xE,   9,   1, 0xD,   5,
 0xC,   4,   5,   9, 0xA,   2,   8, 0xD,   3, 0xF,   1, 0xE,   6,   7, 0xB,   0,
 0xA,   8, 0xE, 0xD,   9, 0xF,   3,   0,   4,   6,   1, 0xC,   7, 0xB,   2,   5,
   3, 0xC,   4, 0xA,   2, 0xF, 0xD, 0xE,   7,   0,   5,   8,   1,   6, 0xB,   9,
 0xA, 0xC,   1,   0,   9, 0xE, 0xD, 0xB,   3,   7, 0xF,   8,   5,   2,   4,   6,
 0xE, 0xA,   1,   8,   7,   6,   5, 0xC,   2, 0xF,   0, 0xD,   3, 0xB,   4,   9,
   3,   8, 0xE,   0,   7,   9, 0xF, 0xC,   1,   6, 0xD,   2,   5, 0xA, 0xB,   4,
   3, 0xA, 0xC,   4, 0xD, 0xB,   9, 0xE, 0xF,   6,   1,   7,   2,   0,   5,   8,
};
