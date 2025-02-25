// Файл MyStack.h
// Шаблонный класс MyStack на основе односвязного списка.
#ifndef MyStack_h  // защита от повторной компиляции
#define MyStack_h  // модуль подключен

namespace MyStack {
// Шаблонный класс ListNode (узел односвязного списка)
template<class INF, class FRIEND>
class ListNode  // узел списка
{
 private:
    INF d;                               // информационная часть узла
    ListNode* next;                      // указатель на следующий узел списка
    ListNode(void) { next = nullptr; };  // конструктор
    friend FRIEND;
};

// Шаблонный класс MyStack на основе односвязного списка.
template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

 public:
    MyStack(void) { top = nullptr; };  // конструктор
    ~MyStack(void) {
        while (top != nullptr) {
            ListNode<INF, MyStack<INF>>* next = top->next;
            delete top;
            top = next;
        }
    };  // освободить динамическую память
    bool empty(void) { return (top == nullptr); };  // стек пустой?
    bool push(INF n) {
        ListNode<INF, MyStack<INF>>* new_node = new ListNode<INF, MyStack<INF>>();
        new_node->d = n;
        new_node->next = top;
        top = new_node;
        return true;
    };  // добавить узел в вершину стека
    bool pop(void) {
        if (top == nullptr) {
            return false;
        }
        ListNode<INF, MyStack<INF>>* next = top->next;
        delete top;
        top = next;
        return true;
    };  // удалить узел из вершины стека
    INF top_inf(void) {
        if (top == nullptr) {
            return 0;
        }
        return top->d;
    };  // считать информацию из вершины стека
    friend std::ostream& operator<<(std::ostream& os, const MyStack<INF>& stack) {
        ListNode<INF, MyStack<INF>>* p = stack.top;
        while (p != nullptr) {
            os << p->d;
            if (p->next != nullptr) {
                os << " * ";
            }
            p = p->next;
        }
        os << std::endl;
        return os;
    };

};

int RunTask();
}  // namespace MyStack

#endif
