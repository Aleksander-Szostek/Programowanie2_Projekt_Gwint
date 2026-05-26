#ifndef KEYWORD_H
#define KEYWORD_H
#include <vector>

class keyword
{
public:
    keyword();

    enum class efektyKart {
        brak = 0,
        summon = 1,
        braterstwo = 2,
        szpieg = 3,
        horn = 4,
        kill = 5,
        pogoda = 6
    };

    ~keyword();

protected:
    std::vector<int> cele;

//signals:
//    void zabijsie();
};

#endif // KEYWORD_H
