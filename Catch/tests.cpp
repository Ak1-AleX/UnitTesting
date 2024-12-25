#include "pch.h"
#include <catch2/catch.hpp>
#include <stdio.h>
#include <stdlib.h>

#define CATCH_CONFIG_MAIN

int isChislo(const char* str) {
    if (*str == '-' || *str == '+') str++; // Знак перед числом
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int writeLog(const char* filename, const char* data) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");

    if (err != 0 || file == NULL) {
        return 0;
    }
    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}

int summa(int a, int b) {
    return a + b;
}

int razn(int a, int b) {
    return a - b;
}

// Тест 1: Проверка корректности обработки допустимых значений ввода
TEST_CASE("Верные входные значения") {
    const char* valid_integer_str = "12345"; // Допустимая строка с целым числом
    const char* valid_integer_str_with_sign = "-12345";

    // Проверяем, что строка с целым числом считается корректной
    REQUIRE(isChislo(valid_integer_str) == 1);
    REQUIRE(isChislo(valid_integer_str_with_sign) == 1);

    // Проверяем, что сложение двух чисел работает правильно
    int result = summa(10, 5);
    REQUIRE(result == 15);
}
// Тест 2: Проверка поведения при некорректных значениях
TEST_CASE("Неверные входные значения") {
    const char* invalid_integer_str = "12a34";  // Некорректная строка с буквой
    const char* invalid_integer_str_with_spaces = " 123 ";  // Строка с пробелами

    REQUIRE(isChislo(invalid_integer_str) == 0);
    REQUIRE(isChislo(invalid_integer_str_with_spaces) == 0);

    int result = summa(10, -5);
    REQUIRE(result == 5);
}
// Тест 3: Проверка граничных значений диапазона
TEST_CASE("Граничные значения целочисленного диапазона") {
    int min_int = INT_MIN;
    int max_int = INT_MAX;

    REQUIRE(min_int == -2147483648);
    REQUIRE(max_int == 2147483647);

    // Проверяем операцию сложения на граничных значениях
    REQUIRE(summa(min_int, 1) == -2147483647);
    REQUIRE(summa(max_int, -1) == 2147483646);
}
// Тест 4: Проверка правильности расчетов в зависимости от входных данных
TEST_CASE("Корректные вычисления на основе входных значений") {

    int result_add = summa(10, 5);
    int result_sub = razn(10, 5);

    REQUIRE(result_add == 15);
    REQUIRE(result_sub == 5);

    REQUIRE(summa(-10, 5) == -5);
    REQUIRE(razn(-10, 5) == -15);
}
// Тест 5. Проверка на запись в файл
TEST_CASE("Запись в log.txt") {
    const char* filename = "log.txt";
    const char* text = "Это тестовая запись";

    REQUIRE(writeLog(filename, text) == 1);
    // Читаем данные из файла
    FILE* file = nullptr;
    char content[256];  // Массив для хранения содержимого файла

    errno_t err = fopen_s(&file, filename, "r");  // Открываем файл для чтения с использованием fopen_s
    if (err == 0 && file) {
        fgets(content, sizeof(content), file);
        fclose(file);
    }
    // Проверяем, что содержимое файла совпадает с ожидаемым
    REQUIRE(strcmp(content, text) == 0);
}