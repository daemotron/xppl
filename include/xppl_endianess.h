#ifndef _XPPL_ENDIANESS_H_
#define _XPPL_ENDIANESS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The following macros are based on rofl0r's one file public domain
 * library to determine endianess at compile time
 * 
 * cf. https://github.com/rofl0r/endianness.h
 * 
 * Their purpose is to define either
 * XPPL_ENDIANESS_LE to signal a little endian platform, or
 * XPPL_ENDIANESS_BE to signal a big endian platform * 
 */

/* This catches all modern GCCs (>= 4.6) and Clang (>=3.2) */
#if (defined __BYTE_ORDER__) && (defined __ORDER_LITTLE_ENDIAN__)
# if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define XPPL_ENDIANNESS_LE 1
#  define XPPL_ENDIANNESS_BE 0
# elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define XPPL_ENDIANNESS_LE 0
#  define XPPL_ENDIANNESS_BE 1
# endif
/* Try to derive from arch/compiler-specific macros */
#elif defined(_X86_) || defined(__x86_64__) || defined(__i386__) || \
      defined(__i486__) || defined(__i586__) || defined(__i686__) || \
      defined(__MIPSEL) || defined(_MIPSEL) || defined(MIPSEL) || \
      defined(__ARMEL__) || \
      defined(__MSP430__) || \
      (defined(__LITTLE_ENDIAN__) && __LITTLE_ENDIAN__ == 1) || \
      (defined(_LITTLE_ENDIAN) && _LITTLE_ENDIAN == 1) || \
      defined(_M_ARM) || defined(_M_ARM64) || \
      defined(_M_IX86) || defined(_M_AMD64)
# define XPPL_ENDIANNESS_LE 1
# define XPPL_ENDIANNESS_BE 0
#elif defined(__MIPSEB) || defined(_MIPSEB) || defined(MIPSEB) || \
      defined(__MICROBLAZEEB__) || defined(__ARMEB__) || \
      (defined(__BIG_ENDIAN__) && __BIG_ENDIAN__ == 1) || \
      (defined(_BIG_ENDIAN) && _BIG_ENDIAN == 1)
# define XPPL_ENDIANNESS_LE 0
# define XPPL_ENDIANNESS_BE 1
/* Try to get it from a header */
#else
# if defined(__linux) || defined(__HAIKU__)
#  include <endian.h>
# elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
       defined(__DragonFly__)
#  include <sys/endian.h>
# elif defined(__APPLE__)
#  include <machine/endian.h>
# endif
#endif

#ifndef XPPL_ENDIANNESS_LE
# undef XPPL_ENDIANNESS_BE
# if defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN)
#  if __BYTE_ORDER == __LITTLE_ENDIAN
#   define XPPL_ENDIANNESS_LE 1
#   define XPPL_ENDIANNESS_BE 0
#  elif __BYTE_ORDER == __BIG_ENDIAN
#   define XPPL_ENDIANNESS_LE 0
#   define XPPL_ENDIANNESS_BE 1
#  endif
# elif defined(BYTE_ORDER) && defined(LITTLE_ENDIAN)
#  if BYTE_ORDER == LITTLE_ENDIAN
#   define XPPL_ENDIANNESS_LE 1
#   define XPPL_ENDIANNESS_BE 0
#  elif BYTE_ORDER == BIG_ENDIAN
#   define XPPL_ENDIANNESS_LE 0
#   define XPPL_ENDIANNESS_BE 1
#  endif
# endif
#endif

/**
 * The following macros provide platform-independent byte-order
 * conversion for 16, 32 and 64 bit integers, as well as float and double
 */
#if IBM
#include <winsock2.h>
#else /* !IBM */
# include <arpa/inet.h>
# if APL
#  include <libkern/OSByteOrder.h>
# else /* LIN */
#  include <endian.h>
# endif /* APL or LIN */
#endif /* Windows or Unix */
#include <stdint.h>

# define xppl_htons(x)  ((uint16_t)htons(x))
# define xppl_htonl(x)  ((uint32_t)htonl(x))
# define xppl_ntohs(x)  ((uint16_t)ntohs(x))
# define xppl_ntohl(x)  ((uint32_t)ntohl(x))

float xppl_htonf(float);
float xppl_ntohf(float);
double xppl_htond(double);
double xppl_ntohd(double);

#if IBM
# if XPPL_ENDIANNESS_LE
#  define xppl_htonll(x) (((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#  define xppl_ntohll(x) (((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
# else
#  define xppl_htonll(x) (x)
#  define xppl_ntohll(x) (x)
#endif
#else /* !IBM */
# if APL
# define xppl_htonll(x) ((uint64_t)OSSwapHostToBigInt64(x))
# define xppl_ntohll(x) ((uint64_t)OSSwapBigToHostInt64(x))
# else /* Linux */
#define xppl_htonll(x) ((uint64_t)htobe64(x))
#define xppl_ntohll(x) ((uint64_t)be64toh(x))
# endif /* APL or LIN */
#endif /* Windows or Unix */

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_ENDIANESS_H_ */
