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
    int N = 3960;
    MyStack<int> stack;

    Multipliers(N, stack);

    // Вывод множителей по убыванию
    std::cout << N << "=";
    MyStack<int> tempStack;
    while (!stack.empty()) {
        int factor = stack.top_inf();
        std::cout << factor;
        stack.pop();
        tempStack.push(factor);
        if (!stack.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;

    // Вывод множителей по возрастанию
    std::cout << N << "=";
    while (!tempStack.empty()) {
        int factor = tempStack.top_inf();
        std::cout << factor;
        tempStack.pop();
        if (!tempStack.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;

    return 0;
}
}  // namespace MyStack
