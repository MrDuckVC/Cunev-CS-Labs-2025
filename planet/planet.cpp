#include "planet.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kPlanetIDLength = 2;
const int kPlanetNameLength = 15;
const int kPlanetDiameterLength = 15;
const int kPlanetLifeLength = 10;
const int kPlanetSatellitesLength = 15;
const char kUnableToOpenFile[] = "Неудача при открытии файла ";
const char kEmptyDatabase[] = "База данных пуста";

void printPlanetsHeader() {
    std::cout << std::setw(kPlanetIDLength) << "ID" << std::setw(kPlanetNameLength) << "Name" << std::setw(kPlanetDiameterLength) << "Diameter"
              << std::setw(kPlanetLifeLength) << "Life" << std::setw(kPlanetSatellitesLength) << "Satellites" << std::endl;
}
void printPlanets(planet::Planet& p, int id) {
    std::cout << std::setw(kPlanetIDLength) << id << std::setw(kPlanetNameLength) << p.getName() << std::setw(kPlanetDiameterLength)
              << p.getDiameter() << std::setw(kPlanetLifeLength) << p.getLife() << std::setw(kPlanetSatellitesLength) << p.getSatellitesNum()
              << std::endl;
};
}  // namespace

namespace planet {
Planet::Planet(int nameLength = kPlanetNameLength) {
    name_ = new char[nameLength];
    name_[0] = '\0';
}
Planet::~Planet() {
    delete[] name_;
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
void Planet::set(char* name, int diameter, bool life, int satellitesNum) {
    setName(name);
    setDiameter(diameter);
    setLife(life);
    setSatellitesNum(satellitesNum);
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
    char* name = new char[kPlanetNameLength];
    int diameter, life, satellitesNum;
    in >> name >> diameter >> life >> satellitesNum >> std::ws;
    p.set(name, diameter, life, satellitesNum);

    delete[] name;
    return in;
}

int read_db(char* dbFileName, planet::Planet*& planets) {
    std::ifstream fin(dbFileName, std::ios::in);
    fin.seekg(0, std::ios::beg);
    if (!fin) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    int n_planet = 0;
    fin >> n_planet;

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
    std::cout << "Main menu:" << std::endl;
    std::cout << "l - read from DB" << std::endl;
    std::cout << "2 - write to DB" << std::endl;
    std::cout << "3 - sort DB" << std::endl;
    std::cout << "4 - add object" << std::endl;
    std::cout << "5 - delete object" << std::endl;
    std::cout << "6 - edit object" << std::endl;
    std::cout << "7 - print DB" << std::endl;
    std::cout << "8 - exit" << std::endl;
    std::cout << "Enter number from 1 to 8 to choose operation: ";
    int resp;
    std::cin >> resp;
    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    return resp;
};

void print_db(planet::Planet* planets, int n_planet) {
    if (n_planet == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Planets:" << std::endl;
    printPlanetsHeader();
    for (int i = 0; i < n_planet; i++) {
        printPlanets(planets[i], i);
    }
};

int write_db(char* dbFileName, planet::Planet* planets, int n_planet) {
    std::ofstream fout(dbFileName, std::ios::out);
    if (!fout) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    fout << static_cast<int>(n_planet) << std::endl;

    for (int i = 0; i < n_planet; i++)
        fout << planets[i] << std::endl;
    fout.close();

    return 0;
}

void add(Planet*& planets, int& n_planet) {
    char* name = new char[kPlanetNameLength];
    int diameter;
    bool life;
    int satellitesNum;
    std::cout << "Enter planet data devided by spaces: name diameter life(1 - yes, 0 - no) satellitesNum" << std::endl;
    std::cin >> name >> diameter >> life >> satellitesNum;

    Planet* newPlanets = new Planet[n_planet + 1];

    for (int i = 0; i < n_planet; i++) {
        newPlanets[i] = planets[i];
    }

    newPlanets[n_planet].set(name, diameter, life, satellitesNum);

    delete[] planets;
    planets = newPlanets;

    n_planet++;
    delete[] name;
}

void edit(Planet*& planets, int n_planet) {
    if (n_planet == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter planet ID to edit: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= n_planet) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    std::cout << "Enter planet data devided by spaces: name diameter life(1 - yes, 0 - no) satellitesNum" << std::endl;
    char* name = new char[kPlanetNameLength];
    int diameter;
    bool life;
    int satellitesNum;
    std::cin >> name >> diameter >> life >> satellitesNum;
    planets[id].set(name, diameter, life, satellitesNum);
    delete[] name;
};

void remove(Planet*& planets, int& n_planet) {
    if (n_planet == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter planet ID to delete: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= n_planet) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    Planet* newPlanets = new Planet[n_planet - 1];
    int j = 0;

    for (int i = 0; i < n_planet; i++) {
        if (id == i) {
            continue;
        }
        newPlanets[j] = planets[i];
        j++;
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

int main() {
    char fileName[] = "sunsys.txt";
    int n_planet = 0;
    Planet* planets = new Planet[n_planet];
    int ind;
    while (true) {
        switch (menu()) {
            case 1:
                n_planet = read_db(fileName, planets);
                if (n_planet < 0)
                    return 1;
                std::cout << "Reading database completed" << std::endl;
                break;
            case 2:
                if (write_db(fileName, planets, n_planet) < 0) {
                    return 1;
                }
                std::cout << "Writing database completed" << std::endl;
                break;
            case 3:
                sort_db(planets, n_planet);
                std::cout << "Sorting database completed" << std::endl;
                break;
            case 4:
                add(planets, n_planet);
                std::cout << "Adding object completed" << std::endl;
                break;
            case 5:
                remove(planets, n_planet);
                std::cout << "Deleting object completed" << std::endl;
                break;
            case 6:
                edit(planets, n_planet);
                std::cout << "Поиск завершен" << std::endl;
                break;
            case 7:
                print_db(planets, n_planet);
                std::cout << "Printing database completed" << std::endl;
                break;
            case 8:
                return 0;
            default:
                std::cout << "Invalid input" << std::endl;
                break;
        }
        std::cout << std::endl;
    }
    return 0;
}
}  // namespace planet
