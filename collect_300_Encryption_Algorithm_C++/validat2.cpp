// validat2.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"

#include "blumshub.h"
#include "rsa.h"
#include "md2.h"
#include "elgamal.h"
#include "nr.h"
#include "dsa.h"
#include "dh.h"
#include "mqv.h"
#include "luc.h"
#include "rabin.h"
#include "rw.h"
#include "blumgold.h"
#include "eccrypto.h"
#include "ecp.h"
#include "ec2n.h"
// #include "zeroknow.h"
#include "asn.h"
#include "rng.h"
#include "files.h"
#include "hex.h"
#include "forkjoin.h"

#include <iostream>
#include <iomanip>

#include "validate.h"

USING_NAMESPACE(CryptoPP)
USING_NAMESPACE(std)

class FixedRNG : public RandomNumberGenerator
{
public:
	FixedRNG(BufferedTransformation &source) : m_source(source) {}

	byte GetByte()
	{
		byte b;
		m_source.Get(b);
		return b;
	}

private:
	BufferedTransformation &m_source;
};

bool BBSValidate()
{
	cout << "\nBlumBlumShub validation suite running...\n\n";

	Integer p("212004934506826557583707108431463840565872545889679278744389317666981496005411448865750399674653351");
	Integer q("100677295735404212434355574418077394581488455772477016953458064183204108039226017738610663984508231");
	Integer seed("63239752671357255800299643604761065219897634268887145610573595874544114193025997412441121667211431");
	BlumBlumShub bbs(p, q, seed);
	bool pass = true, fail;
	int j;

	const byte output1[] = {
		0x49,0xEA,0x2C,0xFD,0xB0,0x10,0x64,0xA0,0xBB,0xB9,
		0x2A,0xF1,0x01,0xDA,0xC1,0x8A,0x94,0xF7,0xB7,0xCE};
	const byte output2[] = {
		0x74,0x45,0x48,0xAE,0xAC,0xB7,0x0E,0xDF,0xAF,0xD7,
		0xD5,0x0E,0x8E,0x29,0x83,0x75,0x6B,0x27,0x46,0xA1};

	byte buf[20];

	bbs.GetBlock(buf, 20);
	fail = memcmp(output1, buf, 20) != 0;
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	for (j=0;j<20;j++)
		cout << setw(2) << setfill('0') << hex << (int)buf[j];
	cout << endl;

	bbs.Seek(10);
	bbs.GetBlock(buf, 10);
	fail = memcmp(output1+10, buf, 10) != 0;
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	for (j=0;j<10;j++)
		cout << setw(2) << setfill('0') << hex << (int)buf[j];
	cout << endl;

	bbs.Seek(1234567);
	bbs.GetBlock(buf, 20);
	fail = memcmp(output2, buf, 20) != 0;
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	for (j=0;j<20;j++)
		cout << setw(2) << setfill('0') << hex << (int)buf[j];
	cout << endl;

	return pass;
}

bool SignatureValidate(PK_Signer &priv, PK_Verifier &pub)
{
	LC_RNG rng(9374);
	const byte *message = (byte *)"test message";
	const int messageLen = 12;
	byte buffer[512];
	bool pass = true, fail;

	memset(buffer, 0, sizeof(buffer));
	priv.SignMessage(rng, message, messageLen, buffer);
	fail = !pub.VerifyMessage(message, messageLen, buffer);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "signature and verification\n";

	++buffer[0];
	fail = pub.VerifyMessage(message, messageLen, buffer);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "checking invalid signature" << endl;

	return pass;
}

bool CryptoSystemValidate(PK_Decryptor &priv, PK_Encryptor &pub)
{
	LC_RNG rng(9375);
	const byte *message = (byte *)"test message";
	const int messageLen = 12;
	SecByteBlock ciphertext(priv.CipherTextLength(messageLen));
	SecByteBlock plaintext(priv.MaxPlainTextLength(ciphertext.size));
	bool pass = true, fail;

	pub.Encrypt(rng, message, messageLen, ciphertext);
	fail = (messageLen!=priv.Decrypt(ciphertext, priv.CipherTextLength(messageLen), plaintext));
	fail = fail || memcmp(message, plaintext, messageLen);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "encryption and decryption\n";

	return pass;
}

