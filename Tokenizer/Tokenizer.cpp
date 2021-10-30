#include "Tokenizer.h"

#include <iostream>

Tokenizer::Tokenizer(size_t bufferSize) : mBufferCapacity(0), mCurrentBufferSize(0), mCurrentTokenDataSize(0)
{
    mBuffer = new char[bufferSize];
    mBufferCapacity = bufferSize;
}

Tokenizer::~Tokenizer()
{
    delete[] mBuffer;
    mBuffer = nullptr;
    mBufferCapacity = 0;
    mCurrentBufferSize = 0;
    mCurrentTokenDataSize = 0;
}

bool Tokenizer::createToken(char *inputDataBuff, size_t inputDataSize, size_t buffSize, size_t &newSize)
{
    if(memmove_s(inputDataBuff+7, buffSize, inputDataBuff, inputDataSize) == 0)
    {
        newSize = inputDataSize+7;
        return true;
    }
    return false;
}

bool Tokenizer::process(const char *data, size_t len)
{
    size_t dataOffset = 0;

    while(mCurrentTokenDataSize && dataOffset < len)
    {
        // jiz ma token data size, nacte data z tokenu
        // dokud neni konec dat nebo konec dat tokenu dle delky z hlavicky
        mBuffer[mCurrentBufferSize++] = *(data + dataOffset);
        dataOffset++;
        mCurrentTokenDataSize--;
    }

    while(mCurrentTokenDataSize == 0 && dataOffset < len)
    {
        while(dataOffset < len && (*(data + dataOffset) == (char)0xFF))
        {
            // ctu dokud nemam nactenou celou prvni cast hlavicky (0xFF0xFF0xFF)
            mBuffer[mCurrentBufferSize++] = *(data + dataOffset);
            dataOffset++;
            mCurrentHeaderSize++;
        }

        if(mCurrentHeaderSize == 3)
        {
            // ma prvni cast  hlavicky, precte delku dat z hlavicky
            while(dataOffset < len && mCurrentHeaderDataSize < 4)
            {
                // ctu dokud nemam nactenou celou prvni cast hlavicky (0xFF0xFF0xFF)
                mBuffer[mCurrentBufferSize++] = *(data + dataOffset);
                dataOffset++;
                mCurrentHeaderDataSize++;
            }

            if(mCurrentHeaderDataSize == 4)
            {
                // nactu delku dat z hlavicky
                mCurrentTokenDataSize = (int)*mBuffer + ((int)*(mBuffer-1)<< 8) + ((int)*(mBuffer-2)<<16) + ((int)*(mBuffer-3)<<24);
                std::cout << "NEW TOKEN DATA SIZE: " << mCurrentTokenDataSize << std::endl;
            }
        }
    }
//        while(*(data + dataOffset) == (char)0xFF &&
//              *(data + dataOffset + 1) == (char)0xFF &&
//              *(data + dataOffset + 2) == (char)0xFF)
//        {

//        }
    }
    return false;
}

bool Tokenizer::hasProcessed()
{
    return false;
}

bool Tokenizer::getProcessed(char *buff, size_t buffSize, const size_t &processed)
{
    return false;
}
