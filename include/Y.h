/**
 * @author  liuziang
 * @contact liuziang@liuziangexit.com
 * @date    5/19/2022
 *
 * CPP implementation of the Y combinator
 *
 * Requires C++14.
 *
 */
#pragma once
#ifndef _liuziangexit_Y
#define _liuziangexit_Y
#include <functional>
#include <type_traits>
#include <utility>

/*
 * This is a CPP implementation of the Y combinator: /f.(/x.f(xx))(/x.f(xx))
 * With variadic arguments support(variadic template)
 *
 * Basically, the Y combinator is something that allows you to write a
 * recursive lambda in a language(e.g. C++ and Java) that doesn't support
 * self-referencing lambda.
 *
 * For example, if you want to write this function as a lambda:
 *
 * void recursion() {
 *   recursion();
 * }
 *
 * You would be wondering how to do it because lambdas don't have names:
 *
 * [] { how_to_call_myself???(); };
 *
 * Most people will figure out this, but even this seemingly promising solution
 * won't work, try it yourself! (actually, this trick works in Swift but not for
 * C++ and Java):
 *
 * auto recursion = [] { recursion(); };
 *
 * But with my Y combinator implementation, you could easily do it:
 *
 * Y<void>(
 *   [](auto self) { self(); }
 * );
 *
 * Here, "void" is your function's return type, you have to explicitly specify
 * it, and then you just pass your lambda as an argument into "Y", it will get
 * executed and receive a functor(that "auto self") that represents itself, you
 * can call this functor to do the recursion.
 *
 * This even works when your function has arguments(any number, any type).
 * For example, we can calculate factorial(it is a function that has a single
 * int argument):
 *
 * auto factorial_of_3 = Y<unsigned int>(
 *   [](auto self, unsigned int n) -> unsigned int {
 *     if (n == 0)
 *       return 1;
 *     else
 *       return n * self(n - 1);
 *   },
 *   3));
 *
 * This implementation is not rocket science but the
 * Mathematical/Logic/Philosophy theory behind it is... I have not fully
 * understood them yet! Check these out!
 * https://www.youtube.com/watch?v=9T8A89jgeTI&t=562s
 * https://en.wikipedia.org/wiki/Fixed-point_combinator
 * https://en.wikipedia.org/wiki/G%C3%B6del%27s_incompleteness_theorems
 * https://en.wikipedia.org/wiki/Halting_problem
 * https://en.wikipedia.org/wiki/Self-reference
 * https://blog.csdn.net/pongba/article/details/1336028 (Chinese)
 */

// disable clang recursion check
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
// user needs to explicitly specify RETURN_TYPE of FUNC but leave FUNC and ARGS
// for auto deducing. f: anything that is CALLABLE
// (https://en.cppreference.com/w/cpp/named_req/Callable) n: parameters to apply
// to f (will be Perfect Forwarded)
template <typename RETURN_TYPE, typename FUNC, typename... ARGS>
RETURN_TYPE Y(FUNC f, ARGS &&...n) {
  auto self_application = [&f](const auto &x, auto &&...nn) -> RETURN_TYPE {
    return f(
        [&x](auto &&...nnn) {
          return x(x, std::forward<decltype(nnn)>(nnn)...);
        },
        std::forward<decltype(nn)>(nn)...);
  };
  return self_application(self_application, std::forward<ARGS>(n)...);
}
#pragma clang diagnostic pop

#endif
