#include <stdio.h>
#include "cstack.h"
#include <check.h>

START_TEST(test_cstack_add)
{
    cstack_st *stack;

    cstack_init(stack, uint64_t);


    uint64_t *p;
    uint64_t val = 10;

    cstack_push(stack, val);
    p = cstack_peek(stack);
    
    ck_assert_int_eq(*p, val);

    val += 10;
    cstack_push(stack,val);
    p = cstack_peek(stack);
    
    ck_assert_int_eq(*p, val);

    val += 10;
    cstack_push(stack,val);
    p = cstack_peek(stack);
    
    ck_assert_int_eq(*p, val);

    val += 10;
    cstack_push(stack, val);
    p = cstack_peek(stack);
    

    ck_assert_int_eq(*p, val);

    val += 10;
    cstack_push(stack, val);
    p = cstack_peek(stack);
    
    ck_assert_int_eq(*p, val);

    val += 10;
    cstack_push(stack, val);
    p = cstack_peek(stack);
    
    ck_assert_int_eq(*p, val);

    cstack_finish(stack);
}
END_TEST

START_TEST(test_cstack_remove)
{
    cstack_st *stack;

    cstack_init(stack, uint64_t);


    uint64_t *p;
    uint64_t val = 10;

    cstack_push(stack, val);
    val += 10;
    cstack_push(stack,val);
    val += 10;
    cstack_push(stack,val);
    val += 10;
    cstack_push(stack, val);
    val += 10;
    cstack_push(stack, val);
    val += 10;
    cstack_push(stack, val);

    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    val -=10;
    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    val -=10;
    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    val -=10;
    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    val -=10;
    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    val -=10;
    p = cstack_peek(stack);
    ck_assert_int_eq(*p, val);

    cstack_pop(stack);

    ck_assert_int_eq(cstack_size(stack), 0);

    cstack_finish(stack);
}
END_TEST

START_TEST(test_cstack_size)
{
    cstack_st *stack;

    cstack_init(stack, uint64_t);

    uint64_t val = 10;

    cstack_push(stack, val);
    val += 10;
    cstack_push(stack,val);
    val += 10;
    cstack_push(stack,val);
    val += 10;
    cstack_push(stack, val);
    val += 10;
    cstack_push(stack, val);
    val += 10;
    cstack_push(stack, val);

    ck_assert_int_eq(cstack_size(stack), 6);

    cstack_finish(stack);
}
END_TEST

Suite * clist_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("clist tests");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_cstack_add);
    tcase_add_test(tc_core, test_cstack_remove);
    tcase_add_test(tc_core, test_cstack_size);


    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{


    //int number_failed;
    Suite *s;
    SRunner *sr;

    s = clist_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    srunner_ntests_failed(sr);
    srunner_free(sr);

}