#ifndef CRYPTOPP_DSA_H
#define CRYPTOPP_DSA_H

#include "pubkey.h"
#include "modexppc.h"
#include "sha.h"

NAMESPACE_BEGIN(CryptoPP)

const int MIN_DSA_PRIME_LENGTH = 512;
const int MAX_DSA_PRIME_LENGTH = 1024;

// both seedLength and primeLength are in bits, but seedLength should
// be a multiple of 8
bool GenerateDSAPrimes(byte *seed, unsigned int seedLength, int &counter,
						  Integer &p, unsigned int primeLength, Integer &q);

class DSABase : virtual public PK_Precomputation, virtual public DigestSignatureSystem
{
public:
	void Precompute(unsigned int precomputationStorage=16);
	void LoadPrecomputation(BufferedTransformation &storedPrecomputation);
	void SavePrecomputation(BufferedTransformation &storedPrecomputation) const;
	unsigned int MaxDigestLength() const {return UINT_MAX;}
	unsigned int DigestSignatureLength() const {return 2*q.ByteCount();}
protected:
	DSABase() {}
	DSABase(const Integer &p, const Integer &q, const Integer &g, const Integer &y);
	Integer EncodeDigest(const byte *digest, unsigned int digestLen) const;
	Integer p, q, g, y;
	ModExpPrecomputation gpc, ypc;
};

class SHA;

class DSAPrivateKey : public DSABase, public SignerTemplate<DigestSigner, SHA>, public PK_WithPrecomputation<PK_Signer>
{
public:
	DSAPrivateKey(const Integer &p, const Integer &q, const Integer &g, const Integer &y, const Integer &x);

	// generate a random private key
	DSAPrivateKey(RandomNumberGenerator &rng, unsigned int keybits);

	// generate a random private key, given p, q, and g
	DSAPrivateKey(RandomNumberGenerator &rng, const Integer &p, const Integer &q, const Integer &g);

	// load a previously generated key
	DSAPrivateKey(BufferedTransformation &storedKey);

	void DEREncode(BufferedTransformation &bt) const;

	void SignDigest(RandomNumberGenerator &rng, const byte *digest, unsigned int digestLen, byte *signature) const;

	// exposed for validation testing
	void RawSign(const Integer &k, const Integer &h, Integer &r, Integer &s) const;

protected:
	Integer x;
};

class DSAPublicKey : public DSABase, public VerifierTemplate<DigestVerifier, SHA>, public PK_WithPrecomputation<PK_Verifier>
{
public:
	DSAPublicKey(const Integer &p, const Integer &q, const Integer &g, const Integer &y);

	// create a matching public key from a private key
	DSAPublicKey(const DSAPrivateKey &priv);

	// load a previously generated key
	DSAPublicKey(BufferedTransformation &storedKey);

	void DEREncode(BufferedTransformation &bt) const;

	bool VerifyDigest(const byte *digest, unsigned int digestLen, const byte *signature) const;

	// exposed for validation testing
	bool RawVerify(const Integer &h, const Integer &r, const Integer &s) const;
};

NAMESPACE_END

#endif
