/**
 * File Format
 * 
 * Header: 4 x 8 bytes
 * 1 - format identifier
 * 2 - entry value size s
 * 3 - entry count
 * 4 - entry size
 * 
 * Entries
 * 8 bytes - key length n incl. terminator
 * s bytes - value
 * n bytes - key (null-terminated)
 */
#include <xppl_endianess.h>
#include <xppl_alloc.h>
#include <xppl_int.h>
#include <xppl_log.h>
#include <xppl_map.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "_io.h"
#include "_entry.h"


#if XPPL_ENDIANNESS_LE
# define XPPL_MAP_IO_IDENT XPPL_MAP_IO_IDENT_LE
#else
# define XPPL_MAP_IO_IDENT XPPL_ENDIANNESS_BE
#endif


size_t
_io_entry_val_size(void)
{
    xppl_map_entry_t entry;
    return sizeof(entry.value);
}


void
_io_save(xppl_map_t *map, const char *file)
{
    uint8_t *buffer = xppl_calloc(4, sizeof(uint64_t));
    //uint64_t *header = (uint64_t *)buffer;
    uint64_t header[4] = { 0UL };
    size_t bufsize = 4 * sizeof(uint64_t);
    uint64_t keylen = 0;
    size_t entrysize = 0;
    size_t valsize = _io_entry_val_size();
    header[0] = xppl_htonll(XPPL_MAP_IO_IDENT);
    header[1] = (uint64_t)valsize;
    header[2] = 0UL;
    header[3] = 0UL;

    for (size_t p = 0; p < map->pages; p++)
    {
        for (size_t e = 0; e < map->page_size; e++)
        {
            if (map->entries[p][e].key != NULL)
            {
                keylen = (uint64_t)strlen(map->entries[p][e].key) + 1;
                entrysize = (sizeof(uint64_t) + valsize + (size_t)keylen) * sizeof(uint8_t); 
                bufsize += entrysize;
                buffer = xppl_realloc(buffer, bufsize);
                memcpy(&buffer[bufsize - entrysize], &keylen, sizeof(uint64_t));
                memcpy(&buffer[bufsize - entrysize + sizeof(uint64_t)], &(map->entries[p][e].value), valsize);
                memcpy(&buffer[bufsize - entrysize + sizeof(uint64_t) + valsize], map->entries[p][e].key, (size_t)keylen - 1);
                buffer[bufsize - 1] = (uint8_t)0U;
                header[2]++;
                header[3] += (uint64_t)entrysize;
            }
        }
    }

    memcpy(buffer, header, 4 * sizeof(uint64_t));

    FILE *fp = fopen(file, "w");
    if (fp == NULL)
    {
        xppl_log_error("Cannot write to file %s", file);
        free(buffer);
        return;
    }
    fwrite(buffer, sizeof(uint8_t), bufsize, fp);
    fclose(fp);
    free(buffer);
}


void
_io_load(xppl_map_t *map, const char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        xppl_log_error("Unable to read file %s", file);
        return;
    }

    uint64_t header[4] = { 0U };
    size_t chunks = fread(&header, sizeof(uint64_t), 4, fp);
    if (chunks != 4)
    {
        xppl_log_warn("File %s has an invalid format: could not read header (only %d bytes read)", chunks);
        fclose(fp);
        return;
    }

    uint64_t format = xppl_ntohll(header[0]);
    if ((format != XPPL_MAP_IO_IDENT_BE) && (format != XPPL_MAP_IO_IDENT_LE))
    {
        xppl_log_warn("File %s has an invalid format: no valid XPPL map header found.");
        fclose(fp);
        return;
    }

    if (format != XPPL_MAP_IO_IDENT)
    {
        xppl_log_warn("File %s has incorrect endianess and cannot be read on this platform.");
        fclose(fp);
        return;
    }

    uint8_t *buffer = xppl_calloc(sizeof(uint8_t), (size_t)header[3]);
    chunks = fread(buffer, sizeof(uint8_t), (size_t)header[3], fp);
    fclose(fp);

    if (chunks < (size_t)header[3])
    {
        xppl_log_error("File %s is corrupted - only found %zu bytes instead of %llu", chunks, header[3]);
        free(buffer);
        return;
    }

    size_t offset = 0;
    while (offset < (size_t)header[3])
    {
        xppl_map_entry_t *entry = _entry_get_or_create(map, (char *)(&buffer[offset + sizeof(uint64_t) + (size_t)header[1]]));
        memcpy(&(entry->value), &buffer[offset + sizeof(uint64_t)], (size_t)header[1]);
        offset += (sizeof(uint64_t) + (size_t)header[1] + (size_t)(*((uint64_t *)(&buffer[offset]))));
    }
}
