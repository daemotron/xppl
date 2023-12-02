#include <xppl_test.h>
#include <xppl_map.h>
#include <xppl_float.h>

#include "_test_xppl_map.h"


bool __test_xppl_map_01_init_destroy(void);
bool __test_xppl_map_02_get_set_int(void);
bool __test_xppl_map_03_get_set_int_collision(void);
bool __test_xppl_map_04_get_set_int_mass(void);
bool __test_xppl_map_05_set_int_overwrite(void);
bool __test_xppl_map_06_get_set_long(void);
bool __test_xppl_map_07_get_set_float(void);
bool __test_xppl_map_08_get_set_double(void);
bool __test_xppl_map_09_get_set_unsigned(void);
bool __test_xppl_map_10_get_set_ptr(void);


void
_test_xppl_map_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Map");
    xppl_test_case_create(suite, __test_xppl_map_01_init_destroy, "initialize and destroy map");
    xppl_test_case_create(suite, __test_xppl_map_02_get_set_int, "get and set int");
    xppl_test_case_create(suite, __test_xppl_map_03_get_set_int_collision, "get and set int with collision");
    xppl_test_case_create(suite, __test_xppl_map_04_get_set_int_mass, "get and set int mass test");
    xppl_test_case_create(suite, __test_xppl_map_05_set_int_overwrite, "set int override");
    xppl_test_case_create(suite, __test_xppl_map_06_get_set_long, "get and set long");
    xppl_test_case_create(suite, __test_xppl_map_07_get_set_float, "get and set float");
    xppl_test_case_create(suite, __test_xppl_map_08_get_set_double, "get and set double");
    xppl_test_case_create(suite, __test_xppl_map_09_get_set_unsigned, "get and set unsigned");
    xppl_test_case_create(suite, __test_xppl_map_10_get_set_ptr, "get and set pointer");
}


bool
__test_xppl_map_01_init_destroy(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    bool flag = (map.page_size == XPPL_MAP_PAGE_SIZE_DEFAULT);
    flag = flag && (map.pages == 1);
    xppl_map_destroy(&map);
    flag = flag && (map.pages == 0);
    return flag;
}


bool
__test_xppl_map_02_get_set_int(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_i(&map, "foo", 123);
    bool flag = (xppl_map_get_i(&map, "foo") == 123);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_03_get_set_int_collision(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    const char *key1 = "foo";
    const char *key2 = "x";
    xppl_map_set_i(&map, key1, 123);
    xppl_map_set_i(&map, key2, 456);
    int val1 = xppl_map_get_i(&map, key1);
    int val2 = xppl_map_get_i(&map, key2);
    bool flag = (val1 == 123) && (val2 == 456);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_04_get_set_int_mass(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 8);
    bool flag = true;
    for (int i = 65; i < 91; i++)
    {
        char key[2] = { '\0', '\0' };
        key[0] = (char)i;
        xppl_map_set_i(&map, key, i);
    }
    for (int i = 65; i < 91; i++)
    {
        char key[2] = { '\0', '\0' };
        key[0] = (char)i;
        flag = flag && (xppl_map_get_i(&map, key) == i);
    }
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_05_set_int_overwrite(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_i(&map, "foo", 123);
    bool flag = (xppl_map_get_i(&map, "foo") == 123);
    xppl_map_set_i(&map, "foo", 456);
    flag = flag & (xppl_map_get_i(&map, "foo") == 456);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_06_get_set_long(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_l(&map, "foo", 123L);
    bool flag = (xppl_map_get_l(&map, "foo") == 123L);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_07_get_set_float(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_f(&map, "foo", 123.456F);
    bool flag = xppl_float_almost_equal_f(xppl_map_get_f(&map, "foo"), 123.456F);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_08_get_set_double(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_d(&map, "foo", 123.456789);
    bool flag = xppl_float_almost_equal_d(xppl_map_get_d(&map, "foo"), 123.456789);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_09_get_set_unsigned(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    xppl_map_set_u(&map, "foo", 123UL);
    bool flag = (xppl_map_get_u(&map, "foo") == 123UL);
    xppl_map_destroy(&map);
    return flag;
}


bool
__test_xppl_map_10_get_set_ptr(void)
{
    xppl_map_t map;
    xppl_map_init(&map, 0);
    const char *text = "Lorem ipsum dolor sit amet";
    xppl_map_set_p(&map, "foo", (void *)text);
    bool flag = xppl_test_assert_str_equals(text, (const char *)xppl_map_get_p(&map, "foo"));
    xppl_map_destroy(&map);
    return flag;
}