bool SimpleKeyAgreementValidate(PK_SimpleKeyAgreementDomain &d)
{
	LC_RNG rng(5234);
	if (d.ValidateDomainParameters(rng))
		cout << "PASSED    simple key agreement domain parameters validation" << endl;
	else
	{
		cout << "FAILED    simple key agreement domain parameters invalid" << endl;
		return false;
	}

	SecByteBlock priv1(d.PrivateKeyLength()), priv2(d.PrivateKeyLength());
	SecByteBlock pub1(d.PublicKeyLength()), pub2(d.PublicKeyLength());
	SecByteBlock val1(d.AgreedValueLength()), val2(d.AgreedValueLength());

	d.GenerateKeyPair(rng, priv1, pub1);
	d.GenerateKeyPair(rng, priv2, pub2);

	memset(val1.ptr, 0x10, val1.size);
	memset(val2.ptr, 0x11, val2.size);

	if (!(d.Agree(val1, priv1, pub2) && d.Agree(val2, priv2, pub1)))
	{
		cout << "FAILED    simple key agreement failed" << endl;
		return false;
	}

	if (memcmp(val1.ptr, val2.ptr, d.AgreedValueLength()))
	{
		cout << "FAILED    simple agreed values not equal" << endl;
		return false;
	}

	cout << "PASSED    simple key agreement" << endl;
	return true;
}

bool AuthenticatedKeyAgreementValidate(PK_AuthenticatedKeyAgreementDomain &d)
{
	LC_RNG rng(5235);
	if (d.ValidateDomainParameters(rng))
		cout << "PASSED    authenticated key agreement domain parameters validation" << endl;
	else
	{
		cout << "FAILED    authenticated key agreement domain parameters invalid" << endl;
		return false;
	}

	SecByteBlock spriv1(d.StaticPrivateKeyLength()), spriv2(d.StaticPrivateKeyLength());
	SecByteBlock epriv1(d.EphemeralPrivateKeyLength()), epriv2(d.EphemeralPrivateKeyLength());
	SecByteBlock spub1(d.StaticPublicKeyLength()), spub2(d.StaticPublicKeyLength());
	SecByteBlock epub1(d.EphemeralPublicKeyLength()), epub2(d.EphemeralPublicKeyLength());
	SecByteBlock val1(d.AgreedValueLength()), val2(d.AgreedValueLength());

	d.GenerateStaticKeyPair(rng, spriv1, spub1);
	d.GenerateStaticKeyPair(rng, spriv2, spub2);
	d.GenerateEphemeralKeyPair(rng, epriv1, epub1);
	d.GenerateEphemeralKeyPair(rng, epriv2, epub2);

	memset(val1.ptr, 0x10, val1.size);
	memset(val2.ptr, 0x11, val2.size);

	if (!(d.Agree(val1, spriv1, epriv1, spub2, epub2) && d.Agree(val2, spriv2, epriv2, spub1, epub1)))
	{
		cout << "FAILED    authenticated key agreement failed" << endl;
		return false;
	}

	if (memcmp(val1.ptr, val2.ptr, d.AgreedValueLength()))
	{
		cout << "FAILED    authenticated agreed values not equal" << endl;
		return false;
	}

	cout << "PASSED    authenticated key agreement" << endl;
	return true;
}

