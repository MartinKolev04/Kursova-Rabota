#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <string>
#include <iostream>

class Textbook {
private:
    std::string title;
    std::string author;
    int edition;
    std::string isbn;
    std::string publishDate;
    int copies;
    bool approved;
    std::string approveDate;
    double price; // цена за брой

public:
    // Конструктори
    Textbook();
    Textbook(const std::string& title,
             const std::string& author,
             int edition,
             const std::string& isbn,
             const std::string& publishDate,
             int copies,
             bool approved,
             const std::string& approveDate,
             double price);

    // Getters / Setters
    std::string getTitle() const;
    void setTitle(const std::string& t);

    std::string getAuthor() const;
    void setAuthor(const std::string& a);

    int getEdition() const;
    void setEdition(int e);

    std::string getISBN() const;
    void setISBN(const std::string& i);

    std::string getPublishDate() const;
    void setPublishDate(const std::string& pd);

    int getCopies() const;
    void setCopies(int c);

    bool isApproved() const;
    void setApproved(bool a);

    std::string getApproveDate() const;
    void setApproveDate(const std::string& ad);

    double getPrice() const;
    void setPrice(double p);

    // Serialization / Deserialization (text line)
    std::string toDataLine() const;
    static Textbook fromDataLine(const std::string& line);

    // Извеждане
    friend std::ostream& operator<<(std::ostream& os, const Textbook& t);
};

#endif
