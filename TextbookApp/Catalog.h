#ifndef CATALOG_H
#define CATALOG_H

#include "Textbook.h"
#include "Distributor.h"
#include <vector>
#include <string>

class Catalog {
private:
std::vector<Textbook> textbooks;
std::vector<Distributor> distributors;
std::string storageFile;

public:
Catalog(const std::string& filename = "data.txt");


// Управление учебници  
void addTextbook(const Textbook& t);  

// read/write версия (за промяна на copies)  
std::vector<Textbook>& getTextbooks() { return textbooks; }  

// read-only версия  
const std::vector<Textbook>& getTextbooks() const { return textbooks; }  

// Управление книгоразпространители  
void addDistributor(const Distributor& d);  
std::vector<Distributor>& getDistributors() { return distributors; }  
const std::vector<Distributor>& getDistributors() const { return distributors; }  

// I/O  
bool saveToFile() const;  
bool loadFromFile();  

// Помощни функции  
double computeOrderTotal(const Distributor& d) const;  


};

#endif
