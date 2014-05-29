#ifndef CRYPTOPP_SHARK_H
#define CRYPTOPP_SHARK_H

#include "config.h"

#ifdef WORD64_AVAILABLE

#include "cryptlib.h"
#include "misc.h"

NAMESPACE_BEGIN(CryptoPP)

class SHARKBase : public BlockTransformation
{
public:
	// values of KEYLENGTH and ROUNDS are defaults only
	enum {KEYLENGTH=16, BLOCKSIZE=8, ROUNDS=6};
	unsigned int BlockSize() const {return BLOCKSIZE;}

protected:
	static void InitEncryptionRoundKeys(const byte *key, unsigned int keyLen, unsigned int rounds, word64 *roundkeys);
	SHARKBase(unsigned int rounds) : rounds(rounds), roundkeys(rounds+1) {}

	unsigned int rounds;
	SecBlock<word64> roundkeys;
};

class SHARKEncryption : public SHARKBase
{
public:
	SHARKEncryption(const byte *key, unsigned int keyLen=KEYLENGTH, unsigned int rounds=ROUNDS);

	void ProcessBlock(byte * inoutBlock) const
		{SHARKEncryption::ProcessBlock(inoutBlock, inoutBlock);}
	void ProcessBlock(const byte *inBlock, byte * outBlock) const;

private:
	friend class SHARKBase;
	SHARKEncryption();
	static const byte sbox[256];
	static const word64 cbox[8][256];
};

class SHARKDecryption : public SHARKBase
{
public:
	SHARKDecryption(const byte *key, unsigned int keyLen=KEYLENGTH, unsigned int rounds=ROUNDS);

	void ProcessBlock(byte * inoutBlock) const
		{SHARKDecryption::ProcessBlock(inoutBlock, inoutBlock);}
	void ProcessBlock(const byte *inBlock, byte * outBlock) const;

private:
	static const byte sbox[256];
	static const word64 cbox[8][256];
};

NAMESPACE_END

#endif
#endif
