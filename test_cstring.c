#include <stdio.h>
#include <check.h>
#include "cstring.h"

START_TEST(test_create_string)
{
    const char *s = "hello world";
    uint32_t size = strlen(s);
    
    cstring_st str = cstring_new(s);

    ck_assert(!strcmp(cstring_raw(str), s));
    ck_assert_int_eq(cstring_size(str), size);
    
    cstring_delete(str);
}
END_TEST

START_TEST(test_string_equals)
{
    const char *s = "hello world";
    const char *sl = "aello world";
    const char *su = "iello world";
    
    cstring_st str1 = cstring_new(s);
    cstring_st str2 = cstring_new(s);

    ck_assert_int_eq(cstring_are_equal(str1, str2), CSTRING_EQUALS);
    
    cstring_delete(str1);

    str1 = cstring_new(sl);
    ck_assert_int_eq(cstring_are_equal(str1, str2), CSTRING_SMALLER);

    cstring_delete(str1);

    str1 = cstring_new(su);
    ck_assert_int_eq(cstring_are_equal(str1, str2), CSTRING_BIGGER);

    cstring_delete(str1);
    cstring_delete(str2);
}
END_TEST


START_TEST(test_string_touperlower)
{
    const char *s = "abcdefg";
    const char *su = "ABCDEFG";


    cstring_st str = cstring_new(s);
    cstring_st stru = cstring_new(su);

    cstring_to_uppercase(str);
    ck_assert_int_eq(cstring_are_equal(str, stru), CSTRING_EQUALS);

    cstring_st strl = cstring_new(s);

    cstring_to_lowercase(stru);
    ck_assert_int_eq(cstring_are_equal(strl, stru), CSTRING_EQUALS);

    cstring_delete(str);
    cstring_delete(stru);
    cstring_delete(strl);
}
END_TEST

START_TEST(test_string_concat)
{
    const char *s = "hello ";
    const char *su = "world!";
    const char *hw = "hello world!";


    cstring_st strh = cstring_new(s);
    cstring_st strhw = cstring_new(hw);

    cstring_add(strh, su);

    ck_assert_int_eq(cstring_are_equal(strh, strhw), CSTRING_EQUALS);

    cstring_delete(strh);
    cstring_delete(strhw);
}
END_TEST

START_TEST(test_string_copy)
{
    const char *hw = "hello world!";


    cstring_st strh = cstring_new(hw);
    cstring_st strhw = cstring_get_copy(strh);

    ck_assert_int_eq(cstring_are_equal(strh, strhw), CSTRING_EQUALS);

    cstring_delete(strh);
    cstring_delete(strhw);
}
END_TEST

START_TEST(test_string_find)
{
    const char *hw = "hello world!";


    cstring_st str = cstring_new(hw);
    
    uint32_t pos = cstring_find_char_pos(str, 'l');
    ck_assert_int_eq(pos, 2);

    char c = *cstring_find_char(str, 'l');
    ck_assert_int_eq(c, 'l');

    pos = cstring_find_str_pos(str, "world");
    ck_assert_int_eq(pos, 6);

    char *cs = cstring_find_str(str, "world");
    cstring_st cc = cstring_new(cs);
    cstring_st cc1 = cstring_new(hw + 6);
    ck_assert_int_eq(cstring_are_equal(cc, cc1), CSTRING_EQUALS);

    cstring_delete(cc);
    cstring_delete(cc1);

    pos = cstring_find_last_char_pos(str, 'l');
    ck_assert_int_eq(pos, 9);

    c = *cstring_find_last_char(str, 'l');
    ck_assert_int_eq(c, 'l');

    pos = cstring_find_last_str_pos(str, "l");
    ck_assert_int_eq(pos, 9);

    cs = cstring_find_last_str(str, "l");
    cc = cstring_new(cs);
    cc1 = cstring_new(hw + 9);
    ck_assert_int_eq(cstring_are_equal(cc, cc1), CSTRING_EQUALS);

    cstring_delete(str);
    cstring_delete(cc);
    cstring_delete(cc1);
}
END_TEST


Suite * clist_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("clist tests");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_string);
    tcase_add_test(tc_core, test_string_equals);
    tcase_add_test(tc_core, test_string_touperlower);
    tcase_add_test(tc_core, test_string_concat);
    tcase_add_test(tc_core, test_string_copy);
    tcase_add_test(tc_core, test_string_find);


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