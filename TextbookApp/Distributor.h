#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include <string>
#include <vector>
#include <iostream>

class Distributor {
private:
    std::string name;
    std::string address;
    std::string phone;
    // поръчки: двойки (bookIndex, quantity)
    std::vector<std::pair<int,int>> orders;

public:
    Distributor();
    Distributor(const std::string& name, const std::string& address, const std::string& phone);

    std::string getName() const;
    void setName(const std::string& n);

    std::string getAddress() const;
    void setAddress(const std::string& a);

    std::string getPhone() const;
    void setPhone(const std::string& p);

    void addOrder(int bookIndex, int quantity);
    const std::vector<std::pair<int,int>>& getOrders() const;

    std::string toDataLine() const;
    static Distributor fromDataLine(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const Distributor& d);
};

#endif
