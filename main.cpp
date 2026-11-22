
#define NOMINMAX

#include "WorkerList.h"
#include "TextProcessor.h"

#include <ctime>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {

    // Определение текущего года
    int currentYear() {
        std::time_t now = std::time(nullptr);
        std::tm local = {};

#ifdef _WIN32
        if (localtime_s(&local, &now) != 0) {
            throw std::runtime_error(
                "Failed to determine current year.");
        }
#else
        if (localtime_r(&now, &local) == nullptr) {
            throw std::runtime_error(
                "Failed to determine current year.");
        }
#endif

        return local.tm_year + 1900;
    }

    // Очистка входного потока
    void clearInput() {
        std::cin.ignore(
            (std::numeric_limits<std::streamsize>::max)(),
            '\n');
    }

    // Ввод целого числа с проверкой корректности
    int readInt(const std::string& prompt) {
        int number;

        std::cout << prompt;

        if (!(std::cin >> number)) {
            if (std::cin.eof()) {
                throw std::runtime_error(
                    "Input ended.");
            }

            std::cin.clear();
            clearInput();

            throw std::invalid_argument(
                "Please enter a valid integer.");
        }

        clearInput();
        return number;
    }

    // Создание работника с вводом данных
    Worker readWorker() {
        Worker worker;

        if (!(std::cin >> worker)) {
            if (std::cin.eof()) {
                throw std::runtime_error(
                    "Input ended.");
            }

            std::cin.clear();
            clearInput();

            throw std::invalid_argument(
                "Failed to read worker data.");
        }

        clearInput();
        return worker;
    }

    // Отображение пользовательского меню
    void showMenu() {
        std::cout
            << "\n1. Add Worker\n"
            << "2. Display All Workers\n"
            << "3. Edit Worker\n"
            << "4. Delete Worker\n"
            << "5. Search Workers by Experience\n"
            << "6. Display Sentences Without Commas\n"
            << "7. Clear Worker List\n"
            << "0. Exit\n";
    }

}

int main() {

    // Создание списка работников и обработчика текста
    WorkerList workers;
    TextProcessor processor;

    // Главный цикл работы программы
    while (true) {

        // Обработка ошибок и исключительных ситуаций
        try {
            showMenu();

            int choice = readInt(
                "Choose an option: ");

            // Завершение программы
            if (choice == 0) {
                break;
            }

            // Выполнение выбранного действия
            switch (choice) {

                // Добавление нового работника
            case 1: {
                int pos = readInt(
                    "Enter insertion position: ");

                if (pos < 1 ||
                    static_cast<std::size_t>(pos)
                > workers.size() + 1) {

                    throw std::out_of_range(
                        "Invalid insertion position.");
                }

                Worker worker = readWorker();

                workers.insert(
                    static_cast<std::size_t>(pos - 1),
                    worker);

                std::cout
                    << "\nWorker added successfully.\n"
                    << "List sorted alphabetically.\n";

                break;
            }

                  // Вывод всех работников
            case 2: {
                std::cout
                    << "\nWORKER LIST:\n";

                workers.printAll();
                break;
            }

                  // Редактирование работника
            case 3: {
                workers.printAll();

                int pos = readInt(
                    "Enter worker number to edit: ");

                if (pos < 1 ||
                    static_cast<std::size_t>(pos)
                > workers.size()) {

                    throw std::out_of_range(
                        "Worker not found.");
                }

                Worker worker = readWorker();

                workers.edit(
                    static_cast<std::size_t>(pos - 1),
                    worker);

                std::cout
                    << "\nWorker updated successfully.\n";

                break;
            }

                  // Удаление работника
            case 4: {
                workers.printAll();

                int pos = readInt(
                    "Enter worker number to delete: ");

                if (pos < 1 ||
                    static_cast<std::size_t>(pos)
                > workers.size()) {

                    throw std::out_of_range(
                        "Worker not found.");
                }

                workers.remove(
                    static_cast<std::size_t>(pos - 1));

                std::cout
                    << "\nWorker deleted successfully.\n";

                break;
            }

                  // Поиск работников по стажу
            case 5: {
                int years = readInt(
                    "Enter minimum experience (years): ");

                std::cout
                    << "\nWorkers with experience over "
                    << years << " years:\n";

                workers.printWithExperienceGreaterThan(
                    years, currentYear());

                break;
            }

                  // Обработка предложений из текстового файла
            case 6: {
                std::string path;

                std::cout
                    << "Enter text file path: ";

                std::getline(std::cin, path);

                if (path.empty()) {
                    throw std::invalid_argument(
                        "File path cannot be empty.");
                }

                processor.printSentencesWithoutCommas(path);
                break;
            }

                  // Очистка списка работников
            case 7: {
                workers.clear();

                std::cout
                    << "\nWorker list cleared.\n";

                break;
            }

                  // Обработка неверного пункта меню
            default: {
                std::cout
                    << "\nInvalid menu option.\n";

                break;
            }
            }
        }

        // Перехват и вывод исключений
        catch (const std::exception& ex) {
            std::cerr
                << "\nError: "
                << ex.what() << '\n';

            if (std::cin.eof()) {
                break;
            }
        }
    }

    // Завершение работы программы
    std::cout
        << "\nProgram terminated.\n";

    return 0;
}