bool RSAValidate()
{
	cout << "\nRSA validation suite running...\n\n";

	byte out[100], outPlain[100];
	unsigned int outLen;
	bool pass = true, fail;

	try
	{
		{
			char *plain = "Everyone gets Friday off.";
			byte *signature = (byte *)
				"\x05\xfa\x6a\x81\x2f\xc7\xdf\x8b\xf4\xf2\x54\x25\x09\xe0\x3e\x84"
				"\x6e\x11\xb9\xc6\x20\xbe\x20\x09\xef\xb4\x40\xef\xbc\xc6\x69\x21"
				"\x69\x94\xac\x04\xf3\x41\xb5\x7d\x05\x20\x2d\x42\x8f\xb2\xa2\x7b"
				"\x5c\x77\xdf\xd9\xb1\x5b\xfc\x3d\x55\x93\x53\x50\x34\x10\xc1\xe1";
			LC_RNG rng(765);

			FileSource keys("rsa512a.dat", true, new HexDecoder);
			RSASSA_PKCS1v15_MD2_Signer rsaPriv(keys);
			RSASSA_PKCS1v15_MD2_Verifier rsaPub(rsaPriv);

			rsaPriv.SignMessage(rng, (byte *)plain, strlen(plain), out);
			fail = memcmp(signature, out, 64) != 0;
			pass = pass && !fail;

			cout << (fail ? "FAILED    " : "PASSED    ");
			cout << "signature\n";

			fail = !rsaPub.VerifyMessage((byte *)plain, strlen(plain), out);
			pass = pass && !fail;

			cout << (fail ? "FAILED    " : "PASSED    ");
			cout << "valid signature verification\n";

			out[10]++;
			fail = rsaPub.VerifyMessage((byte *)plain, strlen(plain), out);
			pass = pass && !fail;

			cout << (fail ? "FAILED    " : "PASSED    ");
			cout << "invalid signature verification\n";
		}
		{
			FileSource keys("rsa512.dat", true, new HexDecoder);
			RSAES_PKCS1v15_Decryptor rsaPriv(keys);
			RSAES_PKCS1v15_Encryptor rsaPub(rsaPriv);

			pass = CryptoSystemValidate(rsaPriv, rsaPub) && pass;
		}
		{
			byte *plain = (byte *)
				"\x54\x85\x9b\x34\x2c\x49\xea\x2a";
			byte *encrypted = (byte *)
				"\x14\xbd\xdd\x28\xc9\x83\x35\x19\x23\x80\xe8\xe5\x49\xb1\x58\x2a"
				"\x8b\x40\xb4\x48\x6d\x03\xa6\xa5\x31\x1f\x1f\xd5\xf0\xa1\x80\xe4"
				"\x17\x53\x03\x29\xa9\x34\x90\x74\xb1\x52\x13\x54\x29\x08\x24\x52"
				"\x62\x51";
			byte *oaepSeed = (byte *)
				"\xaa\xfd\x12\xf6\x59\xca\xe6\x34\x89\xb4\x79\xe5\x07\x6d\xde\xc2"
				"\xf0\x6c\xb5\x8f";
			ByteQueue bq;
			bq.Put(oaepSeed, 20);
			FixedRNG rng(bq);

			FileSource privFile("rsa400pv.dat", true, new HexDecoder);
			FileSource pubFile("rsa400pb.dat", true, new HexDecoder);
			RSAES_OAEP_SHA_Decryptor rsaPriv(privFile);
			RSAES_OAEP_SHA_Encryptor rsaPub(pubFile);

			memset(out, 0, 50);
			memset(outPlain, 0, 8);
			rsaPub.Encrypt(rng, plain, 8, out);
			outLen = rsaPriv.Decrypt(encrypted, outPlain);
			fail = (outLen!=8) || memcmp(out, encrypted, 50) || memcmp(plain, outPlain, 8);
			pass = pass && !fail;

			cout << (fail ? "FAILED    " : "PASSED    ");
			cout << "PKCS 2.0 encryption and decryption\n";
		}
	}
	catch (BERDecodeErr)
	{
		cout << "FAILED    Error decoding RSA key\n";
		pass = false;
	}

	return pass;
}

bool DHValidate()
{
	cout << "\nDH validation suite running...\n\n";

	FileSource f("dh512.dat", true, new HexDecoder());
	DH dh(f);
	return SimpleKeyAgreementValidate(dh);
}

bool MQVValidate()
{
	cout << "\nMQV validation suite running...\n\n";

	FileSource f("mqv512.dat", true, new HexDecoder());
	MQV mqv(f);
	return AuthenticatedKeyAgreementValidate(mqv);
}

bool LUCDIFValidate()
{
	cout << "\nLUCDIF validation suite running...\n\n";

	FileSource f("lucdif.dat", true, new HexDecoder());
	LUCDIF dh(f);
	return SimpleKeyAgreementValidate(dh);
}

bool ElGamalValidate()
{
	cout << "\nElGamal validation suite running...\n\n";
	bool pass = true;
	{
		FileSource fc("elgc2048.dat", true, new HexDecoder);
		ElGamalDecryptor privC(fc);
		ElGamalEncryptor pubC(privC);
		pubC.Precompute();

		pass = CryptoSystemValidate(privC, pubC) && pass;
	}
	{
		LC_RNG rng(4780);
		cout << "Generating new encryption key..." << endl;
		ElGamalDecryptor privC(rng, 128);
		ElGamalEncryptor pubC(privC);

		pass = CryptoSystemValidate(privC, pubC) && pass;
	}
	return pass;
}

