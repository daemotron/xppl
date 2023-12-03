#include <xppl_endianess.h>
#include <xppl_float.h>
#include <xppl_test.h>
#include "_test_xppl_endianess.h"


bool __test_xppl_end_01_def(void);
bool __test_xppl_end_02_int16(void);
bool __test_xppl_end_03_int32(void);
bool __test_xppl_end_04_int64(void);
bool __test_xppl_end_05_float(void);
bool __test_xppl_end_06_double(void);


void
_test_xppl_endianess_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Endianess");
    xppl_test_case_create(suite, __test_xppl_end_01_def, "endianess defined");
    xppl_test_case_create(suite, __test_xppl_end_02_int16, "endiness for int16");
    xppl_test_case_create(suite, __test_xppl_end_03_int32, "endiness for int32");
    xppl_test_case_create(suite, __test_xppl_end_04_int64, "endiness for int64");
    xppl_test_case_create(suite, __test_xppl_end_05_float, "endiness for float");
    xppl_test_case_create(suite, __test_xppl_end_06_double, "endiness for double");
}


bool
__test_xppl_end_01_def(void)
{
    if (XPPL_ENDIANNESS_BE || XPPL_ENDIANNESS_LE)
    {
        return true;
    }
    return false;
}


bool
__test_xppl_end_02_int16(void)
{
    uint16_t original = 0x1122U;
    uint16_t net = xppl_htons(original);
    uint16_t host = xppl_ntohs(net);
    return (host == original);
}


bool
__test_xppl_end_03_int32(void)
{
    uint32_t original = 0x11223344U;
    uint32_t net = xppl_htonl(original);
    uint32_t host = xppl_ntohl(net);
    return (host == original);
}


bool
__test_xppl_end_04_int64(void)
{
    uint64_t original = 0x1122334455667788U;
    uint64_t net = xppl_htonll(original);
    uint64_t host = xppl_ntohll(net);
    return (host == original);
}


bool
__test_xppl_end_05_float(void)
{
    float original = 123.456f;
    float net = xppl_htonf(original);
    float host = xppl_ntohf(net);
    return xppl_float_almost_equal_f(original, host);
}


bool
__test_xppl_end_06_double(void)
{
    double original = 123456.789123;
    double net = xppl_htond(original);
    double host = xppl_ntohd(net);
    return xppl_float_almost_equal_d(original, host);
}
