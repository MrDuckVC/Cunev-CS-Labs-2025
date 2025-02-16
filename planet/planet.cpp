#include "planet.h"
#include <fstream>
#include <iostream>

namespace planet {

int Planet::total = 0;

Planet::Planet(int nameLength) {
    name_ = new char[nameLength];
    name_[0] = '\0';
    total++;
    id_ = total;
}
Planet::~Planet() {
    delete[] name_;
    total--;
}

void Planet::setName(char* newName) {
    delete[] name_;
    name_ = new char[strlen(newName) + 1];
    strcpy(name_, newName);
}
void Planet::setLife(bool newLife) {
    life_ = newLife;
}
void Planet::setDiameter(int newDiameter) {
    diameter_ = newDiameter;
}
void Planet::setSatellitesNum(int newSatellitesNum) {
    satellitesNum_ = newSatellitesNum;
}
char* Planet::getName() {
    return name_;
}
bool Planet::getLife() {
    return life_;
}
int Planet::getDiameter() {
    return diameter_;
}
int Planet::getSatellitesNum() {
    return satellitesNum_;
}
int Planet::getTotal() {
    return total;
}
int Planet::getID() {
    return id_;
}
void Planet::edit() {
}

bool Planet::operator==(Planet& p) {
    return (diameter_ == p.diameter_);
}
bool Planet::operator<(Planet& p) {
    return (diameter_ < p.diameter_);
}
bool Planet::operator>(Planet& p) {
    return (diameter_ > p.diameter_);
}
Planet& Planet::operator=(const Planet& other) {
    if (this != &other) {
        id_ = other.id_;
        diameter_ = other.diameter_;
        life_ = other.life_;
        satellitesNum_ = other.satellitesNum_;

        delete[] name_;
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
    }
    return *this;
}

std::ofstream& operator<<(std::ofstream& out, Planet& p) {
    out << p.getName() << "\t" << p.getDiameter() << "\t" << p.getLife() << "\t" << p.getSatellitesNum();
    return out;
}
std::ifstream& operator>>(std::ifstream& in, Planet& p) {
    char* name = new char[20];
    int diameter, life, satellitesNum;
    in >> name >> diameter >> life >> satellitesNum >> std::ws;
    p.setName(name);
    p.setDiameter(diameter);
    p.setLife(life);
    p.setSatellitesNum(satellitesNum);

    delete[] name;
    return in;
}

int read_db(char* dbFileName, planet::Planet*& planets, const int size) {
    std::ifstream fin(dbFileName, std::ios::in);
    fin.seekg(0, std::ios::beg);
    if (!fin) {
        std::cout << "Неудача при открытии файла " << dbFileName << std::endl;
        return -1;
    }

    int n_planet = 0;
    fin >> n_planet;
    if (n_planet > size) {
        std::cout << "База данных слишком большая!" << std::endl;
        return -1;
    }

    Planet* newPlanets = new Planet[n_planet];
    delete[] planets;
    planets = newPlanets;
    for (int i = 0; i < n_planet; i++) {
        fin >> planets[i];
    }

    fin.close();
    return n_planet;
}

int menu() {
    std::cout << " ===================== ГЛАВНОЕ МЕНЮ =====================" << std::endl;
    std::cout << "l - чтение БД из файла\t\t 5 - удаление объекта из БД" << std::endl;
    std::cout << "2 - запись БД в файл\t\t 6 - редактирование БД" << std::endl;
    std::cout << "3 - сортировка БД\t\t 7 - вывод БД на экран" << std::endl;
    std::cout << "4 - добавление нового в БД\t 8 - выход" << std::endl;
    std::cout << "Для выбора операции введите цифру от 1 до 8" << std::endl;
    int resp;
    std::cin >> resp;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    return resp;
};

void print_db(planet::Planet* planets, int n_planet) {
    if (n_planet == 0) {
        std::cout << "База данных пуста" << std::endl;
        return;
    }

    std::cout << "Планеты:" << std::endl;
    std::cout << "ID\tНазвание\tДиаметр\t\tЖивет\tКол-во сателитов" << std::endl;
    for (int i = 0; i < n_planet; i++) {
        std::cout << planets[i].getID() << "\t" << planets[i].getName() << "\t\t" << planets[i].getDiameter() << "\t\t" << planets[i].getLife()
                  << "\t" << planets[i].getSatellitesNum() << std::endl;
    }
    std::cout << std::endl;
};

int write_db(char* dbFileName, planet::Planet* planets, int n_planet) {
    std::ofstream fout(dbFileName, std::ios::out);
    if (!fout) {
        std::cout << "Неудача при открытии файла " << dbFileName << std::endl;
        return -1;
    }

    fout << static_cast<int>(n_planet) << std::endl;

    for (int i = 0; i < n_planet; i++)
        fout << planets[i] << std::endl;
    fout.close();

    return 0;
}

int find(planet::Planet* planets, int) {
    return 0;
};

void add(Planet*& planets, int& n_planet) {
    std::cout << "Введите данные о планете" << std::endl;
    std::cout << "Название: ";
    char* name = new char[20];
    std::cin >> name;
    std::cout << "Диаметр: ";
    int diameter;
    std::cin >> diameter;
    std::cout << "Живет: ";
    int life;
    std::cin >> life;
    std::cout << "Кол-во сателитов: ";
    int satellitesNum;
    std::cin >> satellitesNum;

    Planet* newPlanets = new Planet[n_planet + 1];

    for (int i = 0; i < n_planet; i++) {
        newPlanets[i] = planets[i];
    }

    newPlanets[n_planet].setName(name);
    newPlanets[n_planet].setDiameter(diameter);
    newPlanets[n_planet].setLife(life);
    newPlanets[n_planet].setSatellitesNum(satellitesNum);

    delete[] planets;

    planets = newPlanets;

    n_planet++;

    delete[] name;
}

void del(Planet*& planets, int& n_planet) {
    if (n_planet == 0) {
        std::cout << "База данных пуста" << std::endl;
        return;
    }

    std::cout << "Введите ID удаляемого объекта" << std::endl;
    int id;
    std::cin >> id;

    Planet* newPlanets = new Planet[n_planet - 1];
    int j = 0;
    bool found = false;

    for (int i = 0; i < n_planet; i++) {
        if (planets[i].getID() == id) {
            found = true;
            continue;
        }
        newPlanets[j] = planets[i];
        j++;
    }

    if (!found) {
        std::cout << "Объект с ID " << id << " не найден" << std::endl;
        delete[] newPlanets;
        return;
    }

    delete[] planets;
    planets = newPlanets;
    n_planet--;
}

void sort_db(planet::Planet*& planets, int n_planet) {
    for (int i = 0; i < n_planet - 1; ++i) {
        for (int j = 0; j < n_planet - i - 1; ++j) {
            if (planets[j] < planets[j + 1]) {
                Planet* temp = new Planet;
                *temp = planets[j];
                planets[j] = planets[j + 1];
                planets[j + 1] = *temp;
            }
        }
    }
}

const int Size = 12;

int main() {
    char fileName[] = "sunsys.txt";
    int n_planet = 0;
    Planet* planets = new Planet[n_planet];
    int ind;
    while (true) {
        switch (menu()) {
            case 1:
                n_planet = read_db(fileName, planets, Size);
                if (n_planet < 0)
                    return 1;
                std::cout << "Чтение базы данных завершено" << std::endl;
                break;
            case 2:
                if (write_db(fileName, planets, n_planet) < 0) {
                    return 1;
                }
                std::cout << "Запись базы данных завершена" << std::endl;
                break;
            case 3:
                sort_db(planets, n_planet);
                break;
            case 4:
                add(planets, n_planet);
                break;
            case 5:
                del(planets, n_planet);
                break;
            case 6:
                if ((ind = find(planets, n_planet)) >= 0)
                    planets[ind].edit();
                else
                    std::cout << "Такой планеты нет" << std::endl;
                break;
            case 7:
                print_db(planets, n_planet);
                break;
            case 8:
                return 0;
            default:
                std::cout << " Неправильный ввод" << std::endl;
                break;
        }
    }
    return 0;
}
}  // namespace planet
