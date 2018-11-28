// qf316
// Takes input from STDIN and output it to STDOUT

int entry() {
    volatile int *input = (int *) 0x30000000;
    volatile int *output = (int *) 0x30000004;
    int c = *input;

    // Assuming EOF is signalled by a negative number (normally -1?)
    while (c >= 0) {
        *output = c;
        c = *input;
    }
    return 0;
}
