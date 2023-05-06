#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <xppl.h>
#include <xppl_test.h>

#include "_test_xppl_common.h"

int
main (int argc, char **argv)
{
    xppl_unused(argc);
    xppl_unused(argv);

    xppl_test_runner_t tr;
    bool result = true;
  
    xppl_test_runner_init(&tr);
    
    _test_xppl_common_register(&tr);

    result = xppl_test_run(&tr);

    xppl_test_runner_destroy(&tr);

    if (result)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
