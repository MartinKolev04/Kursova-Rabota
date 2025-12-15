#include "Distributor.h"
#include <sstream>

Distributor::Distributor() {}
Distributor::Distributor(const std::string& name, const std::string& address, const std::string& phone)
    : name(name), address(address), phone(phone) {}

std::string Distributor::getName() const { return name; }
void Distributor::setName(const std::string& n) { name = n; }

std::string Distributor::getAddress() const { return address; }
void Distributor::setAddress(const std::string& a) { address = a; }

std::string Distributor::getPhone() const { return phone; }
void Distributor::setPhone(const std::string& p) { phone = p; }

void Distributor::addOrder(int bookIndex, int quantity) {
    orders.emplace_back(bookIndex, quantity);
}

const std::vector<std::pair<int,int>>& Distributor::getOrders() const {
    return orders;
}

// Формат: name|address|phone|bookIndex:qty,bookIndex:qty,...
std::string Distributor::toDataLine() const {
    std::ostringstream oss;
    oss << name << "|" << address << "|" << phone << "|";
    for (size_t i = 0; i < orders.size(); ++i) {
        if (i) oss << ",";
        oss << orders[i].first << ":" << orders[i].second;
    }
    return oss.str();
}

Distributor Distributor::fromDataLine(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '|')) parts.push_back(token);
    Distributor d;
    if (parts.size() >= 4) {
        d.name = parts[0];
        d.address = parts[1];
        d.phone = parts[2];
        // parse orders
        std::string ordersStr = parts[3];
        std::istringstream ois(ordersStr);
        std::string pairS;
        while (std::getline(ois, pairS, ',')) {
            if (pairS.empty()) continue;
            size_t pos = pairS.find(':');
            if (pos != std::string::npos) {
                int idx = std::stoi(pairS.substr(0,pos));
                int qty = std::stoi(pairS.substr(pos+1));
                d.orders.emplace_back(idx, qty);
            }
        }
    }
    return d;
}

std::ostream& operator<<(std::ostream& os, const Distributor& d) {
    os << "Ime: " << d.name << "\n"
       << "Adress: " << d.address << "\n"
       << "Telefon: " << d.phone << "\n"
       << "Poruchki (bookIndex:quantity): ";
    for (size_t i = 0; i < d.orders.size(); ++i) {
        if (i) os << ", ";
        os << d.orders[i].first << ":" << d.orders[i].second;
    }
    if (d.orders.empty()) os << "-";
    os << "\n";
    return os;
}

