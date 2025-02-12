#ifndef PLANET_H
#define PLANET_H

#include <cstring>
#include <fstream>

namespace planet {
class Planet {
public:
    Planet(int nameLength = 20);
    ~Planet();

    void edit();

    char *getName();
    void setName(char *newName);
    int getDiameter();
    void setDiameter(int newDiameter);
    bool getLife();
    void setLife(bool newLife);
    int getSatellitesNum();
    void setSatellitesNum(int newSatellitesNum);

    const bool &operator==(const Planet &p);
    const bool &operator<(const Planet &p);
    const bool &operator>(const Planet &p);
    // std::ofstream &operator<<(std::ofstream &out, const Planet &p);
    // Planet &operator>>(const Planet &p);

private:
    char *name_;
    int diameter_;
    bool life_;
    int satellitesNum_;
};
}

#endif // PLANET_H
