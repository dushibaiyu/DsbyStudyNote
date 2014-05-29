#ifndef CRYPTOPP_TEA_H
#define CRYPTOPP_TEA_H

#include "cryptlib.h"
#include "misc.h"

NAMESPACE_BEGIN(CryptoPP)

class TEA : public BlockTransformation
{
public:
	TEA(const byte *userKey);

	enum {KEYLENGTH=16, BLOCKSIZE=8, ROUNDS=32, LOG_ROUNDS=5};
	unsigned int BlockSize() const {return BLOCKSIZE;}

protected:
	static const word32 DELTA;
	SecBlock<word32> k;
};

class TEAEncryption : public TEA
{
public:
	TEAEncryption(const byte *userKey)
		: TEA(userKey) {}

	void ProcessBlock(byte * inoutBlock) const
		{TEAEncryption::ProcessBlock(inoutBlock, inoutBlock);}
	void ProcessBlock(const byte *inBlock, byte *outBlock) const;
};

class TEADecryption : public TEA
{
public:
	TEADecryption(const byte *userKey)
		: TEA(userKey) {}

	void ProcessBlock(byte * inoutBlock) const
		{TEADecryption::ProcessBlock(inoutBlock, inoutBlock);}
	void ProcessBlock(const byte *inBlock, byte *outBlock) const;
};

NAMESPACE_END

#endif
