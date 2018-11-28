// ns4516
// Function correctly returns 1

asm("li $29, 0x24000000");

int test_function();

int entry() {
    return test_function();
}

int test_function() {
    return 1;
}