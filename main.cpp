#include <cstring>
#include <iostream>
#include "containers/myset.h"
#include "containers/myvector.h"

int RunInteractive() {
    return 0;
}

int RunDemo() {
    MyVector<char*> v;
    v.add_element((char*)"Hello!");
    v.add_element((char*)"Привет!");
    v.add_element((char*)"Привет!");
    v.add_element((char*)"Привет!");
    v.add_element((char*)"Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.add_element((char*)"Привет!");
    v.add_element((char*)"Привет!");
    v.add_element((char*)"Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    MyVector v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < MAX_SIZE; i++)
        v1.delete_element(0);
    std::cout << "Вектор v1: " << v1 << std::endl;





    MySet<char*> s, s1, s2;
    s.add_element((char*)"Yes!");
    s.add_element((char*)"Привет!");
    s.add_element((char*)"No");
    char str[] {"Hello!"};
    s.add_element(str);
    std::cout << "Множество s: " << s << std::endl;
    s1.add_element((char*)"Cat");
    s1.add_element((char*)"No");
    s1.add_element((char*)"Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    MySet s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2)
        std::cout << "Множество s3=s2\n";
    else
        std::cout << "Множество s3!=s2\n";
    if (s3 == s1)
        std::cout << "Множество s3=s1\n";
    else
        std::cout << "Множество s3!=s1\n";
    if (s1 == s3)
        std::cout << "Множество s1=s3\n";
    else
        std::cout << "Множество s1!=s3\n";



    MySet<std::string> s4;
    s4.add_element("sdfgdfs");
    s4.add_element("sdf");
    s4.add_element("sdff");
    std::cout << s4 << std::endl;





    MySet<char*> v2;
    char* str4 = new char[strlen("ee1") + 1];
    strcpy(str4, "ee1");
    char* str5 = new char[strlen("d") + 1];
    strcpy(str5, "d");
    char* str6 = new char[strlen("eedfg33") + 1];
    strcpy(str6, "eedfg33");
    char* str7 = new char[strlen("ee444") + 1];
    strcpy(str7, "ee443");

    v2.add_element(str4);
    v2.add_element(str5);
    v2.add_element(str6);
    v2.add_element(str7);

    std::cout << v2 << std::endl;
    delete [] str4;
    delete [] str5;
    delete [] str6;
    delete [] str7;
    MySet<char*> v3(v2);
    v2.delete_element(str6);
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;


    return 0;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    bool isInteractive = false;

    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        return RunInteractive();
    } else {
        return RunDemo();
    }
}
