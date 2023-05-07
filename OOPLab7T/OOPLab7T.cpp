// OOPLab7T.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>
#include <vector>
#include <string>
#include <windows.h>

  


    class Station {
    public:
        std::string name;
        Station(const std::string& name) : name(name) {}
    };

    class Train {
    public:
        int number;
        Station* departure;
        Station* destination;
        std::vector<Station*> intermediateStations;
        float price;
        std::string departureDate;

        Train(int number, Station* departure, Station* destination, float price, std::string departureDate) :
            number(number), departure(departure), destination(destination), price(price), departureDate(departureDate) {}
    };

    class Ticket {
    public:
        Train* train;
        Station* departure;
        Station* destination;
        float price;

        Ticket(Train* train, Station* departure, Station* destination) :
            train(train), departure(departure), destination(destination) {
            price = train->price;
        }
    };

    class Passenger {
    public:
        std::string name;
        Passenger(const std::string& name) : name(name) {}
    };

    class RailwayTicketOffice {
    public:
        std::vector<Train> trains;

        void addTrain(Train train) {
            trains.push_back(train);
        }

        Train* findTrain(Station* departure, Station* destination, std::string departureDate) {
            for (Train& train : trains) {
                if (train.departure == departure && train.destination == destination && train.departureDate == departureDate)
                    return &train;
            }
            return nullptr;
        }

        Ticket createTicket(Passenger* passenger, Train* train) {
            return Ticket(train, train->departure, train->destination);
        }
    };

    int main() {
        setlocale(LC_CTYPE, "ukr");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        // Створюємо станції
        Station kyiv("Kyiv");
        Station lviv("Lviv");

        // Створюємо потяги
        Train train1(123, &kyiv, &lviv, 150.0, "2023-05-10");
        Train train2(456, &kyiv, &lviv, 130.0, "2023-05-11");

        // Створюємо касу
        RailwayTicketOffice ticketOffice;
        ticketOffice.addTrain(train1);
        ticketOffice.addTrain(train2);

        // Створюємо пасажира
        std::string passengerName;
        std::cout << "Введіть ваше ім'я: ";
        std::getline(std::cin, passengerName);
        Passenger passenger(passengerName);

        // Пасажир вибирає станції відправлення та призначення
        std::string departureName, destinationName;
        std::cout << "Введіть назву станції відправлення: ";
        std::getline(std::cin, departureName);
        Station* departure = (departureName == "Kyiv") ? &kyiv : &lviv;

        std::cout << "Введіть назву станції призначення: ";
        std::getline(std::cin, destinationName);
        Station* destination = (destinationName == "Kyiv") ? &kyiv : &lviv;

        // Пасажир вибирає дату відправлення
        std::string departureDate;
        std::cout << "Введіть дату відправлення (рік-місяць-день): ";
        std::getline(std::cin, departureDate);

        // Знаходимо потяг
        Train* train = ticketOffice.findTrain(departure, destination, departureDate);
        if (train == nullptr) {
            std::cout << "Потяг не знайдено!\n";
            return 0;
        }

        // Створюємо квиток та виводимо його інформацію
        Ticket ticket = ticketOffice.createTicket(&passenger, train);
        std::cout << "Квиток для пасажира " << passenger.name << " на потяг номер " << train->number << ":\n"
            << "   Відправлення: " << ticket.departure->name << "\n"
            << "   Призначення: " << ticket.destination->name << "\n"
            << "   Ціна: " << ticket.price << " грн.\n";

        return 0;
    }


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
