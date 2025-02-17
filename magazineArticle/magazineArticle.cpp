#include "magazineArticle.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kMagazineArticleIDLength = 2;
const int kMagazineArticleNameLength = 15;
const int kMagazineArticleWordAmountLength = 15;
const int kMagazineArticleIsPublishedLength = 15;
const int kMagazineArticlePageAmountLength = 15;
const char kUnableToOpenFile[] = "Unable to open file ";
const char kEmptyDatabase[] = "Database is empty";

void PrintMagazineArticleHeader() {
    std::cout << std::setw(kMagazineArticleIDLength) << "ID" << std::setw(kMagazineArticleNameLength) << "Name"
              << std::setw(kMagazineArticleWordAmountLength) << "Word amount" << std::setw(kMagazineArticleIsPublishedLength) << "Is published"
              << std::setw(kMagazineArticlePageAmountLength) << "Page amount" << std::endl;
}
void PrintMagazineArticle(magazineArticle::MagazineArticle& p, int id) {
    std::cout << std::setw(kMagazineArticleIDLength) << id << std::setw(kMagazineArticleNameLength) << p.GetName()
              << std::setw(kMagazineArticleWordAmountLength) << p.GetWordAmount() << std::setw(kMagazineArticleIsPublishedLength)
              << p.GetIsPublished() << std::setw(kMagazineArticlePageAmountLength) << p.GetPageAmount() << std::endl;
};
}  // namespace

