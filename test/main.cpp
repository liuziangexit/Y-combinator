#include "../include/Y.h"
#include <iostream>
#include <string>

void test(bool b) {
  if (!b)
    throw std::exception();
}

int main() {
  // test factorial
  test(6 == Y<unsigned int>(
                [](auto self, unsigned int n) -> unsigned int {
                  if (n == 0)
                    return 1;
                  else
                    return n * self(n - 1);
                },
                3));
  std::cout << "fac(3)=6\n";
  test(720 == Y<unsigned int>(
                  [](auto self, unsigned int n) -> unsigned int {
                    if (n == 0)
                      return 1;
                    else
                      return n * self(n - 1);
                  },
                  6));
  std::cout << "fac(6)=720\n";
  test(1 == Y<unsigned int>(
                [](auto self, unsigned int n) -> unsigned int {
                  if (n == 0)
                    return 1;
                  else
                    return n * self(n - 1);
                },
                1));
  std::cout << "fac(1)=1\n";
  test(1 == Y<unsigned int>(
                [](auto self, unsigned int n) -> unsigned int {
                  if (n == 0)
                    return 1;
                  else
                    return n * self(n - 1);
                },
                0));
  std::cout << "fac(0)=1\n";
  // test no argument no return value
  uint32_t value = 0;
  uint32_t to_be_copy = 88;
  Y<void>([&value, to_be_copy](auto self) {
    if (++value == 3)
      return;
    test(to_be_copy == 88);
    self();
  });
  test(value == 3);

  // test more argument
  value = 0;
  Y<void>(
      [&value, to_be_copy](auto self, std::string str, long bu) {
        if (++value == 3)
          return;
        test(to_be_copy == 88);
        test(str == "gaga");
        test(bu == 9988);
        self(str, bu);
      },
      "gaga", 9988);
  test(value == 3);
  std::cout << "ok!";
}