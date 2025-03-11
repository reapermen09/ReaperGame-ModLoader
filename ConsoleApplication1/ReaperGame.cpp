#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <C:\cstuff\bass24\c\bass.h>
#include "ExampleMod.h"
#include "BetterMathGamesMod.h"
#include "Defaults.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "C:\\cstuff\\bass24\\c\\x64\\bass.lib") //reaper leak fr (also lazy tbh)

#undef max

ExampleMod reaperExampleMod;
BetterMathGamesMod betterMathGamesMod;

void AssetsFolder() {
    const char* folderPath = "C:\\ReaperGame\\Assets";

    DWORD fileAttr = GetFileAttributesA(folderPath);

    if (fileAttr == INVALID_FILE_ATTRIBUTES || !(fileAttr & FILE_ATTRIBUTE_DIRECTORY)) CreateDirectoryA(folderPath, NULL);
}

bool FileExists(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") == 0) {
        fclose(file);
        return true;
    }
    return false;
}

void MP3Silently(const char* mp3File, bool playstop) {
    if (!FileExists(mp3File)) return;

    static bool isInitialized = false;
    if (playstop && !isInitialized) 
    {
        if (!BASS_Init(-1, 44100, 0, 0, NULL)) return;
        isInitialized = true;
    }

    HSTREAM stream = BASS_StreamCreateFile(FALSE, mp3File, 0, 0, BASS_STREAM_AUTOFREE);
    if (!stream) return;

    if (playstop) 
    {
        if (!BASS_ChannelPlay(stream, FALSE)) BASS_Free(); return;
    }
    else BASS_ChannelStop(stream);
   
    BASS_Free();
}


void SetFontSize(int size) {
    if (size < 1 || size > 3) {
        std::cout << "Invalid font size. Setting to default (3).\n";
        size = 3;
    }

    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    constexpr struct { SHORT x, y; } fontSizes[] = {
        {8, 12}, {12, 18}, {16, 24}
    };

    cfi.dwFontSize.X = fontSizes[size - 1].x;
    cfi.dwFontSize.Y = fontSizes[size - 1].y;

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


int getValidInt() {
    int value;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid integer: ";
    }
    return value;
}

int getValidLong() {
    long value;
    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid integer: ";
    }
    return value;
}

void SaveAchievements() {
    std::ofstream achievementsFile(def.achievementsFilePath);
    if (achievementsFile.is_open()) {
        bool* achievements[] = {
            &def.money100, &def.money1000, &def.money10000, &def.money100000, &def.money1000000,
            &def.firstTransaction,
            &def.foundreaper, &def.insultreaper, &def.begreaper,
            &def.points100, &def.points1000, &def.points10000, &def.points100000, &def.points1000000,
            &def.wentToPrison, &def.escapedPrison,
            &def.donotcheck, &def.donotcheck2,
            &def.beatRati
        };

        for (bool* achievement : achievements) achievementsFile << *achievement << "\n";
        achievementsFile.close();
    }
    else std::cout << "Error: Unable to save achievements.\n";
    reaperExampleMod.ModAchievementSave();
}
void LoadAchievements() {
    std::ifstream achievementsFile(def.achievementsFilePath);
    if (achievementsFile.is_open()) {
        bool* achievements[] = {
            &def.money100, &def.money1000, &def.money10000, &def.money100000, &def.money1000000,
            &def.firstTransaction, &def.foundreaper, &def.insultreaper, &def.begreaper,
            &def.points100, &def.points1000, &def.points10000, &def.points100000, &def.points1000000,
            &def.wentToPrison, &def.escapedPrison,
            &def.donotcheck, &def.donotcheck2,
            &def.beatRati
        };

        for (bool* achievement : achievements) achievementsFile >> *achievement;
        achievementsFile.close();
    }
    else std::cout << "No achievements file found... Starting fresh!\n";
    reaperExampleMod.ModAchievementLoad();
}


void DisplayAchievements() {
    std::cout << "Achievements:\n";

    struct Achievement {
        const bool* unlocked;
        const char* message;
    };

    Achievement achievements[] = {
        { &def.money100, "Novice: 100+ money" },
        { &def.money1000, "Grinder Type Guy: 1000+ money" },
        { &def.money10000, "Commander: 10000+ money" },
        { &def.money100000, "Destroyer Type Guy: 100000+ money" },
        { &def.money1000000, "Rich Sigma: 1000000+ money" },

        { &def.firstTransaction, "First Transaction: Completed your first transaction" },
        { &def.foundreaper, "Finding the Reaper: You found Reaper who gave you 100 money" },
        { &def.insultreaper, "Insulting the Reaper: You insulted Reaper, how dare you" },
        { &def.begreaper, "Begging: Stop begging Reaper for money, please" },

        { &def.points100, "Point Grinder: 100+ points" },
        { &def.points1000, "Pointer: 1000+ points" },
        { &def.points10000, "Amazing Player: 10000+ points" },
        { &def.points100000, "Super Player: 100000+ points" },
        { &def.points1000000, "Sigma Player: 1000000+ points" },

        { &def.escapedPrison, "Criminal Crime: You escaped prison" },
        { &def.wentToPrison, "Law Breaker: You went to prison" },

        { &def.beatRati, "Rati's Defeat: You defeated Rati" }
    };

    for (const auto& achievement : achievements) {
        if (*achievement.unlocked) std::cout << achievement.message << "\n";
    }

    reaperExampleMod.ModAchievementDisplay();
}