bool NRValidate()
{
	cout << "\nNR validation suite running...\n\n";
	bool pass = true;
	{
		FileSource f("nr2048.dat", true, new HexDecoder);
		NRSigner<SHA> privS(f);
		privS.Precompute();
		NRVerifier<SHA> pubS(privS);

		pass = SignatureValidate(privS, pubS) && pass;
	}
	{
		LC_RNG rng(4781);
		cout << "Generating new signature key..." << endl;
		NRSigner<SHA> privS(rng, 256);
		NRVerifier<SHA> pubS(privS);

		pass = SignatureValidate(privS, pubS) && pass;
	}
	return pass;
}

bool DSAValidate()
{
	cout << "\nDSA validation suite running...\n\n";

	bool pass = true, fail;
	{
	FileSource fs("dsa512.dat", true, new HexDecoder());
	DSAPrivateKey priv(fs);
	priv.Precompute(16);
	DSAPublicKey pub(priv);

	Integer k("79577ddcaafddc038b865b19f8eb1ada8a2838c6h");
	Integer h("0164b8a914cd2a5e74c4f7ff082c4d97f1edf880h");
	Integer r("9b77,f705,4c81,531c,4e46,a469,2fbf,e0f7,7f7e,bff2h");
	Integer s("95b4,f608,1f8f,890e,4b5a,199e,f10f,fe21,f52b,2d68h");

	Integer pGen, qGen, rOut, sOut;
	int c;

	byte seed[]={0xd5, 0x01, 0x4e, 0x4b, 0x60, 0xef, 0x2b, 0xa8, 0xb6, 0x21, 
				 0x1b, 0x40, 0x62, 0xba, 0x32, 0x24, 0xe0, 0x42, 0x7d, 0xd3};
	Integer p("8df2a494 492276aa 3d25759b b06869cb eac0d83a fb8d0cf7"
			  "cbb8324f 0d7882e5 d0762fc5 b7210eaf c2e9adac 32ab7aac"
			  "49693dfb f83724c2 ec0736ee 31c80291H");
	Integer q("c773218c 737ec8ee 993b4f2d ed30f48e dace915fH");

	fail = !GenerateDSAPrimes(seed, 160, c, pGen, 512, qGen);
	fail = fail || (pGen != p) || (qGen != q);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "prime generation test\n";

	priv.RawSign(k, h, rOut, sOut);
	fail = (rOut != r) || (sOut != s);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "signature test\n";

	fail = !pub.RawVerify(h, r, s);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "valid signature verification\n";

	fail = pub.RawVerify(h+1, r, s);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "PASSED    ");
	cout << "invalid signature verification\n";

	pass = SignatureValidate(priv, pub) && pass;
	}
	FileSource fs("dsa1024.dat", true, new HexDecoder());
	DSAPrivateKey priv(fs);
	priv.LoadPrecomputation(fs);
	DSAPublicKey pub(priv);
	pass = SignatureValidate(priv, pub) && pass;
	return pass;
}

bool LUCValidate()
{
	cout << "\nLUC validation suite running...\n\n";
	bool pass=true;

	{
		FileSource f("luc512.dat", true, new HexDecoder);
		LUCSSA_PKCS1v15_SHA_Signer priv(f);
		LUCSSA_PKCS1v15_SHA_Verifier pub(priv);
		pass = SignatureValidate(priv, pub) && pass;
	}
	{
		FileSource f("luc512.dat", true, new HexDecoder);
		LUCES_OAEP_SHA_Decryptor priv(f);
		LUCES_OAEP_SHA_Encryptor pub(priv);
		pass = CryptoSystemValidate(priv, pub) && pass;
	}
	return pass;
}

bool LUCELGValidate()
{
	cout << "\nLUCELG validation suite running...\n\n";

	FileSource f("lucs512.dat", true, new HexDecoder);
	LUCELG_Signer<SHA> privS(f);
	LUCELG_Verifier<SHA> pubS(privS);

	bool pass = SignatureValidate(privS, pubS);

	FileSource fc("lucc512.dat", true, new HexDecoder);
	LUCELG_Decryptor privC(fc);
	LUCELG_Encryptor pubC(privC);

	pass = CryptoSystemValidate(privC, pubC) && pass;

	return pass;
}

