#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <string>

class Defaults {
public:
    long taxamount = 0;
    long csamount = 0;
    short fontSize = 3;
    bool inprison = false;
    bool secretonefound = false;
    bool secrettwofound = false;
    bool beatRati = false;
    bool begging = false;
    long money = 10;
    long points = 0;
    long csRqToGoToPrison = 15;
    std::string command;
    const std::string developerName = "Reaper";
    const std::string developerExName = "Reaperman";
    std::string folderPath = "C:\\ReaperGame\\SaveData";
    std::string saveFilePath = folderPath + "\\game_save.txt";
    std::string settingsFilePath = folderPath + "\\settings.txt";
    std::string achievementsFilePath = folderPath + "\\achievements.txt";
    const std::string reaperGameEdition = "You are using C++ RgModLoader Edition";

    bool money100 = false;
    bool money1000 = false;
    bool money10000 = false;
    bool money100000 = false;
    bool money1000000 = false;
    bool firstTransaction = false;
    bool foundreaper = false;
    bool insultreaper = false;
    bool begreaper = false;
    bool wentToPrison = false;
    bool escapedPrison = false;
    bool mratiBeat = false;
    bool points100 = false;
    bool points1000 = false;
    bool points10000 = false;
    bool points100000 = false;
    bool points1000000 = false;

    bool donotcheck = false;
    bool donotcheck2 = false;

    bool modSet[];
};
extern Defaults def;

#endif