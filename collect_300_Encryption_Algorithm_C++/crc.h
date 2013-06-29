#ifndef CRYPTOPP_CRC32_H
#define CRYPTOPP_CRC32_H

#include "cryptlib.h"

NAMESPACE_BEGIN(CryptoPP)

/* Must use this value instead of ~0 due to 64-bit computers */
const unsigned long CRC32_NEGL = 0xffffffffL;

class CRC32 : public HashModule
{
public:
	CRC32();
	void Update(const byte *input, unsigned int length);
	void Final(byte *hash);
	unsigned int DigestSize() const {return 4;}

	void Reset() {curr_crc = CRC32_NEGL;}
	void UpdateByte(byte b) {curr_crc = crc_32_tab[byte(curr_crc ^ b)] ^ (curr_crc >> 8);}
	word32 GetCrc() const {return curr_crc ^ CRC32_NEGL;}

private:
	static const unsigned long crc_32_tab[256];
	unsigned long curr_crc;
};

NAMESPACE_END

#endif
