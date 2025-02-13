#include <fstream>
#include <iostream>

int main() {
    std::ofstream fout("sunsys.txt", std::ios::app);
    if (!fout) {
        std::cout << "Неудача при открытии файла sunsys.txt" << std::endl;
        return -1;
    }
    fout << "Mercury\t4878\t0\t0" << std::endl;
    fout << "Venus\t12104\t0\t0" << std::endl;
    fout << "Earth\t12774\t1\t1" << std::endl;
    fout << "Mars\t6786\t1\t2" << std::endl;
    fout << "Jupiter\t142796\t0\t16" << std::endl;
    fout << "Saturn\t120000\t0\t17" << std::endl;
    fout << "Uranus\t51108\t0\t5" << std::endl;
    fout << "Neptune\t49600\t0\t2" << std::endl;
    fout << "Pluto\t2280\t0\t1" << std::endl;
    fout.close();
    return 0;
}
