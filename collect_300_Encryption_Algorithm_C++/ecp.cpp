// ecp.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "ecp.h"
#include "asn.h"
#include "nbtheory.h"

#include "algebra.cpp"
#include "eprecomp.cpp"

NAMESPACE_BEGIN(CryptoPP)

ANONYMOUS_NAMESPACE_BEGIN
static inline ECP::Point ToMontgomery(const MontgomeryRepresentation &mr, const ECP::Point &P)
{
	return P.identity ? P : ECP::Point(mr.ConvertIn(P.x), mr.ConvertIn(P.y));
}

static inline ECP::Point FromMontgomery(const MontgomeryRepresentation &mr, const ECP::Point &P)
{
	return P.identity ? P : ECP::Point(mr.ConvertOut(P.x), mr.ConvertOut(P.y));
}
NAMESPACE_END

ECP::Point ECP::DecodePoint(const byte *encodedPoint) const
{
	if (encodedPoint[0] != 4)	// TODO: handle compressed points
		return Point();
	else
	{
		unsigned int len = field.MaxElementByteLength();
		return Point(FieldElement(encodedPoint+1, len), FieldElement(encodedPoint+1+len, len));
	}
}

void ECP::EncodePoint(byte *encodedPoint, const Point &P) const
{
	if (P.identity)
		memset(encodedPoint, 0, EncodedPointSize());
	else
	{
		encodedPoint[0] = 4;	// uncompressed
		unsigned int len = field.MaxElementByteLength();
		P.x.Encode(encodedPoint+1, len);
		P.y.Encode(encodedPoint+1+len, len);
	}
}

bool ECP::ValidateParameters(RandomNumberGenerator &rng) const
{
	Integer p = FieldSize();
	return p.IsOdd() && VerifyPrime(rng, p)
		&& !a.IsNegative() && a<p && !b.IsNegative() && b<p
		&& ((4*a*a*a+27*b*b)%p).IsPositive();
}

bool ECP::VerifyPoint(const Point &P) const
{
	const FieldElement &x = P.x, &y = P.y;
	Integer p = FieldSize();
	return P.identity ||
		(!x.IsNegative() && x<p && !x.IsNegative() && x<p
		&& !(((x*x+a)*x+b-y*y)%p));
}

bool ECP::Equal(const Point &P, const Point &Q) const
{
	if (P.identity && Q.identity)
		return true;

	if (P.identity && !Q.identity)
		return false;

	if (!P.identity && Q.identity)
		return false;

	return (field.Equal(P.x,Q.x) && field.Equal(P.y,Q.y));
}

ECP::Point ECP::Inverse(const Point &P) const
{
	if (P.identity)
		return P;
	else
		return Point(P.x, field.Inverse(P.y));
}

ECP::Point ECP::Add(const Point &P, const Point &Q) const
{
	if (P.identity) return Q;
	if (Q.identity) return P;
	if (field.Equal(P.x, Q.x))
		return field.Equal(P.y, Q.y) ? Double(P) : Zero();

	Point R(Q.x, Q.y);
	field.Reduce(R.x, P.x);
	field.Reduce(R.y, P.y);
	FieldElement t = field.Divide(R.y, R.x);
	R.x = field.Square(t);
	field.Reduce(R.x, P.x);
	field.Reduce(R.x, Q.x);
	R.y = field.Subtract(P.x, R.x);
	R.y = field.Multiply(t, R.y);
	field.Reduce(R.y, P.y);
	return R;
}

ECP::Point ECP::Double(const Point &P) const
{
	if (P.identity || P.y==field.Zero()) return Zero();

	FieldElement t = field.Square(P.x);
	Point R(t, P.y);
	field.Accumulate(R.x, R.x);
	field.Accumulate(R.y, R.y);
	field.Accumulate(t, R.x);
	field.Accumulate(t, a);
	t = field.Divide(t, R.y);
	R.x = field.Square(t);
	R.y = field.Double(P.x);
	field.Reduce(R.x, R.y);
	R.y = field.Subtract(P.x, R.x);
	R.y = field.Multiply(t, R.y);
	field.Reduce(R.y, P.y);
	return R;
}

