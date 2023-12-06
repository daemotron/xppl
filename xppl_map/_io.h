#ifndef _XPPL_MAP_IO_H_
#define _XPPL_MAP_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define XPPL_MAP_IO_IDENT_LE 0xd7cf4232238abb91
#define XPPL_MAP_IO_IDENT_BE 0x4942b64be752473b

void _io_save(xppl_map_t *, const char *);
void _io_load(xppl_map_t *, const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_MAP_IO_H_ */
