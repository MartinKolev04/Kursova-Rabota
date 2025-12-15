#include "Textbook.h"
#include <sstream>
#include <vector>

Textbook::Textbook()
    : edition(0), copies(0), approved(false), price(0.0) {}

Textbook::Textbook(const std::string& title,
                   const std::string& author,
                   int edition,
                   const std::string& isbn,
                   const std::string& publishDate,
                   int copies,
                   bool approved,
                   const std::string& approveDate,
                   double price)
    : title(title), author(author), edition(edition), isbn(isbn),
      publishDate(publishDate), copies(copies), approved(approved),
      approveDate(approveDate), price(price) {}

// Getters / Setters
std::string Textbook::getTitle() const { return title; }
void Textbook::setTitle(const std::string& t) { title = t; }

std::string Textbook::getAuthor() const { return author; }
void Textbook::setAuthor(const std::string& a) { author = a; }

int Textbook::getEdition() const { return edition; }
void Textbook::setEdition(int e) { edition = e; }

std::string Textbook::getISBN() const { return isbn; }
void Textbook::setISBN(const std::string& i) { isbn = i; }

std::string Textbook::getPublishDate() const { return publishDate; }
void Textbook::setPublishDate(const std::string& pd) { publishDate = pd; }

int Textbook::getCopies() const { return copies; }
void Textbook::setCopies(int c) { copies = c; }

bool Textbook::isApproved() const { return approved; }
void Textbook::setApproved(bool a) { approved = a; }

std::string Textbook::getApproveDate() const { return approveDate; }
void Textbook::setApproveDate(const std::string& ad) { approveDate = ad; }

double Textbook::getPrice() const { return price; }
void Textbook::setPrice(double p) { price = p; }

// Прост сериализиран текстов ред (полета разделени с '|')
std::string Textbook::toDataLine() const {
    std::ostringstream oss;
    // внимателно: символ '|' служи като разделител
    oss << title << "|" << author << "|" << edition << "|" << isbn << "|"
        << publishDate << "|" << copies << "|" << (approved ? "1" : "0") << "|"
        << approveDate << "|" << price;
    return oss.str();
}

Textbook Textbook::fromDataLine(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '|')) parts.push_back(token);

    Textbook t;
    if (parts.size() >= 9) {
        t.title = parts[0];
        t.author = parts[1];
        t.edition = std::stoi(parts[2]);
        t.isbn = parts[3];
        t.publishDate = parts[4];
        t.copies = std::stoi(parts[5]);
        t.approved = (parts[6] == "1");
        t.approveDate = parts[7];
        t.price = std::stod(parts[8]);
    }
    return t;
}

std::ostream& operator<<(std::ostream& os, const Textbook& t) {
    os << "Zaglavie: " << t.title << "\n"
       << "Avtor: " << t.author << "\n"
       << "Izdanie: " << t.edition << "\n"
       << "ISBN: " << t.isbn << "\n"
       << "Data na izdavane: " << t.publishDate << "\n"
       << "Tiraj: " << t.copies << "\n"
       << "Cena (za broi): " << t.price << "\n"
       << "Odobren ot MON: " << (t.approved ? "Da" : "Ne") << "\n"
       << "Data na odobrenie: " << (t.approved ? t.approveDate : "-") << "\n";
    return os;
}

