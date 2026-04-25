#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "Catalog.h"
#include "Library.h"
#include "SearchCriteria.h"
#include "Subscription.h"
#include "User.h"

std::string dateFromTime(std::time_t value) {
    std::tm localTime{};
    localtime_s(&localTime, &value);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
    return std::string(buffer);
}

std::string todayDate() {
    std::time_t now = std::time(nullptr);
    return dateFromTime(now);
}

std::string plusDaysDate(int days) {
    std::time_t now = std::time(nullptr);
    std::time_t shifted = now + static_cast<std::time_t>(days) * 24 * 60 * 60;
    return dateFromTime(shifted);
}

void printAllBooks(Catalog& catalog) {
    std::vector<Book*> books = catalog.allBooks();
    if (books.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        Book* book = books[i];
        std::cout << i + 1 << ". "
                  << book->getTitle() << " | "
                  << book->getAuthor() << " | "
                  << book->getGenre() << " | "
                  << book->getYear() << " | "
                  << (book->isAvailable() ? "доступна" : "занята")
                  << "\n";
    }
}

void searchBooks(Catalog& catalog) {
    std::cout << "Искать по (genre/author/title): ";
    std::string mode;
    std::getline(std::cin, mode);

    std::cout << "Введите значение: ";
    std::string value;
    std::getline(std::cin, value);

    SearchCriteria criteria;
    if (mode == "genre") {
        criteria.setGenre(value);
    } else if (mode == "author") {
        criteria.setAuthor(value);
    } else {
        criteria.setTitle(value);
    }

    std::vector<Book*> found = catalog.find(criteria);
    if (found.empty()) {
        std::cout << "Ничего не найдено.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(found.size()); ++i) {
        std::cout << found[i]->getTitle() << " | "
                  << found[i]->getAuthor() << " | "
                  << found[i]->getGenre() << " | "
                  << found[i]->getYear() << " | "
                  << (found[i]->isAvailable() ? "доступна" : "занята")
                  << "\n";
    }
}

void borrowBook(User* user, Library& library) {
    std::cout << "Введите название книги: ";
    std::string title;
    std::getline(std::cin, title);

    Book* book = library.getCatalog().findByTitle(title);
    if (book == nullptr) {
        std::cout << "Книга не найдена.\n";
        return;
    }

    std::string startDate = todayDate();
    std::string endDate = plusDaysDate(14);
    Loan* loan = user->borrowBookAndTrack(book, library.getFactory(), startDate, endDate);

    if (loan != nullptr) {
        std::cout << "Книга успешно выдана. Срок возврата: " << endDate << "\n";
    }
}

void returnBook(User* user, Library& library) {
    if (!user->hasActiveLoans()) {
        std::cout << "У вас нет активных выдач.\n";
        return;
    }

    std::cout << "Ваши активные выдачи:\n";
    user->printLoans();
    std::cout << "Введите номер выдачи для возврата: ";

    int index = 0;
    std::cin >> index;
    std::cin.ignore(10000, '\n');

    if (user->returnBookByIndex(index - 1, library.getFactory())) {
        std::cout << "Книга успешно возвращена.\n";
    } else {
        std::cout << "Неверный номер выдачи.\n";
    }
}

void leaveReview(User* user, Library& library) {
    std::cout << "Введите название книги: ";
    std::string title;
    std::getline(std::cin, title);

    Book* book = library.getCatalog().findByTitle(title);
    if (book == nullptr) {
        std::cout << "Книга не найдена.\n";
        return;
    }

    std::cout << "Введите текст отзыва: ";
    std::string text;
    std::getline(std::cin, text);

    std::cout << "Введите оценку (1-5): ";
    int score = 0;
    std::cin >> score;
    std::cin.ignore(10000, '\n');

    if (score < 1 || score > 5) {
        std::cout << "Оценка должна быть от 1 до 5.\n";
        return;
    }

    user->leaveReview(book, text, score, todayDate());
    std::cout << "Отзыв добавлен.\n";
}

User* selectOrCreateUser(Library& library, std::vector<User*>& createdUsers) {
    std::cout << "Введите имя пользователя: ";
    std::string userName;
    std::getline(std::cin, userName);

    User* user = library.findUserByName(userName);
    if (user == nullptr) {
        std::cout << "Пользователь не найден. Введите email для регистрации: ";
        std::string email;
        std::getline(std::cin, email);

        Subscription subscription("standard", 3, "2099-12-31");
        user = new User(userName, email, subscription);
        createdUsers.push_back(user);
        library.registerUser(user);
        std::cout << "Пользователь создан.\n";
    } else {
        std::cout << "Пользователь найден.\n";
    }

    return user;
}

int main() {
    Library library("Городская онлайн-библиотека");
    std::vector<User*> createdUsers;

    std::string dataPath = "data/books.txt";
    library.getCatalog().loadFromFile(dataPath);

    User* activeUser = selectOrCreateUser(library, createdUsers);

    while (true) {
        std::cout << "\n";
        std::cout << "1. Показать все книги\n";
        std::cout << "2. Поиск книги\n";
        std::cout << "3. Взять книгу\n";
        std::cout << "4. Вернуть книгу\n";
        std::cout << "5. Оставить отзыв\n";
        std::cout << "6. Мои выдачи\n";
        std::cout << "7. Сменить или создать пользователя\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите пункт: ";

        int option = -1;
        std::cin >> option;
        std::cin.ignore(10000, '\n');

        if (option == 0) {
            library.getCatalog().saveToFile(dataPath);
            break;
        }
        if (option == 1) {
            printAllBooks(library.getCatalog());
        } else if (option == 2) {
            searchBooks(library.getCatalog());
        } else if (option == 3) {
            borrowBook(activeUser, library);
        } else if (option == 4) {
            returnBook(activeUser, library);
        } else if (option == 5) {
            leaveReview(activeUser, library);
        } else if (option == 6) {
            if (activeUser->hasActiveLoans()) {
                activeUser->printLoans();
            } else {
                std::cout << "У вас нет активных выдач.\n";
            }
        } else if (option == 7) {
            activeUser = selectOrCreateUser(library, createdUsers);
        } else {
            std::cout << "Неизвестный пункт меню.\n";
        }
    }

    for (int i = 0; i < static_cast<int>(createdUsers.size()); ++i) {
        delete createdUsers[i];
    }

    return 0;
}
