
#include "WorkerList.h"
#include <iostream>
#include <stdexcept>
#include <utility>

// Конструктор узла списка
WorkerList::Node::Node(
    const Worker& worker, Node* nextNode)
    : data(worker), next(nextNode) {
}

// Конструктор пустого списка
WorkerList::WorkerList()
    : head_(nullptr), size_(0) {
    std::cout
        << "[WorkerList] Default constructor\n";
}

// Конструктор копирования списка
WorkerList::WorkerList(const WorkerList& other)
    : head_(nullptr), size_(0) {

    for (const Node* n = other.head_;
        n != nullptr; n = n->next) {
        insert(size_, n->data);
    }

    std::cout
        << "[WorkerList] Copy constructor\n";
}

// Перегрузка оператора присваивания
WorkerList& WorkerList::operator=(
    const WorkerList& other) {

    if (this != &other) {
        WorkerList copy(other);
        std::swap(head_, copy.head_);
        std::swap(size_, copy.size_);
    }

    return *this;
}

// Деструктор с очисткой динамической памяти
WorkerList::~WorkerList() {
    std::cout << "[WorkerList] Destructor\n";
    clear();
}

// Получение количества работников
std::size_t WorkerList::size() const {
    return size_;
}

// Поиск узла по индексу
WorkerList::Node* WorkerList::nodeAt(
    std::size_t index) {

    if (index >= size_) {
        throw std::out_of_range(
            "Worker with this index does not exist.");
    }

    Node* node = head_;

    for (std::size_t i = 0; i < index; ++i) {
        node = node->next;
    }

    return node;
}

// Получение узла без возможности изменения
const WorkerList::Node* WorkerList::nodeAt(
    std::size_t index) const {

    if (index >= size_) {
        throw std::out_of_range(
            "Worker with this index does not exist.");
    }

    const Node* node = head_;

    for (std::size_t i = 0; i < index; ++i) {
        node = node->next;
    }

    return node;
}

// Сортировка работников по алфавиту
void WorkerList::sortAlphabetically() {
    for (Node* a = head_; a != nullptr; a = a->next) {
        for (Node* b = a->next;
            b != nullptr; b = b->next) {

            if (b->data.getFullName()
                < a->data.getFullName()) {

                // Обмен данными работников
                Worker temp = a->data;
                a->data = b->data;
                b->data = temp;
            }
        }
    }
}

// Добавление работника на выбранную позицию
void WorkerList::insert(
    std::size_t index, const Worker& worker) {

    if (index > size_) {
        throw std::out_of_range(
            "Invalid insertion position.");
    }

    // Динамическое создание нового узла
    if (index == 0) {
        head_ = new Node(worker, head_);
    }
    else {
        Node* prev = nodeAt(index - 1);
        prev->next = new Node(worker, prev->next);
    }

    ++size_;
    sortAlphabetically();
}

// Редактирование работника
void WorkerList::edit(
    std::size_t index, const Worker& worker) {

    nodeAt(index)->data = worker;
    sortAlphabetically();
}

// Удаление работника по индексу
void WorkerList::remove(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range(
            "Invalid deletion position.");
    }

    Node* doomed;

    // Изменение связей списка
    if (index == 0) {
        doomed = head_;
        head_ = head_->next;
    }
    else {
        Node* prev = nodeAt(index - 1);
        doomed = prev->next;
        prev->next = doomed->next;
    }

    delete doomed;
    --size_;
}

// Полная очистка динамического списка
void WorkerList::clear() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }

    size_ = 0;
}

// Вывод всех работников
void WorkerList::printAll() const {
    if (size_ == 0) {
        std::cout << "Worker list is empty.\n";
        return;
    }

    std::size_t i = 1;

    for (const Node* n = head_;
        n != nullptr; n = n->next) {

        std::cout << i++ << ". "
            << n->data << '\n';
    }
}

// Поиск работников со стажем больше заданного
void WorkerList::printWithExperienceGreaterThan(
    int years, int currentYear) const {

    if (years < 0) {
        throw std::invalid_argument(
            "Experience cannot be negative.");
    }

    bool found = false;

    // Проверка стажа каждого работника
    for (const Node* n = head_;
        n != nullptr; n = n->next) {

        int experience =
            n->data.getExperience(currentYear);

        if (experience > years) {
            std::cout
                << n->data.getSurname()
                << " (experience: "
                << experience
                << " years)\n";

            found = true;
        }
    }

    // Сообщение об отсутствии подходящих работников
    if (!found) {
        std::cout
            << "No workers found with this experience.\n";
    }
}