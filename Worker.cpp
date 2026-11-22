
#include "Worker.h"
#include <ctime>
#include <stdexcept>

namespace {
    // Определение текущего года
    int actualYear() {
        std::time_t now = std::time(nullptr);
        std::tm local = {};

#ifdef _WIN32
        if (localtime_s(&local, &now) != 0)
            throw std::runtime_error(
                "Failed to determine current year.");
#else
        if (localtime_r(&now, &local) == nullptr)
            throw std::runtime_error(
                "Failed to determine current year.");
#endif

        return local.tm_year + 1900;
    }

    // Проверка строкового поля на пустое значение
    void requireNonempty(const std::string& text,
        const char* fieldName) {
        if (text.find_first_not_of(" \t\r\n")
            == std::string::npos) {
            throw std::invalid_argument(
                std::string(fieldName) +
                " cannot be empty.");
        }
    }
}

// Конструктор по умолчанию
Worker::Worker()
    : fullName_("Not specified"),
    position_("Not specified"),
    hireYear_(actualYear()) {

    std::cout << "[WORKER] Default constructor: "
        << fullName_ << '\n';
}

// Конструктор с параметрами
Worker::Worker(const std::string& fullName,
    const std::string& position,
    int hireYear)
    : fullName_("Not specified"),
    position_("Not specified"),
    hireYear_(actualYear()) {

    setFullName(fullName);
    setPosition(position);
    setHireYear(hireYear);

    std::cout << "[WORKER] Parameterized constructor: "
        << fullName_ << '\n';
}

// Конструктор копирования
Worker::Worker(const Worker& other)
    : fullName_(other.fullName_),
    position_(other.position_),
    hireYear_(other.hireYear_) {

    std::cout << "[WORKER] Copy constructor: "
        << fullName_ << '\n';
}

// Перегрузка оператора присваивания
Worker& Worker::operator=(const Worker& other) {
    if (this != &other) {
        fullName_ = other.fullName_;
        position_ = other.position_;
        hireYear_ = other.hireYear_;
    }
    return *this;
}

// Деструктор объекта работника
Worker::~Worker() {
    std::cout << "[WORKER] Destructor: "
        << fullName_ << '\n';
}

// Методы получения данных работника
const std::string& Worker::getFullName() const {
    return fullName_;
}

const std::string& Worker::getPosition() const {
    return position_;
}

int Worker::getHireYear() const {
    return hireYear_;
}

// Получение фамилии из полного имени
std::string Worker::getSurname() const {
    std::size_t begin =
        fullName_.find_first_not_of(" \t");

    if (begin == std::string::npos)
        return "";

    std::size_t end =
        fullName_.find_first_of(" \t", begin);

    return fullName_.substr(
        begin,
        end == std::string::npos
        ? end : end - begin);
}

// Вычисление стажа работника
int Worker::getExperience(int currentYear) const {
    if (currentYear < hireYear_) {
        throw std::invalid_argument(
            "Current year is earlier than hire year.");
    }

    return currentYear - hireYear_;
}

// Установка ФИО работника
void Worker::setFullName(const std::string& fullName) {
    requireNonempty(fullName, "Full name");
    fullName_ = fullName;
}

// Установка должности работника
void Worker::setPosition(const std::string& position) {
    requireNonempty(position, "Position");
    position_ = position;
}

// Установка года поступления на работу
void Worker::setHireYear(int hireYear) {
    if (hireYear < 1900 || hireYear > actualYear()) {
        throw std::out_of_range(
            "Hire year must be between 1900 "
            "and the current year.");
    }

    hireYear_ = hireYear;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in,
    Worker& worker) {
    std::string fullName;
    std::string position;
    int hireYear;

    std::cout << "Full name (surname first): ";
    if (!std::getline(in >> std::ws, fullName))
        return in;

    std::cout << "Position: ";
    if (!std::getline(in, position))
        return in;

    std::cout << "Hire year: ";
    if (!(in >> hireYear))
        return in;

    // Создание и присваивание проверенного объекта
    Worker checked(fullName, position, hireYear);
    worker = checked;

    return in;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out,
    const Worker& worker) {
    out << "Full name: " << worker.fullName_
        << " | Position: " << worker.position_
        << " | Hire year: " << worker.hireYear_;

    return out;
}