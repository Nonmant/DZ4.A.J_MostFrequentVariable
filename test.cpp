#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "0 yes no\n"
                "int main() {\n"
                "  int a;\n"
                "  int b;\n"
                "  scanf(\"%d%d\", &a, &b);\n"
                "  printf(\"%d\", a + b);\n"
                "}"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() ==
            "int"
    );
}

TEST_CASE("test 2", ""){
    std::stringstream input(
            "0 yes no\n"
            "#define INT int\n"
            "int main() {\n"
            "  INT a, b;\n"
            "  scanf(\"%d%d\", &a, &b);\n"
            "  printf(\"%d %d\", a + b, 0);\n"
            "}"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "d"
    );
}

TEST_CASE("test 3", ""){
    std::stringstream input(
            "6 no no\n"
            "program\n"
            "var\n"
            "begin\n"
            "end\n"
            "while\n"
            "for\n"
            "program sum;\n"
            "var\n"
            "  A, B: integer;\n"
            "begin\n"
            "  read(A, b);\n"
            "  writeln(a + b);\n"
            "end.\n"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "a"
    );
}

TEST_CASE("test 4", ""){
    std::stringstream input(
            "1 yes yes\n"
            "_\n"
            "a = 0h\n"
            "b = 0h\n"
            "c = 0h\n"
            ""
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "0h"
    );
}

TEST_CASE("shouldn't be only digits", ""){
    std::stringstream input(
            "0 yes yes\n"
            "1 1 1 a"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "a"
    );
}
