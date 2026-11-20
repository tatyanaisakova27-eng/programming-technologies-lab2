
#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>

// Класс для обработки текста из файла
class TextProcessor {
public:
    TextProcessor();
    TextProcessor(const TextProcessor& other);

    // Перегрузка оператора присваивания
    TextProcessor& operator=(
        const TextProcessor& other);

    ~TextProcessor();

    // Чтение файла и вывод предложений без запятых
    void printSentencesWithoutCommas(
        const std::string& fileName) const;
};

#endif