# Y-combinator

[![Build Status](https://github.com/liuziangexit/Y-combinator/workflows/build/badge.svg)](https://github.com/liuziangexit/Y-combinator/actions)
<br>
Y combinator implementation written in C++14.
<br>
使用C++ 14实现的Y combinator。

Basically, the Y combinator is something that allows you to write a recursive lambda in a language(e.g. C++ and Java)
that doesn't support self-referencing lambda.
<br>
简单地说，Y combinator可以让你在不支持lambda自我引用的语言（如C++或Java）中，写出递归的lambda。

For example, if you want to write this function as a lambda:
<br>
例如，如果你想将这个函数写为lambda：

```
void recursion() { 
  recursion(); 
}
```

You would be wondering how to call it because lambdas don't have names:
<br>
你会想，我该如何调用它呢？lambda又没有名字：

```
[] { how_to_call_myself???(); };
```

Most people will figure out this, but even this seemingly promising solution won't work, try it yourself! (actually,
this
trick works in Swift but not for C++ and Java):
<br>
大部分人会搞出这个，但即使这种写法看起来挺靠谱，实际上却不行，你可以试试！（实际上这种写法在Swift里可以，但在C++和Java中却不行）

```
auto recursion = [] { recursion(); };
```

But with my Y combinator implementation, you could easily do it:
<br>
但有了我写的Y combinator，你可以很容易地做到：

```
#include <Y.h>

int main() {

  // this recursive lambda never returns, it's just calling itself again and again until stack overflow
  // 这个递归的lambda不返回，它只是疯狂地调用他自己直到栈用完
  Y<void>(
    [](auto self) { self(); }
  );

  // this recursive lambda actually does something, it calculates factorial
  // 这个递归的lambda终于干了点正事，它计算阶乘
  unsigned int fac_of_3 = Y<unsigned int>(
    [](auto self, unsigned int n) -> unsigned int {
      if (n == 0)
        return 1;
      else
        return n * self(n - 1);
    },
    3));
  
}
```

For more information, please visit [Source Code](include/Y.h).
<br>
了解更多信息，请看[源代码](include/Y.h)。

You might be wondering can we implement Y in Java? The answer is no because Java has baby FP ability. (Fxck Java by the
way...)
<br>
你可能在想，我们可以在Java中实现Y吗？答案是否定的，因为Java的函数式编程能力不够强。（顺便说一句，傻x Java。。。）
