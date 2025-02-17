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

void PrintPlanetsHeader() {
    std::cout << std::setw(kPlanetIDLength) << "ID" << std::setw(kPlanetNameLength) << "Name" << std::setw(kPlanetDiameterLength) << "Diameter"
              << std::setw(kPlanetLifeLength) << "Life" << std::setw(kPlanetSatellitesLength) << "Satellites" << std::endl;
}
void PrintPlanets(planet::Planet& p, int id) {
    std::cout << std::setw(kPlanetIDLength) << id << std::setw(kPlanetNameLength) << p.GetName() << std::setw(kPlanetDiameterLength)
              << p.GetDiameter() << std::setw(kPlanetLifeLength) << p.GetLife() << std::setw(kPlanetSatellitesLength) << p.GetSatellitesNum()
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

void Planet::SetName(char* newName) {
    delete[] name_;
    name_ = new char[strlen(newName) + 1];
    strcpy(name_, newName);
}
void Planet::SetLife(bool newLife) {
    life_ = newLife;
}
void Planet::SetDiameter(int newDiameter) {
    diameter_ = newDiameter;
}
void Planet::SetSatellitesNum(int newSatellitesNum) {
    satellitesNum_ = newSatellitesNum;
}
void Planet::Set(char* name, int diameter, bool life, int satellitesNum) {
    SetName(name);
    SetDiameter(diameter);
    SetLife(life);
    SetSatellitesNum(satellitesNum);
}
char* Planet::GetName() {
    return name_;
}
bool Planet::GetLife() {
    return life_;
}
int Planet::GetDiameter() {
    return diameter_;
}
int Planet::GetSatellitesNum() {
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
    out << p.GetName() << "\t" << p.GetDiameter() << "\t" << p.GetLife() << "\t" << p.GetSatellitesNum();
    return out;
}
std::ifstream& operator>>(std::ifstream& in, Planet& p) {
    char* name = new char[kPlanetNameLength];
    int diameter, life, satellitesNum;
    in >> name >> diameter >> life >> satellitesNum >> std::ws;
    p.Set(name, diameter, life, satellitesNum);

    delete[] name;
    return in;
}

int Menu() {
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

int ReadDB(char* dbFileName, planet::Planet*& planets) {
    std::ifstream fin(dbFileName, std::ios::in);
    fin.seekg(0, std::ios::beg);
    if (!fin) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    int planetsAmount = 0;
    fin >> planetsAmount;

    Planet* newPlanets = new Planet[planetsAmount];
    delete[] planets;
    planets = newPlanets;
    for (int i = 0; i < planetsAmount; i++) {
        fin >> planets[i];
    }

    fin.close();
    return planetsAmount;
}

int WriteDB(char* dbFileName, planet::Planet* planets, int planetsAmount) {
    std::ofstream fout(dbFileName, std::ios::out);
    if (!fout) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    fout << static_cast<int>(planetsAmount) << std::endl;

    for (int i = 0; i < planetsAmount; i++)
        fout << planets[i] << std::endl;
    fout.close();

    return 0;
}

void SortDB(planet::Planet*& planets, int planetsAmount) {
    for (int i = 0; i < planetsAmount - 1; ++i) {
        for (int j = 0; j < planetsAmount - i - 1; ++j) {
            if (planets[j] < planets[j + 1]) {
                Planet* temp = new Planet;
                *temp = planets[j];
                planets[j] = planets[j + 1];
                planets[j + 1] = *temp;
            }
        }
    }
}

void AddObj(Planet*& planets, int& planetsAmount) {
    char* name = new char[kPlanetNameLength];
    int diameter;
    bool life;
    int satellitesNum;
    std::cout << "Enter planet data devided by spaces: name diameter life(1 - yes, 0 - no) satellitesNum" << std::endl;
    std::cin >> name >> diameter >> life >> satellitesNum;

    Planet* newPlanets = new Planet[planetsAmount + 1];

    for (int i = 0; i < planetsAmount; i++) {
        newPlanets[i] = planets[i];
    }

    newPlanets[planetsAmount].Set(name, diameter, life, satellitesNum);

    delete[] planets;
    planets = newPlanets;

    planetsAmount++;
    delete[] name;
}

void RemoveObj(Planet*& planets, int& planetsAmount) {
    if (planetsAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter planet ID to delete: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= planetsAmount) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    Planet* newPlanets = new Planet[planetsAmount - 1];
    int j = 0;

    for (int i = 0; i < planetsAmount; i++) {
        if (id == i) {
            continue;
        }
        newPlanets[j] = planets[i];
        j++;
    }

    delete[] planets;
    planets = newPlanets;
    planetsAmount--;
}

void EditObj(Planet*& planets, int planetsAmount) {
    if (planetsAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter planet ID to edit: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= planetsAmount) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    std::cout << "Enter planet data devided by spaces: name diameter life(1 - yes, 0 - no) satellitesNum" << std::endl;
    char* name = new char[kPlanetNameLength];
    int diameter;
    bool life;
    int satellitesNum;
    std::cin >> name >> diameter >> life >> satellitesNum;
    planets[id].Set(name, diameter, life, satellitesNum);
    delete[] name;
};

void PrintDB(planet::Planet* planets, int planetsAmount) {
    if (planetsAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Planets:" << std::endl;
    PrintPlanetsHeader();
    for (int i = 0; i < planetsAmount; i++) {
        PrintPlanets(planets[i], i);
    }
};

int main() {
    char fileName[] = "sunsys.txt";
    int planetsAmount = 0;
    Planet* planets = new Planet[planetsAmount];
    int ind;
    while (true) {
        switch (Menu()) {
            case 1:
                planetsAmount = ReadDB(fileName, planets);
                if (planetsAmount < 0)
                    return 1;
                std::cout << "Reading database completed" << std::endl;
                break;
            case 2:
                if (WriteDB(fileName, planets, planetsAmount) < 0) {
                    return 1;
                }
                std::cout << "Writing database completed" << std::endl;
                break;
            case 3:
                SortDB(planets, planetsAmount);
                std::cout << "Sorting database completed" << std::endl;
                break;
            case 4:
                AddObj(planets, planetsAmount);
                std::cout << "Adding object completed" << std::endl;
                break;
            case 5:
                RemoveObj(planets, planetsAmount);
                std::cout << "Deleting object completed" << std::endl;
                break;
            case 6:
                EditObj(planets, planetsAmount);
                std::cout << "Поиск завершен" << std::endl;
                break;
            case 7:
                PrintDB(planets, planetsAmount);
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
