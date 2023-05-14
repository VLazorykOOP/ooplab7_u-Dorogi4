#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>

class Train {
public:
    int number;
    std::string departure;
    std::string destination;
    float price;
    std::string departureDate;
    std::string type;

    Train(int number, std::string departure, std::string destination, float price, std::string departureDate, std::string type) :
        number(number), departure(departure), destination(destination), price(price), departureDate(departureDate), type(type) {}
};

class Ticket {
public:
    Train train;
    std::string departure;
    std::string destination;
    float price;
    std::string type;

    Ticket(const Train& train, const std::string& departure, const std::string& destination, const std::string& type) :
        train(train), departure(departure), destination(destination), type(type) {
        price = train.price;
    }
};

class Passenger {
public:
    std::string name;
    Passenger(const std::string& name) : name(name) {}
};

class RailwayTicketOffice {
public:
    std::vector<Train*> trains;

    void addTrain(Train* train) {
        trains.push_back(train);
    }

    Train* findTrain(const std::string& departure, const std::string& destination, const std::string& departureDate, const std::string& type) {
        for (Train* train : trains) {
            if (train->departure == departure && train->destination == destination && train->departureDate == departureDate && train->type == type)
                return train;
        }
        return nullptr;
    }

    Ticket createTicket(Passenger* passenger, Train* train) {
        return Ticket(*train, train->departure, train->destination, train->type);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    RailwayTicketOffice ticketOffice;


    std::ifstream inputFile("trains.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        int number;
        std::string departure, destination, departureDate, type;
        float price;

        std::istringstream iss(line);
        iss >> number >> departure >> destination >> price >> departureDate >> type;

        Train* train = new Train(number, departure, destination, price, departureDate, type);
        ticketOffice.addTrain(train);
    }


    std::string passengerName;
    std::cout << "Введіть ваше ім'я: ";
    std::getline(std::cin, passengerName);
    Passenger passenger(passengerName);


    std::string departure, destination;
    std::cout << "Виберіть станцію відправлення: ";
    std::getline(std::cin, departure);
    std::cout << "Виберіть станцію призначення: ";
    std::getline(std::cin, destination);

    std::string type, departureDate;
    std::cout << "Виберіть тип потяга: ";
    std::getline(std::cin, type);
    std::cout << "Введіть дату відправлення (у форматі дд.мм.рррр): ";
    std::getline(std::cin, departureDate);

    // Знаходимо потяг, який відповідає критеріям
    Train* train = ticketOffice.findTrain(departure, destination, departureDate, type);

    if (train == nullptr) {
        std::cout << "Потяг не знайдено." << std::endl;
        return 0;
    }
    std::cout << "-------------------------------------\n";


    Ticket ticket = ticketOffice.createTicket(&passenger, train);
    std::cout << "Ім'я пасажира: " << passenger.name << std::endl;
    std::cout << "Тип потяга: " << ticket.type << std::endl;
    std::cout << "Відправлення: " << ticket.departure << std::endl;
    std::cout << "Призначення: " << ticket.destination << std::endl;
    std::cout << "Ціна квитка: " << ticket.price << " грн" << std::endl;

    return 0;
}
