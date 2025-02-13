#include <iostream>
#include <fstream>
#include "planet.h"

namespace planet {

Planet::Planet(int nameLength) { name_ = new char[nameLength]; }
Planet::~Planet() { delete[] name_; }

void Planet::setName(char *newName) { delete[] name_; name_ = new char[strlen(newName) + 1]; strcpy(name_, newName); }
void Planet::setLife(bool newLife) { life_ = newLife; }
void Planet::setDiameter(int newDiameter) { diameter_ = newDiameter; }
void Planet::setSatellitesNum(int newSatellitesNum) { satellitesNum_ = newSatellitesNum; }
char* Planet::getName() { return name_; }
bool Planet::getLife() { return life_; }
int Planet::getDiameter() { return diameter_; }
int Planet::getSatellitesNum() { return satellitesNum_; }
void Planet::edit() {}

bool Planet::operator==(Planet &p) { return (diameter_ == p.diameter_); }
bool Planet::operator<(Planet &p) { return (diameter_ < p.diameter_); }
bool Planet::operator>(Planet &p) { return (diameter_ > p.diameter_); }

std::ostream &operator<<(std::ostream &out, Planet p) {
    std::cout << "p.getDiameter()" << std::endl;
    std::cout << p.getName() << std::endl;
    out << p.getName() << "\t" << p.getDiameter() << "\t" << p.getLife() << "\t" << p.getSatellitesNum();
    std::cout << "p.getDiameter()" << std::endl;
    return out;
}
std::ofstream &operator<<(std::ofstream &out, Planet p) {
    out << (&p)->getName() << "\t" << (&p)->getDiameter() << "\t" << (&p)->getLife() << "\t" << (&p)->getSatellitesNum() << "\n\r";
    return out;
}
std::ifstream &operator>>(std::ifstream &in, Planet p) {
    char buf[128];
    in.getline(buf, 128);
    char *name = new char[20];
    int diameter, life, satellitesNum;
    sscanf(buf, "%s\t%d\t%d\t%d\n", name, &diameter, &life, &satellitesNum);
    // in >> name >> diameter >> life >> satellitesNum >> std::ws;
    p.setName(name);
    p.setDiameter(diameter);
    p.setLife(life);
    p.setSatellitesNum(satellitesNum);

    delete[] name;
    return in;
}

int read_db(char *dbFileName, planet::Planet *planets, const int size) {
    std::ifstream fin(dbFileName, std::ios::in);
    if (!fin) {
        std::cout << "Неудача при открытии файла " << dbFileName << std::endl;
        return -1;
    }

    int n_planet = 0;
    Planet inputPlanets[size];
    while (!fin.eof() && n_planet < size) {
        fin >> inputPlanets[n_planet];
        std::cout << inputPlanets[n_planet].getName() << std::endl;
        n_planet++;
    }

    Planet *newPlanets = new Planet[n_planet + 1];
    for (int i = 0; i < n_planet; i++) {
        newPlanets[i] = inputPlanets[i];
    }

    delete[] planets;
    planets = newPlanets;

    fin.close();
    return n_planet;
}

int menu() {
    std::cout << " ============== ГЛАВНОЕ МЕНЮ ========================" << std::endl;
    std::cout << "l - вывод базы из файла\t\t 4 - вывод базы на экран" << std::endl;
    std::cout << "2 - вывод базы в файл\t\t 5 - сортировка базы" << std::endl;
    std::cout << "3 - поиск планеты\t\t 6 - выход" << std::endl;
    std::cout << "Для выбора операции введите цифру от 1 до 6" << std::endl;
    int resp;
    std::cin >> resp;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    return resp;
};

void print_db(planet::Planet *planets, int n_planet) {
    std::cout << "Планеты:" << std::endl;
    std::cout << "Название\tДиаметр\tЖивет\tКол-во сателитов" << std::endl;
    for (int i = 0; i < n_planet; i++) {
        std::cout << planets[i] << std::endl;
    }
    std::cout << std::endl;

};

int write_db(char *dbFileName, planet::Planet *planets, int n_planet) {
    std::ofstream fout(dbFileName);
    if (!fout) {
        std::cout << "Неудача при открытии файла " << dbFileName << std::endl;
        return -1;
    }
    for (int i = 0; i < n_planet; i++)
        fout << planets[i];
    fout.close();
    return 0;
}

int find(planet::Planet *, int) {
    return 0;
};

void sort_db(planet::Planet *planets, int n_planet) {
    for (int i = 0; i < n_planet - 1; i++)
        for (int j = i + 1; j < n_planet; j++)
            if (planets[i] > planets[j])
                std::swap(planets[i], planets[j]);
}

const int Size = 12;
const int l_record = 80;

int main() {
    char file_name[] = "sunsys.txt";
    Planet *planets = new Planet[Size];
    int n_planet;
    int ind;
    while (true) {
        switch (menu()) {
            case 1:
                n_planet = read_db(file_name, planets, Size);
                if (n_planet < 0)
                    return 1;
                std::cout << "Чтение базы данных завершено" << std::endl;
                break;
            case 2:
                if (write_db(file_name, planets, n_planet) < 0) {
                    return 1;
                }
                break;
            case 3:
                if ((ind = find(planets, n_planet)) >= 0)
                    planets[ind].edit();
                else
                    std::cout << "Такой планеты нет" << std::endl;
                break;
            case 4:
                print_db(planets, n_planet);
                break;
            case 5:
                sort_db(planets, n_planet);
                break;
            case 6:
                return 0;
            default:
                std::cout << " Неправильный ввод" << std::endl;
                break;
        }
    }
    return 0;
}
}
