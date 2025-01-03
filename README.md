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
