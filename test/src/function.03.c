// qf316
// Should find the most common number in an array

asm("li $29, 0x24000000");

int mostCommon(int numbers[], int size);

int entry() {
    int numbers[] = {1, 2, 2, 3, 3, 3, 3, 4};
    return mostCommon(numbers, 8);
}

int mostCommon(int numbers[], int size) {
    int currentMostCommon = numbers[0];
    int count = 1;
    for (int i = 1; i < size; i++) {
        count += (numbers[i] == currentMostCommon) ? 1 : -1;
        if (count == 0) {
            currentMostCommon = numbers[i];
            count++;
        }
    }
    return currentMostCommon;
}
