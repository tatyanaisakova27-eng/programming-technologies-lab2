
#include "TextProcessor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
    // Проверка предложения на наличие непробельных символов
    bool hasVisibleText(const std::string& sentence) {
        return sentence.find_first_not_of(
            " \t\r\n") != std::string::npos;
    }

    // Проверка отсутствия запятых и вывод подходящего предложения
    bool outputIfSuitable(
        const std::string& sentence) {

        if (!hasVisibleText(sentence) ||
            sentence.find(',') != std::string::npos) {
            return false;
        }

        std::istringstream stream(sentence);
        std::string line;
        std::string result;

        // Удаление начальных пробелов и объединение строк предложения
        while (std::getline(stream, line)) {
            std::size_t start =
                line.find_first_not_of(" \t\r\n");

            if (start != std::string::npos) {
                if (!result.empty()) {
                    result += " ";
                }
                result += line.substr(start);
            }
        }

        if (result.empty()) {
            return false;
        }

        // Вывод предложения, прошедшего проверку
        std::cout << result << '\n';
        return true;
    }
}

// Конструктор по умолчанию
TextProcessor::TextProcessor() {
    std::cout
        << "[TextProcessor] Default constructor\n";
}

// Конструктор копирования
TextProcessor::TextProcessor(
    const TextProcessor& other) {

    std::cout
        << "[TextProcessor] Copy constructor\n";
}

// Перегрузка оператора присваивания
TextProcessor& TextProcessor::operator=(
    const TextProcessor& other) {

    return *this;
}

// Деструктор класса
TextProcessor::~TextProcessor() {
    std::cout
        << "[TextProcessor] Destructor\n";
}

// Чтение текстового файла и поиск предложений без запятых
void TextProcessor::printSentencesWithoutCommas(
    const std::string& fileName) const {

    std::ifstream input(fileName);

    // Проверка успешного открытия файла
    if (!input.is_open()) {
        throw std::runtime_error(
            "Failed to open file: " + fileName);
    }

    std::cout
        << "\nSentences without commas:\n";

    std::string sentence;
    char ch;
    std::size_t matched = 0;

    // Посимвольное чтение файла и разделение текста на предложения
    while (input.get(ch)) {
        sentence += ch;

        if (ch == '.' || ch == '!' || ch == '?') {
            if (outputIfSuitable(sentence)) {
                ++matched;
            }

            sentence.clear();
        }
    }

    // Проверка ошибок при чтении файла
    if (input.bad()) {
        throw std::runtime_error(
            "File reading error.");
    }

    // Обработка последнего предложения без завершающего знака
    if (outputIfSuitable(sentence)) {
        ++matched;
    }

    // Сообщение при отсутствии подходящих предложений
    if (matched == 0) {
        std::cout
            << "No sentences without commas found.\n";
    }
}