#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "Catalog.h"
#include "Library.h"
#include "User.h"
std::string dateFromTime(std::time_t value) {
    std::tm localTime{};
    localtime_s(&localTime, &value);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
    return buffer;
}

std::string todayDate() {
    return dateFromTime(std::time(nullptr));
}

std::string plusDaysDate(int days) {
    return dateFromTime(std::time(nullptr) + static_cast<std::time_t>(days) * 24 * 60 * 60);
}

int main() {
    Library library("Online Library");
    library.getCatalog().loadFromFile("data/books.txt");

    std::vector<User*> users;
    User* user = new User("Guest", "guest@example.com", 3);
    users.push_back(user);
    library.registerUser(user);

    std::vector<Book*> books = library.getCatalog().allBooks();
    if (books.empty()) {
        std::cout << "Catalog is empty.\n";
    } else {
        std::cout << "Books:\n";
        for (int i = 0; i < static_cast<int>(books.size()); ++i) {
            Book* book = books[i];
            std::cout << i + 1 << ". " << book->getTitle() << " | " << book->getAuthor() << " | " << book->getGenre() << " | " << book->getYear() << "\n";
        }

        Book* firstBook = books[0];
        std::cout << "\nBorrowing: " << firstBook->getTitle() << "\n";
        if (user->borrowBookAndTrack(firstBook, library.getFactory(), todayDate(), plusDaysDate(14)) != nullptr) {
            std::cout << "Loan created.\n";
        }

        if (user->hasActiveLoans()) {
            std::cout << "\nActive loans:\n";
            user->printLoans();
            if (user->returnBookByIndex(0, library.getFactory())) {
                std::cout << "Loan returned.\n";
            }
        }

        user->leaveReview(firstBook, "Good book", 5, todayDate());
    }

    library.getCatalog().saveToFile("data/books.txt");

    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        delete users[i];
    }

    return 0;
}
