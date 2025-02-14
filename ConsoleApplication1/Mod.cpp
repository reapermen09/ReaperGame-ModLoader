#include "Mod.h"
#include <C:\cstuff\bass24\c\bass.h>
#include <chrono>
#include <thread>
#include "Defaults.h"
#pragma comment(lib, "C:\\cstuff\\bass24\\c\\x64\\bass.lib")

///Enable/Disable mod DO NOT set developer credits here
void Mod::CheckEnable(bool set) {
    modEnabled = set;
}

///Checks existance of the save file
void Mod::EnsureSaveDirectory(bool Notify) {
    DWORD ftyp = GetFileAttributesA(def.folderPath.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES || !(ftyp & FILE_ATTRIBUTE_DIRECTORY)) {
        std::cout << "Save directory doesn't exist. Creating: " << def.folderPath << std::endl;
        if (!CreateDirectoryA(def.folderPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            std::cerr << "Failed to create directory! Error Code: " << GetLastError() << std::endl;
        }
    }
}

///Special typing effect! delay_ms is how long it takes to write out
void Mod::Type(const std::string& text, int delay_ms) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << std::endl;
}

///Checks file existance
bool Mod::FileExists(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") == 0) {
        fclose(file);
        return true;
    }
    return false;
}

///Plays music if playstop is true it will play, if playstop is false it will stop playing
///The usual path is "C:\\ReaperGame\\Assets\\"
void Mod::Music(const char* mp3File, bool playstop) {
    if (!FileExists(mp3File)) {
        return;
    }

    if (playstop) {
        if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
            return;
        }

        HSTREAM stream = BASS_StreamCreateFile(FALSE, mp3File, 0, 0, BASS_STREAM_AUTOFREE);
        if (!stream) {
            BASS_Free();
            return;
        }

        if (!BASS_ChannelPlay(stream, FALSE)) {
            BASS_Free();
            return;
        }
    }
    else {
        HSTREAM stream = BASS_StreamCreateFile(FALSE, mp3File, 0, 0, BASS_STREAM_AUTOFREE);
        if (stream) {
            BASS_ChannelStop(stream);
            BASS_Free();
        }
    }
}

///Loads game data
void Mod::HandleLoad() {
    std::ifstream loadFile(def.saveFilePath);
    if (loadFile.is_open()) {
        std::string line;
        if (getline(loadFile, line)) def.money = std::stoi(line);
        if (getline(loadFile, line)) def.points = std::stoi(line);
        if (getline(loadFile, line)) def.taxamount = std::stoi(line);
        if (getline(loadFile, line)) def.secretonefound = std::stoi(line);
        if (getline(loadFile, line)) def.secrettwofound = std::stoi(line);
        if (getline(loadFile, line)) def.csamount = std::stoi(line);
        if (getline(loadFile, line)) def.inprison = std::stoi(line);

        std::cout << "Game loaded! (Money: " << def.money << "), (Points: " << def.points << "), (Taxes needed to pay: " << def.taxamount << "), (Child support you owe: " << def.csamount << ")\n";
    }
    else {
        std::cout << "No saved game found.\n";
    }
}

///Saves game data
void Mod::HandleSave() {
    std::ofstream saveFile(def.saveFilePath, std::ios::out | std::ios::trunc);
    if (saveFile.is_open()) {
        saveFile << def.money << "\n" << def.points << "\n" << def.taxamount << "\n" << def.secretonefound << "\n" << def.secrettwofound << "\n" << def.csamount << "\n" << def.inprison << std::endl;
    }
    else {
        std::cout << "Error saving game.\n";
    }
}

///Makes changes to normal achievements (DO NOT ADD ACHIEVEMENTS HERE) However, you can make mod achievement checks here
void Mod::ModifyAchievements() {}

///You can change points, taxes, money, etc
void Mod::ModifyAttributes() {}

///Load mod
void Mod::InitializeMod() {}

///Save Mod stuff (used for custom)
void Mod::ModSave() {}

///Load Mod stuff (used for custom)
void Mod::ModLoad() {}

///Add commands (always include: cout << "\033[A\33[2K\r";)
void Mod::CommandList() {}

///Adds bosses
void Mod::Bosses() {}

///Save Mod Achievements (used for custom)
void Mod::ModAchievementSave() {}

///Load Mod Achievements (used for custom)
void Mod::ModAchievementLoad() {}

///Display Mod Achievements (used for custom)
void Mod::ModAchievementDisplay() {}

///Load something
void Mod::Load() {}

///See mod description (does not need a mod enable check)
void Mod::ModDescription() {}

///Checks the execution of a command
bool Mod::CommandUsed() { return false; }

/// Set your developer name
std::string Mod::Developer(std::string developer) { return developer; }