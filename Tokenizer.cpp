#include "Tokenizer.h"
#include <cstdint>
#include <memory>

typedef std::uint32_t FrameLength;

Tokenizer::Buffer::~Buffer()
{
    if (mData)
        free(mData);
}

void Tokenizer::Buffer::ensureCapacity(size_t capacity)
{
    // TODO: kontrola chyb
    if (capacity > mCapacity)
    {
        mCapacity = capacity;
        mData = (char *)realloc(mData, mCapacity);
    }
}

void Tokenizer::Coder::code(const char *data, size_t size)
{
    if (!data)
        size = 0;
    mFrameLength = size + sizeof(FrameLength);
    mBuffer.ensureCapacity(mFrameLength);
    // POZOR! Endianita
    *reinterpret_cast<FrameLength *>(mBuffer.data()) = static_cast<FrameLength>(mFrameLength);
    if (size)
        memcpy(mBuffer.data() + sizeof(FrameLength), data, size);
}

void Tokenizer::Decoder::reset()
{
    if (mFrameLength)
    {
        // Odstranit frame z bufra
        mBufferSize -= mFrameLength;
        memmove(mBuffer.data(), mBuffer.data() + mFrameLength, mBufferSize);
        mFrameLength = 0;
    }
}

void Tokenizer::Decoder::feed(const char *data, size_t size)
{
    if (data && size)
    {
        mBuffer.ensureCapacity(mBufferSize + size);
        memcpy(mBuffer.data() + mBufferSize, data, size);
        mBufferSize += size;
    }
}

bool Tokenizer::Decoder::decode()
{
    if (mBufferSize >= sizeof(FrameLength))
    {
        // POZOR! Endianita
        const FrameLength frameLength = *reinterpret_cast<const FrameLength *>(mBuffer.data());
        if (mBufferSize >= frameLength)
        {
            mFrameLength = frameLength;
            return true;
        }
    }
    return false;
}
