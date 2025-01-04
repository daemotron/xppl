# X-Plane Plugin Library (XPPL)

This is a modular collection of utility functions I wrote for various plugins for the
[X-Plane](https://x-plane.com) flight simulator. The code is portable between
Windows, macOS and Linux. It is not a classic library in the sense that this code doesn't
provide build support for a shared / dynamically linked library.

![XPPL Build Status](https://github.com/daemotron/xppl/actions/workflows/cmake.yml/badge.svg?branch=main)
![MIT License](https://img.shields.io/badge/license-MIT-green.svg)

## How XPPL is organized

The code for each module of the XPPL collection resides in their own directory (cf. list
of modules below). The corresponding public interface header files can all be found in
the `include` directory.

The `xppl_common` module is mandatory; without it being present, none of the other modules
will compile. All public interface functions from the `xppl_common` module are declared
in the header file `xppl.h`; other modules have their own dedicated header file.

## Using XPPL

The easiest way to incorporate some of XPPL's functionality into a plugin project is
to add it as a [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules),
and cherry-pick the modules you actually need by adding the corresponding modules to
your own plugin's build scripts.

```bash
# add XPPL as submodule
git submodule add https://github.com/daemotron/xppl.git

# update the XPPL submodule
git submodule update --remote xppl
```

Assuming the above, the file system layout of your plugin project might look like this:

```
+--+ myPlugin
   |
   + SDK/
   |
   + src/
   |
   + xppl/
   |
   +-- CMakeLists.txt
```

* `SDK` contains a copy of the X-Plane SDK
* `src` contains your own plugin source files
* `xppl` is this repository, embedded as submodule

In your `CMakeLists.txt`, you can embed XPPL modules this way:

1. Add the XPPL `include` directory to the include directories of your project:
   ```cmake
   include_directories ("xppl/include")
   ```
2. Include the matching XPPL headers in your own source files:
   ```c
   #include <xppl.h>
   ```
3. Add the mandatory `xppl_common` module to your source files:
   ```cmake
   file(GLOB_RECURSE XPPL_COMMON_SOURCES "xppl/xppl_common/*.c")
   ...
   set(SOURCES ... ${XPPL_COMMON_SOURCES})
   ```
4. Optionally add further modules in the same way as you added the `common` module.

**Please Note:** the `xppl_common` module is mandatory, all other modules are optional.

## XPPL Modules

### xppl_common

#### Basic Macros

```c
#include <xppl.h>

/* min and max macros */
int i = xppl_max(3, 5);
int j = xppl_min(3, 5);

/* mark unused arguments to prevent compiler warnings */
PLUGIN_API void
XPluginReceiveMessage(XPLMPluginID from, int msg, void *param)
{
    xppl_unused(from);
    xppl_unused(msg);
    xppl_unused(param);
}

/* numeric constants to string */
const char *s = xppl_str(12345);

/* for fatal errors */
xppl_crash();
```

#### Safe Memory Allocation

```c
#include <xppl_alloc.h>

/* will crash gracefully if memory allocation fails */
void *ptr = xppl_malloc(1024);
void *buf = xppl_calloc(50, sizeof(char));
ptr = xppl_realloc(ptr, 2048);
```

#### Endianess

Platform-independent byte-order conversion for 16, 32 and 64 bit integers, as well as float and double

```c
#include <xppl_endianess.h>

if (XPPL_ENDIANESS_LE) {
   /* we're little endian */
}

if (XPPL_ENDIANESS_BE) {
   /* we're big endian */
}

uint16_t sn  = xppl_htons(1234);
uint32_t ln  = xppl_htonl(1234);
uint64_t lln = xppl_htonll(1234);
uint16_t sh  = xppl_ntohs(sn);
uint32_t lh  = xppl_ntohl(ln);
uint64_t llh = xppl_ntohll(lln);

float  fn = xppl_htonf(123.45);
double dn = xppl_htond(123.45);
float  fh = xppl_ntohf(fn);
double dh = xppl_ntohd(dn);
```

#### Float and Int

Comparing floating-point with '==' or '!=' is unsafe

```c
#include <xppl_float.h>

if (xppl_float_almost_equal_f(123.4, 123.4)) {}
if (xppl_float_almost_equal_d(12345.678, 12345.678)) {}
if (xppl_float_almost_equal_l(123456789.123456789, 123456789.123456789)) {}
```

You need big integers?

```c
#include <xppl_int.h>

#ifdef XPPL_INT_128
int128_t super;
uint128_t usuper;
#else
int64_t super;
uint64_t usuper;
#endif
usuper = xppl_int_abs(super);
```

#### Hashing

Non-cryptographic Fowler–Noll–Vo hash functions

```c
#include <xppl_hash.h>

uint64_t h1  = xppl_hash_fnv1("my identifying string");
uint64_t h1a = xppl_hash_fnv1a("my identifying string");
```

#### Logging

```c
#include <xppl_log.h>

/* initialize logger */
xppl_log_init(XPLMDebugString, XPPL_LOG_INFO, "My Plugin");

/* send log messages */
xppl_log_debug("This message won't show");
xppl_log_warn("This one will");

/* also works with format strings, just like printf */
int t = 15;
xppl_log_info("The outside temperature is %d degrees", t);

/* clean up your mess */
xppl_log_destroy();
```

#### Paths

Check and manipulate paths across different platforms

```c
#include <xppl_path.h>

/* check if a path exists */
if (xppl_path_exists("Resources/plugins/foo")) {}

/* create a directory */
xppl_path_create_dir("foo");

/* create a directory recursively */
xppl_path_create_recursive("Output/foo/bar", "/");

/* chop off the last part of a path */
char buffer[256] = { '\0' };
size_t len = xppl_path_dirname("foo/bar/baz", "/", buffer, 256);

printf("%s\n", buffer) /* result: foo/bar */
```

### xppl_config

Cf. [Configuration File with XPPL](https://daemotron.net/2023/09/23/configuration-file-with-xppl/) for a more in-depth description

```c
#include <xppl_config.h>

/* initialize configuration context */
xppl_config_ctx_t cfg;
xppl_config_init(&cfg, "MyPlugin Configuration", "Output/myplugin/config.txt", XPLMGetDirectorySeparator(), true)

/* register configuration options and their default values */
long long default_int = 1234;
char default_str[] = "Hello World";
xppl_config_register(&cfg, "my_int", XPPL_CONFIG_INT, &default_int, "My configurable integer");
xppl_config_register(&cfg, "my_str", XPPL_CONFIG_STRING, default_str, "My configurable string");

/* load or create configuration file */
xppl_config_load(&cfg);

/* retrieve configuration value by key */
long long conf_int = xppl_config_data_get_i(&cfg, "my_int");
char conf_str[255];
size_t len = xppl_config_data_get_s(&cfg, "my_str", conf_str, 255);
```

### xppl_map

Simple hash maps with optional persistence

```c
#include <xppl_map.h>

/* create a map */
xppl_map_t map;
xppl_map_init(&map, 0);

/* put some values */
xppl_map_set_i(&map, "my int", 123);
xppl_map_set_f(&map, "my float", 123.456F);

/* get value from map */
int i = xppl_map_get_i(&map, "my int");

/* save map to a file */
xppl_map_save(&map, "Output/myplugin/data.map");

/* clean up */
xppl_map_destroy(&map);
```

### xppl_test

Simple unit test -- to see how this works, best take a look at the unit tests in `./test`.
