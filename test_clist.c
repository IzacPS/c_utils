#include <stdio.h>
#include "include/clist.h"
#include <check.h>
//#include "xxhash.h"

START_TEST(test_clist_add)
{
    clist_st *list;
    clist_init(list, int);

    int a = 4;
    clist_add(list, a);

    int *last = clist_iter_end(list);
    ck_assert_int_eq(a, *last);
    
    clist_finish(list);
}
END_TEST

START_TEST(test_clist_remove)
{
    clist_st *list;
    clist_init(list, int);
    int a = 4;
    clist_add(list, a);
    a+=4;
    clist_add(list, a);

    clist_remove_at(list, 0);
    clist_remove_at(list, 0);

    ck_assert_int_eq(clist_size(list), 0);


    clist_add(list, a);

    int *addra = clist_iter_start(list);
    int *addrb = clist_iter_end(list);

    ck_assert_uint_eq(*addra, *addrb);

    clist_finish(list);
}
END_TEST

START_TEST(test_clist_remove_comparing)
{
    clist_st *list;
    clist_init(list, int);
    int a = 4;
    clist_add(list, a);
    a+=4;
    clist_add(list, a);
    
    int b = 4;
    int c = 8;
    clist_remove(list, b, has_same_memory_content);
    clist_remove(list, c, has_same_memory_content);

    ck_assert_int_eq(clist_size(list), 0);


    clist_add(list, a);

    int *addra = clist_iter_start(list);
    int *addrb = clist_iter_end(list);

    ck_assert_uint_eq(*addra, *addrb);

    clist_finish(list);
}
END_TEST

START_TEST(test_clist_get_position)
{
    clist_st *list;
    clist_init(list, int);

    int a = 10;
    clist_add(list, a);

    int *b = clist_get(list, 0);
    ck_assert_int_eq(a, *b);

    a = 15;
    clist_add(list, a);

    b = clist_get(list, 1);
    ck_assert_int_eq(a, *b);

    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_normal)
{
    clist_st *list;
    clist_init(list, int);
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    for(int i = 0; i < 7; i++)
        clist_add(list, arr[i]);

    int index = 0;
    clist_foreach(list)
    {
        int *v = it;
        ck_assert_int_eq(arr[index++], *v);
    }

    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_indexed)
{
    clist_st *list;
    clist_init(list, int);
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    for(int i = 0; i < 7; i++)
        clist_add(list, arr[i]);

    clist_foreach_indexed(list)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }


    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_normal_step)
{
    clist_st *list;
    clist_init(list, int);
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};
    for(int i = 0; i < 8; i++)
        clist_add(list, arr[i]);

    int index = 0;
    clist_foreach_step(list, 2)
    {
        int *v = it;
        ck_assert_int_eq(arr[index], *v);
        index += 2;
    }


    clist_finish(list);
}
END_TEST


START_TEST(test_clist_compare_loop_indexed_step)
{
    clist_st *list;
    clist_init(list, int);
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};
    for(int i = 0; i < 8; i++)
        clist_add(list, arr[i]);

    clist_foreach_step_indexed(list, 2)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }


    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_normal)
{
    clist_st *list;
    clist_init(list, int);
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    for(int i = 0; i < 7; i++)
        clist_add(list, arr[i]);

    int index = 6;
    clist_foreach_reverse(list)
    {
        int *v = it;
        ck_assert_int_eq(arr[index], *v);
        index--;
    }

    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_indexed)
{
    clist_st *list;
    clist_init(list, int);
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    for(int i = 0; i < 7; i++)
        clist_add(list, arr[i]);

    clist_foreach_reverse_indexed(list)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }


    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_normal_step)
{
    clist_st *list;
    clist_init(list, int);
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};
    for(int i = 0; i < 8; i++)
        clist_add(list, arr[i]);

    int index = 7;
    clist_foreach_reverse_step(list, 2)
    {
        int *v = it;
        ck_assert_int_eq(arr[index], *v);
        index -= 2;
    }


    clist_finish(list);
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_indexed_step)
{
    clist_st *list;
    clist_init(list, int);
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};
    for(int i = 0; i < 8; i++)
        clist_add(list, arr[i]);

    clist_foreach_reverse_step_indexed(list, 2)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }


    clist_finish(list);
}
END_TEST

Suite * clist_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("clist tests");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_clist_add);
    tcase_add_test(tc_core, test_clist_remove);
    tcase_add_test(tc_core, test_clist_remove_comparing);
    tcase_add_test(tc_core, test_clist_get_position);
    tcase_add_test(tc_core, test_clist_compare_loop_normal);
    tcase_add_test(tc_core, test_clist_compare_loop_indexed);
    tcase_add_test(tc_core, test_clist_compare_loop_normal_step);
    tcase_add_test(tc_core, test_clist_compare_loop_indexed_step);
    tcase_add_test(tc_core, test_clist_compare_loop_reverse_normal);
    tcase_add_test(tc_core, test_clist_compare_loop_reverse_indexed);
    tcase_add_test(tc_core, test_clist_compare_loop_reverse_normal_step);
    tcase_add_test(tc_core, test_clist_compare_loop_reverse_indexed_step);


    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{


    int number_failed;
    Suite *s;
    SRunner *sr;

    s = clist_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    //printf("zero array size: %ld", sizeof(char[0]));
}