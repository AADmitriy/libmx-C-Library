double mx_pow(double n, unsigned int pow) {
    if (pow == 0 || (n == 0 && pow == 0)) {
        return 1;
    }
    else {
        return n * mx_pow(n, pow - 1);
    }
}

