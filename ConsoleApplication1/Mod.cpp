#include "Mod.h"
#include <C:\cstuff\bass24\c\bass.h>
#include <chrono>
#include <thread>
#include "Defaults.h"
#pragma comment(lib, "C:\\cstuff\\bass24\\c\\x64\\bass.lib")

///Enable/Disable mod
void Mod::CheckEnable(bool set) {
    modEnabled = set;
}

///Checks existance of the save file
void Mod::EnsureSaveDirectory(bool Notify) {
    DWORD ftyp = GetFileAttributesA(def.folderPath.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES || !(ftyp & FILE_ATTRIBUTE_DIRECTORY)) {
        cout << "Save directory doesn't exist. Creating: " << def.folderPath << endl;
        if (!CreateDirectoryA(def.folderPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            cerr << "Failed to create directory! Error Code: " << GetLastError() << endl;
        }
    }
}

///Special typing effect! delay_ms is how long it takes to write out
void Mod::Type(const string& text, int delay_ms) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    cout << endl;
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
    ifstream loadFile(def.saveFilePath);
    if (loadFile.is_open()) {
        string line;
        if (getline(loadFile, line)) def.money = stoi(line);
        if (getline(loadFile, line)) def.points = stoi(line);
        if (getline(loadFile, line)) def.taxamount = stoi(line);
        if (getline(loadFile, line)) def.secretonefound = stoi(line);
        if (getline(loadFile, line)) def.secrettwofound = stoi(line);
        if (getline(loadFile, line)) def.csamount = stoi(line);
        if (getline(loadFile, line)) def.inprison = stoi(line);

        cout << "Game loaded! (Money: " << def.money << "), (Points: " << def.points << "), (Taxes needed to pay: " << def.taxamount << "), (Child support you owe: " << def.csamount << ")\n";
    }
    else {
        cout << "No saved game found.\n";
    }
}

///Saves game data
void Mod::HandleSave() {
    ofstream saveFile(def.saveFilePath, ios::out | ios::trunc);
    if (saveFile.is_open()) {
        saveFile << def.money << "\n" << def.points << "\n" << def.taxamount << "\n" << def.secretonefound << "\n" << def.secrettwofound << "\n" << def.csamount << "\n" << def.inprison << endl;
    }
    else {
        cout << "Error saving game.\n";
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

///Add commands
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