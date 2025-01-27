#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

#undef max

int taxamount = 0;
int csamount = 0;
int fontSize;
bool inprison = false;
bool secretonefound;
bool secrettwofound;
bool begging;
int money = 10;
int points = 0;
string folderPath = "C:\\ReaperGame\\SaveData";
string saveFilePath = folderPath + "\\game_save.txt";
string settingsFilePath = folderPath + "\\settings.txt";
string achievementsFilePath = folderPath + "\\achievements.txt";

void SetFontSize(int size) {
    if (size < 1 || size > 3) {
        cout << "Invalid font size. Setting to default (3).\n";
        size = 3;
    }
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    switch (size) {
    case 1:
        cfi.dwFontSize.X = 8;
        cfi.dwFontSize.Y = 12;
        break;
    case 2:
        cfi.dwFontSize.X = 12;
        cfi.dwFontSize.Y = 18;
        break;
    case 3:
        cfi.dwFontSize.X = 16;
        cfi.dwFontSize.Y = 24;
        break;
    }

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

int getValidInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        else {
            return value;
        }
    }
}

bool money100 = false;
bool money1000 = false;
bool money10000 = false;
bool money100000 = false;
bool money1000000 = false;

bool firstTransaction = false;
bool foundreaper = false;
bool insultreaper = false;
bool begreaper = false;

bool points100 = false;
bool points1000 = false;
bool points10000 = false;
bool points100000 = false;
bool points1000000 = false;

void SaveAchievements()
{
    ofstream achievementsFile(achievementsFilePath);
    if (achievementsFile.is_open())
    {
        achievementsFile << money100 << "\n";
        achievementsFile << money1000 << "\n";
        achievementsFile << money10000 << "\n";
        achievementsFile << money100000 << "\n";
        achievementsFile << money1000000 << "\n";

        achievementsFile << firstTransaction << "\n";
        achievementsFile << foundreaper << "\n";
        achievementsFile << insultreaper << "\n";
        achievementsFile << begreaper << "\n";

        achievementsFile << points100 << "\n";
        achievementsFile << points1000 << "\n";
        achievementsFile << points10000 << "\n";
        achievementsFile << points100000 << "\n";
        achievementsFile << points1000000 << "\n";

        achievementsFile.close();
    }
    else
    {
        cout << "Error: Unable to save achievements.\n";
    }
}

void LoadAchievements()
{
    ifstream achievementsFile(achievementsFilePath);
    if (achievementsFile.is_open())
    {
        achievementsFile >> money100;
        achievementsFile >> money1000;
        achievementsFile >> money10000;
        achievementsFile >> money100000;
        achievementsFile >> money1000000;

        achievementsFile >> firstTransaction;
        achievementsFile >> foundreaper;
        achievementsFile >> insultreaper;
        achievementsFile >> begreaper;

        achievementsFile >> points100;
        achievementsFile >> points1000;
        achievementsFile >> points10000;
        achievementsFile >> points100000;
        achievementsFile >> points1000000;

        achievementsFile.close();
    }
    else
    {
        cout << "No achievements file found... Starting fresh!\n";
    }
}

void DisplayAchievements()
{
    cout << "Achievements:\n";

    if (money100) cout << "Novice: 100+ money\n";
    if (money1000) cout << "Grinder Type Guy: 1000+ money\n";
    if (money10000) cout << "Commander: 10000+ money\n";
    if (money100000) cout << "Destroyer Type Guy: 100000+ money\n";
    if (money1000000) cout << "Rich Sigma: 1000000+ money\n";

    if (firstTransaction) cout << "First Transaction: Completed your first transaction\n";
    if (foundreaper) cout << "Finding the Reaper: You found Reaper who gave you 100 money\n";
    if (insultreaper) cout << "Insulting the Reaper: You insulted Reaper, how dare you\n";
    if (begreaper) cout << "Begging: Stop begging Reaper for money, please\n";

    if (points100) cout << "Point Grinder: 100+ points\n";
    if (points1000) cout << "Pointer: 1000+ points\n";
    if (points10000) cout << "Amazing Player: 10000+ points\n";
    if (points100000) cout << "Super Player: 100000+ points\n";
    if (points1000000) cout << "Sigma Player: 1000000+ points\n";
}

