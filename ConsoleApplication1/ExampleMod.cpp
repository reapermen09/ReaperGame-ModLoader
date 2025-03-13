#include "ExampleMod.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Defaults.h"

bool beatReaper = false;
bool beatenRati = false;
bool reaperHasBeenBeaten = false;
bool inboss = false;
ExampleMod::ExampleMod() { CheckEnable(def.modSet[0]); }

void ExampleMod::ModifyAttributes() {
    if (!modEnabled) {
        std::cout << "[Mod Disabled]\n";
        return;
    }
    else
    {
        if (inboss && beatReaper)
        {
            def.money += 10000;
            std::ofstream saveFile(def.saveFile, std::ios::out | std::ios::trunc);
            if (saveFile.is_open()) {
                saveFile << def.money << "\n" << def.points << "\n" << def.taxamount << "\n" << def.secretonefound << "\n" << def.secrettwofound << "\n" << def.csamount << "\n" << def.inprison << std::endl;
            }
            else {
                std::cout << "Error saving game.\n";
            }
        }
    }
}
void ExampleMod::CommandList() 
{
    if (modEnabled)
    {
        std::cout << "\033[A\33[2K\r"; // this will clear a line above (always include this at the very top of your command list)
        std::cout << "/exampleboss [ExampleMod]\n\n"; // always end with a \n\n for the sake of other mods
    }
}
std::string saveAchievements = "C:\\ReaperGame\\SaveData\\ExampleModAchievements.txt";

void ExampleMod::ModAchievementDisplay()
{
    if (modEnabled)
    {
        if (beatReaper)
        {
            std::cout << "Reaper Destroyed: You beat Reaper\n";
        }
    }
}

void ExampleMod::ModAchievementLoad()
{
    if (modEnabled)
    {
        std::ifstream achievementsFile(saveAchievements);
        if (achievementsFile.is_open()) {
            achievementsFile >> beatReaper;
            achievementsFile >> reaperHasBeenBeaten;
            achievementsFile.close();
        }
        else {
            std::cout << "No achievements file found... Starting fresh!\n";
        }
    }
}

void ExampleMod::ModifyAchievements()
{
    if (modEnabled)
    {
        if (beatReaper && !reaperHasBeenBeaten)
        {
            std::cout << "You got the Reaper Destroyed achievement! (You beat Reaper)\n";
            reaperHasBeenBeaten = true;
        }
        ModAchievementSave();
    }
}

void ExampleMod::ModAchievementSave()
{
    if (modEnabled)
    {
        std::ofstream achievementsFile(saveAchievements);
        if (achievementsFile.is_open()) {
            achievementsFile << beatReaper << "\n";
            achievementsFile << reaperHasBeenBeaten << "\n";
            achievementsFile.close();
        }
        else {
            std::cout << "Error: Unable to save achievements.\n";
        }
    }
}

bool ExampleMod::CommandUsed()
{
    if (def.command == "/exampleboss")
    {
        Bosses();
        return true;
    }
    else return false;
}

