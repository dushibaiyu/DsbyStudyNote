// default.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "default.h"
#include "cbc.h"
#include <time.h>
#include <memory>

NAMESPACE_BEGIN(CryptoPP)

static const unsigned int MASH_ITERATIONS = 200;
static const unsigned int SALTLENGTH = 8;
static const unsigned int BLOCKSIZE = Default_ECB_Encryption::BLOCKSIZE;
static const unsigned int KEYLENGTH = Default_ECB_Encryption::KEYLENGTH;

// The purpose of this function Mash() is to take an arbitrary length input
// string and *deterministicly* produce an arbitrary length output string such
// that (1) it looks random, (2) no information about the input is
// deducible from it, and (3) it contains as much entropy as it can hold, or
// the amount of entropy in the input string, whichever is smaller.

void Mash(byte *const in, word16 inLen, byte *out, word16 outLen, int iterations)
{
	unsigned int bufSize = (outLen-1+DefaultHashModule::DIGESTSIZE-((outLen-1)%DefaultHashModule::DIGESTSIZE));

	// ASSERT: bufSize == (the smallest multiple of DIGESTSIZE that is >= outLen)

	byte b[2];
	SecByteBlock buf(bufSize);
	SecByteBlock outBuf(bufSize);
	DefaultHashModule hash;

	unsigned int i;
	for(i=0; i<outLen; i+=DefaultHashModule::DIGESTSIZE)
	{
		b[0] = (byte) i >> 8;
		b[1] = (byte) i;
		hash.Update(b, 2);
		hash.Update(in, inLen);
		hash.Final(outBuf+i);
	}

	while (iterations-- > 1)
	{
		memcpy(buf, outBuf, bufSize);
		for (i=0; i<bufSize; i+=DefaultHashModule::DIGESTSIZE)
		{
			b[0] = (byte) i >> 8;
			b[1] = (byte) i;
			hash.Update(b, 2);
			hash.Update(buf, bufSize);
			hash.Final(outBuf+i);
		}
	}

	memcpy(out, outBuf, outLen);
}

static void GenerateKeyIV(const char *passphrase, const byte *salt, unsigned int saltLength, byte *key, byte *IV)
{
	unsigned int passphraseLength = strlen(passphrase);
	SecByteBlock temp(passphraseLength+saltLength);
	memcpy(temp, passphrase, passphraseLength);
	memcpy(temp+passphraseLength, salt, saltLength);
	SecByteBlock keyIV(KEYLENGTH+BLOCKSIZE);
	Mash(temp, passphraseLength + saltLength, keyIV, KEYLENGTH+BLOCKSIZE, MASH_ITERATIONS);
	memcpy(key, keyIV, KEYLENGTH);
	memcpy(IV, keyIV+KEYLENGTH, BLOCKSIZE);
}

// ********************************************************

DefaultEncryptor::DefaultEncryptor(const char *passphrase, BufferedTransformation *outQ)
	: Filter(outQ)
{
	assert(SALTLENGTH <= DefaultHashModule::DIGESTSIZE);
	assert(BLOCKSIZE <= DefaultHashModule::DIGESTSIZE);

	SecByteBlock salt(DefaultHashModule::DIGESTSIZE), keyCheck(DefaultHashModule::DIGESTSIZE);
	DefaultHashModule hash;

	// use hash(passphrase | time | clock) as salt
	hash.Update((byte *)passphrase, strlen(passphrase));
	time_t t=time(0);
	hash.Update((byte *)&t, sizeof(t));
	clock_t c=clock();
	hash.Update((byte *)&c, sizeof(c));
	hash.Final(salt);

	// use hash(passphrase | salt) as key check
	hash.Update((byte *)passphrase, strlen(passphrase));
	hash.Update(salt, SALTLENGTH);
	hash.Final(keyCheck);

	outQueue->Put(salt, SALTLENGTH);

	// mash passphrase and salt together into key and IV
	SecByteBlock key(KEYLENGTH);
	SecByteBlock IV(BLOCKSIZE);
	GenerateKeyIV(passphrase, salt, SALTLENGTH, key, IV);

	cipher.reset(new Default_ECB_Encryption(key));
	outQueue.reset(new CBCPaddedEncryptor(*cipher, IV, outQueue.release()));

	outQueue->Put(keyCheck, BLOCKSIZE);
}

void DefaultEncryptor::Put(byte inByte)
{
	outQueue->Put(inByte);
}

void DefaultEncryptor::Put(const byte *inString, unsigned int length)
{
	outQueue->Put(inString, length);
}

// ********************************************************

DefaultDecryptor::DefaultDecryptor(const char *p, BufferedTransformation *outQueue)
	: Filter(outQueue),
	  passphrase(strlen(p)+1),
	  salt(SALTLENGTH),
	  keyCheck(BLOCKSIZE)
{
	strcpy(passphrase, p);
	state = WAITING_FOR_KEYCHECK;
	count = 0;
}

void DefaultDecryptor::Put(byte inByte)
{
	if (state==WAITING_FOR_KEYCHECK)
	{
		assert (count < SALTLENGTH+BLOCKSIZE);

		if (count < SALTLENGTH)
			salt[count]=inByte;
		else
			keyCheck[count-SALTLENGTH]=inByte;

		if (++count == SALTLENGTH+BLOCKSIZE)
			CheckKey();
	}
	else
		outQueue->Put(inByte);
}

void DefaultDecryptor::Put(const byte *inString, unsigned int length)
{
	while (state==WAITING_FOR_KEYCHECK && length)
	{
		Put(*inString++);
		length--;
	}

	if (length)
		outQueue->Put(inString, length);
}

void DefaultDecryptor::CheckKey()
{
	SecByteBlock check(STDMAX((unsigned int)2*BLOCKSIZE, (unsigned int)DefaultHashModule::DIGESTSIZE));

	DefaultHashModule hash;
	hash.Update((byte *)passphrase.ptr, strlen(passphrase));
	hash.Update(salt, SALTLENGTH);
	hash.Final(check);

	SecByteBlock key(KEYLENGTH);
	SecByteBlock IV(BLOCKSIZE);
	GenerateKeyIV(passphrase, salt, SALTLENGTH, key, IV);

	cipher.reset(new Default_ECB_Decryption(key));
	std::auto_ptr<CBCPaddedDecryptor> decryptor(new CBCPaddedDecryptor(*cipher, IV));

	decryptor->Put(keyCheck, BLOCKSIZE);
	decryptor->ProcessBuf();
	decryptor->Get(check+BLOCKSIZE, BLOCKSIZE);

	if (memcmp(check, check+BLOCKSIZE, BLOCKSIZE))
		state = KEY_BAD;
	else
		state = KEY_GOOD;

	decryptor->Attach(outQueue.release());
	outQueue.reset(decryptor.release());
}

NAMESPACE_END