void AchievementReachedCheck(int money, int points)
{
    
    if (money >= 100 && !money100)
    {
        //cout << "You got the Novice achievement! (100+ money)\n";
        money100 = true;
    }
    if (money >= 1000 && !money1000)
    {
        //cout << "You got the Grinder Type Guy achievement! (1000+ money)\n";
        money1000 = true;
    }
    if (money >= 10000 && !money10000)
    {
        //cout << "You got the Commander achievement! (10000+ money)\n";
        money10000 = true;
    }
    if (money >= 100000 && !money100000)
    {
        //cout << "You got the Destroyer Type Guy achievement! (100000+ money)\n";
        money100000 = true;
    }
    if (money >= 1000000 && !money1000000)
    {
        //cout << "You got the Rich Sigma achievement! (1000000+ money)\n";
        money1000000 = true;
    }
    if (points > 0 && !firstTransaction)
    {
        //cout << "You got the First Transaction achievement! (You did your first transaction)\n";
        firstTransaction = true;
    }

    if (secretonefound && !foundreaper)
    {
        //cout << "Finding the Reaper (You found Reaper who gave you 100 money)\n";
        firstTransaction = true;
    }

    if (secrettwofound > 0 && !insultreaper)
    {
        //cout << "Insulting the Reaper (You insulted Reaper, how dare you)\n";
        firstTransaction = true;
    }

    if (begging && !begreaper)
    {
        //cout << "You got the Begging achievement! (Stop begging Reaper for money, please)\n";
        firstTransaction = true;
    }

    if (points >= 100 && !points100)
    {
        //cout << "You got the Point Grinder achievement! (100+ points)\n";
        points100 = true;
    }
    if (points >= 1000 && !points1000)
    {
        //cout << "You got the Pointer achievement! (1000+ points)\n";
        points1000 = true;
    }
    if (points >= 10000 && !points10000)
    {
        //cout << "You got the Amazing Player achievement! (10000+ points)\n";
        points10000 = true;
    }
    if (points >= 100000 && !points100000)
    {
        //cout << "You got the Super Player achievement! (100000+ points)\n";
        points100000 = true;
    }
    if (points >= 1000000 && !points1000000)
    {
        //cout << "You got the Sigma Player achievement! (1000000+ points)\n";
        points1000000 = true;
    }
    SaveAchievements();
}

void DisplayCommands() {
    cout << "\nAvailable commands:\n";
    cout << "/help - Show this help message\n";
    cout << "/achievements - Shows your gained achievements\n";
    cout << "/transaction - Convert your money into points (Includes tax)\n";
    cout << "/playagame - Play a math game (Includes tax)\n";
    cout << "/money - Show your money balance\n";
    cout << "/points - Show your points\n";
    cout << "/save - Save your game progress\n";
    cout << "/load - Load your game progress\n";
    cout << "/support - Check support\n";
    cout << "/settings - Change game settings\n";
    cout << "/gamble - Gamble your money for a chance to win (Includes tax)\n";
    cout << "/taxes - Pay your taxes\n";
    cout << "/childsupport - Pay your child support\n";
    cout << "/exit - Exit game\n";
    cout << "/clear - clears all text (keeps commands)\n\n";
}

void LoadSettings(string& autoload, string& autosave, const string& settingsFilePath) {
    string fontsize = "";
    ifstream settingsFile(settingsFilePath);
    if (settingsFile.is_open()) {
        getline(settingsFile, autoload);
        getline(settingsFile, autosave);
        getline(settingsFile, fontsize);

        try {
            fontSize = stoi(fontsize);
        }
        catch (const invalid_argument& e) {
            fontSize = 3;
        }
    }
    else {
        autoload = "off";
        autosave = "off";
        fontSize = 3;
        cout << "Settings file could not be loaded. Using default settings.\n";
    }
}
void SaveSettings(const string& autoload, const string& autosave, const string& settingsFilePath) {
    ofstream settingsFile(settingsFilePath, ios::out | ios::trunc);
    if (settingsFile.is_open()) {
        settingsFile << autoload << "\n";
        settingsFile << autosave << "\n";
        settingsFile << fontSize << "\n";
    }
    else {
        cout << "Error saving settings.\n";
    }
}

