#include <gtest/gtest.h>

#include "lab2.cpp"  // ���������� ��������� � �����

// ���� ������ �������� � ���������
TEST(ThreadTests, FindMinMax) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  findMinMax(&data);  // �������� ������� ��������

  EXPECT_EQ(data.min, 3);
  EXPECT_EQ(data.max, 20);
}

// ���� ���������� �������� ��������
TEST(ThreadTests, CalculateAverage) {
  ThreadData data;
  data.array = {10, 5, 20, 3, 8};

  calculateAverage(&data);  // �������� ������� ��������

  EXPECT_NEAR(data.average, 9.2, 0.01);
}

// ���� ������ ������������ � ������������� ��������
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

  std::vector<double> expected = {10, 5, 9.2, 9.2, 8};  // 3 � 20 ��������
  for (size_t i = 0; i < data.array.size(); ++i) {
    EXPECT_NEAR(data.array[i], expected[i], 0.01);
  }
}

// ���� �������������� ����������
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
