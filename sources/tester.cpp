// Copyright 2018 Your Name <your_email>

#include <tester.hpp>
#include <iostream>

Tester::Tester(std::vector<int> series):
    m_series(series), L1_size(96*1024 / sizeof(int)), tmp(0), count(0)
{
}

int* Tester::get_random_array(int size) {
  int* array = new int [size];
  for (int i=0; i < size; ++i){
    array[i] = random();
  }
  return array;
}

void Tester::free_array(int* array){
  delete[] array;
}

int Tester::random_16(int zero, int array_size) {
  int a = zero + random() % (array_size - zero + 1);
  if (a/16 == 0){
    return a;
  } else{
    int b = a%16;
    a = a - b;
  }
  return a;
}

double Tester::direct(int array_size) {
  int* array = get_random_array(array_size);
  // warming up по размеру L1
  if (array_size < L1_size) {
    count = L1_size / array_size;
    for (int k = 0; k < count; ++k) {
      for (int i = 0; i < array_size; i += step) tmp = array[i];
    }
  } else {
    for (int i = 0; i < L1_size; i += step) tmp = array[i];
  }
  // test
  int elapsed_seconds = 0;
  for (int i = 0; i < iter; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < array_size; j += step) {
      tmp = array[j];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsed_seconds +=
        std::chrono::duration_cast
            <std::chrono::microseconds>(finish - start).count();
  }
  free_array(array);
  tmp = 0;
  count = 0;
  return (static_cast<double> (elapsed_seconds) / iter);
}

double Tester::reverse(int array_size) {
  int* array = get_random_array(array_size);
  int elapsed_seconds = 0;
  // warming up по размеру L1
  if (array_size < L1_size) {
    count = L1_size / array_size;
    for (int k = 0; k < count; ++k) {
      for (int i = 0; i < array_size; i += step) tmp = array[i];
    }
  } else {
    for (int i = 0; i < L1_size; i += step) tmp = array[i];
  }
  // test
  for (int j = 0; j < iter; ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = array_size - array_size % step - 1; i >= 0; i -= step) {
      tmp = array[i];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsed_seconds =
        std::chrono::duration_cast
            <std::chrono::microseconds>(finish - start).count();
  }
  free_array(array);
  tmp = 0;
  count = 0;
  return (static_cast<double> (elapsed_seconds) / iter);
}

double Tester::randomn(int array_size) {
  int* array = get_random_array(array_size);
  // warming up по размеру L1
  if (array_size < L1_size) {
    count = L1_size / array_size;
    for (int k = 0; k < count; ++k) {
      for (int i = 0; i < array_size; i += step) tmp = array[i];
    }
  } else {
    for (int i = 0; i < L1_size; i += step) tmp = array[i];
  }
  // test
  int elapsed_seconds = 0;
  for (int i = 0; i < iter; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < array_size; j += step) {
      tmp = array[random_16(0, array_size)];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsed_seconds +=
        std::chrono::duration_cast
            <std::chrono::microseconds>(finish - start).count();
  }
  free_array(array);
  tmp = 0;
  count = 0;
  return (static_cast<double> (elapsed_seconds) / iter);
}

void Tester::experiment(std::ostream& out) {
  //direct
  out << "Investigation:" << std::endl << "travel variant: direct" <<\
 std::endl << "experiments: " << std::endl;
  for (size_t i = 0; i < m_series.size(); ++i){
    out << "    number: " << i + 1 << std::endl <<\
           "    input data:" << std::endl <<\
           "      buffer_size: " << m_series[i] / 256 << " KiB" <<\
                                                           std::endl <<\
           "    results:" << std::endl <<\
           "      duration: " << direct(m_series[i]) <<\
           " mcs" << std::endl; }
//reverse
  out << std::endl << std::endl << "travel variant: reverse" <<\
 std::endl << "experiments: " << std::endl;
  for (size_t i = 0; i < m_series.size(); ++i) {
    out << "    number: " << i + 1 << std::endl
        << "    input data:" << std::endl
        << "      buffer_size: " << m_series[i] / 256 << " KiB" << std::endl
        << "    results:" << std::endl
        << "     duration: " << reverse(m_series[i]) << " mcs" << std::endl; }
  //random
  out << std::endl << std::endl << "travel variant: random" <<\
 std::endl << "experiments: " << std::endl;
  for (size_t i = 0; i < m_series.size(); ++i){
    out << "    number: " << i + 1 << std::endl <<\
           "    input data:" << std::endl <<\
           "      buffer_size: " << m_series[i] / 256 << " KiB" <<\
                                                           std::endl <<\
           "    results:" << std::endl <<\
           "      duration: " << randomn(m_series[i]) <<\
           " mcs" << std::endl; }
}

Tester::~Tester()
{}
