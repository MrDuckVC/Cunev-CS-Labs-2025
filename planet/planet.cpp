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
char *Planet::getName() { return name_; }
bool Planet::getLife() { return life_; }
int Planet::getDiameter() { return diameter_; }
int Planet::getSatellitesNum() { return satellitesNum_; }

const bool &Planet::operator==(const Planet &p) { return (diameter_ == p.diameter_); }
const bool &Planet::operator<(const Planet &p) { return (diameter_ < p.diameter_); }
const bool &Planet::operator>(const Planet &p) { return (diameter_ > p.diameter_); }

std::ofstream &operator<<(std::ofstream &out, Planet *p) {
    out << p->getName() << "\t" << p->getDiameter() << "\t" << p->getLife() << "\t" << p->getSatellitesNum() << "\n";
    return out;
}
std::ifstream &operator>>(std::ifstream &in, Planet *p) {
    char *name;
    int diameter, life, satellitesNum;
    in >> name >> diameter >> life >> satellitesNum;
    p->setName(name);
    p->setDiameter(diameter);
    p->setLife(life);
    p->setSatellitesNum(satellitesNum);
    return in;
}

int read_db(char *dbFileName, planet::Planet *planets, const int) {
    std::ifstream fin(dbFileName);
    int n_planet = 0;
    while (!fin.eof()) {
        fin >> planets[n_planet];
        n_planet++;
    }
    fin.close();
    return n_planet;
};

int menu();

void print_db(planet::Planet *, int);

int write_db(char *, planet::Planet *, int) {
    std::ofstream fout(dbFileName);
    for (int i = 0; i < n_planet; i++) {
        fout << planets[i].name << "\t" << planets[i].diameter << "\t"
             << planets[i].life << "\t" << planets[i].satellitesNum << std::endl;
    }
    fout.close();
    return 0;
};

int find(planet::Planet *, int);

void sort_db(planet::Planet *, int);

const int Size = 12;
const int l_record = 80;

int main() {
    char *file_name = "sunsys.txt";
    planet::Planet planets[Size];
    int n_planet;
    int ind;
    while (true) {
        switch (menu()) {
            case 1:
                n_planet = read_db(file_name, planets, Size);
                break;
            case 2:
                write_db(file_name, planets, n_planet);
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
