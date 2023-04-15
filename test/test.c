#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "state_machine.h"


/* These functions will be used to initialize
   and clean resources up after each test run */
int setup(void **state) {
    (void)state;
    return 0;
}

int teardown(void **state) {
    (void)state;
    return 0;
}


int main(void) {
    const struct CMUnitTest tests[] = {
        0,
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */
    int count_fail_tests = cmocka_run_group_tests(tests, setup, teardown);

    return count_fail_tests;
}
