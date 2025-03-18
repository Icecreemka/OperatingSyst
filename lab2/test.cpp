#include <gtest/gtest.h>

#include "lab2.cpp"  // Подключите заголовок с кодом

// Тест поиска минимума и максимума
TEST(ThreadTests, FindMinMax) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  findMinMax(&data);  // Вызываем функцию напрямую

  EXPECT_EQ(data.min, 3);
  EXPECT_EQ(data.max, 20);
}

// Тест вычисления среднего значения
TEST(ThreadTests, CalculateAverage) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  calculateAverage(&data);  // Вызываем функцию напрямую

  EXPECT_NEAR(data.average, 9.2, 0.01);
}

// Тест замены минимального и максимального значений
TEST(ThreadTests, ReplaceMinMaxWithAverage) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  findMinMax(&data);
  calculateAverage(&data);

  for (double& num : data.array) {
    if (num == data.min || num == data.max) {
      num = data.average;
    }
  }

  std::vector<double> expected = {10, 5, 9.2, 9.2, 8};  // 3 и 20 заменены
  for (size_t i = 0; i < data.array.size(); ++i) {
    EXPECT_NEAR(data.array[i], expected[i], 0.01);
  }
}

// Тест многопоточного выполнения
TEST(ThreadTests, Multithreading) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  HANDLE hMinMax = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
  HANDLE hAverage = CreateThread(NULL, 0, calculateAverage, &data, 0, NULL);

  WaitForSingleObject(hMinMax, INFINITE);
  WaitForSingleObject(hAverage, INFINITE);

  CloseHandle(hMinMax);
  CloseHandle(hAverage);

  EXPECT_EQ(data.min, 3);
  EXPECT_EQ(data.max, 20);
  EXPECT_NEAR(data.average, 9.2, 0.01);
}
