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
    char* getName();
    void setName(char* newName);
    int getDiameter();
    void setDiameter(int newDiameter);
    bool getLife();
    void setLife(bool newLife);
    int getSatellitesNum();
    void setSatellitesNum(int newSatellitesNum);

    static int getTotal();
    int getID();

    bool operator==(Planet&);
    bool operator<(Planet&);
    bool operator>(Planet&);
    Planet& operator=(const Planet& other);

private:
    static int total;
    int id_;
    char* name_;
    int diameter_;
    bool life_;
    int satellitesNum_;
};

int main();
}  // namespace planet

#endif  // PLANET_H