ECP::Point ECP::Multiply(const Integer &k, const Point &P) const
{
//	return GeneralizedMultiplication(*this, P, k);
	MontgomeryRepresentation mr(field.GetModulus());
	ECP ecpmr(mr, mr.ConvertIn(a), mr.ConvertIn(b));
	return FromMontgomery(mr, ecpmr.IntMultiply(ToMontgomery(mr, P), k));
}

ECP::Point ECP::CascadeMultiply(const Integer &k1, const Point &P, const Integer &k2, const Point &Q) const
{
//	return CascadeMultiplication(*this, P, k1, Q, k2);
	MontgomeryRepresentation mr(field.GetModulus());
	ECP ecpmr(mr, mr.ConvertIn(a), mr.ConvertIn(b));
	return FromMontgomery(mr, ecpmr.CascadeIntMultiply(ToMontgomery(mr, P), k1, ToMontgomery(mr, Q), k2));
}

// ********************************************************

EcPrecomputation<ECP>::EcPrecomputation()
{
}

EcPrecomputation<ECP>::EcPrecomputation(const EcPrecomputation<ECP> &ecp)
	: mr(new MontgomeryRepresentation(*ecp.mr))
	, ec(new ECP(*mr, ecp.ec->GetA(), ecp.ec->GetB()))
	, ep(new ExponentiationPrecomputation<ECP>(*ec, *ecp.ep))
{
}

EcPrecomputation<ECP>::EcPrecomputation(const ECP &ecIn, const ECP::Point &base, unsigned int maxExpBits, unsigned int storage)
	: mr(new MontgomeryRepresentation(ecIn.GetField().GetModulus()))
	, ec(new ECP(*mr, mr->ConvertIn(ecIn.GetA()), mr->ConvertIn(ecIn.GetB())))
	, ep(NULL)
{
	Precompute(base, maxExpBits, storage);
}

EcPrecomputation<ECP>::~EcPrecomputation()
{
}

void EcPrecomputation<ECP>::Precompute(const ECP::Point &base, unsigned int maxExpBits, unsigned int storage)
{
	ep.reset(new ExponentiationPrecomputation<ECP>(*ec, ToMontgomery(*mr, base), maxExpBits, storage));
}

void EcPrecomputation<ECP>::Load(BufferedTransformation &bt)
{
	ep.reset(new ExponentiationPrecomputation<ECP>(*ec));
	BERSequenceDecoder seq(bt);
	ep->storage = (unsigned int)(Integer(seq).ConvertToLong());
	ep->exponentBase.BERDecode(seq);
	ep->g.resize(ep->storage);

	for (unsigned i=0; i<ep->storage; i++)
	{
		ep->g[i].identity = false;
		ep->g[i].x.BERDecode(seq);
		ep->g[i].y.BERDecode(seq);
	}
}

void EcPrecomputation<ECP>::Save(BufferedTransformation &bt) const
{
	assert(ep.get());
	DERSequenceEncoder seq(bt);
	Integer(ep->storage).DEREncode(seq);
	ep->exponentBase.DEREncode(seq);

	for (unsigned i=0; i<ep->storage; i++)
	{
		ep->g[i].x.DEREncode(seq);
		ep->g[i].y.DEREncode(seq);
	}
}

ECP::Point EcPrecomputation<ECP>::Multiply(const Integer &exponent) const
{
	assert(ep.get());
	return FromMontgomery(*mr, ep->Exponentiate(exponent));
}

ECP::Point EcPrecomputation<ECP>::CascadeMultiply(const Integer &exponent, const EcPrecomputation<ECP> &pc2, const Integer &exponent2) const
{
	assert(ep.get());
	return FromMontgomery(*mr, ep->CascadeExponentiate(exponent, *pc2.ep, exponent2));
}

NAMESPACE_END
