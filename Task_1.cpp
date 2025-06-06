#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int secretNumber = std::rand() % 100 + 1;
    int guess;

    std::cout << "Guess the number (between 1 and 100): ";

    while (true) {
        std::cin >> guess;

        if (guess > secretNumber) {
            std::cout << "Too high! Try again: ";
        } else if (guess < secretNumber) {
            std::cout << "Too low! Try again: ";
        } else {
            std::cout << "Congratulations! You guessed the correct number: " << secretNumber << std::endl;
            break;
        }
    }

    return 0;
}
