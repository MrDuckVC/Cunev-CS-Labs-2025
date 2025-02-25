#include <iostream>
#include "MyStack.h"

namespace MyStack {
void Multipliers(int n, MyStack<int>& stack) {
    int divisor = 2;
    while (n > 1) {
        while (n % divisor == 0) {
            stack.push(divisor);
            n /= divisor;
        }
        divisor++;
    }
}

int RunTask() {
    MyStack<char> TestStack;
    TestStack.push('A');
    TestStack.push('B');
    TestStack.push('C');
    std::cout << TestStack;

    int N = 3960;
    MyStack<int> stack;

    Multipliers(N, stack);
    std::cout << stack;

    // Вывод множителей по убыванию
    std::cout << N << " = " << stack;

    MyStack<int> tempStack;
    while (!stack.empty()) {
        int factor = stack.top_inf();
        // std::cout << factor;
        stack.pop();
        tempStack.push(factor);
        if (!stack.empty()) {
            // std::cout << " * ";
        }
    }

    // Вывод множителей по возрастанию
    std::cout << N << " = " << tempStack;

    return 0;
}
}  // namespace MyStack
