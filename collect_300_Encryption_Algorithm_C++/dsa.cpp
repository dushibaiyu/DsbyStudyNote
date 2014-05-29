// dsa.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "dsa.h"
#include "asn.h"
#include "nbtheory.h"
#include "sha.h"

NAMESPACE_BEGIN(CryptoPP)

bool GenerateDSAPrimes(byte *seed, unsigned int g, int &counter,
						  Integer &p, unsigned int L, Integer &q)
{
	assert(L >= MIN_DSA_PRIME_LENGTH && L <= MAX_DSA_PRIME_LENGTH);

	SHA sha;
	SecByteBlock U(SHA::DIGESTSIZE);
	SecByteBlock temp(SHA::DIGESTSIZE);
	SecByteBlock W(((L-1)/160+1) * SHA::DIGESTSIZE);
	const int n = (L-1) / 160;
	const int b = (L-1) % 160;
	Integer X;

	sha.CalculateDigest(U, seed, g/8);

	for (int i=g/8-1, carry=true; i>=0 && carry; i--)
		carry=!++seed[i];

	sha.CalculateDigest(temp, seed, g/8);
	xorbuf(U, temp, SHA::DIGESTSIZE);

	U[0] |= 0x80;
	U[SHA::DIGESTSIZE-1] |= 1;
	q.Decode(U, SHA::DIGESTSIZE);

	if (!IsPrime(q))
		return false;

	for (counter = 0; counter < 4096; counter++)
	{
		for (int k=0; k<=n; k++)
		{
			for (int i=g/8-1, carry=true; i>=0 && carry; i--)
				carry=!++seed[i];
			sha.CalculateDigest(W+(n-k)*SHA::DIGESTSIZE, seed, g/8);
		}
		W[SHA::DIGESTSIZE - 1 - b/8] |= 0x80;
		X.Decode(W + SHA::DIGESTSIZE - 1 - b/8, L/8);
		p = X-((X % (2*q))-1);

		if (p.GetBit(L-1) && IsPrime(p))
			return true;
	}
	return false;
}

DSABase::DSABase(const Integer &p, const Integer &q,
				   const Integer &g, const Integer &y)
	: p(p), q(q), g(g), y(y), 
	  gpc(p, g, q.BitCount(), 1), ypc(p, y, q.BitCount(), 1)
{
}

void DSABase::Precompute(unsigned int precomputationStorage)
{
	gpc.Precompute(p, g, q.BitCount(), precomputationStorage);
	ypc.Precompute(p, y, q.BitCount(), precomputationStorage);
}

void DSABase::LoadPrecomputation(BufferedTransformation &bt)
{
	gpc.Load(p, bt);
	ypc.Load(p, bt);
}

void DSABase::SavePrecomputation(BufferedTransformation &bt) const
{
	gpc.Save(bt);
	ypc.Save(bt);
}

Integer DSABase::EncodeDigest(const byte *digest, unsigned int digestLen) const
{
	Integer h;
	if (digestLen*8 <= q.BitCount())
		h.Decode(digest, digestLen);
	else
	{
		h.Decode(digest, q.ByteCount());
		h >>= q.ByteCount()*8 - q.BitCount();
	}
	return h;
}

// ***********************************************************

DSAPrivateKey::DSAPrivateKey(const Integer &p, const Integer &q,
							 const Integer &g, const Integer &y, const Integer &x)
	: DSABase(p, q, g, y), x(x)
{
}

DSAPrivateKey::DSAPrivateKey(RandomNumberGenerator &rng, unsigned int keybits)
{
	SecByteBlock seed(SHA::DIGESTSIZE);
	Integer h;
	int c;

	do
	{
		rng.GetBlock(seed, SHA::DIGESTSIZE);
	} while (!GenerateDSAPrimes(seed, SHA::DIGESTSIZE*8, c, p, keybits, q));

	do
	{
		h.Randomize(rng, 2, p-2);
		g = a_exp_b_mod_c(h, (p-1)/q, p);
	} while (g <= 1);

	x.Randomize(rng, 2, q-2);
	gpc.Precompute(p, g, q.BitCount(), 1);
	y = gpc.Exponentiate(x);
	ypc.Precompute(p, y, q.BitCount(), 1);
}

