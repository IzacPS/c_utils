#include <stdio.h>
#include "include/carray.h"
#include <check.h>

START_TEST(test_clist_compare_loop_normal)
{
    int carray[7];
    
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    
    int index = 0;
    carray_foreach(carray)
    {
        memcpy(it, arr + index++, sizeof(int));
    }
    index = 0;
    carray_foreach(carray)
    {
        int *v = it;
        ck_assert_int_eq(arr[index++], *v);
    }

}
END_TEST

START_TEST(test_clist_compare_loop_indexed)
{
    int carray[7];
    
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    
    carray_foreach_indexed(carray)
    {
        memcpy(it.value, arr + it.index, sizeof(int));
    }

    carray_foreach_indexed(carray)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }
}
END_TEST

START_TEST(test_clist_compare_loop_normal_step)
{
    int carray[8];
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};

    int index = 0;
    carray_foreach_step(carray, 2)
    {
        memcpy(it, arr + index, sizeof(int));
        index += 2;
    }

    index = 0;
    carray_foreach_step(carray, 2)
    {
        int *v = it;
        ck_assert_int_eq(arr[index], *v);
        index += 2;
    }

}
END_TEST


START_TEST(test_clist_compare_loop_indexed_step)
{
    int carray[8];
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};

    carray_foreach_step_indexed(carray, 2)
    {
        memcpy(it.value, arr + it.index, sizeof(int));
    }

    carray_foreach_step_indexed(carray, 2)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }

}
END_TEST

START_TEST(test_clist_compare_loop_reverse_normal)
{
    int carray[7];
    
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    
    int index = 6;
    carray_foreach_reverse(carray)
    {
        memcpy(it, arr + index--, sizeof(int));
    }

    index = 6;
    carray_foreach_reverse(carray)
    {
        int *v = it;
        ck_assert_int_eq(arr[index--], *v);
    }
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_indexed)
{
    int carray[7];
    
    int arr[7] = {10, 3, 54, 6, 23, 89, 23};
    
    carray_foreach_reverse_indexed(carray)
    {
        memcpy(it.value, arr + it.index, sizeof(int));
    }

    carray_foreach_reverse_indexed(carray)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_normal_step)
{
    int carray[8];
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};

    int index = 7;
    carray_foreach_reverse_step(carray, 2)
    {
        memcpy(it, arr + index, sizeof(int));
        index -= 2;
    }

    index = 7;
    carray_foreach_reverse_step(carray, 2)
    {
        int *v = it;
        ck_assert_int_eq(arr[index], *v);
        index -= 2;
    }
}
END_TEST

START_TEST(test_clist_compare_loop_reverse_indexed_step)
{
    int carray[8];
    int arr[8] = {10, 3, 54, 6, 23, 89, 23, 20};

    carray_foreach_reverse_step_indexed(carray, 2)
    {
        memcpy(it.value, arr + it.index, sizeof(int));
    }

    carray_foreach_reverse_step_indexed(carray, 2)
    {
        int *v = it.value;
        ck_assert_int_eq(arr[it.index], *v);
    }
}
END_TEST

Suite * clist_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("clist tests");
    tc_core = tcase_create("Core");

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

    printf("number of failed tests: %d", number_failed);
}