bool RabinValidate()
{
	cout << "\nRabin validation suite running...\n\n";
	bool pass=true;

	{
		FileSource f("rabi512.dat", true, new HexDecoder);
		RabinSignerWith(SHA) priv(f);
		RabinVerifierWith(SHA) pub(priv);
		pass = SignatureValidate(priv, pub) && pass;
	}
	{
		FileSource f("rabi512.dat", true, new HexDecoder);
		RabinDecryptor priv(f);
		RabinEncryptor pub(priv);
		pass = CryptoSystemValidate(priv, pub) && pass;
	}
	return pass;
}

bool RWValidate()
{
	cout << "\nRW validation suite running...\n\n";

	FileSource f("rw512.dat", true, new HexDecoder);
	RWSigner<SHA> priv(f);
	RWVerifier<SHA> pub(priv);

	return SignatureValidate(priv, pub);
}

bool BlumGoldwasserValidate()
{
	cout << "\nBlumGoldwasser validation suite running...\n\n";

	FileSource f("blum512.dat", true, new HexDecoder);
	BlumGoldwasserPrivateKey priv(f);
	BlumGoldwasserPublicKey pub(priv);

	return CryptoSystemValidate(priv, pub);
}

bool ECPValidate()
{
	cout << "\nECP validation suite running...\n\n";

	Integer modulus("199999999999999999999999980586675243082581144187569");
	Integer a("659942,b7261b,249174,c86bd5,e2a65b,45fe07,37d110h");
	Integer b("3ece7d,09473d,666000,5baef5,d4e00e,30159d,2df49ah");
	Integer x("25dd61,4c0667,81abc0,fe6c84,fefaa3,858ca6,96d0e8h");
	Integer y("4e2477,05aab0,b3497f,d62b5e,78a531,446729,6c3fach");
	Integer r("100000000000000000000000000000000000000000000000151");
	Integer k(2);
	Integer d("76572944925670636209790912427415155085360939712345");

	ECP ec(modulus, a, b);
	ECP::Point P(x, y);
	P = ec.Multiply(k, P);
	ECP::Point Q(ec.Multiply(d, P));
	ECSigner<ECP, SHA> priv(ec, P, Q, r, d);
	ECVerifier<ECP, SHA> pub(priv);
	ECDHC<ECP> ecdhc(ec, P, r, k);
	ECMQVC<ECP> ecmqvc(ec, P, r, k);

	priv.Precompute();
	ByteQueue queue;
	priv.SavePrecomputation(queue);
	pub.LoadPrecomputation(queue);

	bool pass = SignatureValidate(priv, pub);
	pass = CryptoSystemValidate(priv, pub) && pass;
	pass = SimpleKeyAgreementValidate(ecdhc) && pass;
	pass = AuthenticatedKeyAgreementValidate(ecmqvc) && pass;

	return pass;
}

bool EC2NValidate()
{
	cout << "\nEC2N validation suite running...\n\n";

	Integer r("3805993847215893016155463826195386266397436443");
	Integer k(12);
	Integer d("2065729449256706362097909124274151550853609397");

	GF2N gf2n(155, 62, 0);
	byte b[]={0x7, 0x33, 0x8f};
	EC2N ec(gf2n, PolynomialMod2::Zero(), PolynomialMod2(b,3));
	EC2N::Point P(0x7B, 0x1C8);
	P = ec.Multiply(k, P);
	EC2N::Point Q(ec.Multiply(d, P));
	ECSigner<EC2N, SHA> priv(ec, P, Q, r, d);
	ECVerifier<EC2N, SHA> pub(priv);
	ECDHC<EC2N> ecdhc(ec, P, r, k);
	ECMQVC<EC2N> ecmqvc(ec, P, r, k);

	priv.Precompute();
	ByteQueue queue;
	priv.SavePrecomputation(queue);
	pub.LoadPrecomputation(queue);

	bool pass = SignatureValidate(priv, pub);
	pass = CryptoSystemValidate(priv, pub) && pass;
	pass = SimpleKeyAgreementValidate(ecdhc) && pass;
	pass = AuthenticatedKeyAgreementValidate(ecmqvc) && pass;

	return pass;
}