DSAPrivateKey::DSAPrivateKey(RandomNumberGenerator &rng, const Integer &pIn, const Integer &qIn, const Integer &gIn)
{
	p = pIn;
	q = qIn;
	g = gIn;

	x.Randomize(rng, 2, q-2);
	gpc.Precompute(p, g, q.BitCount(), 1);
	y = gpc.Exponentiate(x);
	ypc.Precompute(p, y, q.BitCount(), 1);
}

DSAPrivateKey::DSAPrivateKey(BufferedTransformation &bt)
{
	BERSequenceDecoder seq(bt);
	p.BERDecode(seq);
	q.BERDecode(seq);
	g.BERDecode(seq);
	y.BERDecode(seq);
	x.BERDecode(seq);
	gpc.Precompute(p, g, q.BitCount(), 1);
	ypc.Precompute(p, y, q.BitCount(), 1);
}

void DSAPrivateKey::DEREncode(BufferedTransformation &bt) const
{
	DERSequenceEncoder seq(bt);
	p.DEREncode(seq);
	q.DEREncode(seq);
	g.DEREncode(seq);
	y.DEREncode(seq);
	x.DEREncode(seq);
}

void DSAPrivateKey::SignDigest(RandomNumberGenerator &rng, const byte *digest, unsigned int digestLen, byte *signature) const
{
	Integer h = EncodeDigest(digest, digestLen);
	Integer k(rng, 2, q-2);
	Integer r, s;

	RawSign(k, h, r, s);
	r.Encode(signature, q.ByteCount());
	s.Encode(signature+q.ByteCount(), q.ByteCount());
}

void DSAPrivateKey::RawSign(const Integer &k, const Integer &h, Integer &r, Integer &s) const
{
//    r = a_exp_b_mod_c(g, k, p) % q;
	r = gpc.Exponentiate(k) % q;
	Integer kInv = EuclideanMultiplicativeInverse(k, q);
	s = (kInv * (x*r + h)) % q;
}

// ***********************************************************

DSAPublicKey::DSAPublicKey(const Integer &p, const Integer &q,
							const Integer &g, const Integer &y)
	: DSABase(p, q, g, y)
{
}

DSAPublicKey::DSAPublicKey(const DSAPrivateKey &priv)
	: DSABase(priv)
{
}

DSAPublicKey::DSAPublicKey(BufferedTransformation &bt)
{
	BERSequenceDecoder seq(bt);
	p.BERDecode(seq);
	q.BERDecode(seq);
	g.BERDecode(seq);
	y.BERDecode(seq);
	gpc.Precompute(p, g, q.BitCount(), 1);
	ypc.Precompute(p, y, q.BitCount(), 1);
}

void DSAPublicKey::DEREncode(BufferedTransformation &bt) const
{
	DERSequenceEncoder seq(bt);
	p.DEREncode(seq);
	q.DEREncode(seq);
	g.DEREncode(seq);
	y.DEREncode(seq);
}

bool DSAPublicKey::VerifyDigest(const byte *digest, unsigned int digestLen, const byte *signature) const
{
	Integer h = EncodeDigest(digest, digestLen);
	Integer r(signature, q.ByteCount());
	Integer s(signature+q.ByteCount(), q.ByteCount());

	return RawVerify(h, r, s);
}

bool DSAPublicKey::RawVerify(const Integer &h, const Integer &r, const Integer &s) const
{
	if (r>=q || r<1 || s>=q || s<1)
		return false;

	Integer w = EuclideanMultiplicativeInverse(s, q);
	Integer u1 = (h * w) % q;
	Integer u2 = (r * w) % q;
	// verify r == (g^u1 * y^u2 mod p) mod q
//	return r == ModularArithmetic(p).CascadeExponentiate(g, u1, y, u2) % q;
	return r == gpc.CascadeExponentiate(u1, ypc, u2) % q;
}

NAMESPACE_END
