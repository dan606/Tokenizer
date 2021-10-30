#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unistd.h>
#include <stdint.h>

// first 3 bytes
uint8_t TOKEN_HEADER[3]={0xFF,0xFF,0xFF};
// next 4 bytes is length
// 0x00 0x00 0x00 0x0A // 10 bytes

// [HEADER] [DATA LENGTH] [DATA]
// XX XX XX YY YY YY YY . . . . . . . .

class Tokenizer
{
public:
    Tokenizer(size_t bufferSize);
    ~Tokenizer();

public:
    // create token to write
    bool createToken(char* inputDataBuff, size_t inputDataSize, size_t buffSize, size_t& newSize);

    // read tokens
    bool process(const char* data, size_t len);

    bool hasProcessed();
    bool getProcessed(char* buff, size_t buffSize, const size_t& processed);


private:
    char* mBuffer;                  // buffer pro cetni a zapis
    size_t mBufferCapacity;         // maximalni kapacita buffera
    size_t mCurrentBufferSize;      // aktualni naplneni buffera
    size_t mCurrentHeaderSize;      // stav nacteni aktualni hlavicky
    size_t mCurrentHeaderDataSize;  // stav nacteni aktualni velikosti dat z hlvicky
    size_t mCurrentTokenDataSize;   // nactena delka dat z hlavicky
};

#endif // TOKENIZER_H