void ExampleMod::Bosses()
{
    if (modEnabled) 
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        Type("REAPER: MAHAHAHA!!! YOU HAVE SUMMONED ME... THE REAPER!!!", 70);
        Sleep(1000);
        Type("REAPER: NOW I MUST END YOU...", 70);
        Sleep(2000);
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        Music("C:\\ReaperGame\\Assets\\gamble.mp3", true);
        inboss = true;
        int reaperHP = 120;
        int playerHP;

        std::ifstream achievementsFile("C:\\ReaperGame\\SaveData\\achievements.txt");
        if (achievementsFile.is_open()) {
            std::string line;
            int lineNumber = 0;
            while (getline(achievementsFile, line)) {
                lineNumber++;
                if (lineNumber == 19) {
                    std::istringstream(line) >> beatenRati;
                    break;
                }
            }
            achievementsFile.close();
        }
        if (beatenRati)
        {
            playerHP = 70;
        }
        else
        {
            playerHP = 60;
        }
        int playerPotions = 7;

        while (reaperHP > 0 && playerHP > 0) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            std::cout << "PLAYERS TURN!!!\n\n";
            std::cout << "Reaper Health: " + std::to_string(reaperHP) + "\n";
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
            std::getline(std::cin, input);
            int damageToReaper = rand() % 16 + 3;
            int chance = rand() % 101 + 1;

            if (input == "Emotional Damage" || input == "emotional damage") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + std::to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... You have missed and caused no emotional damage...\n", 60);
                    Type("REAPERS'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(std::to_string(damageToReaper) + " emotional damage done to Reaper... \n", 60);
                    Type("Reaper has: " + std::to_string(reaperHP) + " HP left. Cry... \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Tax Forms" || input == "tax forms") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + std::to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... You have missed...\n", 60);
                    Type("REAPERS'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(std::to_string(damageToReaper) + " Tax Forms given to Reaper... \n", 60);
                    Type("Reaper has: " + std::to_string(reaperHP) + " HP left. I HATE TAXES!!! \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Child Support" || input == "child support") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + std::to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... Reaper doesnt have a child currently...\n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(std::to_string(damageToReaper) + " Child Support money taken from Reaper... \n", 60);
                    Type("Reaper has: " + std::to_string(reaperHP) + " HP left. I HATE PAYING CHILD SUPPORT!!! \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
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
                Type("Rolling Special Dice...\n", 60);
                std::this_thread::sleep_for(std::chrono::milliseconds(400));

                CycleColor();
                Type("Special Dice came out as... " + std::to_string(damageToReaper * 2) + " damage!\n", 60);

                if (chance <= 15)
                {
                    CycleColor();
                    Type("BUT WAIT... Reaper is skibidi toilet deluxe and you missed...\n", 60);

                    CycleColor();
                    Type("REAPER'S TURN!!!\n\n", 30);
                }
                else
                {
                    reaperHP -= damageToReaper *= 2;

                    CycleColor();
                    Type(std::to_string(damageToReaper) + " damage done to Reaper...\n", 60);

                    CycleColor();
                    Type("Reaper has: " + std::to_string(reaperHP) + " HP left.\n", 60);

                    CycleColor();
                    Type("REAPER'S TURN!!!\n\n", 30);
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                }

                std::cout << "\033[0m"; //reset
            }
            else if (input == "Heal" || input == "heal") {
                if (playerPotions > 0) {
                    playerHP += 50;
                    playerPotions--;
                    Type("You used a healing potion! +" + std::to_string(50) + " HP.\n", 60);
                    Type("You have " + std::to_string(playerPotions) + " healing potions left.\n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
                else {
                    Type("No potions left! Try a different option...\n", 60);
                    continue;
                }
            }
            else {
                Type("Invalid option! Try again.\n", 60);
                continue;
            }

            //Reaper's turn
            if (reaperHP > 0) {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                std::cout << "REAPERS TURN!!!\n\n";
                std::cout << "Reaper Health: " + std::to_string(reaperHP) + "\n";
                std::cout << "Player Health: " + std::to_string(playerHP) + "\n\n";

                int reaperDamage = rand() % 31 + 11;
                playerHP -= reaperDamage;
                Type("Reaper dealt " + std::to_string(reaperDamage) + " damage to you.\n", 60);
                Type("You have: " + std::to_string(playerHP) + " HP left.\n", 60);
                Type("PLAYER'S TURN!!!\n\n", 30);
                Sleep(2000);
            }
        }

        if (reaperHP <= 0) {
            Type("Reaper has been defeated! You win!\n", 60);
            Type("You won 10,000 money\n", 60);
            beatReaper = true;
            ModifyAttributes();
            inboss = false;
            ModifyAchievements();
            Sleep(1000);
            std::cout << "type /help for commands\n";
        }
        else if (playerHP <= 0) {
            Type("You have been defeated by Reaper... Game Over!\n", 60);
            Sleep(1000);
            std::cout << "type /help for commands\n";
        }
    }
}

void ExampleMod::ModDescription()
{
    //you shouldnt put an enable check here preferably
    std::cout << "This is an Example Description!\n\n";
}

void ExampleMod::InitializeMod() {
    if (modEnabled) {
        std::cout << "[ReaperGameExampleMod] Mod Initialized!\n" << Developer("Reaper09");
        EnsureSaveDirectory(false);
        HandleLoad();
        ModifyAttributes();
        HandleSave();
    }
}