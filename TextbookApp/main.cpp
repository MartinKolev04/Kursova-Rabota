#include <iostream>
#include <limits>
#include "Catalog.h"


int readInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min()) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v && v >= minVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cout << "Nevaliden izhod.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDouble(const std::string& prompt, double minVal = 0.0) {
    double v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v && v >= minVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cout << "Nevaliden izhod.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    if (s.empty()) {
        std::cout << "Poleto ne moje da bude prazno\n";
        return readLine(prompt);
    }
    return s;
}

bool readYesNo(const std::string& prompt) {
    while (true) {
        std::string s;
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, s);
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "Molq vuvedi 'y' ili 'n'.\n";
    }
}

void addTextbookInteractive(Catalog& cat) {
    std::string title = readLine("Zaglavie: ");
    std::string author = readLine("Avtor: ");
    int edition = readInt("Poreno izdanie(chislo): ", 1);
    std::string isbn = readLine("ISBN: ");
    std::string publishDate = readLine("Data na iztichane: ");
    int copies = readInt("Tiraj (broi): ", 1);
    double price = readDouble("Cena za broi: ", 0.0);
    bool approved = readYesNo("Odobren li e ot MON?");
    std::string approveDate = "-";
    if (approved) approveDate = readLine("Data na odobrenie: ");

    Textbook t(title, author, edition, isbn, publishDate, copies, approved, approveDate, price);
    cat.addTextbook(t);
    std::cout << "Uchebnikut e dobaven.\n";
}

void addDistributorInteractive(Catalog& cat) {
    std::string name = readLine("Ime na knigorazprostranitel: ");
    std::string address = readLine("Adress: ");
    std::string phone = readLine("Telefon: ");
    Distributor d(name, address, phone);
    cat.addDistributor(d);
    std::cout << "Knogorazprostranitelqt e dobaven.\n";
}

void listTextbooks(const Catalog& cat) {
    const auto& t = cat.getTextbooks();
    if (t.empty()) { std::cout << "Nqma uchebnici.\n"; return; }
    for (size_t i = 0; i < t.size(); ++i) {
        std::cout << "ID=" << i << ":\n" << t[i] << "--------\n";
    }
}

void listDistributors(Catalog& cat) {
    const auto& d = cat.getDistributors();
    if (d.empty()) { std::cout << "Nqma knigorazprostraniteli.\n"; return; }
    for (size_t i = 0; i < d.size(); ++i) {
        std::cout << "ID=" << i << ":\n" << d[i] << "--------\n";
    }
}

void makeOrderInteractive(Catalog& cat) {
    if (cat.getTextbooks().empty() || cat.getDistributors().empty()) {
        std::cout << "Trqbva da ima pone 1 uchebnik i edin knigorazprostranitel.\n";
    return;
    }


    listDistributors(cat);
    int did = readInt("Izberi ID na knigorazprostranitel: ", 0);
    if (did >= (int)cat.getDistributors().size()) {
        std::cout << "Nqma takova ID.\n";
    return;
    }

    listTextbooks(cat);
    int bid = readInt("Izberi ID na uchebnik: ", 0);
    if (bid >= (int)cat.getTextbooks().size()) {
        std::cout << "Nqma takova ID.\n";
    return;
    }

int qty = readInt("Kolichestvo: ", 1);
int nal = cat.getTextbooks()[bid].getCopies();

if (qty > nal) {
    std::cout << "GRESHKA: Nqma dostatuchno nalichni broiki!\n";
    std::cout << "V momenta ima samo: " << nal << " broya.\n";
    return;
}

cat.getTextbooks()[bid].setCopies(nal - qty);
cat.getDistributors()[did].addOrder(bid, qty);

std::cout << "Uspeshno poruchihte " << qty << " broya.\n";
std::cout << "Ostavashti nalichni: " << cat.getTextbooks()[bid].getCopies() << " broya.\n";

double total = cat.computeOrderTotal(cat.getDistributors()[did]);
std::cout << "Obshta stoinost na poruchkite za tozi knigorazprostranitel: " << total << "\n";


}


void saveAndExit(Catalog& cat) {
    if (cat.saveToFile()) std::cout << "Dannite sa zapisani vuv fila.\n";
    else std::cout << "Greshka pri zapis vuv fila!\n";
}

int main() {
    Catalog catalog("data.txt");
    catalog.loadFromFile();

    while (true) {
        std::cout << "\n--- Menu ---\n"
                  << "1. Dobavi uchebnik\n"
                  << "2. Dobavi knigorazprostranitel\n"
                  << "3. Pokaji uchebnici\n"
                  << "4. Pokaji knigorazprostraniteli\n"
                  << "5. Napravi poruchka (za izbran knigorazprostranitel)\n"
                  << "6. Zapazi danni vuv faila\n"
                  << "0. Zapazi i izhod\n Izbor: ";
        int ch = readInt("", 0);
        switch (ch) {
            case 1: addTextbookInteractive(catalog); break;
            case 2: addDistributorInteractive(catalog); break;
            case 3: listTextbooks(catalog); break;
            case 4: listDistributors(catalog); break;
            case 5: makeOrderInteractive(catalog); break;
            case 6:
                if (catalog.saveToFile()) std::cout << "Zapisano.\n"; else std::cout << "Greshka pri zapis.\n";
                break;
            case 0:
                saveAndExit(catalog);
                std::cout << "Krai.\n";
                return 0;
            default: std::cout << "Nevaliden izbor.\n";
        }
    }

    return 0;
}
