#ifndef BETTERMATHGAMESMOD_H
#define BETTERMATHGAMESMOD_H

#include "Mod.h"

class BetterMathGamesMod : public Mod {
public:
    BetterMathGamesMod();
    void ModifyAttributes() override;
    void InitializeMod() override;
    void CommandList() override;
    void Load() override;
};

#endif