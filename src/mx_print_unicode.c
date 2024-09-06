#include <stdio.h>
#include <wchar.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

void mx_print_unicode(wchar_t c) {
    setlocale(LC_ALL, "en_US.UTF-8");
    char buffer[MB_CUR_MAX];
    int len = wctomb(buffer, c);

    if (len > 0){ write(STDOUT_FILENO, buffer, len); }
}