namespace magazineArticle {
MagazineArticle::MagazineArticle(int nameLength = kMagazineArticleNameLength) {
    name_ = new char[nameLength];
    name_[0] = '\0';
}
MagazineArticle::~MagazineArticle() {
    delete[] name_;
}

void MagazineArticle::SetName(char* newName) {
    delete[] name_;
    name_ = new char[strlen(newName) + 1];
    strcpy(name_, newName);
}
void MagazineArticle::SetIsPublished(bool newIsPublished) {
    isPublished_ = newIsPublished;
}
void MagazineArticle::SetWordAmount(int newWordAmount) {
    wordAmount_ = newWordAmount;
}
void MagazineArticle::SetPageAmount(int newPageAmount) {
    pageAmount_ = newPageAmount;
}
void MagazineArticle::Set(char* name, int wordAmount, bool isPublished, int pageAmount) {
    SetName(name);
    SetWordAmount(wordAmount);
    SetIsPublished(isPublished);
    SetPageAmount(pageAmount);
}
char* MagazineArticle::GetName() {
    return name_;
}
bool MagazineArticle::GetIsPublished() {
    return isPublished_;
}
int MagazineArticle::GetWordAmount() {
    return wordAmount_;
}
int MagazineArticle::GetPageAmount() {
    return pageAmount_;
}

bool MagazineArticle::operator==(MagazineArticle& p) {
    return (wordAmount_ == p.wordAmount_);
}
bool MagazineArticle::operator<(MagazineArticle& p) {
    return (wordAmount_ < p.wordAmount_);
}
bool MagazineArticle::operator>(MagazineArticle& p) {
    return (wordAmount_ > p.wordAmount_);
}
MagazineArticle& MagazineArticle::operator=(const MagazineArticle& other) {
    if (this != &other) {
        wordAmount_ = other.wordAmount_;
        isPublished_ = other.isPublished_;
        pageAmount_ = other.pageAmount_;

        delete[] name_;
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
    }
    return *this;
}
std::ofstream& operator<<(std::ofstream& out, MagazineArticle& p) {
    out << p.GetName() << "\t" << p.GetWordAmount() << "\t" << p.GetIsPublished() << "\t" << p.GetPageAmount();
    return out;
}
std::ifstream& operator>>(std::ifstream& in, MagazineArticle& p) {
    char* name = new char[kMagazineArticleNameLength];
    int wordAmount, isPublished, pageAmount;
    in >> name >> wordAmount >> isPublished >> pageAmount >> std::ws;
    p.Set(name, wordAmount, isPublished, pageAmount);

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

int ReadDB(char* dbFileName, magazineArticle::MagazineArticle*& magazineArticles) {
    std::ifstream fin(dbFileName, std::ios::in);
    fin.seekg(0, std::ios::beg);
    if (!fin) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    int magazineArticlesAmount = 0;
    fin >> magazineArticlesAmount;

    MagazineArticle* newMagazineArticles = new MagazineArticle[magazineArticlesAmount];
    delete[] magazineArticles;
    magazineArticles = newMagazineArticles;
    for (int i = 0; i < magazineArticlesAmount; i++) {
        fin >> magazineArticles[i];
    }

    fin.close();
    return magazineArticlesAmount;
}

int WriteDB(char* dbFileName, magazineArticle::MagazineArticle* magazineArticles, int magazineArticlesAmount) {
    std::ofstream fout(dbFileName, std::ios::out);
    if (!fout) {
        std::cout << kUnableToOpenFile << dbFileName << std::endl;
        return -1;
    }

    fout << static_cast<int>(magazineArticlesAmount) << std::endl;

    for (int i = 0; i < magazineArticlesAmount; i++)
        fout << magazineArticles[i] << std::endl;
    fout.close();

    return 0;
}

void SortDB(magazineArticle::MagazineArticle*& magazineArticles, int magazineArticlesAmount) {
    for (int i = 0; i < magazineArticlesAmount - 1; ++i) {
        for (int j = 0; j < magazineArticlesAmount - i - 1; ++j) {
            if (magazineArticles[j] < magazineArticles[j + 1]) {
                MagazineArticle* temp = new MagazineArticle;
                *temp = magazineArticles[j];
                magazineArticles[j] = magazineArticles[j + 1];
                magazineArticles[j + 1] = *temp;
            }
        }
    }
}

void AddObj(MagazineArticle*& magazineArticles, int& magazineArticlesAmount) {
    char* name = new char[kMagazineArticleNameLength];
    int wordAmount;
    bool isPublished;
    int pageAmount;
    std::cout << "Enter magazine article data devided by spaces: name wordAmount isPublished(1 - yes, 0 - no) pageAmount" << std::endl;
    std::cin >> name >> wordAmount >> isPublished >> pageAmount;

    MagazineArticle* newMagazineArticles = new MagazineArticle[magazineArticlesAmount + 1];

    for (int i = 0; i < magazineArticlesAmount; i++) {
        newMagazineArticles[i] = magazineArticles[i];
    }

    newMagazineArticles[magazineArticlesAmount].Set(name, wordAmount, isPublished, pageAmount);

    delete[] magazineArticles;
    magazineArticles = newMagazineArticles;

    magazineArticlesAmount++;
    delete[] name;
}

void RemoveObj(MagazineArticle*& magazineArticles, int& magazineArticlesAmount) {
    if (magazineArticlesAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter magazine article ID to delete: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= magazineArticlesAmount) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    MagazineArticle* newMagazineArticles = new MagazineArticle[magazineArticlesAmount - 1];
    int j = 0;

    for (int i = 0; i < magazineArticlesAmount; i++) {
        if (id == i) {
            continue;
        }
        newMagazineArticles[j] = magazineArticles[i];
        j++;
    }

    delete[] magazineArticles;
    magazineArticles = newMagazineArticles;
    magazineArticlesAmount--;
}

void EditObj(MagazineArticle*& magazineArticles, int magazineArticlesAmount) {
    if (magazineArticlesAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Enter magazine article ID to edit: ";
    int id = 0;
    std::cin >> id;

    if (id < 0 || id >= magazineArticlesAmount) {
        std::cout << "Object " << id << " not found" << std::endl;
        return;
    }

    std::cout << "Enter magazine article data devided by spaces: name wordAmount isPublished(1 - yes, 0 - no) pageAmount" << std::endl;
    char* name = new char[kMagazineArticleNameLength];
    int wordAmount;
    bool isPublished;
    int pageAmount;
    std::cin >> name >> wordAmount >> isPublished >> pageAmount;
    magazineArticles[id].Set(name, wordAmount, isPublished, pageAmount);
    delete[] name;
};

void PrintDB(magazineArticle::MagazineArticle* magazineArticles, int magazineArticlesAmount) {
    if (magazineArticlesAmount == 0) {
        std::cout << kEmptyDatabase << std::endl;
        return;
    }

    std::cout << "Magazine article:" << std::endl;
    PrintMagazineArticleHeader();
    for (int i = 0; i < magazineArticlesAmount; i++) {
        PrintMagazineArticle(magazineArticles[i], i);
    }
};

int main() {
    char fileName[] = "library.txt";
    int magazineArticlesAmount = 0;
    MagazineArticle* magazineArticles = new MagazineArticle[magazineArticlesAmount];
    int ind;
    while (true) {
        switch (Menu()) {
            case 1:
                magazineArticlesAmount = ReadDB(fileName, magazineArticles);
                if (magazineArticlesAmount < 0)
                    return 1;
                std::cout << "Reading database completed" << std::endl;
                break;
            case 2:
                if (WriteDB(fileName, magazineArticles, magazineArticlesAmount) < 0) {
                    return 1;
                }
                std::cout << "Writing database completed" << std::endl;
                break;
            case 3:
                SortDB(magazineArticles, magazineArticlesAmount);
                std::cout << "Sorting database completed" << std::endl;
                break;
            case 4:
                AddObj(magazineArticles, magazineArticlesAmount);
                std::cout << "Adding object completed" << std::endl;
                break;
            case 5:
                RemoveObj(magazineArticles, magazineArticlesAmount);
                std::cout << "Deleting object completed" << std::endl;
                break;
            case 6:
                EditObj(magazineArticles, magazineArticlesAmount);
                std::cout << "Поиск завершен" << std::endl;
                break;
            case 7:
                PrintDB(magazineArticles, magazineArticlesAmount);
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
}  // namespace magazineArticle
