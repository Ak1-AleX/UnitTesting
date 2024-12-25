// ����������� ���������� catch2
#include <catch2/catch.hpp>
#include <stdio.h>
#include <stdlib.h>

#define CATCH_CONFIG_MAIN

// ������������� ������� ��� ������
int isNum(const char* str);
int write(const char* filename, const char* data);
int sum(int a, int b);
int sub(int a, int b);


// ���� 1: �������� ������������ ��������� ���������� �������� �����
TEST_CASE("Correct input values") {

    // ������� ����� � ����� ������
    const char* valid_integer_str = "12345"; 
    const char* valid_integer_str_with_sign = "-12345";

    // �������� �� ������������ �����
    REQUIRE(isNum(valid_integer_str) == 1);
    REQUIRE(isNum(valid_integer_str_with_sign) == 1);
}

// ���� 2: �������� ��������� ��� ������������ ���������
TEST_CASE("Inorrect input values") {
    const char* invalid_integer_str = "12a45";  // ������������ ������ � ������
    const char* invalid_integer_str_with_spaces = " 987 ";  // ������ � ���������

    REQUIRE(isNum(invalid_integer_str) == 0);
    REQUIRE(isNum(invalid_integer_str_with_spaces) == 0);

    REQUIRE(sum(10, -5) == 5);
}

// ���� 3: �������� ��������� �������� ���������
TEST_CASE("Boundary values of integer range") {
    int min_int = INT_MIN;
    int max_int = INT_MAX;

    REQUIRE(min_int == -2147483648);
    REQUIRE(max_int == 2147483647);

    // ��������� �������� �������� �� ��������� ���������
    REQUIRE(sum(min_int, 1) == -2147483647);
    REQUIRE(sum(max_int, -1) == 2147483646);
}

// ���� 4: �������� ������������ �������� � ����������� �� ������� ������
TEST_CASE("Correct calculations based on input values") {
    REQUIRE(sum(-10, 5) == -5);
    REQUIRE(sub(-10, 5) == -15);
}

// ���� 5. �������� �� ������ � ����
TEST_CASE("Writing to log.txt") {

    // �������� ����� � ���������� ������
    const char* filename = "log.txt";
    const char* text = "Some text";
    char content[1000];

    REQUIRE(write(filename, text) == 1);

    // ������ ������ �� �����
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if (err == 0 && file) {
        fgets(content, sizeof(content), file);
        fclose(file);
    }

    // �������� ����������� �����
    REQUIRE(strcmp(content, text) == 0);
}


// ����� ������ ����� � ������
int isNum(const char* str) {

    // ���� ���� ���� ����� ������
    if (*str == '-' || *str == '+') str++;

    // ����� ������ ���� � ������
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

// �������� �� ������ � ����
int write(const char* filename, const char* data) {

    // �������� ����� �� ������
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");

    if (err != 0 || file == NULL) {
        return 0;
    }
    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}

// ����� ������ �����
int sum(int a, int b) {
    return a + b;
}

// �������� ������ �����
int sub(int a, int b) {
    return a - b;
}
