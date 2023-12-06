#include <xppl_map.h>
#include "_entry.h"
#include "_page.h"
#include "_io.h"


void
xppl_map_init(xppl_map_t *map, size_t page_size)
{
    if (page_size == 0)
    {
        page_size = XPPL_MAP_PAGE_SIZE_DEFAULT;
    }
    map->entries = NULL;
    map->page_size = page_size;
    map->pages = 0;
    _page_create(map);
}


void
xppl_map_destroy(xppl_map_t *map)
{
    _page_destroy_all(map);
}


xppl_map_entry_t *
xppl_map_get(xppl_map_t *map, const char *key)
{
    return _entry_get(map, key);
}


int
xppl_map_get_i(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return 0;
    }
    else
    {
        return entry->value.i;
    }
}


long
xppl_map_get_l(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return 0L;
    }
    else
    {
        return entry->value.l;
    }
}


float
xppl_map_get_f(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return 0.0f;
    }
    else
    {
        return entry->value.f;
    }
}


double
xppl_map_get_d(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return 0.0;
    }
    else
    {
        return entry->value.d;
    }
}


unsigned long
xppl_map_get_u(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return 0ul;
    }
    else
    {
        return entry->value.u;
    }
}


void *
xppl_map_get_p(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        return NULL;
    }
    else
    {
        return entry->value.p;
    }
}


void
xppl_map_set_i(xppl_map_t *map, const char *key, int value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_i(map, key, value);
    }
    else
    {
        entry->value.i = value;
    }
}


void
xppl_map_set_l(xppl_map_t *map, const char *key, long value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_l(map, key, value);
    }
    else
    {
        entry->value.l = value;
    }
}


void
xppl_map_set_f(xppl_map_t *map, const char *key, float value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_f(map, key, value);
    }
    else
    {
        entry->value.f = value;
    }
}


void
xppl_map_set_d(xppl_map_t *map, const char *key, double value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_d(map, key, value);
    }
    else
    {
        entry->value.d = value;
    }
}


void
xppl_map_set_u(xppl_map_t *map, const char *key, unsigned long value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_u(map, key, value);
    }
    else
    {
        entry->value.u = value;
    }
}


void
xppl_map_set_p(xppl_map_t *map, const char *key, void *value)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry == NULL)
    {
        _entry_create_p(map, key, value);
    }
    else
    {
        entry->value.p = value;
    }
}


void
xppl_map_delete(xppl_map_t *map, const char *key)
{
    xppl_map_entry_t *entry = _entry_get(map, key);
    if (entry != NULL)
    {
        _entry_destroy(entry);
    }
}


void
xppl_map_load(xppl_map_t *map, const char *file)
{
    _io_load(map, file);
}


void
xppl_map_save(xppl_map_t *map, const char *file)
{
    _io_save(map, file);
}
