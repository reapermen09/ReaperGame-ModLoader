#include "BetterMathGamesMod.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Defaults.h"

#undef max;
BetterMathGamesMod::BetterMathGamesMod() {
    cout << "[BetterMathGamesMod] Mod Initialized!\n";
    CheckEnable(def.modSet2);
}

void BetterMathGamesMod::ModifyAttributes() {
    if (!modEnabled) {
        cout << "[Mod Disabled]\n";
        return;
    }
}
void BetterMathGamesMod::CommandList()
{
    if (modEnabled) {
        cout << "\033[A\33[2K\r";
        cout << "/playmath (Better Math Games Mod)\n\n";
    }
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

    cout << "Random numbers generated: " << num1 << " and " << num2 << endl;

    cout << "Choose an operation:\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Division\n";
    cout << "Enter your choice (1-4): ";

    int operationChoice;
    cin >> operationChoice;

    while (cin.fail() || operationChoice < 1 || operationChoice > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice! Please select between 1-4: ";
        cin >> operationChoice;
    }

    double correctAnswer{};
    switch (operationChoice) {
    case 1:
        correctAnswer = num1 + num2;
        cout << "What is " << num1 << " + " << num2 << "? ";
        break;
    case 2:
        correctAnswer = num1 - num2;
        cout << "What is " << num1 << " - " << num2 << "? ";
        break;
    case 3:
        correctAnswer = num1 * num2;
        cout << "What is " << num1 << " * " << num2 << "? ";
        break;
    case 4:
        if (num2 != 0) {
            correctAnswer = static_cast<double>(num1) / num2;
            cout << "What is " << num1 << " / " << num2 << "? ";
        }
        else {
            cout << "Division by zero is not allowed! Please try again." << endl;
            return;
        }
        break;
    }

    double userAnswer;
    cin >> userAnswer;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
        cin >> userAnswer;
    }

    if (std::abs(userAnswer - correctAnswer) < 0.01) {
        cout << "Correct! The answer is indeed " << correctAnswer << ".\n";
        def.money += abs(ceil(num2 / 4));
        cout << "Your money increased by " << ceil(num2/4) << endl;
    }
    else {
        cout << "Incorrect. The correct answer is " << correctAnswer << ".\n";
    }
}

void PlayGame() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        int choice;
        cout << "Select an option:\n";
        cout << "1. Find the area of a triangle\n";
        cout << "2. Find the area of a square\n";
        cout << "3. Solve for a side of a right triangle\n";
        cout << "4. Perform arithmetic operations\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please select between 1-4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: {
            double base = rand() % 100 + 1;
            double height = rand() % 100 + 1;

            double area = CalculateTriangleArea(base, height);

            cout << "Given a triangle with base = " << base << " and height = " << height << ", what is the area?\n";
            double userArea;
            cin >> userArea;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number: ";
                cin >> userArea;
            }

            if (std::abs(userArea - area) < 0.01) {
                cout << "Correct! The area of the triangle is indeed " << area << ".\n";
                def.money += abs(ceil(area / 4));
                cout << "Your money increased by " << abs(ceil(area / 4)) << endl;
            }
            else {
                cout << "Incorrect. The correct area is " << area << ".\n";
            }
            break;
        }
        case 2: {
            double side = rand() % 100 + 1;

            double area = CalculateSquareArea(side);

            cout << "Given a square with side length = " << side << ", what is the area?\n";
            double userArea;
            cin >> userArea;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number: ";
                cin >> userArea;
            }

            if (std::abs(userArea - area) < 0.01) {
                cout << "Correct! The area of the square is indeed " << area << ".\n";
                def.money += abs(ceil(area / 3));
                cout << "Your money increased by " << abs(ceil(area / 3)) << endl;
            }
            else {
                cout << "Incorrect. The correct area is " << area << ".\n";
            }
            break;
        }
        case 3: {
            double sideA = rand() % 20 + 1;
            double sideB = rand() % 20 + 1;

            double hypotenuse = FindMissingSide(sideA, sideB);

            cout << "If side A = " << sideA << " and side B = " << sideB << ", what is the value of the hypotenuse C (rounded to 2 decimal places)?\n";
            double userHypotenuse;
            cin >> userHypotenuse;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number: ";
                cin >> userHypotenuse;
            }

            if (std::abs(userHypotenuse - hypotenuse) < 0.01) {
                cout << "Correct! The hypotenuse is indeed " << hypotenuse << ".\n";
                def.money += abs(ceil(hypotenuse * 2.5));
                cout << "Your money increased by " << abs(ceil(hypotenuse * 2.5)) << endl;
            }
            else {
                cout << "Incorrect. The correct hypotenuse is " << hypotenuse << ".\n";
            }
            break;
        }
        case 4: {
            int minRandom, maxRandom;
            cout << "Enter the minimum random number: ";
            cin >> minRandom;
            cout << "Enter the maximum random number: ";
            cin >> maxRandom;

            if (minRandom >= maxRandom) {
                cout << "Invalid range. Minimum must be less than maximum." << endl;
                break;
            }

            ArithmeticOperations(minRandom, maxRandom);
            break;
        }
        default:
            cout << "Invalid choice! Please select between 1-4." << endl;
            break;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        while (cin.fail() || (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 'y' or 'n': ";
            cin >> playAgain;
        }
    }
}

void BetterMathGamesMod::Load()
{
    PlayGame();
}

void BetterMathGamesMod::InitializeMod() {
    if (modEnabled) {
        cout << "[BetterMathGamesMod] Mod Initialized!\n";
        EnsureSaveDirectory(false);
        HandleLoad();
        ModifyAttributes();
        HandleSave();
    }
}