/******************************************************************
 * S-BOX for Twister
 *
 *
 *******************************************************************/

#include <stdint.h>
#include <avr/pgmspace.h>

static const uint8_t twister_sbox[256] PROGMEM = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

  
  
/* Twister MDS matrix */
static const uint8_t twister_mds[8][8] PROGMEM = {
  {2, 1, 1, 5, 7, 8, 6, 1},
  {1, 2, 1, 1, 5, 7, 8, 6},
  {6, 1, 2, 1, 1, 5, 7, 8},
  {8, 6, 1, 2, 1, 1, 5, 7},
  {7, 8, 6, 1, 2, 1, 1, 5},
  {5, 7, 8, 6, 1, 2, 1, 1},
  {1, 5, 7, 8, 6, 1, 2, 1},
  {1, 1, 5, 7, 8, 6, 1, 2}
};
  
/*  
static const uint8_t twister_multab[8][256] PROGMEM = {
  {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
  },
  {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
    32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
    64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94,
    96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126,
    128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158,
    160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190,
    192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222,
    224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254,
    77, 79, 73, 75, 69, 71, 65, 67, 93, 95, 89, 91, 85, 87, 81, 83,
    109, 111, 105, 107, 101, 103, 97, 99, 125, 127, 121, 123, 117, 119, 113, 115,
    13, 15, 9, 11, 5, 7, 1, 3, 29, 31, 25, 27, 21, 23, 17, 19,
    45, 47, 41, 43, 37, 39, 33, 35, 61, 63, 57, 59, 53, 55, 49, 51,
    205, 207, 201, 203, 197, 199, 193, 195, 221, 223, 217, 219, 213, 215, 209, 211,
    237, 239, 233, 235, 229, 231, 225, 227, 253, 255, 249, 251, 245, 247, 241, 243,
    141, 143, 137, 139, 133, 135, 129, 131, 157, 159, 153, 155, 149, 151, 145, 147,
    173, 175, 169, 171, 165, 167, 161, 163, 189, 191, 185, 187, 181, 183, 177, 179
  },
  {
    0, 3, 6, 5, 12, 15, 10, 9, 24, 27, 30, 29, 20, 23, 18, 17,
    48, 51, 54, 53, 60, 63, 58, 57, 40, 43, 46, 45, 36, 39, 34, 33,
    96, 99, 102, 101, 108, 111, 106, 105, 120, 123, 126, 125, 116, 119, 114, 113,
    80, 83, 86, 85, 92, 95, 90, 89, 72, 75, 78, 77, 68, 71, 66, 65,
    192, 195, 198, 197, 204, 207, 202, 201, 216, 219, 222, 221, 212, 215, 210, 209,
    240, 243, 246, 245, 252, 255, 250, 249, 232, 235, 238, 237, 228, 231, 226, 225,
    160, 163, 166, 165, 172, 175, 170, 169, 184, 187, 190, 189, 180, 183, 178, 177,
    144, 147, 150, 149, 156, 159, 154, 153, 136, 139, 142, 141, 132, 135, 130, 129,
    205, 206, 203, 200, 193, 194, 199, 196, 213, 214, 211, 208, 217, 218, 223, 220,
    253, 254, 251, 248, 241, 242, 247, 244, 229, 230, 227, 224, 233, 234, 239, 236,
    173, 174, 171, 168, 161, 162, 167, 164, 181, 182, 179, 176, 185, 186, 191, 188,
    157, 158, 155, 152, 145, 146, 151, 148, 133, 134, 131, 128, 137, 138, 143, 140,
    13, 14, 11, 8, 1, 2, 7, 4, 21, 22, 19, 16, 25, 26, 31, 28,
    61, 62, 59, 56, 49, 50, 55, 52, 37, 38, 35, 32, 41, 42, 47, 44,
    109, 110, 107, 104, 97, 98, 103, 100, 117, 118, 115, 112, 121, 122, 127, 124,
    93, 94, 91, 88, 81, 82, 87, 84, 69, 70, 67, 64, 73, 74, 79, 76
  },
  {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
    64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124,
    128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188,
    192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252,
    77, 73, 69, 65, 93, 89, 85, 81, 109, 105, 101, 97, 125, 121, 117, 113,
    13, 9, 5, 1, 29, 25, 21, 17, 45, 41, 37, 33, 61, 57, 53, 49,
    205, 201, 197, 193, 221, 217, 213, 209, 237, 233, 229, 225, 253, 249, 245, 241,
    141, 137, 133, 129, 157, 153, 149, 145, 173, 169, 165, 161, 189, 185, 181, 177,
    154, 158, 146, 150, 138, 142, 130, 134, 186, 190, 178, 182, 170, 174, 162, 166,
    218, 222, 210, 214, 202, 206, 194, 198, 250, 254, 242, 246, 234, 238, 226, 230,
    26, 30, 18, 22, 10, 14, 2, 6, 58, 62, 50, 54, 42, 46, 34, 38,
    90, 94, 82, 86, 74, 78, 66, 70, 122, 126, 114, 118, 106, 110, 98, 102,
    215, 211, 223, 219, 199, 195, 207, 203, 247, 243, 255, 251, 231, 227, 239, 235,
    151, 147, 159, 155, 135, 131, 143, 139, 183, 179, 191, 187, 167, 163, 175, 171,
    87, 83, 95, 91, 71, 67, 79, 75, 119, 115, 127, 123, 103, 99, 111, 107,
    23, 19, 31, 27, 7, 3, 15, 11, 55, 51, 63, 59, 39, 35, 47, 43
  },
  {
    0, 5, 10, 15, 20, 17, 30, 27, 40, 45, 34, 39, 60, 57, 54, 51,
    80, 85, 90, 95, 68, 65, 78, 75, 120, 125, 114, 119, 108, 105, 102, 99,
    160, 165, 170, 175, 180, 177, 190, 187, 136, 141, 130, 135, 156, 153, 150, 147,
    240, 245, 250, 255, 228, 225, 238, 235, 216, 221, 210, 215, 204, 201, 198, 195,
    13, 8, 7, 2, 25, 28, 19, 22, 37, 32, 47, 42, 49, 52, 59, 62,
    93, 88, 87, 82, 73, 76, 67, 70, 117, 112, 127, 122, 97, 100, 107, 110,
    173, 168, 167, 162, 185, 188, 179, 182, 133, 128, 143, 138, 145, 148, 155, 158,
    253, 248, 247, 242, 233, 236, 227, 230, 213, 208, 223, 218, 193, 196, 203, 206,
    26, 31, 16, 21, 14, 11, 4, 1, 50, 55, 56, 61, 38, 35, 44, 41,
    74, 79, 64, 69, 94, 91, 84, 81, 98, 103, 104, 109, 118, 115, 124, 121,
    186, 191, 176, 181, 174, 171, 164, 161, 146, 151, 152, 157, 134, 131, 140, 137,
    234, 239, 224, 229, 254, 251, 244, 241, 194, 199, 200, 205, 214, 211, 220, 217,
    23, 18, 29, 24, 3, 6, 9, 12, 63, 58, 53, 48, 43, 46, 33, 36,
    71, 66, 77, 72, 83, 86, 89, 92, 111, 106, 101, 96, 123, 126, 113, 116,
    183, 178, 189, 184, 163, 166, 169, 172, 159, 154, 149, 144, 139, 142, 129, 132,
    231, 226, 237, 232, 243, 246, 249, 252, 207, 202, 197, 192, 219, 222, 209, 212
  },
  {
    0, 6, 12, 10, 24, 30, 20, 18, 48, 54, 60, 58, 40, 46, 36, 34,
    96, 102, 108, 106, 120, 126, 116, 114, 80, 86, 92, 90, 72, 78, 68, 66,
    192, 198, 204, 202, 216, 222, 212, 210, 240, 246, 252, 250, 232, 238, 228, 226,
    160, 166, 172, 170, 184, 190, 180, 178, 144, 150, 156, 154, 136, 142, 132, 130,
    205, 203, 193, 199, 213, 211, 217, 223, 253, 251, 241, 247, 229, 227, 233, 239,
    173, 171, 161, 167, 181, 179, 185, 191, 157, 155, 145, 151, 133, 131, 137, 143,
    13, 11, 1, 7, 21, 19, 25, 31, 61, 59, 49, 55, 37, 35, 41, 47,
    109, 107, 97, 103, 117, 115, 121, 127, 93, 91, 81, 87, 69, 67, 73, 79,
    215, 209, 219, 221, 207, 201, 195, 197, 231, 225, 235, 237, 255, 249, 243, 245,
    183, 177, 187, 189, 175, 169, 163, 165, 135, 129, 139, 141, 159, 153, 147, 149,
    23, 17, 27, 29, 15, 9, 3, 5, 39, 33, 43, 45, 63, 57, 51, 53,
    119, 113, 123, 125, 111, 105, 99, 101, 71, 65, 75, 77, 95, 89, 83, 85,
    26, 28, 22, 16, 2, 4, 14, 8, 42, 44, 38, 32, 50, 52, 62, 56,
    122, 124, 118, 112, 98, 100, 110, 104, 74, 76, 70, 64, 82, 84, 94, 88,
    218, 220, 214, 208, 194, 196, 206, 200, 234, 236, 230, 224, 242, 244, 254, 248,
    186, 188, 182, 176, 162, 164, 174, 168, 138, 140, 134, 128, 146, 148, 158, 152
  },
  {
    0, 7, 14, 9, 28, 27, 18, 21, 56, 63, 54, 49, 36, 35, 42, 45,
    112, 119, 126, 121, 108, 107, 98, 101, 72, 79, 70, 65, 84, 83, 90, 93,
    224, 231, 238, 233, 252, 251, 242, 245, 216, 223, 214, 209, 196, 195, 202, 205,
    144, 151, 158, 153, 140, 139, 130, 133, 168, 175, 166, 161, 180, 179, 186, 189,
    141, 138, 131, 132, 145, 150, 159, 152, 181, 178, 187, 188, 169, 174, 167, 160,
    253, 250, 243, 244, 225, 230, 239, 232, 197, 194, 203, 204, 217, 222, 215, 208,
    109, 106, 99, 100, 113, 118, 127, 120, 85, 82, 91, 92, 73, 78, 71, 64,
    29, 26, 19, 20, 1, 6, 15, 8, 37, 34, 43, 44, 57, 62, 55, 48,
    87, 80, 89, 94, 75, 76, 69, 66, 111, 104, 97, 102, 115, 116, 125, 122,
    39, 32, 41, 46, 59, 60, 53, 50, 31, 24, 17, 22, 3, 4, 13, 10,
    183, 176, 185, 190, 171, 172, 165, 162, 143, 136, 129, 134, 147, 148, 157, 154,
    199, 192, 201, 206, 219, 220, 213, 210, 255, 248, 241, 246, 227, 228, 237, 234,
    218, 221, 212, 211, 198, 193, 200, 207, 226, 229, 236, 235, 254, 249, 240, 247,
    170, 173, 164, 163, 182, 177, 184, 191, 146, 149, 156, 155, 142, 137, 128, 135,
    58, 61, 52, 51, 38, 33, 40, 47, 2, 5, 12, 11, 30, 25, 16, 23,
    74, 77, 68, 67, 86, 81, 88, 95, 114, 117, 124, 123, 110, 105, 96, 103
  },
  {
    0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120,
    128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248,
    77, 69, 93, 85, 109, 101, 125, 117, 13, 5, 29, 21, 45, 37, 61, 53,
    205, 197, 221, 213, 237, 229, 253, 245, 141, 133, 157, 149, 173, 165, 189, 181,
    154, 146, 138, 130, 186, 178, 170, 162, 218, 210, 202, 194, 250, 242, 234, 226,
    26, 18, 10, 2, 58, 50, 42, 34, 90, 82, 74, 66, 122, 114, 106, 98,
    215, 223, 199, 207, 247, 255, 231, 239, 151, 159, 135, 143, 183, 191, 167, 175,
    87, 95, 71, 79, 119, 127, 103, 111, 23, 31, 7, 15, 55, 63, 39, 47,
    121, 113, 105, 97, 89, 81, 73, 65, 57, 49, 41, 33, 25, 17, 9, 1,
    249, 241, 233, 225, 217, 209, 201, 193, 185, 177, 169, 161, 153, 145, 137, 129,
    52, 60, 36, 44, 20, 28, 4, 12, 116, 124, 100, 108, 84, 92, 68, 76,
    180, 188, 164, 172, 148, 156, 132, 140, 244, 252, 228, 236, 212, 220, 196, 204,
    227, 235, 243, 251, 195, 203, 211, 219, 163, 171, 179, 187, 131, 139, 147, 155,
    99, 107, 115, 123, 67, 75, 83, 91, 35, 43, 51, 59, 3, 11, 19, 27,
    174, 166, 190, 182, 142, 134, 158, 150, 238, 230, 254, 246, 206, 198, 222, 214,
    46, 38, 62, 54, 14, 6, 30, 22, 110, 102, 126, 118, 78, 70, 94, 86
  }
};
    
*/    