// ns4516
// Function correctly returns 1 + 2 = 3

asm("li $29, 0x24000000");

int add(int a, int b);

int entry() {
    return add(1, 2);
}

int add(int a, int b) {
    return a + b;
}
