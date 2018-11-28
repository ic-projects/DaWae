// qf316
// Recursive multiplication should return correct result

asm("li $29, 0x24000000");

int multiply(int a, int b);

int entry() {
    return multiply(78, 27);
}

int multiply(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a + multiply(a, b - 1);
}