void ResetSettings(const string& settingsFilePath) {
    ofstream settingsFile(settingsFilePath, ios::out | ios::trunc);
    if (settingsFile.is_open()) {
        settingsFile << "off\n";
        settingsFile << "off\n";
        settingsFile << "3\n";
        cout << "Settings reset to default values.\n";
    }
    else {
        cout << "Error resetting settings.\n";
    }
}

void Settings(string& autoload, string& autosave, const string& settingsFilePath) {
    while (true) {
        cout << "Settings:\n";
        cout << "1 = Autoload save data: " << autoload << "\n";
        cout << "2 = Autosave save data: " << autosave << "\n";
        cout << "3 = Change Font Size (Current size: " << fontSize << ")\n";
        cout << "4 = Reset settings\n";
        cout << "5 = Exit settings\n";
        cout << "Enter your choice (number ex: 1, 2, 3, 4, 5): ";

        int choice = getValidInt();
        if (choice == 1) {
            cout << "Toggle Autoload save data (on/off): ";
            cin >> autoload;
        }
        else if (choice == 2) {
            cout << "Toggle Autosave save data (on/off): ";
            cin >> autosave;
        }
        else if (choice == 3) {
            cout << "Enter new font size (1 is for small, 2 is for medium, and 3 is for large): ";
            fontSize = getValidInt();
            SetFontSize(fontSize);
        }
        else if (choice == 4) {
            ResetSettings(settingsFilePath);
            autoload = "off";
            autosave = "off";
        }
        else if (choice == 5) {
            SaveSettings(autoload, autosave, settingsFilePath);
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void HandleSupport() {
    cout << "Game by Reapermen, contact zxteam27@gmail.com for any support or suggestions...\n";
}

void HandleTransaction(int& money, int& points) {
    while (true) {
        cout << "How much money would you like to convert into points? (Current money: " << money << "): ";
        int convertAmount = getValidInt();

        if (convertAmount <= 0) {
            cout << "Invalid input. Please enter a positive number.\n";
        }
        else if (convertAmount > money) {
            cout << "You do not have enough money. You only have " << money << ".\n";
            cout << "Would you like to try again (y/n)? ";
            string response;
            cin >> response;
            if (response != "y" || response != "Y") break;
        }
        else {
            points += convertAmount;
            money -= convertAmount;
            cout << "Your points increased by " << convertAmount << ", and your money decreased by " << convertAmount << ".\n";
            double tax = convertAmount / 4;
            tax = ceil(tax);
            taxamount += static_cast<int>(tax);
            AchievementReachedCheck(money, points);
            break;
        }
    }
}

void HandlePlayAGame(int& money, int& points, mt19937& gen) {
    uniform_int_distribution<int> dist(1, 100);

    while (true) {
        int randomNum1 = dist(gen);
        int randomNum2 = dist(gen);
        int correctAnswer;
        string operation;

        cout << "Choose operation (add/subtract). Adding gives 3 points/money, subtracting gives 5 points/money: ";
        cin >> operation;

        if (operation == "add") {
            cout << "What is " << randomNum1 << " + " << randomNum2 << "? ";
            correctAnswer = randomNum1 + randomNum2;
        }
        else if (operation == "subtract") {
            cout << "What is " << randomNum1 << " - " << randomNum2 << "? ";
            correctAnswer = randomNum1 - randomNum2;
        }
        else {
            cout << "Invalid operation. Please choose 'add' or 'subtract'.\n";
            continue;
        }

        int playerAnswer = getValidInt();
        if (playerAnswer == correctAnswer) {
            int reward = (operation == "add") ? 3 : 5;
            money += reward;
            points += reward;
            cout << "Correct! Your money and points increased by " << reward << ".\n";
            double tax = reward / 3;
            tax = ceil(tax);
            taxamount += static_cast<int>(tax);
            csamount += 1;
            AchievementReachedCheck(money, points);
            break;
        }
        else {
            cout << "Wrong answer! Would you like to try again (y/n)? ";
            string retry;
            cin >> retry;
            if (retry != "y" || retry != "Y") break;
        }
    }
}

void HandleSave(const string& saveFilePath, int money, int points, bool notify) {
    ofstream saveFile(saveFilePath, ios::out | ios::trunc);
    if (saveFile.is_open()) {
        saveFile << money << "\n" << points << "\n" << taxamount << "\n" << secretonefound << "\n" << secrettwofound << "\n" << csamount << "\n" << inprison << endl;
        if (notify == true)
        {
            cout << "Game saved!\n";
        }
    }
    else {
        cout << "Error saving game.\n";
    }
}

void HandleLoad(const string& saveFilePath, int& money, int& points) {
    ifstream loadFile(saveFilePath);
    if (loadFile.is_open()) {
        string line;
        if (getline(loadFile, line)) money = stoi(line);
        if (getline(loadFile, line)) points = stoi(line);
        if (getline(loadFile, line)) taxamount = stoi(line);
        if (getline(loadFile, line)) secretonefound = stoi(line);
        if (getline(loadFile, line)) secrettwofound = stoi(line);
        if (getline(loadFile, line)) csamount = stoi(line);

        cout << "Game loaded! (Money: " << money << "), (Points: " << points << "), (Taxes needed to pay: " << taxamount << "), (Child support you owe: " << csamount << ")\n" << inprison;
    }
    else {
        cout << "No saved game found.\n";
    }
}

void HandleExit() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    int hour = ltm.tm_hour;
    cout << "Exiting game! " << (hour >= 6 && hour < 18 ? "Have a good day!" : "Have a good night!") << "\n";
    AchievementReachedCheck(money, points);
}

void HandlePoints(int points) {
    cout << "Current points: " << points << endl;
    AchievementReachedCheck(money, points);
}

void HandleMoney(int money) {
    cout << "Current money: " << money << endl;
    AchievementReachedCheck(money, points);
}

void HandleGamble(int& money) {
    if (money <= 0) {
        cout << "You don't have enough money to gamble.\n";
        return;
    }

    cout << "How much money would you like to gamble? (Current money: " << money << "): ";
    int gambleAmount = getValidInt();

    if (gambleAmount <= 0) {
        cout << "Invalid amount. Please enter a positive number.\n";
        return;
    }
    else if (gambleAmount > money) {
        cout << "You don't have enough money to gamble that amount.\n";
        return;
    }

    uniform_int_distribution<int> dist(1, 100);
    uniform_real_distribution<double> dist2(1, 2.5);
    random_device rd;
    mt19937 gen(rd());
    int chance = dist(gen);
    double chance2 = dist2(gen);

    if (chance <= 66) {
        int winnings = gambleAmount * chance2;
        winnings = ceil(winnings);
        money += static_cast<int>(winnings);
        cout << "You won! You gained " << winnings << " money.\n";
        double tax = winnings / 3;
        tax = ceil(tax);
        taxamount += static_cast<int>(tax);
        csamount += 1;
        AchievementReachedCheck(money, points);
    }
    else {
        money -= gambleAmount;
        cout << "You lost! You lost " << gambleAmount << " money.\n";
    }
}

void HandleTaxes(int& money, int& taxamount) {
    if (taxamount <= 0) {
        cout << "You don't owe any taxes right now.\n";
        return;
    }

    string response;

    do {
        cout << "You owe: " << taxamount << " in taxes." << endl;
        cout << "Would you like to pay the taxes (y/n)? ";
        cin >> response;

        if (response == "y" || response == "Y") {
            while (taxamount > 0) {
                cout << "How much money would you like to pay for your taxes? (Current money: " << money << ", Remaining taxes: " << taxamount << "): ";
                int payment = getValidInt();

                if (payment > money) {
                    cout << "You do not have enough money to pay this amount. You only have " << money << ".\n";
                }
                else if (payment > taxamount) {
                    cout << "You only owe " << taxamount << " in taxes. Enter a smaller amount.\n";
                }
                else if (payment <= 0) {
                    cout << "Invalid input. Please enter a positive number.\n";
                }
                else {
                    money -= payment;
                    taxamount -= payment;
                    cout << "You paid " << payment << " in taxes. Your remaining balance is " << money << ".\n";

                    if (taxamount <= 0) {
                        cout << "You have fully paid your taxes.\n";
                        return;
                    }

                    cout << "Remaining taxes: " << taxamount << ". Would you like to continue paying? (y/n): ";
                    cin >> response;

                    if (response != "y" && response != "Y") {
                        cout << "You chose not to pay any more taxes. Remaining taxes: " << taxamount << ".\n";
                        return;
                    }
                }
            }
        }
        else if (response != "n" && response != "N") {
            cout << "Invalid input. Please respond with 'y' or 'n'.\n";
        }

    } while (response != "n" && response != "N");

    if (response == "n" || response == "N") {
        cout << "You chose not to pay taxes. The tax amount remains the same.\n";
    }
}

void ChildSupport(int& money, int& childsupportamount)
{
    if (childsupportamount <= 0) {
        cout << "You don't owe child support.\n";
        return;
    }

    string response;

    do {
        cout << "You owe: " << childsupportamount << " in child support." << endl;
        cout << "Would you like to pay child support (y/n)? ";
        cin >> response;

        if (response == "y" || response == "Y") {
            if (money >= childsupportamount) {
                money -= childsupportamount;
                childsupportamount = 0;
                cout << "Child support fully paid. Remaining money: " << money << "\n";
            }
            else {
                cout << "You do not have enough money to pay the full child support.\n";
                cout << "Paying what you can: " << money << "\n";
                childsupportamount -= money;
                money = 0;
                cout << "Remaining child support amount: " << childsupportamount << "\n";
            }
        }
        else if (response != "n" && response != "N") {
            cout << "Invalid input. Please respond with 'y' or 'n'.\n";
        }

    } while (response != "n" && response != "N" && childsupportamount > 0);

    if (childsupportamount > 0) {
        cout << "You still owe " << childsupportamount << " in child support. Please pay soon.\n";
    }
    else {
        cout << "Child support is fully paid. Thank you!\n";
    }
}

void OutOfPrison()
{
    cout << "YOU ARE OUT OF PRISON!!!";
    HandleSupport();

    if (system(("mkdir " + folderPath).c_str())) {}

    random_device rd;
    mt19937 gen(rd());

    string autoload, autosave;
    LoadSettings(autoload, autosave, settingsFilePath);
    SetFontSize(fontSize);

    if (autoload == "on") {
        HandleLoad(saveFilePath, money, points);
    }
    LoadAchievements();
    AchievementReachedCheck(money, points);
    DisplayCommands();
}

void Prison()
{
    csamount = 0;
    inprison = true;
    HandleSave(saveFilePath, money, points, true);
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    HandleSupport();
    SetFontSize(fontSize);
    inprison = true;
    string options;
    cout << "\nYou are in prison for not paying your child support" << endl;
    Prisonlist:
    cout << "\nYour options are:\n";
    cout << "1. Math (Medium but free)\n\n";
    cout << "2. Bribery (Easy but costs money)\n\n";
    cout << "3. Prisonbreak (Hard but free)\n\n";

    cin >> options;

    if (options == "Bribery")
    {
        if (money <= 0) {
            cout << "You don't have enough money to bribe.\n";
            return;
        }

        cout << "How much money would you like to bribe? (Current money: " << money << ") the higher the better chance: ";
        int bribeAmount = getValidInt();

        if (bribeAmount <= 0) {
            cout << "Invalid amount. Please enter a positive number.\n";
            return;
        }
        else if (bribeAmount > money) {
            cout << "You don't have enough money to bribe that amount.\n";
            return;
        }

        uniform_int_distribution<int> dist(1, 100);
        random_device rd;
        mt19937 gen(rd());
        int chance = dist(gen);

        if (chance <= pow(bribeAmount, 0.75f)) {
            cout << "You lost " << bribeAmount << " money.\n";
            OutOfPrison();
        }
        else
        {
            cout << "Your bribe was declined...";
            goto Prisonlist;
        }
    }
        else if (options == "Prisonbreak")
        {
            uniform_int_distribution<int> dist(1, 100);
            random_device rd;
            mt19937 gen(rd());
            int chance = dist(gen);
            if (chance <= 10)
            {
                OutOfPrison();
            }
            else
            {
                cout << "You failed to escape...";
                goto Prisonlist;
            }

        }
        else if (options == "Math")
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(100, 1000);

            while (true) {
                int randomNum1 = dist(gen);
                int randomNum2 = dist(gen);
                int correctAnswer;
                string operation;

                cout << "Choose operation (add/subtract) numbers are generated randon from 100 to 1000: ";
                cin >> operation;

                if (operation == "add") {
                    cout << "What is " << randomNum1 << " + " << randomNum2 << "? ";
                    correctAnswer = randomNum1 + randomNum2;
                }
                else if (operation == "subtract") {
                    cout << "What is " << randomNum1 << " - " << randomNum2 << "? ";
                    correctAnswer = randomNum1 - randomNum2;
                }
                else {
                    cout << "Invalid operation. Please choose 'add' or 'subtract'.\n";
                    continue;
                }

                int playerAnswer = getValidInt();
                if (playerAnswer == correctAnswer) {
                    OutOfPrison();
                    break;
                }
                else {
                    cout << "Wrong answer! Would you like to try again (y/n)? ";
                    string retry;
                    cin >> retry;
                    if (retry != "y" || retry != "Y") break;
                }
            }
        }
        else {
            if (options != "Options")
            {
                cout << "Invalid response\n";
                goto Prisonlist;
            }
        }   
    
}

int main() {
    system("title Reaper's Cool Game");

    HandleSupport();

    if (system(("mkdir " + folderPath).c_str())) {}

    random_device rd;
    mt19937 gen(rd());

    string autoload, autosave;
    LoadSettings(autoload, autosave, settingsFilePath);
    SetFontSize(fontSize);

    if (autoload == "on") {
        HandleLoad(saveFilePath, money, points);
    }
    LoadAchievements();
    AchievementReachedCheck(money, points);
    DisplayCommands();

    while (true) {
        if (!inprison)
        {
            if (csamount == 15)
            {
                Prison();
            }
            string command;
            cin >> command;
            if (command == "/help") DisplayCommands();

            else if (command == "/achievements")
            {
                DisplayAchievements();
            }
            else if (command == "/support") HandleSupport();
            else if (command == "/transaction") HandleTransaction(money, points);
            else if (command == "/playagame") HandlePlayAGame(money, points, gen);
            else if (command == "/save") HandleSave(saveFilePath, money, points, true);
            else if (command == "/load") HandleLoad(saveFilePath, money, points);
            else if (command == "/settings") Settings(autoload, autosave, settingsFilePath);
            else if (command == "/gamble") HandleGamble(money);
            else if (command == "/taxes") HandleTaxes(money, taxamount);
            else if (command == "/childsupport") ChildSupport(money, csamount);
            else if (command == "/exit") {
                if (autosave == "on") {
                    HandleSave(saveFilePath, money, points, true);
                }
                HandleExit();
                string response;
                cout << "Confirm (y/n)?";
                cin >> response;
                if (response == "y" || response == "Y")
                {
                    break;
                }
                else
                {
                    return 0;
                }
            }
            else if (command == "/clear")
            {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                HandleSupport();
                LoadSettings(autoload, autosave, settingsFilePath);
                SetFontSize(fontSize);
                if (autoload == "on") {
                    HandleLoad(saveFilePath, money, points);
                }
                DisplayCommands();
            }
            else if (command == "/points") HandlePoints(points);
            else if (command == "/money") HandleMoney(money);

            else if (command == "/reaper")
            {
                if (secretonefound == false)
                {
                    cout << "Guh, I guess you have found me\nI will give you 100 money, i paid the taxes for you btw and np.\n";
                    money += 100;
                    secretonefound = true;
                    AchievementReachedCheck(money, points);
                }
                else {
                    cout << "Bro STOP BEGGING ME FOR MONEY PLEASE BRUH...\n";
                    begging = true;
                    AchievementReachedCheck(money, points);
                }
            }
            else if (command == "/kys")
            {
                if (secrettwofound == false)
                {
                    cout << "Did you just tell me to keep myself safe??? I am stealing your money\n";
                    double moneystolen = money / 3;
                    moneystolen = ceil(moneystolen);
                    money -= static_cast<int>(moneystolen);
                    cout << "reaper just stole " << moneystolen << " money from you\n";
                    secrettwofound = true;
                    AchievementReachedCheck(money, points);
                }
                else {
                    cout << "Odd specimen\n";
                }
            }
            else {
                cout << "Invalid command. Type /help for available commands.\n";
            }

            if (autosave == "on") {
                HandleSave(saveFilePath, money, points, false);
            }
        }
    }
    return 0;
}