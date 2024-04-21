#include <IRremote.hpp>
#include "Common.h"

#define NORELAY 255
#define NO_IRKEY 255
#define NO_BTKEY 255
typedef enum
{
  OP_N, // NO Operation
  OP_H, // Set High
  OP_L, // Set Low
  OP_T  // Toggle Corrent State
}Operation;
typedef struct 
{
  uint8_t Key;
  Operation OP;
}Command;

// LGSMART REMOTE
#define NUM_OUTPUTS 10

#define SW_0 16
#define SW_1 17
#define SW_2 18
#define SW_3 19
#define SW_4 20
#define SW_5 21
#define SW_6 22
#define SW_7 23
#define SW_8 24
#define SW_9 25

#if(HILTEST==1)
#define R0 NORELAY
#define R1 24
#define R2 25
#define R3 26
#define R4 27
#define R5 NORELAY
#define R6 NORELAY
#define R7 NORELAY
#define R8 NORELAY
#define R9 NORELAY
#else
#define R0 NORELAY
#define R1 4
#define R2 5
#define R3 6
#define R4 7
#define R5 NORELAY
#define R6 NORELAY
#define R7 NORELAY
#define R8 NORELAY
#define R9 NORELAY
#endif


IRRawDataType Codes[NUM_OUTPUTS]=
{SW_0,SW_1,SW_2,SW_3,SW_4,SW_5,SW_6,SW_7,SW_8,SW_9};
uint8_t RELAYS[NUM_OUTPUTS]=
{R0,  R1,  R2,  R3,  R4,  R5,  R6,  R7,  R8,  R9  };

#define RelayState(x) ((States>>x)&1)

#define SetBitH(bit_pos) (States |=(  1 << bit_pos))
#define SetBitL(bit_pos) (States &= ~(1 << bit_pos))
#define SetBitT(bit_pos) (States ^=(  1 << bit_pos))