void PlayAchievementSound() {
    PlaySound(TEXT("C:\\ReaperGame\\Assets\\achievement.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void PlayActionSound() {
    PlaySound(TEXT("C:\\ReaperGame\\Assets\\action.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void AchievementReachedCheck(int money, int points) {
    struct Achievement {
        int threshold;
        bool& unlocked;
        const char* message;
    };

    Achievement moneyAchievements[] = {
        {100, def.money100, "You got the Novice achievement! (100+ money)\n"},
        {1000, def.money1000, "You got the Grinder Type Guy achievement! (1000+ money)\n"},
        {10000, def.money10000, "You got the Commander achievement! (10000+ money)\n"},
        {100000, def.money100000, "You got the Destroyer Type Guy achievement! (100000+ money)\n"},
        {1000000, def.money1000000, "You got the Rich Sigma achievement! (1000000+ money)\n"}
    };

    Achievement pointsAchievements[] = {
        {1, def.firstTransaction, "You got the First Transaction achievement! (First transaction)\n"},
        {100, def.points100, "You got the Point Grinder achievement! (100+ points)\n"},
        {1000, def.points1000, "You got the Pointer achievement! (1000+ points)\n"},
        {10000, def.points10000, "You got the Amazing Player achievement! (10000+ points)\n"},
        {100000, def.points100000, "You got the Super Player achievement! (100000+ points)\n"},
        {1000000, def.points1000000, "You got the Sigma Player achievement! (1000000+ points)\n"}
    };

    for (const auto& achievement : moneyAchievements) {
        if (money >= achievement.threshold && !achievement.unlocked) {
            PlayAchievementSound();
            std::cout << achievement.message;
            achievement.unlocked = true;
        }
    }

    for (const auto& achievement : pointsAchievements) {
        if (points >= achievement.threshold && !achievement.unlocked) {
            PlayAchievementSound();
            std::cout << achievement.message;
            achievement.unlocked = true;
        }
    }

    struct OtherAcheivements {
        bool condition;
        bool& unlocked;
        const char* message;
    };

    OtherAcheivements otherAchievements[] = {
        {def.secretonefound, def.foundreaper, "Finding the Reaper (You found Reaper who gave you 100 money)\n"},
        {def.secrettwofound > 0, def.insultreaper, "Insulting the Reaper (You insulted Reaper, how dare you)\n"},
        {def.begging, def.begreaper, "You got the Begging achievement! (Stop begging Reaper for money, please)\n"},
        {def.mratiBeat, def.beatRati, "You got the Boss Defeater achievement! (You beat Rati)\n"},
        {def.wentToPrison && !def.donotcheck, def.donotcheck, "You got the Law Breaker achievement! (You went to prison)\n"},
        {def.escapedPrison && !def.donotcheck2, def.donotcheck2, "You got the Criminal Crime achievement! (You escaped prison)\n"}
    };

    for (const auto& achievement : otherAchievements) {
        if (achievement.condition && !achievement.unlocked) {
            PlayAchievementSound();
            std::cout << achievement.message;
            achievement.unlocked = true;
        }
    }

    SaveAchievements();
}

void DisplayCommands() {
    std::vector<std::string> commands = {
        "/help - Show this help message",
        "/achievements - Shows your gained achievements",
        "/transaction - Convert your money into points (Includes tax)",
        "/playagame - Play a math game (Includes tax)",
        "/money - Show your money balance",
        "/points - Show your points",
        "/save - Save your game progress",
        "/load - Load your game progress",
        "/support - Check support",
        "/settings - Change game settings",
        "/gamble - Gamble your money for a chance to win (Includes tax)",
        "/taxes - Pay your taxes",
        "/childsupport - Pay your child support",
        "/exit - Exit game",
        "/clear - Clears all text (keeps commands)",
        "/checkdesc[ModNameHere] - You can see the real mod name in the ModLoader menu in ModList (has to be enabled)"
    };

    std::cout << "\nAvailable commands:\n";

    for (const auto& command : commands) {
        std::cout << command << "\n";
    }
    std::cout << std::endl;

    reaperExampleMod.CommandList();
    betterMathGamesMod.CommandList();
}

void LoadSettings(std::string& autoload, std::string& autosave, const std::string& settingsFilePath) {
    std::string fontsize = "";
    std::ifstream settingsFile(settingsFilePath);
    if (settingsFile.is_open()) {
        getline(settingsFile, autoload);
        getline(settingsFile, autosave);
        getline(settingsFile, fontsize);

        try {
            def.fontSize = std::stoi(fontsize);
        }
        catch (const std::invalid_argument& e) {
            def.fontSize = 3;
        }
    }
    else {
        autoload = "off";
        autosave = "off";
        def.fontSize = 3;
        std::cout << "Settings file could not be loaded. Using default settings.\n";
    }
}
void SaveSettings(const std::string& autoload, const std::string& autosave, const std::string& settingsFilePath) {
    std::ofstream settingsFile(settingsFilePath, std::ios::out | std::ios::trunc);
    if (settingsFile.is_open()) {
        settingsFile << autoload << "\n";
        settingsFile << autosave << "\n";
        settingsFile << def.fontSize << "\n";
    }
    else {
        std::cout << "Error saving settings.\n";
    }
}

void ResetSettings(const std::string& settingsFilePath) {
    std::ofstream settingsFile(settingsFilePath, std::ios::out | std::ios::trunc);
    if (settingsFile.is_open()) {
        settingsFile << "off\n";
        settingsFile << "off\n";
        settingsFile << "3\n";
        std::cout << "Settings reset to default values.\n";
    }
    else std::cout << "Error resetting settings.\n";
}

void Settings(std::string& autoload, std::string& autosave, const std::string& settingsFilePath) {
    while (true) {
        std::cout << "Settings:\n";
        std::cout << "1 = Autoload save data: " << autoload << "\n";
        std::cout << "2 = Autosave save data: " << autosave << "\n";
        std::cout << "3 = Change Font Size (Current size: " << def.fontSize << ")\n";
        std::cout << "4 = Reset settings\n";
        std::cout << "5 = Exit settings\n";
        std::cout << "Enter your choice (number ex: 1, 2, 3, 4, 5): ";

        int choice = getValidInt();
        if (choice == 1) {
            std::cout << "Toggle Autoload save data (on/off): ";
            std::cin >> autoload;
            PlayActionSound();
        }
        else if (choice == 2) {
            std::cout << "Toggle Autosave save data (on/off): ";
            std::cin >> autosave;
            PlayActionSound();
        }
        else if (choice == 3) {
            std::cout << "Enter new font size (1 is for small, 2 is for medium, and 3 is for large): ";
            def.fontSize = getValidInt();
            SetFontSize(def.fontSize);
            PlayActionSound();
        }
        else if (choice == 4) {
            ResetSettings(settingsFilePath);
            autoload = "off";
            autosave = "off";
        }
        else if (choice == 5) {
            SaveSettings(autoload, autosave, settingsFilePath);
            PlayActionSound();
            break;
        }
        else std::cout << "Invalid choice. Please try again.\n";
    }
}

void HandleSupport() {
    std::cout << "Game by Reapermen, contact zxteam27@gmail.com for any support or suggestions...\n";
}

void HandleTransaction(long& money, long& points) {
    while (true) {
        std::cout << "How much money would you like to convert into points? (Current money: " << money << "): ";
        long convertAmount = getValidLong();

        if (convertAmount <= 0) std::cout << "Invalid input. Please enter a positive number.\n";
        else if (convertAmount > money) {
            std::cout << "You do not have enough money. You only have " << money << ".\n";
            std::cout << "Would you like to try again (y/n)? ";
            std::string response;
            std::cin >> response;
            if (response != "y" || response != "Y") break;
        }
        else {
            points += convertAmount;
            money -= convertAmount;
            std::cout << "Your points increased by " << convertAmount << ", and your money decreased by " << convertAmount << ".\n";
            double tax = convertAmount / 6;
            tax = ceil(tax);
            def.taxamount += static_cast<int>(tax);
            PlayActionSound();
            AchievementReachedCheck(money, points);
            break;
        }
    }
}

void HandlePlayAGame(long& money, long& points) {


    while (true) {
        int randomNum1 = rand() % 501 + 1;
        int randomNum2 = rand() % 501 + 1;
        int correctAnswer;
        std::string operation;

        std::cout << "Choose operation (add/subtract). Adding gives 20 points/money, subtracting gives 30 points/money: ";
        std::cin >> operation;

        if (operation == "add") {
            std::cout << "What is " << randomNum1 << " + " << randomNum2 << "? ";
            correctAnswer = randomNum1 + randomNum2;
        }
        else if (operation == "subtract") {
            std::cout << "What is " << randomNum1 << " - " << randomNum2 << "? ";
            correctAnswer = randomNum1 - randomNum2;
        }
        else {
            std::cout << "Invalid operation. Please choose 'add' or 'subtract'.\n";
            continue;
        }

        int playerAnswer = getValidInt();
        if (playerAnswer == correctAnswer) {
            int reward = (operation == "add") ? 20 : 30;
            money += reward;
            points += reward;
            std::cout << "Correct! Your money and points increased by " << reward << ".\n";
            double tax = reward / 8;
            tax = ceil(tax);
            def.taxamount += static_cast<int>(tax);
            def.csamount += 1;
            PlayActionSound();
            AchievementReachedCheck(money, points);
            break;
        }
        else {
            PlayActionSound();
            std::cout << "Wrong answer! Would you like to try again (y/n)? ";
            std::string retry;
            std::cin >> retry;
            if (retry != "y" || retry != "Y") break;
        }
    }
}

void HandleSave(const std::string& saveFilePath, long money, long points, bool notify) {
    std::ofstream saveFile(saveFilePath, std::ios::out | std::ios::trunc);
    if (saveFile.is_open()) {
        saveFile << money << "\n" << points << "\n" << def.taxamount << "\n" << def.secretonefound << "\n" << def.secrettwofound << "\n" << def.csamount << "\n" << def.inprison << std::endl;
        if (notify == true) std::cout << "Game saved!\n";
    }
    else std::cout << "Error saving game.\n";
}

void HandleLoad(const std::string& saveFilePath, long& money, long& points) {
    std::ifstream loadFile(saveFilePath);
    if (loadFile.is_open()) {
        std::string line;
        if (getline(loadFile, line)) money = std::stoi(line);
        if (getline(loadFile, line)) points = std::stoi(line);
        if (getline(loadFile, line))  def.taxamount = std::stoi(line);
        if (getline(loadFile, line))  def.secretonefound = std::stoi(line);
        if (getline(loadFile, line))  def.secrettwofound = std::stoi(line);
        if (getline(loadFile, line))  def.csamount = std::stoi(line);
        if (getline(loadFile, line))  def.inprison = std::stoi(line);

        std::cout << "Game loaded! (Money: " << money << "), (Points: " << points << "), (Taxes needed to pay: " << def.taxamount << "), (Child support you owe: " << def.csamount << ")\n";
    }
    else std::cout << "No saved game found.\n";
}

void HandleExit() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    int hour = ltm.tm_hour;
    std::cout << "Exiting game! " << (hour >= 6 && hour < 18 ? "Have a good day!" : "Have a good night!") << "\n";
    AchievementReachedCheck(def.money, def.points);
    std::string response;
    std::cout << "Confirm (y/n)?";
    std::cin >> response;
    if (response == "y" || response == "Y") exit(0);
}

void HandlePoints(long points) {
    std::cout << "Current points: " << points << std::endl;
    AchievementReachedCheck(def.money, points);
}

void HandleMoney(long money) {
    std::cout << "Current money: " << money << std::endl;
    AchievementReachedCheck(money, def.points);
}

void HandleGamble(long& money) {
    MP3Silently("C:\\ReaperGame\\Assets\\gamble.mp3", true);

    if (money <= 0) {
        std::cout << "You don't have enough money to gamble.\n";
        MP3Silently("C:\\ReaperGame\\Assets\\gamble.mp3", false);
        return;
    }

    Gamble:
    std::cout << "How much money would you like to gamble? (Current money: " << money << "): ";
    long gambleAmount = getValidLong();

    if (gambleAmount <= 0) {
        std::cout << "Invalid amount. Please enter a positive number.\n";
        goto Gamble;
    }
    else if (gambleAmount > money) {
        std::cout << "You don't have enough money to gamble that amount.\n";
        return;
    }

    int chance = rand() % 101;
    double chance2 = ((rand() % 201) / 100.0) + 1.25;  //between 1.25 and 3.25

    if (chance <= 66) {
        long winnings = ceil(gambleAmount * chance2);
        money += winnings;
        std::cout << "You won! You gained " << winnings << " money.\n";

        long tax = ceil(winnings / 5.0);
        def.taxamount += tax;
        def.csamount += 1;

        MP3Silently("C:\\ReaperGame\\Assets\\gamble.mp3", false);
        PlayActionSound();
        AchievementReachedCheck(money, def.points);
    }
    else {
        money -= gambleAmount;
        std::cout << "You lost! You lost " << gambleAmount << " money.\n";

        MP3Silently("C:\\ReaperGame\\Assets\\gamble.mp3", false);
        PlayActionSound();
    }
}
void Game(); //needed a declaration thanks so much w3schools for the help :3

void Prison() {
    MP3Silently("C:\\ReaperGame\\Assets\\prison.mp3", true);
    def.inprison = true;
    def.csamount = 0;
    def.wentToPrison = true;
    HandleSave(def.saveFilePath, def.money, def.points, true);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    HandleSupport();
    SetFontSize(def.fontSize);
    AchievementReachedCheck(def.money, def.points);
    SaveAchievements();

    std::cout << "\nYou are in prison for not paying your child support\n";

    while (def.inprison) {
        std::cout 
            << "\nYour options are:\n"
            << "1. Math (Medium but free)\n"
            << "2. Bribery (Easy but costs money)\n"
            << "3. Prisonbreak (Hard but free)\n"
            << "Choose an option: ";

        std::string option;
        std::cin >> option;
        std::transform(option.begin(), option.end(), option.begin(), ::tolower);

        if (option == "bribery") {
            if (def.money <= 0) {
                std::cout << "You don't have enough money to bribe.\n";
                continue;
            }
            std::cout << "How much money would you like to bribe? (Current money: " << def.money << ") the higher, the better chance: ";
            int bribeAmount = getValidLong();

            if (bribeAmount <= 0 || bribeAmount > def.money) {
                std::cout << "Invalid amount.\n";
                continue;
            }

            if ((rand() % 101) < pow(bribeAmount, 0.75f)) {
                def.money -= bribeAmount;
                std::cout << "You lost " << bribeAmount << " money.\nYOU ARE OUT OF PRISON!!!\n";
                def.inprison = false;
            }
            else std::cout << "Your bribe was declined...\n";
        }
        else if (option == "prisonbreak") {
            if ((rand() % 101) < 10) {
                std::cout << "YOU ARE OUT OF PRISON!!!\n";
                def.inprison = false;
            }
            else std::cout << "You failed to escape...\n";
        }
        else if (option == "math") {
            while (true) {
                int num1 = rand() % 901 + 100, num2 = rand() % 901 + 100, answer;
                std::string operation;
                std::cout << "Choose operation (add/subtract): ";
                std::cin >> operation;

                if (operation == "add") {
                    std::cout << "What is " << num1 << " + " << num2 << "? ";
                    answer = num1 + num2;
                }
                else if (operation == "subtract") {
                    std::cout << "What is " << num1 << " - " << num2 << "? ";
                    answer = num1 - num2;
                }
                else {
                    std::cout << "Invalid operation.\n";
                    continue;
                }

                if (getValidInt() == answer) {
                    std::cout << "YOU ARE OUT OF PRISON!!!\n";
                    def.inprison = false;
                    break;
                }
                else {
                    std::cout << "Wrong answer! Try again? (y/n): ";
                    std::string retry;
                    std::cin >> retry;
                    if (retry != "y" && retry != "Y") break;
                }
            }
        }
        else std::cout << "Invalid response.\n";
    }

    MP3Silently("C:\\ReaperGame\\Assets\\prison.mp3", false);
    def.escapedPrison = true;
    AchievementReachedCheck(def.money, def.points);
    Sleep(1000);
    HandleSave(def.saveFilePath, def.money, def.points, true);
    Game();
}

void HandleTaxes(long& money, long& taxamount) {
    if (taxamount <= 0) {
        std::cout << "You don't owe any taxes right now.\n";
        return;
    }

    std::string response;

    do {
        std::cout << "You owe: " << taxamount << " in taxes.std::" << std::endl;
        std::cout << "Would you like to pay the taxes (y/n)? ";
        std::cin >> response;

        if (response == "y" || response == "Y") {
            while (taxamount > 0) {
                std::cout << "How much money would you like to pay for your taxes? (Current money: " << money << ", Remaining taxes: " << taxamount << "): ";
                long payment = getValidLong();

                if (payment > money) std::cout << "You do not have enough money to pay this amount. You only have " << money << ".\n";
                else if (payment > taxamount) std::cout << "You only owe " << taxamount << " in taxes. Enter a smaller amount.\n";
                else if (payment <= 0) std::cout << "Invalid input. Please enter a positive number.\n";
                else {
                    money -= payment;
                    taxamount -= payment;
                    std::cout << "You paid " << payment << " in taxes. Your remaining balance is " << money << ".\n";
                    PlayActionSound();
                    if (taxamount <= 0) {
                        std::cout << "You have fully paid your taxes.\n";
                        return;
                    }

                    std::cout << "Remaining taxes: " << taxamount << ". Would you like to continue paying? (y/n): ";
                    std::cin >> response;

                    if (response != "y" && response != "Y") {
                        std::cout << "You chose not to pay any more taxes. Remaining taxes: " << taxamount << ".\n";
                        return;
                    }
                }
            }
        }
        else if (response != "n" && response != "N") std::cout << "Invalid input. Please respond with 'y' or 'n'.\n";
    }
    while (response != "n" && response != "N");

    if (response == "n" || response == "N") std::cout << "You chose not to pay taxes. The tax amount remains the same.\n";
}

void ChildSupport(long& money, long& childsupportamount)
{
    if (childsupportamount <= 0) {
        std::cout << "You don't owe child support.\n";
        return;
    }

    std::string response;

    do {
        std::cout << "You owe: " << childsupportamount << " in child support." << std::endl;
        std::cout << "Would you like to pay child support (y/n)? ";
        std::cin >> response;

        if (response == "y" || response == "Y") {
            if (money >= childsupportamount) {
                money -= childsupportamount;
                childsupportamount = 0;
                std::cout << "Child support fully paid. Remaining money: " << money << "\n";
                PlayActionSound();
                AchievementReachedCheck(money, def.points);
            }
            else {
                std::cout << "You do not have enough money to pay the full child support.\n";
                std::cout << "Paying what you can: " << money << "\n";
                childsupportamount -= money;
                money = 0;
                std::cout << "Remaining child support amount: " << childsupportamount << "\n";
            }
        }
        else if (response != "n" && response != "N") std::cout << "Invalid input. Please respond with 'y' or 'n'.\n";

    }
    while (response != "n" && response != "N" && childsupportamount > 0);

    if (childsupportamount > 0) std::cout << "You still owe " << childsupportamount << " in child support. Please pay soon.\n";
    else std::cout << "Child support is fully paid. Thank you!\n";
}

void TypeEffect(const std::string& text, int delay_ms) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << std::endl;
}

void Mrati();

void Game()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    AssetsFolder();
    HandleSupport();
    std::cout << def.reaperGameEdition << std::endl;

    if (system(("mkdir " + def.folderPath).c_str())) {}

    std::string autoload, autosave;
    LoadSettings(autoload, autosave, def.settingsFilePath);
    SetFontSize(def.fontSize);

    if (autoload == "on") {
        HandleLoad(def.saveFilePath, def.money, def.points);
    }
    LoadAchievements();
    AchievementReachedCheck(def.money, def.points);
    DisplayCommands();

    while (true)
        if (!def.inprison)
        {
            if (def.csamount == def.csRqToGoToPrison) Prison();
            //commands
            std::cin >> def.command;
            std::transform(def.command.begin(), def.command.end(), def.command.begin(), ::tolower);
            if (def.command == "/help") DisplayCommands();
            else if (def.command == "/achievements") DisplayAchievements();
            else if (def.command == "/support") HandleSupport();
            else if (def.command == "/transaction") HandleTransaction(def.money, def.points);
            else if (def.command == "/playagame") HandlePlayAGame(def.money, def.points);
            else if (def.command == "/save") HandleSave(def.saveFilePath, def.money, def.points, true);
            else if (def.command == "/load") HandleLoad(def.saveFilePath, def.money, def.points);
            else if (def.command == "/settings") Settings(autoload, autosave, def.settingsFilePath);
            else if (def.command == "/gamble") HandleGamble(def.money);
            else if (def.command == "/taxes") HandleTaxes(def.money, def.taxamount);
            else if (def.command == "/childsupport") ChildSupport(def.money, def.csamount);

            else if (def.command == "/exit") 
            {
                if (autosave == "on") HandleSave(def.saveFilePath, def.money, def.points, true);
                HandleExit();
            }
            else if (def.command == "/clear")
            {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                HandleSupport();
                LoadSettings(autoload, autosave, def.settingsFilePath);
                SetFontSize(def.fontSize);
                if (autoload == "on") HandleLoad(def.saveFilePath, def.money, def.points);
                DisplayCommands();
            }
            else if (def.command == "/points") HandlePoints(def.points);
            else if (def.command == "/money") HandleMoney(def.money);

            else if (def.command == "/reaper")
            {
                if (def.secretonefound == false)
                {
                    std::cout << "Guh, I guess you have found me\nI will give you 1000 money, i paid the taxes for you btw and np.\n";
                    def.money += 1000;
                    def.secretonefound = true;
                    AchievementReachedCheck(def.money, def.points);
                }
                else {
                    std::cout << "Bro STOP BEGGING ME FOR MONEY PLEASE BRUH...\n";
                    def.begging = true;
                    AchievementReachedCheck(def.money, def.points);
                }
            }
            else if (def.command == "/kys")
            {
                if (def.secrettwofound == false)
                {
                    std::cout << "Did you just tell me to keep myself safe??? I am stealing your money\n";
                    double moneystolen = def.money / 3;
                    moneystolen = ceil(moneystolen);
                    def.money -= static_cast<long>(moneystolen);
                    std::cout << "reaper just stole " << moneystolen << " money from you\n";
                    def.secrettwofound = true;
                    AchievementReachedCheck(def.money, def.points);
                }
                else std::cout << "Odd specimen\n";
            }
            else if (def.command == "/therat")
            {
                std::string input;
                TypeEffect("MRATI: LET ME TELL YOU A STORY...\n", 70);
                std::cout << "(y/n)?";
                std::cin >> input;
                if (input == "y" || input == "Y")
                {
                    TypeEffect("MRATI: Why thank you actually! :D\n", 70);
                    goto Story;
                }
                else if (input == "n" || input == "N")
                {
                    TypeEffect("MRATI: (Ignoring your input)\n", 70);
                    goto Story;
                }
                else 
                {
                    TypeEffect("MRATI: Learn how to respond you!!!", 70);
                    goto Story;
                }
            Story:
                TypeEffect("MRATI: Anyways... I was a crocodile once bit by an evil rat!\n", 70);
                TypeEffect("MRATI: This is why I love joe biden he is so awesome! :3\n", 70);
                TypeEffect("MRATI: This is why I am a rat...\n", 70);
                TypeEffect("MRATI: Cool story?\n", 70);
                std::cout << "(y/n)?";
                std::string input2;
                std::cin >> input2;
                if (input2 == "y" || input2 == "Y")
                {
                    TypeEffect("MRATI: Thank you I am proud to be your guest :D\n", 70);
                }
                else if (input2 == "n" || input2 == "N")
                {
                    TypeEffect("MRATI: KYS\n", 70);
                    TypeEffect("......... Boss encounter!!!\n", 70);
                    Sleep(250);
                    Mrati();
                }
                else TypeEffect("MRATI: Learn how to respond you!!!", 70);
            }
            /*
            //Description Commands ISSUES HERE
            else if (def.command == "/checkdesc[ExampleMod]")
            {
                reaperExampleMod.ModDescription();
            }
            else if (def.command == "/checkdesc[bettermathdamesmod]")
            {
                betterMathGamesMod.ModDescription();
            }
            */
            //MOD COMMAND ALLOW LIST
            else if (reaperExampleMod.CommandUsed());
            else if (betterMathGamesMod.CommandUsed());

            else std::cout << "Invalid command. Type /help for available commands.\n";

            if (autosave == "on") {
                HandleSave(def.saveFilePath, def.money, def.points, false);
            }
        }
}

struct Mods {
    std::string name;
    bool isEnabled;

    Mods(std::string modName) : name(modName), isEnabled(false) {}
};

void SaveModSettings(const std::vector<Mods>& modList, const std::string& filePath) {
    std::ofstream modFile(filePath);
    if (modFile.is_open()) {
        for (const auto& mod : modList) {
            modFile << mod.name << " " << (mod.isEnabled ? "true" : "false") << std::endl;
        }
        modFile.close();
        std::cout << "Mod settings saved to " << filePath << std::endl;
    }
    else {
        std::cout << "Error opening file for writing mod settings.\n";
    }
}

void LoadModSettings(std::vector<Mods>& modList, const std::string& filePath) {
    std::ifstream modFile(filePath);
    if (modFile.is_open()) {
        std::string modName;
        std::string status;
        while (modFile >> modName >> status) {
            for (auto& mod : modList) {
                if (mod.name == modName) mod.isEnabled = (status == "true");
            }
        }
        modFile.close();
    }
}

#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

void DisplayModList(const std::vector<Mods>& modList) {
    std::cout << "ModList:\n";
    for (size_t i = 0; i < modList.size(); ++i) {
        std::cout << i + 1 << ". " << modList[i].name << " ["
            << (modList[i].isEnabled ? "Enabled" : "Disabled") << "]\n";
    }
}

int GetValidModChoice(size_t modCount) {
    int choice;
    while (true) {
        std::cout << "Select a mod to toggle (1-" << modCount << "): ";
        std::cin >> choice;

        if (!std::cin.fail() && choice >= 1 && choice <= static_cast<int>(modCount)) {
            return choice - 1;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice! Try again.\n";
    }
}

bool GetYesNoInput(const std::string& prompt) {
    char input;
    std::cout << prompt << " (y/n): ";
    std::cin >> input;
    return (input == 'y' || input == 'Y');
}

int main() {
    system("title RgModLoader v1.2");
    SetFontSize(def.fontSize);

    std::cout << "Game and Modloader made by " << def.developerExName << "\n";
    std::cout << "Credits List: NOT DONE YET\n";

    std::string filePath = "C:\\ReaperGame\\SaveData\\ModLoadList.txt";
    std::vector<Mods> modList = { 
        Mods("ExampleMod"), 
        Mods("BetterMathGamesMod") 
    };

    LoadModSettings(modList, filePath);

    for (size_t i = 0; i < modList.size(); ++i) {
        def.modSet[i] = modList[i].isEnabled;
    }

    reaperExampleMod.CheckEnable(def.modSet[0]);
    betterMathGamesMod.CheckEnable(def.modSet[1]);

    DisplayModList(modList);

    while (GetYesNoInput("Would you like to change any settings?")) {
        int modIndex = GetValidModChoice(modList.size());

        if (GetYesNoInput("Would you like to " +
            std::string(modList[modIndex].isEnabled ? "Disable" : "Enable") +
            " " + modList[modIndex].name + "?"))
        {
            modList[modIndex].isEnabled = !modList[modIndex].isEnabled;
            def.modSet[modIndex] = modList[modIndex].isEnabled;

            std::cout << modList[modIndex].name << " is now "
                << (modList[modIndex].isEnabled ? "Enabled" : "Disabled") << ".\n";

            SaveModSettings(modList, filePath);

            if (modList[modIndex].isEnabled) {
                if (modIndex == 0) reaperExampleMod.InitializeMod();
                if (modIndex == 1) betterMathGamesMod.InitializeMod();
            }
        }
    }

    reaperExampleMod.CheckEnable(def.modSet[0]);
    betterMathGamesMod.CheckEnable(def.modSet[1]);

    if (GetYesNoInput("Start Game?")) {
        srand(static_cast<unsigned>(time(0)));
        Game();
    }
    else {
        std::cout << "Exiting Modloader...\n";
    }

    return 0;
}








int ratiHP = 20;
int playerHP = 50;
int playerPotions = 5;
int money = 0;


void CheckRatiDeath()
{
        TypeEffect("Rati has been defeated! You win!\n", 60);
        TypeEffect("You won 5,000 money\n", 60);
        money += 5000;
        def.beatRati = true;
        AchievementReachedCheck(money, def.points);
        Sleep(1000);
        std::cout << "type /help for commands\n";
        return;
}
void CheckPlayerDeath()
{       TypeEffect("You have been defeated by Rati... Game Over!\n", 60);
        Sleep(1000);
        std::cout << "type /help for commands\n";
        return;
}

//BOSS!!!

void Mrati() {
    MP3Silently("C:\\ReaperGame\\Assets\\mrati.mp3", true);

        TypeEffect("MRATI: YOUR OPINION DOESNT MATTER TO A MAN LIKE ME!@#$%\n", 40);
        Sleep(800);
        TypeEffect("MRATI: I'll make you pay...\n", 40);
        Sleep(2200);

        while (ratiHP > 0 && playerHP > 0) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            std::cout << "PLAYERS TURN!!!\n\n";
            std::cout << "RATI Health: " + std::to_string(ratiHP) + "\n";
            std::cout << "Player Health: " + std::to_string(playerHP) + "\n\n";

            std::cout << "Attack Options:\n";
            std::cout << "Emotional Damage\n";
            std::cout << "Tax Forms\n";
            std::cout << "Child Support\n";
            if (playerPotions > 0) {
                std::cout << "Heal (" << playerPotions << " potions left)\n";
            }
            std::cout << "\n";

            std::string input;
            getline(std::cin, input);
            int damageToRat = rand() % 11 + 1;
            int chance = rand() % 101 + 1;

            if (input == "Emotional Damage" || input == "emotional damage") {
                TypeEffect("Rolling Dice...\n", 60);
                Sleep(400);
                TypeEffect("Dice came out as... " + std::to_string(damageToRat) + " damage!\n", 60);

                if (chance <= 10) {
                    TypeEffect("BUT WAIT... You have missed and caused no emotional damage...\n", 60);
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                }
                else {
                    ratiHP -= damageToRat;
                    TypeEffect(std::to_string(damageToRat) + " emotional damage done to rati... \n", 60);
                    TypeEffect("Rati has: " + std::to_string(ratiHP) + " HP left. Cry... \n", 60);
                    if (ratiHP <= 0) CheckRatiDeath();
                    else
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Tax Forms" || input == "tax forms") {
                TypeEffect("Rolling Dice...\n", 60);
                Sleep(400);
                TypeEffect("Dice came out as... " + std::to_string(damageToRat) + " damage!\n", 60);

                if (chance <= 10) {
                    TypeEffect("BUT WAIT... You have missed...\n", 60);
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                }
                else {
                    ratiHP -= damageToRat;
                    TypeEffect(std::to_string(damageToRat) + " Tax Forms given to rati... \n", 60);
                    TypeEffect("Rati has: " + std::to_string(ratiHP) + " HP left. I HATE TAXES!!! \n", 60);
                    if (ratiHP <= 0) CheckRatiDeath();
                    else
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Child Support" || input == "child support") {
                TypeEffect("Rolling Dice...\n", 60);
                Sleep(400);
                TypeEffect("Dice came out as... " + std::to_string(damageToRat) + " damage!\n", 60);

                if (chance <= 10) {
                    TypeEffect("BUT WAIT... Rati doesnt have a child currently...\n", 60);
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                }
                else {
                    ratiHP -= damageToRat;
                    TypeEffect(std::to_string(damageToRat) + " Child Support money taken from rati... \n", 60);
                    TypeEffect("Rati has: " + std::to_string(ratiHP) + " HP left. I HATE PAYING CHILD SUPPORT!!! \n", 60);
                    if(ratiHP <= 0) CheckRatiDeath();
                    else
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            if (input == "Attack Options" || input == "attack options")
            {
                const std::string rainbowColors[] = {
                    "\033[31m", //Red
                    "\033[32m", //Green
                    "\033[33m", //Yellow
                    "\033[34m", //Blue
                    "\033[35m"  //Magenta
                };

                int colorIndex = 0;
                auto CycleColor = [&]() {
                    std::cout << rainbowColors[colorIndex];
                    colorIndex = (colorIndex + 1) % 5;
                    };

                CycleColor();
                TypeEffect("Rolling Special Dice...\n", 60);
                std::this_thread::sleep_for(std::chrono::milliseconds(400));

                CycleColor();
                TypeEffect("Special Dice came out as... " + std::to_string(damageToRat * 2) + " damage!\n", 60);

                if (chance <= 10)
                {
                    CycleColor();
                    TypeEffect("BUT WAIT... Rati is sigma and you missed...\n", 60);

                    CycleColor();
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                }
                else
                {
                    ratiHP -= damageToRat *= 2;

                    CycleColor();
                    TypeEffect(std::to_string(damageToRat) + " damage done to rati...\n", 60);

                    CycleColor();
                    TypeEffect("Rati has: " + std::to_string(ratiHP) + " HP left.\n", 60);

                    CycleColor();

                    if (ratiHP <= 0) CheckRatiDeath();
                    else
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                }

                std::cout << "\033[0m"; //reset
            }
            else if (input == "Heal" || input == "heal") {
                if (playerPotions > 0) {
                    playerHP += 20;
                    playerPotions--;
                    TypeEffect("You used a healing potion! +" + std::to_string(20) + " HP.\n", 60);
                    TypeEffect("You have " + std::to_string(playerPotions) + " healing potions left.\n", 60);
                    TypeEffect("RATI'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
                else {
                    TypeEffect("No potions left! Try a different option...\n", 60);
                    continue;
                }
            }
            else {
                TypeEffect("Invalid option! Try again.\n", 60);
                continue;
            }

            //Rati's turn
            if (ratiHP > 0) {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                std::cout << "RATIS TURN!!!\n\n";
                std::cout << "RATI Health: " + std::to_string(ratiHP) + "\n";
                std::cout << "Player Health: " + std::to_string(playerHP) + "\n\n";

                int ratiDamage = rand() % 11 + 1;
                playerHP -= ratiDamage;
                TypeEffect("Rati dealt " + std::to_string(ratiDamage) + " damage to you.\n", 60);
                TypeEffect("You have: " + std::to_string(playerHP) + " HP left.\n", 60);
                if (playerHP <= 0) CheckPlayerDeath();
                else
                TypeEffect("PLAYER'S TURN!!!\n\n", 30);
                Sleep(2000);
            }
        }
    }