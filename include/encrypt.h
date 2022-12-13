#ifndef ENCRYPT_HEADER
#define ENCRYPT_HEADER

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Std_Types.h"





void AddRoundKey(unsigned char * state, unsigned char * roundKey);
void SubBytes(unsigned char * state);
void ShiftRows(unsigned char * state);
void MixColumns(unsigned char * state);
void Round(unsigned char * state, unsigned char * key);
void FinalRound(unsigned char * state, unsigned char * key);
void AESEncrypt(uint32* message, unsigned char * expandedKey, uint8* encryptedMessage);
void KeyExpansionCore(unsigned char * in, unsigned char i);
void KeyExpansion(unsigned char inputKey[16], unsigned char expandedKeys[176]);
void addPadding(const uint8* message , int messageLen , uint32* paddedMessage);
void startEncryption(const uint8* message , uint32 messageLen, uint8* macPtr, uint32* macLengthPtr);

// #endif
#endif  // ENCRYPTION_ENCRYPT_H_
