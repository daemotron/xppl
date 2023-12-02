#include <xppl_alloc.h>
#include <xppl_map.h>
#include "_page.h"
#include "_entry.h"


void
_page_create(xppl_map_t *map)
{
    if (map == NULL)
    {
        return;
    }
    map->pages++;
    if (map->entries == NULL)
    {
        map->entries = xppl_calloc(map->pages, sizeof(xppl_map_entry_t *));
    }
    else
    {
        map->entries = xppl_realloc(map->entries, sizeof(xppl_map_entry_t *) * map->pages);
    }
    map->entries[map->pages - 1] = xppl_calloc(map->page_size, sizeof(xppl_map_entry_t));
    for (size_t i = 0; i < map->page_size; i++)
    {
        map->entries[map->pages - 1][i].key = NULL;
    }
}


void
_page_destroy_all(xppl_map_t *map)
{
    for (;map->pages > 0; map->pages--)
    {
        for (size_t i = 0; i < map->page_size; i++)
        {
            _entry_destroy(&map->entries[map->pages - 1][i]);
        }
        free(map->entries[map->pages - 1]);
    }
    free(map->entries);
}
