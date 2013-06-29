#ifndef CRYPTOPP_DEFAULT_H
#define CRYPTOPP_DEFAULT_H

#include "sha.h"
#include "des.h"
#include "filters.h"

NAMESPACE_BEGIN(CryptoPP)

typedef DES_EDE_Encryption Default_ECB_Encryption;
typedef DES_EDE_Decryption Default_ECB_Decryption;
typedef SHA DefaultHashModule;

class DefaultEncryptor : public Filter
{
public:
	DefaultEncryptor(const char *passphrase, BufferedTransformation *outQueue = NULL);

	void Put(byte inByte);
	void Put(const byte *inString, unsigned int length);

private:
	member_ptr<Default_ECB_Encryption> cipher;
};

class DefaultDecryptor : public Filter
{
public:
	DefaultDecryptor(const char *passphrase, BufferedTransformation *outQueue = NULL);

	void Put(byte inByte);
	void Put(const byte *inString, unsigned int length);

	enum State {WAITING_FOR_KEYCHECK, KEY_GOOD, KEY_BAD};
	State CurrentState() const {return state;}

private:
	void CheckKey();
	State state;
	SecBlock<char> passphrase;
	SecByteBlock salt, keyCheck;
	int count;
	member_ptr<Default_ECB_Decryption> cipher;
};

NAMESPACE_END

#endif
