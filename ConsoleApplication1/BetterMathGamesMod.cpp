#include "BetterMathGamesMod.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Defaults.h"

#undef max;
BetterMathGamesMod::BetterMathGamesMod() { CheckEnable(def.modSet2); }

void BetterMathGamesMod::ModifyAttributes() {
    if (!modEnabled) {
        std::cout << "[Mod Disabled]\n";
        return;
    }
}
void BetterMathGamesMod::CommandList()
{
    if (modEnabled) {
        std::cout << "\033[A\33[2K\r";
        std::cout << "/playmath [BetterMathGamesMod]\n\n";
    }
}

bool BetterMathGamesMod::CommandUsed()
{
     if (def.command == "/playmath")
     {
        Load();
        return true;
     }
     else return false;
}
double CalculateTriangleArea(double base, double height) {
    return 0.5 * base * height;
}

double CalculateSquareArea(double side) {
    return side * side;
}

double FindMissingSide(double sideA, double sideB) {
    return sqrt(sideA * sideA + sideB * sideB);
}

void ArithmeticOperations(int minRandom, int maxRandom) {
    int num1 = rand() % (maxRandom - minRandom + 1) + minRandom;
    int num2 = rand() % (maxRandom - minRandom + 1) + minRandom;

    std::cout << "Choose an operation:\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Division\n";
    std::cout << "Enter your choice (1-4): ";

    int operationChoice;
    std::cin >> operationChoice;

    while (std::cin.fail() || operationChoice < 1 || operationChoice > 4) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice! Please select between 1-4: ";
        std::cin >> operationChoice;
    }

    double correctAnswer{};
    switch (operationChoice) {
    case 1:
        correctAnswer = num1 + num2;
        std::cout << "What is " << num1 << " + " << num2 << "? ";
        break;
    case 2:
        correctAnswer = num1 - num2;
        std::cout << "What is " << num1 << " - " << num2 << "? ";
        break;
    case 3:
        correctAnswer = num1 * num2;
        std::cout << "What is " << num1 << " * " << num2 << "? ";
        break;
    case 4:
        if (num2 != 0) {
            correctAnswer = static_cast<double>(num1) / num2;
            std::cout << "What is " << num1 << " / " << num2 << "? ";
        }
        else {
            std::cout << "Division by zero is not allowed! Please try again." << std::endl;
            return;
        }
        break;
    }

    double userAnswer;
    std::cin >> userAnswer;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a number: ";
        std::cin >> userAnswer;
    }

    if (std::abs(userAnswer - correctAnswer) < 0.01) {
        std::cout << "Correct! The answer is indeed " << correctAnswer << ".\n";
        def.money += abs(ceil(num2 / 4)) + 1;
        std::cout << "Your money increased by " << ceil(1 + (num2/4)) << std::endl;
        double tax = abs(ceil(num2 / 8));
        def.taxamount += static_cast<int>(tax);
        def.csamount += 1;
    }
    else {
        std::cout << "Incorrect. The correct answer is " << correctAnswer << ".\n";
    }
}

