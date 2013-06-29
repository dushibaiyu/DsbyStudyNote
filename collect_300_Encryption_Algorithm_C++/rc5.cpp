// rc5.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "rc5.h"

NAMESPACE_BEGIN(CryptoPP)

#ifdef _MSC_VER
#define ROTL(x,y) (_rotl((x), (unsigned int)(y)))
#define ROTR(x,y) (_rotr((x), (unsigned int)(y)))
#else
#define ROTL(x,y) (rotl((x), (unsigned int)(y) % (sizeof(RC5_WORD)*8)))
#define ROTR(x,y) (rotr((x), (unsigned int)(y) % (sizeof(RC5_WORD)*8)))
#endif

RC5Base::RC5Base(const byte *k, unsigned int keylen, unsigned int rounds)
	: r(rounds), sTable(2*(r+1))
{
	static const RC5_WORD MAGIC_P = 0xb7e15163L;    // magic constant P for wordsize
	static const RC5_WORD MAGIC_Q = 0x9e3779b9L;    // magic constant Q for wordsize
	static const int U=sizeof(RC5_WORD);

	const unsigned int c=(keylen-1)/U + 1;
	SecBlock<RC5_WORD> l(c);

	l[(keylen-1)/U] = 0;	// clear top word for when keylen%U != 0
	for (int i = (keylen-1) ; i >= 0; i--)
		l[i/U] = (l[i/U] << 8) + k[i];

	sTable[0] = MAGIC_P;
	for (unsigned j=1; j<sTable.size;j++)
		sTable[j] = sTable[j-1] + MAGIC_Q;

	RC5_WORD a=0, b=0;
	const unsigned n = 3*STDMAX(sTable.size,c);

	for (unsigned h=0; h < n; h++)
	{
		a = sTable[h % sTable.size] = ROTL((sTable[h % sTable.size] + a + b), 3);
		b = l[h % c] = ROTL((l[h % c] + a + b), (a+b));
	}
}

ANONYMOUS_NAMESPACE_BEGIN
// Fetch 8 bytes from user's buffer into "left" and "right"
// in LITTLE-endian order
static inline void GETBLOCK(const byte *block, word32 &left, word32 &right)
{
#ifdef IS_LITTLE_ENDIAN
	left = *(word32 *)block;
	right = *(word32 *)(block+4);
#else
	left = byteReverse(*(word32 *)block);
	right = byteReverse(*(word32 *)(block+4));
#endif
}

// Put 8 bytes back into user's buffer in LITTLE-endian order
static inline void PUTBLOCK(byte *block, word32 left, word32 right)
{
#ifdef IS_LITTLE_ENDIAN
	*(word32 *)block = left;
	*(word32 *)(block+4) = right;
#else
	*(word32 *)block = byteReverse(left);
	*(word32 *)(block+4) = byteReverse(right);
#endif
}
NAMESPACE_END

void RC5Encryption::ProcessBlock(const byte *in, byte *out) const
{
	const RC5_WORD *sptr = sTable;
	RC5_WORD a, b;

	GETBLOCK(in, a, b);
	a += sptr[0];
	b += sptr[1];
	sptr += 2;

	for(unsigned i=0; i<r; i++)
	{
		a = ROTL(a^b,b) + sptr[2*i+0];
		b = ROTL(a^b,a) + sptr[2*i+1];
	}

	PUTBLOCK(out, a, b);
}

void RC5Decryption::ProcessBlock(const byte *in, byte *out) const
{
	const RC5_WORD *sptr = sTable+sTable.size;
	RC5_WORD a, b;

	GETBLOCK(in, a, b);

	for (unsigned i=0; i<r; i++)
	{
		sptr-=2;
		b = ROTR(b-sptr[1], a) ^ a;
		a = ROTR(a-sptr[0], b) ^ b;
	}
	b -= sTable[1];
	a -= sTable[0];

	PUTBLOCK(out, a, b);
}

NAMESPACE_END
