int mx_sqrt(int x) {
    if (x <= 0) {
        return 0;
    }

    unsigned int result = 1;

    while (result * result <= (unsigned int)x) {
        if (result * result == (unsigned int)x) {
            return (int)result;
        }

        result++;
    }

    return 0;
}