void PlayGame() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        int choice;
        std::cout << "Select an option:\n";
        std::cout << "1. Find the area of a triangle\n";
        std::cout << "2. Find the area of a square\n";
        std::cout << "3. Solve for a side of a right triangle\n";
        std::cout << "4. Perform arithmetic operations\n";
        std::cout << "5. Exit Math Game\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        while (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice! Please select between 1-4: ";
            std::cin >> choice;
        }

        switch (choice) {
        case 1: {
            double base = rand() % 100 + 1;
            double height = rand() % 100 + 1;

            double area = CalculateTriangleArea(base, height);

            std::cout << "Given a triangle with base = " << base << " and height = " << height << ", what is the area?\n";
            double userArea;
            std::cin >> userArea;

            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number: ";
                std::cin >> userArea;
            }

            if (std::abs(userArea - area) < 0.01) {
                std::cout << "Correct! The area of the triangle is indeed " << area << ".\n";
                def.money += abs(ceil(area / 4)) + 1;
                std::cout << "Your money increased by " << abs(ceil(1 + (area / 4))) + 1 << std::endl;
                double tax = abs(ceil(area / 9));
                def.taxamount += static_cast<int>(tax);
                def.csamount += 1;
            }
            else {
                std::cout << "Incorrect. The correct area is " << area << ".\n";
            }
            break;
        }
        case 2: {
            double side = rand() % 100 + 1;

            double area = CalculateSquareArea(side);

            std::cout << "Given a square with side length = " << side << ", what is the area?\n";
            double userArea;
            std::cin >> userArea;

            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number: ";
                std::cin >> userArea;
            }

            if (std::abs(userArea - area) < 0.01) {
                std::cout << "Correct! The area of the square is indeed " << area << ".\n";
                def.money += abs(ceil(area / 3));
                std::cout << "Your money increased by " << abs(ceil(1 + (area / 3))) + 1 << std::endl;
                double tax = abs(ceil(area / 8));
                def.taxamount += static_cast<int>(tax);
                def.csamount += 1;
            }
            else {
                std::cout << "Incorrect. The correct area is " << area << ".\n";
            }
            break;
        }
        case 3: {
            double sideA = rand() % 20 + 1;
            double sideB = rand() % 20 + 1;

            double hypotenuse = FindMissingSide(sideA, sideB);

            std::cout << "If side A = " << sideA << " and side B = " << sideB << ", what is the value of the hypotenuse C (rounded to 2 decimal places)?\n";
            double userHypotenuse;
            std::cin >> userHypotenuse;

            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number: ";
                std::cin >> userHypotenuse;
            }

            if (std::abs(userHypotenuse - hypotenuse) < 0.01) {
                std::cout << "Correct! The hypotenuse is indeed " << hypotenuse << ".\n";
                def.money += abs(ceil(hypotenuse * 2.5)) + 1;
                std::cout << "Your money increased by " << abs(ceil(1 + (hypotenuse * 2.5))) + 1 << std::endl;
                double tax = abs(ceil(hypotenuse));
                def.taxamount += static_cast<int>(tax);
                def.csamount += 1;
            }
            else {
                std::cout << "Incorrect. The correct hypotenuse is " << hypotenuse << ".\n";
            }
            break;
        }
        case 4: {
            int minRandom, maxRandom;
            std::cout << "Enter the minimum random number: ";
            std::cin >> minRandom;
            std::cout << "Enter the maximum random number: ";
            std::cin >> maxRandom;

            if (minRandom >= maxRandom) {
                std::cout << "Invalid range. Minimum must be less than maximum." << std::endl;
                break;
            }

            ArithmeticOperations(minRandom, maxRandom);
            break;
        }
        case 5: break;

        default:
            std::cout << "Invalid choice! Please select between 1-4." << std::endl;
            break;
        }

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;

        while (std::cin.fail() || (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter 'y' or 'n': ";
            std::cin >> playAgain;
        }
    }
}

void BetterMathGamesMod::Load()
{
    PlayGame();
}

void BetterMathGamesMod::ModDescription()
{
    std::string nextLine[] = {
        "This mod adds a new command called /playmath\n",
        "Adds Find the Area of a triangle\n",
        "Adds Find the Area of a square\n",
        "Adds Find the missing side of a triangle\n",
        "Adds more and better arithmetic equations\n"
    };

    for (const auto& line : nextLine)
    {
        std::cout << line << std::endl;
    }
}

void BetterMathGamesMod::InitializeMod() {
    if (modEnabled) {
        std::cout << "[BetterMathGamesMod] Mod Initialized!\n";
        EnsureSaveDirectory(false);
        HandleLoad();
        ModifyAttributes();
        HandleSave();
    }
}