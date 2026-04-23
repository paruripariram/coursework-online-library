#include <iostream>
#include <vector>

#include "Author.h"
#include "Book.h"
#include "Catalog.h"
#include "Library.h"
#include "SearchCriteria.h"
#include "Subscription.h"
#include "User.h"

int main() {
    std::string dataPath = "data/books.txt";

    std::cout << "Шаг 1: Создаем библиотеку...\n";
    Library library("Городская онлайн-библиотека");
    library.getCatalog().loadFromFile(dataPath);

    std::cout << "Шаг 2: Создаем авторов и книги...\n";
    Author author1("Айзек Азимов", "Классик научной фантастики");
    Author author2("Джоан Роулинг", "Автор фэнтези-саги");
    Author author3("Артур Конан Дойл", "Мастер детектива");

    Book book1("Основание", "фантастика", 1951, author1);
    Book book2("Я, робот", "фантастика", 1950, author1);
    Book book3("Гарри Поттер и философский камень", "фэнтези", 1997, author2);
    Book book4("Этюд в багровых тонах", "детектив", 1887, author3);
    Book book5("Гарри Поттер и тайная комната", "фэнтези", 1998, author2);

    library.getCatalog().addBook(&book1);
    library.getCatalog().addBook(&book2);
    library.getCatalog().addBook(&book3);
    library.getCatalog().addBook(&book4);
    library.getCatalog().addBook(&book5);

    std::cout << "Шаг 3: Создаем пользователей и подписки...\n";
    Subscription subscription1("standard", 3, "2026-12-31");
    Subscription subscription2("basic", 1, "2026-12-31");

    User user1("Иван", "ivan@example.com", subscription1);
    User user2("Мария", "maria@example.com", subscription2);

    library.registerUser(&user1);
    library.registerUser(&user2);

    std::cout << "Шаг 4: Поиск книг по жанру 'фантастика'...\n";
    SearchCriteria criteria;
    criteria.setGenre("фантастика");
    std::vector<Book*> foundBooks = library.getCatalog().find(criteria);
    for (int i = 0; i < static_cast<int>(foundBooks.size()); ++i) {
        std::cout << "Найдена книга: " << foundBooks[i]->getTitle() << "\n";
    }

    std::cout << "Шаг 5: Просмотр информации о книге...\n";
    book1.printInfo();

    std::cout << "Шаг 6: Пользователь 1 берет книгу...\n";
    user1.borrowBook(&book1, library.getFactory(), "2026-04-17", "2026-05-01");

    std::cout << "Шаг 7: Пользователь 2 пытается взять ту же книгу...\n";
    user2.borrowBook(&book1, library.getFactory(), "2026-04-17", "2026-05-10");

    std::cout << "Шаг 8: Пользователь 1 оставляет отзыв...\n";
    user1.leaveReview(&book1, "Сильная и умная фантастика", 5, "2026-04-17");

    std::cout << "Шаг 9: Пользователь 1 возвращает книгу...\n";
    user1.returnBookByTitle("Основание", library.getFactory());

    std::cout << "Шаг 10: Вывод статистики библиотеки...\n";
    library.printStatistics();

    library.getCatalog().saveToFile(dataPath);

    return 0;
}
