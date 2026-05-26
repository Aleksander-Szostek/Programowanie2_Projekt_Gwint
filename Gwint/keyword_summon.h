#ifndef KEYWORD_SUMMON_H
#define KEYWORD_SUMMON_H

#include "keyword.h"

class keyword_summon : public keyword
{
public:
    keyword_summon();

    void onPlayEffekt() override;

};

#endif // KEYWORD_SUMMON_H
