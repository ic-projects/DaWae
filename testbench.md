# Testbench

The testbench is written in Python 2.7.

As Python is not installed by default on the test machines, we are using `pyinstaller` to bundle our testbench with Python, into a single binary, which can be executed on its own.

- If any test takes longer than 5 seconds to run, then the testbench will automatically timeout.

- To increase the timeout, change `TEST_TIMEOUT` as required in `test/mips_testbench.py` and run `make testbench-build` on a machine with `pyinstaller` to rebundle the testbench.

- Alternatively, if Python is installed on the machine, simply run `python test/mips_testbench.py <path-to-mips-simulator>` to use the testbench

## Adding a new test

To add a new test:

1. Create a file in `test/src/` with the code to be compiled/assembled:
    - `<test-name>.s` for MIPS assembly instructions
    - `<test-name>.c` for C code (note that using standard libraries such as `stdio` may not work)
        - Implementing input and output should be done by reading and writing to `0x30000000` and `0x30000004` respectively
        - An example of how to do this is shown in `test/src/function.04.c`

2. Create a file `<test-name>.mips.out` in `test/output/` with:
    - 1st line with the exit code (e.g. `0`)
    - Output (checked against `stdout`) on the rest of the lines
    
3. Any data to be input into `stdin` while running the test should be put into a file `test/input/<test-name>.in`
    - If no input is needed, then there's no need to create the file
