
#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <string>

// Класс для хранения информации о работнике
class Worker {
private:
    // Основные данные работника
    std::string fullName_;
    std::string position_;
    int hireYear_;

public:
    Worker();

    Worker(const std::string& fullName,
        const std::string& position,
        int hireYear);

    Worker(const Worker& other);

    Worker& operator=(const Worker& other);

    ~Worker();

    // Методы получения данных работника
    const std::string& getFullName() const;
    const std::string& getPosition() const;
    int getHireYear() const;
    std::string getSurname() const;
    int getExperience(int currentYear) const;

    // Методы изменения данных работника
    void setFullName(const std::string& fullName);
    void setPosition(const std::string& position);
    void setHireYear(int hireYear);

    // Перегрузка оператора ввода данных работника
    friend std::istream& operator>>(
        std::istream& in, Worker& worker);

    // Перегрузка оператора вывода информации о работнике
    friend std::ostream& operator<<(
        std::ostream& out, const Worker& worker);
};

#endif