#ifndef MOD_H
#define MOD_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;

class Mod {
protected:
    bool modEnabled = true;

public:
    virtual ~Mod() {}

    ///Enable/Disable mod
    virtual void CheckEnable(bool set);
    ///Checks existence of the save file
    virtual void EnsureSaveDirectory(bool notify);
    ///Loads game data
    virtual void HandleLoad();
    ///Saves game data
    virtual void HandleSave();
    ///Makes changes to normal achievements (DO NOT ADD ACHIEVEMENTS HERE) However, you can make mod achievement checks here (also not made for loading)
    virtual void ModifyAchievements();
    ///You can change points, taxes, money, etc
    virtual void ModifyAttributes();
    ///Load mod
    virtual void InitializeMod();
    ///Save Mod stuff (used for custom)
    virtual void ModSave();
    ///Load Mod stuff (used for custom)
    virtual void ModLoad();
    ///Display Mod Achievements (used for custom)
    virtual void ModAchievementDisplay();
    ///Save Mod Achievements (used for custom)
    virtual void ModAchievementSave();
    ///Load Mod Achievements (used for custom)
    virtual void ModAchievementLoad();
    ///Add commands (always include: cout << "\033[A\33[2K\r";)
    virtual void CommandList();
    ///Adds bosses
    virtual void Bosses();
    ///Checks file existence
    virtual bool FileExists(const char* filename);
    ///Plays music if playstop is true it will play, if playstop is false it will stop playing
    ///The usual path is "C:\\ReaperGame\\Assets\\"
    virtual void Music(const char* mp3File, bool playstop);
    ///Special typing effect! delay_ms is how long it takes to write out
    virtual void Type(const string& text, int delay_ms);
    ///Load Something
    virtual void Load();
    ///See mod description (does not need a mod enable check)
    virtual void ModDescription();
};
#endif