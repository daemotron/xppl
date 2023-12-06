#include <string.h>
#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_hash.h>
#include <xppl_map.h>
#include "_entry.h"
#include "_page.h"


size_t
__entry_locate_free_page(xppl_map_t *map, size_t index)
{
    for (size_t i = 0; i < map->pages; i++)
    {
        if (map->entries[i][index].key == NULL)
        {
            return i;
        }
    }
    _page_create(map);
    return (map->pages - 1);
}


xppl_map_entry_t *
__entry_create(xppl_map_t *map, const char *key)
{
    uint64_t hash = xppl_hash_fnv1a(key);
    size_t keylen = strlen(key);
    size_t index = ((size_t)hash) % map->page_size;
    size_t page = __entry_locate_free_page(map, index);

    map->entries[page][index].key = xppl_calloc(keylen + 1, sizeof(char));
    memcpy(map->entries[page][index].key, key, keylen);
    map->entries[page][index].hash = hash;

    return &(map->entries[page][index]);
}


void
_entry_create_i(xppl_map_t *map, const char *key, int value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.i = value;
}


void
_entry_create_l(xppl_map_t *map, const char *key, long value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.l = value;
}


void
_entry_create_f(xppl_map_t *map, const char *key, float value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.f = value;
}


void
_entry_create_d(xppl_map_t *map, const char *key, double value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.d = value;
}


void
_entry_create_u(xppl_map_t *map, const char *key, unsigned long value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.u = value;
}


void
_entry_create_p(xppl_map_t *map, const char *key, void *value)
{
    xppl_map_entry_t *entry = __entry_create(map, key);
    entry->value.p = value;
}


void
_entry_destroy(xppl_map_entry_t *entry)
{
    free(entry->key);
    entry->key = NULL;
    entry->hash = (uint64_t)0;
    entry->value.u = 0UL;
}


xppl_map_entry_t *
_entry_get(xppl_map_t *map, const char *key)
{
    uint64_t hash = xppl_hash_fnv1a(key);
    size_t index = ((size_t)hash) % map->page_size;
    for (size_t i = 0; i < map->pages; i++)
    {
        if (!(map->entries[i][index].key == NULL) && (strncmp(map->entries[i][index].key, key, xppl_min(strlen(map->entries[i][index].key), strlen(key))) == 0))
        {
            return &(map->entries[i][index]);
        }
    }
    return NULL;
}


xppl_map_entry_t *
_entry_get_or_create(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        entry = __entry_create(map, key);
    }
    return entry;
}
