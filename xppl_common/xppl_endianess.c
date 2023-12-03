#include <string.h>
#include <xppl_endianess.h>
#include <xppl_int.h>


uint32_t
__load_u32be(const unsigned char *buf)
{
    return (uint32_t)buf[0] << 24 | (uint32_t)buf[1] << 16 |
           (uint32_t)buf[2] <<  8 | (uint32_t)buf[3] <<  0;
}


uint64_t
__load_u64be(const unsigned char *buf)
{
    return (uint64_t)buf[0] << 56 | (uint64_t)buf[1] << 48 |
           (uint64_t)buf[2] << 40 | (uint64_t)buf[3] << 32 |
           (uint64_t)buf[4] << 24 | (uint64_t)buf[5] << 16 |
           (uint64_t)buf[6] <<  8 | (uint64_t)buf[7] <<  0;
}


float
xppl_htonf(float value)
{
    if (XPPL_ENDIANNESS_BE)
    {
        return value;
    }
    unsigned char buf[4];
    memcpy(&buf[0], &value, 4);
    uint32_t i = __load_u32be(buf);
    float result;
    memcpy(&result, &i, 4);
    return result;
}


float
xppl_ntohf(float value)
{
    return xppl_htonf(value);
}


double
xppl_htond(double value)
{
    if (XPPL_ENDIANNESS_BE)
    {
        return value;
    }
    unsigned char buf[8];
    memcpy(&buf[0], &value, 8);
    uint64_t i = __load_u64be(buf);
    double result;
    memcpy(&result, &i, 8);
    return result;
}


double
xppl_ntohd(double value)
{
    return xppl_htond(value);
}
