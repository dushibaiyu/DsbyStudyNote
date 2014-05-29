// gzip.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "gzip.h"

NAMESPACE_BEGIN(CryptoPP)

Gzip::Gzip(int dlevel, BufferedTransformation *bt)
	: Deflator(dlevel, bt),
	  totalLen(0)
{
	assert (dlevel >= 1 && dlevel <= 9);
	outQueue->Put(MAGIC1);
	outQueue->Put(MAGIC2);
	outQueue->Put(DEFLATED);
	outQueue->Put(0);       // general flag
	outQueue->PutLong(0);   // time stamp
	byte extra = (dlevel == 1) ? FAST : ((dlevel == 9) ? SLOW : 0);
	outQueue->Put(extra);
	outQueue->Put(GZIP_OS_CODE);
}

void Gzip::Put(byte inByte)
{
	Deflator::Put(inByte);
	crc.Update(&inByte, 1);
	++totalLen;
}

void Gzip::Put(const byte *inString, unsigned int length)
{
	Deflator::Put(inString, length);
	crc.Update(inString, length);
	totalLen += length;
}

void Gzip::InputFinished()
{
	Deflator::InputFinished();
	outQueue->PutLong(crc.GetCrc(), false);
	outQueue->PutLong(totalLen, false);
}

// 'this' : used in base member initializer list
#pragma warning(disable: 4355)

Gunzip::Gunzip(BufferedTransformation *output,
			   BufferedTransformation *bypassed)
	: Fork(2), inflater(new BodyProcesser(*this), new TailProcesser(*this))
{
	SelectOutPort(1);
	Attach(bypassed ? bypassed : new BitBucket);
	SelectOutPort(0);
	Attach(output);

	state = PROCESS_HEADER;
	tailLen = 0;
}

void Gunzip::Put(const byte *inString, unsigned int length)
{
	switch (state)
	{
		case PROCESS_HEADER:
			inQueue.Put(inString, length);
			if (inQueue.CurrentSize()>=MAX_HEADERSIZE)
				ProcessHeader();
			break;
		case PROCESS_BODY:
			inflater.Put(inString, length);
			break;
		case AFTER_END:
			AccessPort(1).Put(inString, length);
			break;
	}
}

void Gunzip::InputFinished()
{
	if (state==PROCESS_HEADER)
		ProcessHeader();

	if (state!=AFTER_END)
		inflater.InputFinished();
}

void Gunzip::ProcessHeader()
{
	byte buf[6];
	byte b, flags;

	if (inQueue.Get(buf, 2)!=2) goto error;
	if (buf[0] != MAGIC1 || buf[1] != MAGIC2) goto error;
	if (!inQueue.Skip(1)) goto error;    // skip extra flags
	if (!inQueue.Get(flags)) goto error;
	if (flags & (ENCRYPTED | CONTINUED)) goto error;
	if (inQueue.Skip(6)!=6) goto error;    // Skip file time, extra flags and OS type

	if (flags & EXTRA_FIELDS)   // skip extra fields
	{
		word16 length;
		if(!inQueue.GetShort(length, false)) goto error;
		if (inQueue.Skip(length)!=length) goto error;
	}

	if (flags & FILENAME)   // skip filename
		do
			if(!inQueue.Get(b)) goto error;
		while (b);

	if (flags & COMMENTS)   // skip comments
		do
			if(!inQueue.Get(b)) goto error;
		while (b);

	inQueue.TransferTo(inflater);
	state = PROCESS_BODY;
	return;
error:
	throw HeaderErr();
}

void Gunzip::ProcessTail()
{
	assert(tailLen == 8);

	word32 calculatedCrc = crc.GetCrc();

	if ((((word32)tail[0]) | ((word32)tail[1] << 8) | ((word32)tail[2] << 16) | ((word32)tail[3] << 24)) != calculatedCrc)
		throw CrcErr();

	if ((((word32)tail[4]) | ((word32)tail[5] << 8) | ((word32)tail[6] << 16) | ((word32)tail[7] << 24)) != totalLen)
		throw LengthErr();

	tailLen = 9;    // signal TailProcesser to bypass everything from now on
}

Gunzip::BodyProcesser::BodyProcesser(Gunzip &parent)
	: parent(parent)
{
	parent.totalLen = 0;
}

void Gunzip::BodyProcesser::Put(const byte *inString, unsigned int length)
{
	parent.AccessPort(0).Put(inString, length);
	parent.crc.Update(inString, length);
	parent.totalLen += length;
}

Gunzip::TailProcesser::TailProcesser(Gunzip &parent)
	: parent(parent)
{
	parent.tailLen = 0;
}

void Gunzip::TailProcesser::Put(const byte *inString, unsigned int length)
{
	if (parent.tailLen < 8)
	{
		int l = STDMIN(8-parent.tailLen, length);
		memcpy(parent.tail+parent.tailLen, inString, l);
		inString += l;
		length -= l;
		parent.tailLen += l;
	}

	if (parent.tailLen == 8)
		parent.ProcessTail();

	if (length)
		parent.AccessPort(1).Put(inString, length);
}

NAMESPACE_END
