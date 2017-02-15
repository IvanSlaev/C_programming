TESTING IMPLEMENTATION

We are goint to implement google C++ testing framework for creating a 
simple C++ unit test for a simple C program. 
Note that you must download the sourcecode of googletest by:
$ git clone https://github.com/google/googletest.git

Don't forteg to change the path in GTEST_DIR variable in Makefile

Compilation is completed successfully and the sample.c C program is
tested whit Google C++ unit test framework: GoogleTest.
Note that the small program "sample.c" is compiled with C++ compiler in order to
obtain an C++ object file "sample.o" which can be used in unit test compilation. 
Otherwise the linker with invoke an "unknown reference to: the_tested_function".
