#include "Catalog.h"
#include <fstream>
#include <sstream>

Catalog::Catalog(const std::string& filename) : storageFile(filename) {}

void Catalog::addTextbook(const Textbook& t) {
    textbooks.push_back(t);
}

void Catalog::addDistributor(const Distributor& d) {
    distributors.push_back(d);
}

bool Catalog::saveToFile() const {
    std::ofstream ofs(storageFile);
    if (!ofs) return false;

    ofs << "TEXTBOOKS\n";
    for (const auto& t : textbooks)
        ofs << t.toDataLine() << "\n";

    ofs << "DISTRIBUTORS\n";
    for (const auto& d : distributors)
        ofs << d.toDataLine() << "\n";

    return true;
}

bool Catalog::loadFromFile() {
    std::ifstream ifs(storageFile);
    if (!ifs) return false;

    std::string line;
    enum Section { NONE, TB, DIST } sec = NONE;

    while (std::getline(ifs, line)) {
        if (line == "TEXTBOOKS") { sec = TB; continue; }
        if (line == "DISTRIBUTORS") { sec = DIST; continue; }
        if (line.empty()) continue;

        if (sec == TB)
            textbooks.push_back(Textbook::fromDataLine(line));
        else if (sec == DIST)
            distributors.push_back(Distributor::fromDataLine(line));
    }
    return true;
}

double Catalog::computeOrderTotal(const Distributor& d) const {
    double total = 0.0;
    for (const auto& pr : d.getOrders()) {
        int idx = pr.first;
        int qty = pr.second;
        if (idx >= 0 && idx < static_cast<int>(textbooks.size())) {
            total += textbooks[idx].getPrice() * qty;
        }
    }
    return total;
}
