// rc6.cpp - written and placed in the public domain by Sean Woods
// based on Wei Dai's RC5 code.

#include "pch.h"
#include "rc6.h"

NAMESPACE_BEGIN(CryptoPP)

#ifdef _MSC_VER
#define ROTL(x,y) (_rotl((x), (unsigned int)(y)))
#define ROTR(x,y) (_rotr((x), (unsigned int)(y)))
#else
#define ROTL(x,y) (rotl((x), (unsigned int)(y) % (sizeof(RC6_WORD)*8)))
#define ROTR(x,y) (rotr((x), (unsigned int)(y) % (sizeof(RC6_WORD)*8)))
#endif

RC6Base::RC6Base(const byte *k, unsigned int keylen, unsigned int rounds)
	: r(rounds), sTable((2*r)+4)
{
	static const RC6_WORD MAGIC_P = 0xb7e15163L;    // magic constant P for wordsize
	static const RC6_WORD MAGIC_Q = 0x9e3779b9L;    // magic constant Q for wordsize
	static const int U=sizeof(RC6_WORD);

	const unsigned int c=(keylen-1)/U + 1;
	SecBlock<RC6_WORD> l(c);

	l[(keylen-1)/U] = 0;	// clear top word for when keylen%U != 0
	for (int i = (keylen-1) ; i >= 0; i--)
		l[i/U] = (l[i/U] << 8) + k[i];

	sTable[0] = MAGIC_P;
	for (unsigned j=1; j<sTable.size;j++)
		sTable[j] = sTable[j-1] + MAGIC_Q;

	RC6_WORD a=0, b=0;
	const unsigned n = 3*STDMAX(sTable.size,c);

	for (unsigned h=0; h < n; h++)
	{
		a = sTable[h % sTable.size] = ROTL((sTable[h % sTable.size] + a + b), 3);
		b = l[h % c] = ROTL((l[h % c] + a + b), (a+b));
	}
}

ANONYMOUS_NAMESPACE_BEGIN
// Fetch 8 bytes from user's buffer into "a", "b", "c", "d"
// in LITTLE-endian order
static inline void GETBLOCK(const byte *block, word32 &a, word32 &b, word32 &c, word32 &d)
{
#ifdef IS_LITTLE_ENDIAN
	a = *(word32 *)block;
	b = *(word32 *)(block+4);
	c = *(word32 *)(block+8);
	d = *(word32 *)(block+12);
#else
	a = byteReverse(*(word32 *)block);
	b = byteReverse(*(word32 *)(block+4));
	c = byteReverse(*(word32 *)(block+8));
	d = byteReverse(*(word32 *)(block+12));
#endif
}

// Put 8 bytes back into user's buffer in LITTLE-endian order
static inline void PUTBLOCK(byte *block, word32 a, word32 b, word32 c, word32 d)
{
#ifdef IS_LITTLE_ENDIAN
	*(word32 *)block = a;
	*(word32 *)(block+4) = b;
	*(word32 *)(block+8) = c;
	*(word32 *)(block+12) = d;
#else
	*(word32 *)block = byteReverse(a);
	*(word32 *)(block+4) = byteReverse(b);
	*(word32 *)(block+8) = byteReverse(c);
	*(word32 *)(block+12) = byteReverse(d);
#endif
}
NAMESPACE_END

void RC6Encryption::ProcessBlock(const byte *in, byte *out) const
{
	const RC6_WORD *sptr = sTable;
	RC6_WORD a, b, c, d, t, u;

	GETBLOCK(in, a, b, c, d);
	b += sptr[0];
	d += sptr[1];
	sptr += 2;

	for(unsigned i=0; i<r; i++)
	{
		t = ROTL(b*(2*b+1), 5);
		u = ROTL(d*(2*d+1), 5);
		a = ROTL(a^t,u) + sptr[0];
		c = ROTL(c^u,t) + sptr[1];
		t = a; a = b; b = c; c = d; d = t;
		sptr += 2;
	}

	a += sptr[0];
	c += sptr[1];

	PUTBLOCK(out, a, b, c, d);
}

void RC6Decryption::ProcessBlock(const byte *in, byte *out) const
{
	const RC6_WORD *sptr = sTable+sTable.size;
	RC6_WORD a, b, c, d, t, u;

	GETBLOCK(in, a, b, c, d);

	sptr -= 2;
	c -= sptr[1];
	a -= sptr[0];

	for (unsigned i=0; i < r; i++)
	{
		sptr -= 2;
		t = a; a = d; d = c; c = b; b = t;
		u = ROTL(d*(2*d+1), 5);
		t = ROTL(b*(2*b+1), 5);
		c = ROTR(c-sptr[1], t) ^ u;
		a = ROTR(a-sptr[0], u) ^ t;
	}

	sptr -= 2;
	d -= sTable[1];
	b -= sTable[0];

	PUTBLOCK(out, a, b, c, d);
}

NAMESPACE_END
