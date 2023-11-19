#include <xppl_int.h>
#include <xppl_hash.h>


uint64_t
xppl_hash_fnv1(const char *key)
{
    uint64_t hash = XPPL_HASH_FNV_OFFSET;
    for (const char *ptr = key; *ptr; ptr++)
    {
        hash *= XPPL_HASH_FNV_PRIME;
        hash ^= (uint64_t)(unsigned char)(*ptr);
    }
    return hash;
} 


uint64_t
xppl_hash_fnv1a(const char *key)
{
    uint64_t hash = XPPL_HASH_FNV_OFFSET;
    for (const char *ptr = key; *ptr; ptr++)
    {
        hash ^= (uint64_t)(unsigned char)(*ptr);
        hash *= XPPL_HASH_FNV_PRIME;
    }
    return hash;
} 
