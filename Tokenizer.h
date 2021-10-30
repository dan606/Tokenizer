#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstddef>

namespace Tokenizer {

class Buffer
{
public:
    inline Buffer() :
        mData(nullptr), mCapacity(0)
    { }

    ~Buffer();

public:
    inline char * data() const
    {
        return mData;
    }

    inline size_t capacity() const
    {
        return mCapacity;
    }

    void ensureCapacity(size_t capacity);

private:
    char * mData;
    size_t mCapacity;
};

class Coder
{
public:
    inline Coder() :
        mFrameLength(0)
    { }

public:
    inline const char * data() const
    {
        return mBuffer.data();
    }

    inline size_t size() const
    {
        return mFrameLength;
    }

    void code(const char * data, size_t size);

private:
    Buffer mBuffer;
    size_t mFrameLength;
};

class Decoder
{
public:
    inline Decoder() :
        mBufferSize(0), mFrameLength(0)
    { }

public:
    inline const char * data() const
    {
        return mBuffer.data();
    }

    inline size_t size() const
    {
        return mFrameLength;
    }

    void reset();

    void feed(const char * data, size_t size);

    bool decode();

private:
    Buffer mBuffer;
    size_t mBufferSize;
    size_t mFrameLength;
};

}

#endif // TOKENIZER_H
