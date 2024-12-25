// подключение фреймворка catch2
#include <catch2/catch.hpp>
#include <stdio.h>
#include <stdlib.h>

#define CATCH_CONFIG_MAIN

// инициализация функций для тестов
int isNum(const char* str);
int write(const char* filename, const char* data);
int sum(int a, int b);
int sub(int a, int b);


// Тест 1: Проверка корректности обработки допустимых значений ввода
TEST_CASE("Correct input values") {

    // Задание строк с целым числом
    const char* valid_integer_str = "12345"; 
    const char* valid_integer_str_with_sign = "-12345";

    // Проверка на корректность строк
    REQUIRE(isNum(valid_integer_str) == 1);
    REQUIRE(isNum(valid_integer_str_with_sign) == 1);
}

// Тест 2: Проверка поведения при некорректных значениях
TEST_CASE("Inorrect input values") {
    const char* invalid_integer_str = "12a45";  // Некорректная строка с буквой
    const char* invalid_integer_str_with_spaces = " 987 ";  // Строка с пробелами

    REQUIRE(isNum(invalid_integer_str) == 0);
    REQUIRE(isNum(invalid_integer_str_with_spaces) == 0);

    REQUIRE(sum(10, -5) == 5);
}

// Тест 3: Проверка граничных значений диапазона
TEST_CASE("Boundary values of integer range") {
    int min_int = INT_MIN;
    int max_int = INT_MAX;

    REQUIRE(min_int == -2147483648);
    REQUIRE(max_int == 2147483647);

    // Проверяем операцию сложения на граничных значениях
    REQUIRE(sum(min_int, 1) == -2147483647);
    REQUIRE(sum(max_int, -1) == 2147483646);
}

// Тест 4: Проверка правильности расчетов в зависимости от входных данных
TEST_CASE("Correct calculations based on input values") {
    REQUIRE(sum(-10, 5) == -5);
    REQUIRE(sub(-10, 5) == -15);
}

// Тест 5. Проверка на запись в файл
TEST_CASE("Writing to log.txt") {

    // создание файла и некоторого текста
    const char* filename = "log.txt";
    const char* text = "Some text";
    char content[1000];

    REQUIRE(write(filename, text) == 1);

    // Чтение данных из файла
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if (err == 0 && file) {
        fgets(content, sizeof(content), file);
        fclose(file);
    }

    // Проверка содержимого файла
    REQUIRE(strcmp(content, text) == 0);
}


// поиск целого числа в строке
int isNum(const char* str) {

    // если есть знак перед числом
    if (*str == '-' || *str == '+') str++;

    // поиск целого чила в строке
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

// проверка на запись в файл
int write(const char* filename, const char* data) {

    // открытие файла на запись
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");

    if (err != 0 || file == NULL) {
        return 0;
    }
    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}

// сумма данных чисел
int sum(int a, int b) {
    return a + b;
}

// разность данных чисел
int sub(int a, int b) {
    return a - b;
}
