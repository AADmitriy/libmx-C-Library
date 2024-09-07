![Libmx C library (1)](https://github.com/user-attachments/assets/ac986998-806e-4602-86ed-4778a4eb0122)

Libmx library contains a lot of simple yet useful functions for working with memory, strings, linked lists, and more. 

To set it up, just download this repository and run `make` in the project directory, this will create the static library libmx.a.

Then you can use it in your code by including `libmx.h` in your file, adding `libmx.a` and `/inc` to the code directory, and finally running:

`clang -std=c11 your_file_name.c -I ./inc -L -l libmx.a`

For ucode students, I left my test file here, maybe you will find it useful.
