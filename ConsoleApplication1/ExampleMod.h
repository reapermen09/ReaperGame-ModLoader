#ifndef EXAMPLEMOD_H
#define EXAMPLEMOD_H

#include "Mod.h"

class ExampleMod : public Mod {
public:
    ExampleMod();
    void ModifyAttributes() override;
    void InitializeMod() override;
    void CommandList() override;
    void Bosses() override;
    void ModAchievementSave() override;
    void ModAchievementLoad() override;
    void ModifyAchievements() override;
    void ModAchievementDisplay() override;
    void ModDescription() override;
};

#endif