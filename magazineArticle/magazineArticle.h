#ifndef MAGAZINEARTICLE_H
#define MAGAZINEARTICLE_H

#include <cstring>
#include <fstream>

namespace magazineArticle {
class MagazineArticle {
 public:
    MagazineArticle(int nameLength);
    ~MagazineArticle();
    char* GetName();
    void SetName(char* newName);
    int GetWordAmount();
    void SetWordAmount(int newWordAmount);
    bool GetIsPublished();
    void SetIsPublished(bool newIsPublished);
    int GetPageAmount();
    void SetPageAmount(int newPageAmount);
    void Set(char* name, int diameter, bool life, int pageAmount);

    bool operator==(MagazineArticle&);
    bool operator<(MagazineArticle&);
    bool operator>(MagazineArticle&);
    MagazineArticle& operator=(const MagazineArticle& other);

 private:
    char* name_;
    int wordAmount_;
    bool isPublished_;
    int pageAmount_;
};

int main();
}  // namespace magazineArticle

#endif  // MAGAZINEARTICLE_H
