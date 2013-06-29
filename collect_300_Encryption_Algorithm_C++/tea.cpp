// tea.cpp - modified by Wei Dai from code in the original paper

#include "pch.h"
#include "tea.h"

NAMESPACE_BEGIN(CryptoPP)

const word32 TEA::DELTA = 0x9e3779b9;

TEA::TEA(const byte *userKey)
	: k(4)
{
	for (int j=0;j<4;j++)
		k[j] = ((word32)userKey[4*j]<<24) | ((word32)userKey[4*j+1]<<16) 
			 | ((word32)userKey[4*j+2]<<8) | ((word32)userKey[4*j+3]);
}

void TEAEncryption::ProcessBlock(const byte *in, byte *out) const
{
#ifdef IS_LITTLE_ENDIAN
	word32 y = byteReverse(*(word32 *)in);
	word32 z = byteReverse(*(word32 *)(in+4));
#else
	word32 y = *(word32 *)in;
	word32 z = *(word32 *)(in+4);
#endif

	word32 sum = 0;
	for (int i=0; i<ROUNDS; i++)
	{   
		sum += DELTA;
		y += (z << 4) + k[0] ^ z + sum ^ (z >> 5) + k[1];
		z += (y << 4) + k[2] ^ y + sum ^ (y >> 5) + k[3];
	}

#ifdef IS_LITTLE_ENDIAN
	*(word32 *)out = byteReverse(y);
	*(word32 *)(out+4) = byteReverse(z);
#else
	*(word32 *)out = y;
	*(word32 *)(out+4) = z;
#endif
}

void TEADecryption::ProcessBlock(const byte *in, byte *out) const
{
#ifdef IS_LITTLE_ENDIAN
	word32 y = byteReverse(*(word32 *)in);
	word32 z = byteReverse(*(word32 *)(in+4));
#else
	word32 y = *(word32 *)in;
	word32 z = *(word32 *)(in+4);
#endif

	word32 sum = DELTA << LOG_ROUNDS;
	for (int i=0; i<ROUNDS; i++)
	{
		z -= (y << 4) + k[2] ^ y + sum ^ (y >> 5) + k[3]; 
		y -= (z << 4) + k[0] ^ z + sum ^ (z >> 5) + k[1];
		sum -= DELTA;
	}

#ifdef IS_LITTLE_ENDIAN
	*(word32 *)out = byteReverse(y);
	*(word32 *)(out+4) = byteReverse(z);
#else
	*(word32 *)out = y;
	*(word32 *)(out+4) = z;
#endif
}

NAMESPACE_END
