// hex.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "hex.h"

NAMESPACE_BEGIN(CryptoPP)

const byte HexEncoder::vec[17] = "0123456789ABCDEF";

void HexEncoder::Put(const byte *inString, unsigned int length)
{
	while (length--)
		HexEncoder::Put(*inString++);
}

void HexDecoder::Put(const byte *inString, unsigned int length)
{
	while (length--)
		HexDecoder::Put(*inString++);
}

NAMESPACE_END
