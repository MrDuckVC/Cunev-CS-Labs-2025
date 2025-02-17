#ifndef PLANET_H
#define PLANET_H

#include <cstring>
#include <fstream>

namespace planet {
class Planet {
 public:
    Planet(int nameLength);
    ~Planet();
    char* GetName();
    void SetName(char* newName);
    int GetDiameter();
    void SetDiameter(int newDiameter);
    bool GetLife();
    void SetLife(bool newLife);
    int GetSatellitesNum();
    void SetSatellitesNum(int newSatellitesNum);
    void Set(char* name, int diameter, bool life, int satellitesNum);

    bool operator==(Planet&);
    bool operator<(Planet&);
    bool operator>(Planet&);
    Planet& operator=(const Planet& other);

 private:
    char* name_;
    int diameter_;
    bool life_;
    int satellitesNum_;
};

int main();
}  // namespace planet

#endif  // PLANET_H
