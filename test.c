#include "libmx.h"

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/*
void print_storage_info(const int* next, const int* prev, int ints) {
    if (next) {
        printf("%s location: %p. Size: %d ints (%ld bytes).\n", (next != prev ? "New" : "Old"), (void*)next, ints, ints * sizeof(int));
    }
    else
        puts("Allocation failed.\n");
}
*/

void print_char_arr(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    
    printf("\n");
}

void test_mx_strsplit(char const *s, char c) {
    printf("Input string: \"%s\"\n", s);
    printf("Delimiter: '%c'\n", c);
    char **words = mx_strsplit(s, c);
    if (words) {
        printf("Result:\n");
        for (int i = 0; words[i]; i++) {
            printf("Word %d: \"%s\"\n", i + 1, words[i]);
            mx_strdel(&words[i]);
        }
        free(words);
    } else {
        printf("Memory allocation failed.\n");
    }
}

void printList(t_list *head) {
    printf("Linked list content:\n");
    while (head != NULL) {
        printf("%s ", head->data);
        head = head->next;
    }
    printf("\n");
}

bool compare(void *a, void *b) {
    return *(char*)a > *(char*)b;
}

int main(void) {
    // =============================================Utils pack===================================================================

    // mx_print_unicode_test
    /*
    {
        setlocale(LC_ALL, "en_US.UTF-8");
    
        wchar_t smiley = L'😊';
        wchar_t chinese = L'里';
        wchar_t arabic = L'د';
        wchar_t persian = L'چ';
    
        mx_print_unicode(smiley);
        mx_print_unicode(chinese);
        mx_print_unicode(persian);
        mx_print_unicode(arabic);
        mx_print_unicode(L'😊');
    
        mx_printstr(setlocale(LC_CTYPE, NULL));
    }
    */

    // mx_print_strarr
    /*
    {
        char *str_arr[] = {"abc", "bfdafd", "fdafdsad", NULL};
        char *str_arr2[] = {"111111", "222222", "33333333", NULL};
    
        mx_print_strarr(str_arr, "delim");
        mx_print_strarr(str_arr, NULL);
        mx_print_strarr(NULL, "delim");
        mx_print_strarr(str_arr2, "00000");
    }
    */

    // mx_itoa
    /*
    mx_printstr(mx_itoa(-42));
    mx_printchar('\n');
    mx_printstr(mx_itoa(0));
    mx_printchar('\n');
    mx_printstr(mx_itoa(24322));
    mx_printchar('\n');
    mx_printstr(mx_itoa(-2147483648));
    mx_printchar('\n');
    mx_printstr(mx_itoa(2147483647));
    mx_printchar('\n');
    */

    // mx_sqrt
    /*
    {
        mx_printint(mx_sqrt(2025000000));
        mx_printchar('\n');
        mx_printint(mx_sqrt(2147483647));
        mx_printchar('\n');
        mx_printint(mx_sqrt(2147395600));
        mx_printchar('\n');
    }
    */
    // mx_nbr_to_hex
    /*
    {
        puts("Test 1\n");
        unsigned long num = 15;
        printf("%lu\n", num);
        char *hex_str = mx_nbr_to_hex(num);
        printf("%s\n", hex_str);
        free(hex_str);
        
        puts("Test 2\n");
        unsigned long num2 = 52;
        printf("%lu\n", num2);
        char *hex_str2 = mx_nbr_to_hex(num2);
        printf("%s\n", hex_str2);
        free(hex_str2);
        
        puts("Test 3\n");
        unsigned long num3 = 1000;
        printf("%lu\n", num3);
        char *hex_str3 = mx_nbr_to_hex(num3);
        printf("%s\n", hex_str3);
        free(hex_str3);
        
        puts("Test 4\n");
        unsigned long num4 = 0;
        printf("%lu\n", num4);
        char *hex_str4 = mx_nbr_to_hex(num4);
        printf("%s\n", hex_str4);
        free(hex_str4);
        
        puts("Test 5\n");
        unsigned long num5 = 4294967295;
        printf("%lu\n", num5);
        char *hex_str5 = mx_nbr_to_hex(num5);
        printf("%s\n", hex_str5);
        free(hex_str5);
    }
    */

    // mx_hex_to_nbr
    /*
    {
        puts("Test 1\n");
        char *str = "C4";
        printf("%s\n", str);
        unsigned long num = mx_hex_to_nbr(str);
        printf("%lu\n", num);
        
        puts("Test 2\n");
        char *str2 = "FADE";
        printf("%s\n", str2);
        unsigned long num2 = mx_hex_to_nbr(str2);
        printf("%lu\n", num2);
        
        puts("Test 3\n");
        char *str3 = "ffffffff";
        printf("%s\n", str3);
        unsigned long num3 = mx_hex_to_nbr(str3);
        printf("%lu\n", num3);
        
        puts("Test 4\n");
        char *str4 = "0";
        printf("%s\n", str4);
        unsigned long num4 = mx_hex_to_nbr(str4);
        printf("%lu\n", num4);
        
        puts("Test 5\n");
        char *str5 = "ffffffffffffffff";
        printf("%s\n", str5);
        unsigned long num5 = mx_hex_to_nbr(str5);
        printf("%lu\n", num5);
        
        puts("Test 6\n");
        char *str6 = "123456789";
        printf("%s\n", str6);
        unsigned long num6 = mx_hex_to_nbr(str6);
        printf("%lu\n", num6);
    }
    */

    // mx_bubble_sort
    /*
    {
        printf("Test 1\n");
        char *test_case1[] = {"banana", "apple", "orange", "grape"};
        int size1 = sizeof(test_case1) / sizeof(test_case1[0]);
        
        printf("%d\n", mx_bubble_sort(test_case1, size1));
        print_char_arr(test_case1, size1);
        
        
        printf("Test 2\n");
        char *test_case2[] = {"apple", "banana", "grape", "orange"};
        int size2 = sizeof(test_case2) / sizeof(test_case2[0]);
        
        printf("%d\n", mx_bubble_sort(test_case2, size2));
        print_char_arr(test_case2, size2);
        
        
        printf("Test 3\n");
        char *test_case3[] = {"orange", "grape", "banana", "apple"};
        int size3 = sizeof(test_case3) / sizeof(test_case3[0]);
        
        printf("%d\n", mx_bubble_sort(test_case3, size3));
        print_char_arr(test_case3, size3);
        
        
        printf("Test 4\n");
        char *test_case4[] = {"apple"};
        int size4 = sizeof(test_case4) / sizeof(test_case4[0]);
        
        printf("%d\n", mx_bubble_sort(test_case4, size4));
        print_char_arr(test_case4, size4);
        
        
        printf("Test 5\n");
        char *test_case5[] = {"abc", "xyz", "ghi", "def"};
        int size5 = sizeof(test_case5) / sizeof(test_case5[0]);
        
        printf("%d\n", mx_bubble_sort(test_case5, size5));
        print_char_arr(test_case5, size5);
        
    
        printf("Test 6\n");
        char *test_case6[] = {"abc", "acb", "a"};
        int size6 = sizeof(test_case6) / sizeof(test_case6[0]);
        
        printf("%d\n", mx_bubble_sort(test_case6, size6));
        print_char_arr(test_case6, size6);
    }
    */

    // mx_binary_search
    /*
    {
        char *arr[] = {"222", "Abcd", "aBc", "ab", "az", "z"};
        int count = 0;
        
        printf("Test 1\n");
        printf("%d\n", mx_binary_search(arr, 6, "ab", &count));
        printf("%d\n", count);
        count = 0;
        
        printf("Test 2\n");
        printf("%d\n", mx_binary_search(arr, 6, "aBc", &count));
        printf("%d\n", count);
        count = 0;
        
        printf("Test 3\n");
        printf("%d\n", mx_binary_search(arr, 6, "aBz", &count));
        printf("%d\n", count);
        count = 0;
        
        printf("Test 4\n");
        char *arr1[] = {"222"};
        printf("%d\n", mx_binary_search(arr1, 1, "aBc", &count));
        printf("%d\n", count);
        count = 0;
    }
    */

    // mx_quicksort
    /*
    {
        char *arr[] = {"Michelangelo", "Donatello", "Leonardo", "Raphael", NULL};
    
        mx_print_strarr(arr, ", ");
        mx_printint(mx_quicksort(arr, 0, 3));
        mx_print_strarr(arr, ", ");
    
        char *arr1[] = {"DMC", "Clint Eastwood", "Dr Brown", "Einstein", "Jessica", "Biff Tannen", NULL};
    
        mx_print_strarr(arr1, ", ");
        mx_printint(mx_quicksort(arr1, 0, 5));
        mx_print_strarr(arr1, ", ");
    }
    */

    // =============================================String pack===================================================================

    // mx_strdel
    /*
    {
        printf("Test 1:\n");
        char *str = (char*)malloc(10 * sizeof(char)); // Allocate memory for a string
        // Check if memory allocation was successful
        if (str == NULL) {
            printf("Memory allocation failed\n");
            return 1; // Return with error code
        }
        // Copy some content into the allocated memory
        strcpy(str, "Hello");
        
        // Use the string...
        printf("String before freeing: %s\n", str);
        
        // Free the string's memory and set it to NULL
        mx_strdel(&str);
        
        // Check if the string is now NULL
        if (str == NULL) {
            printf("String after freeing: %s\n", str);
        }
        
        printf("Test 2:\n");
        char *str1 = NULL;
        // Use the string...
        printf("String before freeing: %s\n", str1);
        
        // Free the string's memory and set it to NULL
        mx_strdel(&str1);
        
        // Check if the string is now NULL
        printf("String after freeing: %s\n", str1);
        
        printf("Test 3:\n");
        char **str2 = NULL;
        
        // Free the string's memory and set it to NULL
        mx_strdel(str2);
    }
    */

    // mx_get_char_index
    /*
    {
        char *str = "abcdef12345";
        mx_printint(mx_get_char_index(str, 'e'));
        mx_printint(mx_get_char_index(str, '5'));
        mx_printint(mx_get_char_index(str, 'a'));
        mx_printint(mx_get_char_index(str, 'z'));
        char *str0 = "";
        mx_printint(mx_get_char_index(str0, 'e'));
        mx_printint(mx_get_char_index(NULL, 'e'));
    }
    */

    // mx_strdup
    /*
    {
        // Test case 1: Empty string
        char *result1 = mx_strdup("");
        printf("%s\n", result1);
        
        // Test case 2: Non-empty string
        char *result2 = mx_strdup("Hello, world!");
        printf("%s\n", result2);
        
        // Test case 3: NULL input
        char *result3 = mx_strdup(NULL);
        printf("%s\n", result3);
    
        // Free allocated memory
        free(result1);
        free(result2);
        free(result3);
    }
    */

    // mx_strndup
    /*
    {
        char *result1 = mx_strndup("", 0);
        mx_printstr(result1);
        mx_printchar('\n');
        
        char *result2 = mx_strndup("Hello, world!", 8);
        mx_printstr(result2);
        mx_printchar('\n');
        
        char *result3 = mx_strndup(NULL, 0);
        printf("%s\n", result3);
    
        free(result1);
        free(result2);
        free(result3);
    }
    */

    // mx_strnew
    /*
    {
        // Test case 1: Allocate a new string of size 5
        char *str1 = mx_strnew(5);
        printf("Allocated string 1: %s\n", str1);
        free(str1);
    
        // Test case 2: Allocate a new string of size 0
        char *str2 = mx_strnew(0);
        printf("Allocated string 2: %s\n", str2);
        free(str2);
    }
    */

    // mx_strtrim
    /*
    {
        // Test case 1: Trim leading and trailing whitespace
        const char *input1 = "   Hello, world!   ";
        char *result1 = mx_strtrim(input1);
        printf("Test Case 1 Result: \"%s\"\n", result1); // Expected: "Hello, world!"
        free(result1);
    
        // Test case 2: Only leading whitespace
        const char *input2 = "     ";
        char *result2 = mx_strtrim(input2);
        printf("Test Case 2 Result: \"%s\"\n", result2); // Expected: ""
        free(result2);
    
        // Test case 3: Only trailing whitespace
        const char *input3 = "Hello, world!    ";
        char *result3 = mx_strtrim(input3);
        printf("Test Case 3 Result: \"%s\"\n", result3); // Expected: "Hello, world!"
        free(result3);
    
        // Test case 4: No leading or trailing whitespace
        const char *input4 = "Hello, world!";
        char *result4 = mx_strtrim(input4);
        printf("Test Case 4 Result: \"%s\"\n", result4); // Expected: "Hello, world!"
        free(result4);
    
        // Test case 5: Empty string
        const char *input5 = "";
        char *result5 = mx_strtrim(input5);
        printf("Test Case 5 Result: \"%s\"\n", result5); // Expected: ""
        free(result5);
    
        // Test case 6: NULL string
        const char *input6 = NULL;
        char *result6 = mx_strtrim(input6);
        printf("Test Case 6 Result: \"%s\"\n", result6); // Expected: NULL
    }
    */

    // mx_strsplit
    /*
    {
        // Test case 1: Single word string
        char s1[] = "hello";
        test_mx_strsplit(s1, ' ');
    
        // Test case 2: String with multiple words
        char s2[] = "hello world!";
        test_mx_strsplit(s2, ' ');
    
        // Test case 3: String with multiple words and multiple delimiters
        char s3[] = "a,b,c,d,e";
        test_mx_strsplit(s3, ',');
    
        // Test case 4: String with empty words
        char s4[] = "   Knock, knock,    Neo.   ";
        test_mx_strsplit(s4, ' ');
    
        // Test case 5: Empty string
        char s5[] = "";
        test_mx_strsplit(s5, ' ');
    
        // Test case 6: String with single word and delimiter
        char s6[] = "**Good bye,**Mr.*Anderson.****";
        test_mx_strsplit(s6, '*');
    
        // Test case 7: String with delimiter only
        char *s7 = NULL;
        test_mx_strsplit(s7, ',');
    }
    */

    // mx_strjoin
    /*
    {
        // Test case 1: Both strings are NULL
        char *result1 = mx_strjoin(NULL, NULL);
        if (result1 == NULL) {
            printf("Test case 1 passed\n");
        } else {
            printf("Test case 1 failed\n");
        }
        free(result1); // Free dynamically allocated memory
    
        // Test case 2: First string is NULL
        char *result2 = mx_strjoin(NULL, "Hello");
        if (result2 != NULL && strcmp(result2, "Hello") == 0) {
            printf("Test case 2 passed\n");
        } else {
            printf("Test case 2 failed\n");
        }
        free(result2); // Free dynamically allocated memory
    
        // Test case 3: Second string is NULL
        char *result3 = mx_strjoin("Hello", NULL);
        if (result3 != NULL && strcmp(result3, "Hello") == 0) {
            printf("Test case 3 passed\n");
        } else {
            printf("Test case 3 failed\n");
        }
        free(result3); // Free dynamically allocated memory
    
        // Test case 4: Both strings are not NULL
        char *result4 = mx_strjoin("Hello ", "world");
        if (result4 != NULL && strcmp(result4, "Hello world") == 0) {
            printf("Test case 4 passed\n");
        } else {
            printf("Test case 4 failed\n");
        }
        free(result4); // Free dynamically allocated memory
        
        // Test case 5: 
        char *result5 = mx_strjoin(" ", "");
        if (result5 != NULL && strcmp(result5, " ") == 0) {
            printf("Test case 5 passed\n");
        } else {
            printf("Test case 5 failed\n");
        }
        free(result5); // Free dynamically allocated memory
    }
    */
    
    // mx_file_to_str
    /*
    {
        const char *file_name = "Makefile";
    
        char *file_str = mx_file_to_str(file_name);
        if (file_str == NULL) {
            printf("NULL\n");
        }
        else {
            printf("%s\n", file_str);
            free(file_str);
        }
    }
    */


    // mx_get_substr_index
    /*
    {
        mx_printint(mx_get_substr_index("McDonalds", "Don")); //returns 2
        mx_printchar('\n');
        mx_printint(mx_get_substr_index("McDowalds Donuts", "on")); //returns 11
        mx_printchar('\n');
        mx_printint(mx_get_substr_index("McDowalds Doputs", "on")); //returns -1
        mx_printchar('\n');
        mx_printint(mx_get_substr_index("", "Donatello")); //returns -1
        mx_printchar('\n');
        mx_printint(mx_get_substr_index("McDowalds Doputs", "s")); //returns 8
        mx_printchar('\n');
        mx_printint(mx_get_substr_index("McDonalds", NULL)); //returns -2
        mx_printchar('\n');
        mx_printint(mx_get_substr_index(NULL, "Don")); //returns -2
        mx_printchar('\n');
    }
    */

    // mx_replace_substr
    /*
    {
        char *new_str1 = mx_replace_substr("McDonalds", "alds", "uts"); //returns "McDonuts"
        mx_printstr(new_str1);
        mx_printchar('\n');
        free(new_str1);
    
        char *new_str2 = mx_replace_substr("Ululu tulu", "lu", "ta"); //returns "Utata tuta"
        mx_printstr(new_str2);
        mx_printchar('\n');
        free(new_str2);
    
        char *new_str3 = mx_replace_substr("space double int", " double int", ""); //returns "space"
        mx_printstr(new_str3);
        mx_printchar('\n');
        free(new_str3);
    
        if (mx_replace_substr("space double int", "", "fdafsfasfs") == NULL) {
            mx_printstr("(null)");
            mx_printchar('\n');
        }
    }
    */

    // mx_read_line
    /*
    {
        int fd = open("fragment", O_RDONLY);
        char *str = mx_strnew(150);
        int res;
    
        res = mx_read_line(&str, 7, '\n', fd);
        mx_printint(res);
        mx_printchar('\n');
        mx_printstr(str);
        mx_printchar('\n');
        res = mx_read_line(&str, 35, 'a', fd); 
        mx_printint(res);
        mx_printchar('\n');
        mx_printstr(str);
        mx_printchar('\n');
        res = mx_read_line(&str, 1, '.', fd);
        mx_printint(res);
        mx_printchar('\n');
        mx_printstr(str);
        mx_printchar('\n');
        res = mx_read_line(&str, 10, '\n', fd);
        mx_printint(res);
        mx_printchar('\n');
        mx_printstr(str);
        mx_printchar('\n');
    
        free(str);
        close(fd);
    }
    {
        int fd2 = open("fragment", O_RDONLY);
        char *str2 = mx_strnew(150);
        int res2;
    
        res2 = mx_read_line(&str2, 20, '#', fd2);
        mx_printint(res2);
        mx_printchar('\n');
        mx_printstr(str2);
        mx_printchar('\n');
        res2 = mx_read_line(&str2, 20, '#', fd2);
        mx_printint(res2);
        mx_printchar('\n');
        mx_printstr(str2);
        mx_printchar('\n');
    
        free(str2);
        close(fd2);
    }
    
    {
        char *str3 = mx_strnew(500);
        int res3;
    
        res3 = mx_read_line(&str3, 20, '#', 0);
        mx_printint(res3);
        mx_printchar('\n');
        mx_printstr(str3);
        mx_printchar('\n');
        res3 = mx_read_line(&str3, 20, '#', 0);
        mx_printint(res3);
        mx_printchar('\n');
        mx_printstr(str3);
        mx_printchar('\n');
    
        free(str3);
    }
    
    {
        int fd4 = open("cat.txt", O_RDONLY);
        char *str4 = mx_strnew(1500);
        int res4;
    
        res4 = mx_read_line(&str4, 20, '\0', fd4);
        mx_printint(res4);
        mx_printchar('\n');
        mx_printstr(str4);
        mx_printchar('\n');
        res4 = mx_read_line(&str4, 20, '#', fd4);
        mx_printint(res4);
        mx_printchar('\n');
        mx_printstr(str4);
        mx_printchar('\n');
    
        free(str4);
        close(fd4);
    }
    {
        int fd5 = open("Makefile", O_RDONLY);
        char *str5 = mx_strnew(1500);
        int res5;
    
        res5 = mx_read_line(&str5, 20, '\t', fd5);
        mx_printint(res5);
        mx_printchar('\n');
        mx_printstr(str5);
        mx_printchar('\n');
        res5 = mx_read_line(&str5, 20, '\0', fd5);
        mx_printint(res5);
        mx_printchar('\n');
        mx_printstr(str5);
        mx_printchar('\n');
    
        free(str5);
        close(fd5);
    }

    {
        char *str5 = mx_strnew(1500);
        int res5;

        res5 = mx_read_line(&str5, 20, '\t', 123);
        mx_printint(res5);
        mx_printchar('\n');
        mx_printstr(str5);
        mx_printchar('\n');

        free(str5);
    }
    */
    
    // =============================================Memory pack===================================================================

    // mx_memset
    /*
    {
        char arr[10];
    
        mx_memset(arr, 'f', sizeof(arr));
    
        for (unsigned long i = 0; i < sizeof(arr); i++) {
            printf("%c", arr[i]);
        }
    }

    // Test case 1: Set all bytes to zero
    {
        char buffer[10] = "abcdefghi";
        mx_memset(buffer, 0, sizeof(buffer));
        int passed = 1;
        for (size_t i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] != 0) {
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    // Test case 2: Set part of an array
    {
        char buffer[10] = "abcdefghi";
        mx_memset(buffer + 3, 'X', 3);  // Set 3 bytes starting at index 3 to 'X'
        if (mx_strncmp(buffer, "abcXXXghi", 10) == 0) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    // Test case 3: Set entire array to a non-zero value
    {
        int buffer[5];
        mx_memset(buffer, -1, sizeof(buffer));  // Set all bytes to 0xFF
        int passed = 1;
        for (size_t i = 0; i < sizeof(buffer); i++) {
            if (((unsigned char*)buffer)[i] != 0xFF) {
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    // Test case 4: Set string to null terminators
    {
        char buffer[20] = "Hello, World!";
        mx_memset(buffer + 5, '\0', 5);  // Null terminate after "Hello"
        if (mx_strcmp(buffer, "Hello") == 0) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 failed.\n");
        }
    }

    // Test case 5: Set large amount of memory
    {
        char large_buffer[1000];
        mx_memset(large_buffer, 'A', sizeof(large_buffer));
        int passed = 1;
        for (size_t i = 0; i < sizeof(large_buffer); i++) {
            if (large_buffer[i] != 'A') {
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */


    // mx_memcpy
    /*
    {
        char dst[10];
        char src[10] = "1234567890";
        mx_memcpy(dst, src, sizeof(src));
    
        for (unsigned long i = 0; i < sizeof(dst); i++) {
            printf("%c", dst[i]);
        }
    
        char dst1[15];
        char src1[1] = "1";
        mx_memcpy(dst1, src1, sizeof(src1));
    
        for (unsigned long i = 0; i < sizeof(dst1); i++) {
            printf("%c", dst1[i]);
        }
    }
    // Test case 1: Normal copying of non-overlapping arrays
    {
        char src[] = "Hello, World!";
        char dst[20];
        mx_memcpy(dst, src, strlen(src) + 1);
        if (mx_strcmp(dst, src) == 0) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    // Test case 2: Copying part of the array
    {
        char src[] = "abcdef";
        char dst[10] = {0};
        mx_memcpy(dst, src, 3);  // Copy first 3 characters
        if (mx_strncmp(dst, "abc", 3) == 0) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    // Test case 3: Copying empty array
    {
        char src[] = "";
        char dst[10] = "test";
        mx_memcpy(dst, src, 1);  // Copy empty string (null terminator)
        if (mx_strcmp(dst, "") == 0) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    // Test case 4: Overlapping memory blocks (undefined behavior)
    {
        char src[] = "abcdefgh";
        mx_memcpy(src + 2, src, 5);  // Overlapping source and destination
        if (mx_memcmp(src, "ababcdef", 8) == 0) {
            printf("Test 4 passed. Not good\n");
        } else {
            printf("Test 4 failed. Good\n");
        }
    }

    // Test case 5: Copying binary data
    {
        int src[] = {1, 2, 3, 4, 5};
        int dst[5];
        mx_memcpy(dst, src, sizeof(src));
        if (mx_memcmp(dst, src, sizeof(src)) == 0) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */

    // mx_memccpy
    /*
    {
        char dst[10];
        char src[10] = "1234567890";
        mx_memccpy(dst, src, '#', sizeof(src));
    
        for (unsigned long i = 0; i < sizeof(dst); i++) {
            mx_printchar(dst[i]);
        }
        mx_printchar('\n');
    
        char dst1[15];
        char src1[10] = "1234567890";
        mx_memccpy(dst1, src1, '5', sizeof(src1));
    
        for (unsigned long i = 0; i < 5; i++) {
            mx_printchar(dst1[i]);
        }
        mx_printchar('\n');
    }
    // Test case 1: Regular copy, character found
    {
        char src[] = "abcdef";
        char dest[10];
        char *result = mx_memccpy(dest, src, 'd', sizeof(src));
        if (result != NULL && mx_strncmp(dest, "abcd", 4) == 0) {
            mx_printstr("Test 1 passed.\n");
        } else {
            mx_printstr("Test 1 failed.\n");
        }
    }

    // Test case 2: Regular copy, character not found
    {
        char src[] = "abcdef";
        char dest[10] = {0};
        char *result = mx_memccpy(dest, src, 'x', sizeof(src));
        if (result == NULL && mx_strncmp(dest, "abcdef", 6) == 0) {
            mx_printstr("Test 2 passed.\n");
        } else {
            mx_printstr("Test 2 failed.\n");
        }
    }

    // Test case 3: Copy up to and including character at the beginning
    {
        char src[] = "abcdef";
        char dest[10] = {0};
        char *result = mx_memccpy(dest, src, 'a', sizeof(src));
        if (result != NULL && mx_strncmp(dest, "a", 1) == 0) {
            mx_printstr("Test 3 passed.\n");
        } else {
            mx_printstr("Test 3 failed.\n");
        }
    }

    // Test case 4: Copy partial array with character found
    {
        char src[] = "abcdef";
        char dest[10] = {0};
        char *result = mx_memccpy(dest, src, 'e', 5);  // Only copy up to 5 bytes
        if (result != NULL && mx_strncmp(dest, "abcde", 5) == 0) {
            mx_printstr("Test 4 passed.\n");
        } else {
            mx_printstr("Test 4 failed.\n");
        }
    }

    // Test case 5: No copy when size is 0
    {
        char src[] = "abcdef";
        char dest[10] = {0};
        char *result = mx_memccpy(dest, src, 'd', 0);  // Copy 0 bytes
        if (result == NULL && dest[0] == '\0') {
            mx_printstr("Test 5 passed.\n");
        } else {
            mx_printstr("Test 5 failed.\n");
        }
    }
    */

    // mx_memcmp
    /*
    {
        char myStr1[] = "1239";
        char myStr2[] = "1234";
        int cmp = mx_memcmp(myStr1, myStr2, 4);
    
        if (cmp > 0) {
            printf("%s is greater than %s\n", myStr1, myStr2);
        } else if (cmp < 0) {
            printf("%s is greater than %s\n", myStr2, myStr1);
        } else {
            printf("%s is equal to %s\n", myStr1, myStr2);
        }
    }

    {
        char arr1[] = "abcdef";
        char arr2[] = "abcdef";
        int result = mx_memcmp(arr1, arr2, strlen(arr1));
        if (result == 0) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    {
        char arr1[] = "abcde";
        char arr2[] = "abcdf";
        int result = mx_memcmp(arr1, arr2, strlen(arr1));
        if (result < 0) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    {
        char arr1[] = "abcdf";
        char arr2[] = "abcde";
        int result = mx_memcmp(arr1, arr2, strlen(arr1));
        if (result > 0) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    {
        char arr1[] = "abcdef";
        char arr2[] = "abcde";
        int result = mx_memcmp(arr1, arr2, 5);
        if (result == 0) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 failed.\n");
        }
    }

    {
        char arr1[] = "";
        char arr2[] = "";
        int result = mx_memcmp(arr1, arr2, 0);
        if (result == 0) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */

    // mx_memchr
    /*
    {
        char myStr[] = "Hello World!";
        char *myPtr = (char*)mx_memchr(myStr, 'o', 5);
        if (myPtr != NULL) {
            printf("%s", myPtr);
        }
        else {
            printf("(null)");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memchr(arr, 'd', strlen(arr));
        if (result == &arr[3]) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memchr(arr, 'z', strlen(arr));
        if (result == NULL) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memchr(arr, 'a', strlen(arr));
        if (result == &arr[0]) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memchr(arr, 'g', strlen(arr));
        if (result == &arr[6]) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memchr(arr, 'g', 4);
        if (result == NULL) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */

    // mx_memrchr
    /*
    {
        char myStr[] = "Hello World!";
        char *myPtr = (char*)mx_memrchr(myStr, 'l', 12);
        if (myPtr != NULL) {
            mx_printstr(myPtr);
        }
        else {
            mx_printstr("(null)");
        }
    
        mx_printstr(mx_memrchr("Trinity", 'i', 7));
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memrchr(arr, 'd', strlen(arr));
        if (result == &arr[3]) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memrchr(arr, 'z', strlen(arr));
        if (result == NULL) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memrchr(arr, 'a', strlen(arr));
        if (result == &arr[0]) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memrchr(arr, 'g', strlen(arr));
        if (result == &arr[6]) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 failed.\n");
        }
    }

    {
        char arr[] = "abcdefg";
        char *result = mx_memrchr(arr, 'g', 4);
        if (result == NULL) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */

    // mx_memmem
    /*
    {
        char myStr[25] = "Helllito Wlittblrldlittl!";
        char little[5] = "to dd";
        char *myPtr = NULL;
        myPtr = (char*)mx_memmem(myStr, 25, little, 3);
        if (myPtr != NULL) {
            puts(myPtr);
        }
        else {
            printf("(null)");
        }
    }

    {
        char haystack[] = "abcdefg";
        char needle[] = "abc";
        char *result = (char*)mx_memmem(haystack, strlen(haystack), needle, strlen(needle));
        if (result == haystack) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 failed.\n");
        }
    }

    {
        char haystack[] = "abcdefg";
        char needle[] = "efg";
        char *result = (char*)mx_memmem(haystack, strlen(haystack), needle, strlen(needle));
        if (result == &haystack[4]) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 failed.\n");
        }
    }

    {
        char haystack[] = "abcdefg";
        char needle[] = "xyz";
        char *result = (char*)mx_memmem(haystack, strlen(haystack), needle, strlen(needle));
        if (result == NULL) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 failed.\n");
        }
    }

    {
        char haystack[] = "abcdefg";
        char needle[] = "";
        char *result = (char*)mx_memmem(haystack, strlen(haystack), needle, 0);
        if (result == haystack) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 failed.\n");
        }
    }

    {
        char haystack[] = "abc";
        char needle[] = "abcdef";
        char *result = (char*)mx_memmem(haystack, strlen(haystack), needle, strlen(needle));
        if (result == NULL) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 failed.\n");
        }
    }
    */

    // mx_memmove
    /*
    {
        char csrc[100] = "Geeksfor"; 
        mx_memmove(csrc+5, csrc, strlen(csrc)+1); 
        mx_printstr(csrc);
    
        char str1[] = "12345";
        char str2[] = "abc";
    
        char *ptr = (char*)mx_memmove(str1, str2, 1);
        mx_printstr(ptr);
    
        char dest_str[] = "oldstring";
        const char src_str[]  = "newstring";
        printf("Before memmove dest = %s, src = %s\n", dest_str, src_str);
        memmove(dest_str, src_str, 9);
        printf("After memmove dest = %s, src = %s\n", dest_str, src_str);
    
        char dest_str1[] = "Tutorialspoint"; 
	    char src_str1[] = "Tutors";
    
	    puts("source string [src_str] before memmove:-"); 
	    puts(dest_str1); 
    
	    memmove(dest_str1, src_str1, sizeof(src_str1)); 
    
	    puts("\nsource string [src_str] after memmove:-"); 
	    puts(dest_str1); 
    }
    */

    // mx_realloc
    /*
    {
        int *ptr = (int *)malloc(sizeof(int)*2); 
        int i; 
        int *ptr_new; 
         
        *ptr = 10;  
        *(ptr + 1) = 20; 
    
        ptr_new = (int *)mx_realloc(ptr, sizeof(int)*3); 
        *(ptr_new + 2) = 30; 
        for(i = 0; i < 3; i++) {
            printf("%d ", *(ptr_new + i));
        }
        free(ptr_new);
    
        int *ptr1 = (int *)malloc(sizeof(int)*3); 
        int i1; 
        int *ptr_new1; 
         
        *ptr1 = 10;  
        *(ptr1 + 1) = 20;
        *(ptr1 + 2) = 30;
    
        ptr_new1 = (int *)mx_realloc(ptr1, sizeof(int)*1); 
        
        for(i1 = 0; i1 < 1; i1++) {
            printf("%d ", *(ptr_new1 + i1));
        }
        free(ptr_new1);
    
        const int pattern[] = {1, 2, 3, 4, 5, 6, 7, 8};
        const int pattern_size = sizeof pattern / sizeof(int);
        int *next = NULL, *prev = NULL;
     
        if ((next = (int*)malloc(pattern_size * sizeof *next))) {
            mx_memcpy(next, pattern, sizeof pattern);
            print_storage_info(next, prev, pattern_size);
        }
        else
            return EXIT_FAILURE;
     
        const int realloc_size[] = {10, 12, 512, 32768, 65536, 32768};
     
        for (int i = 0; i != sizeof realloc_size / sizeof(int); ++i) {
            if ((next = (int*)mx_realloc(prev = next, realloc_size[i] * sizeof(int)))) {
                print_storage_info(next, prev, realloc_size[i]);
                assert(!mx_memcmp(next, pattern, sizeof pattern));
            }
            else {
                free(prev);
                return EXIT_FAILURE;
            }
        }
     
        free(next);
    }
    */

    // =============================================Linked List pack===================================================================

    // mx_sort_list
    /*
    {
        // Array of data to fill the linked list
        char *arr[] = {"ydfs", "ff", "F"};
        int size = sizeof(arr) / sizeof(arr[0]);
    
        // Create an empty linked list
        t_list *head = NULL;
    
        // Fill the linked list with data from the array
        for (int i = 0; i < size; i++) {
            mx_push_back(&head, (void*)arr[i]);
        }
    
        // Print the content of the linked list
        printList(head);
        
        t_list *new_head = mx_sort_list(head, compare);
    
        printList(new_head);
        // Free dynamically allocated memory used by the linked list
        t_list *temp;
        while (new_head != NULL) {
            temp = new_head;
            new_head = new_head->next;
            free(temp);
        }
    }
    */


    

    
    return 0;
}
