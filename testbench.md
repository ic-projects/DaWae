# Testbench

The testbench is written in Python 2.7.

## Adding a new test

To add a new test:

1. Create a file `<test-name>.s` in `test/src/` with some MIPS assembly instructions.
2. Create a file `<test-name>.mips.out` in `test/output/` with:
    - 1st line with the exit code (e.g. `0`)
    - Output (`stdout`) on the rest of the lines
