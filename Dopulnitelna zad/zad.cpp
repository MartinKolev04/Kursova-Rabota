#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// ===== Базов клас за електронни компоненти =====
class Component {
protected:
    string code;        // номенклатурен номер
    string name;        // наименование
    double value;       // стойност
    string unit;        // мерна единица

public:
    // Конструктор
    Component(string c = "", string n = "", double v = 0, string u = "")
        : code(c), name(n), value(v), unit(u) {}

    // Деструктор
    virtual ~Component() {}

    // Виртуална функция за извеждане
    virtual void print() const {
        cout << "Code: " << code << ", Name: " << name
             << ", Value: " << value << " " << unit;
    }

    // Гетъри
    string getName() const { return name; }
    double getValue() const { return value; }

    // Презареждане на оператора <<
    friend ostream& operator<<(ostream& os, const Component& comp) {
        comp.print();
        return os;
    }

    // Функция за запис във файл
    virtual void saveToFile(ofstream& out) const {
        out << code << " " << name << " " << value << " " << unit;
    }
};

// ===== Производен клас за конкретен компонент =====
class SpecificComponent : public Component {
private:
    string country;    // държава производител
    double price;      // цена

public:
    SpecificComponent(string c = "", string n = "", double v = 0, string u = "",
                      string country = "", double price = 0)
        : Component(c, n, v, u), country(country), price(price) {}

    // Деструктор
    ~SpecificComponent() {}

    // Презаписване на print
    void print() const override {
        Component::print();
        cout << ", Country: " << country << ", Price: " << price;
    }

    // Презаписване на saveToFile
    void saveToFile(ofstream& out) const override {
        Component::saveToFile(out);
        out << " " << country << " " << price << endl;
    }
};

// ===== Главна програма =====
int main() {
    vector<SpecificComponent> components;

    // Добавяне на няколко компонента
    components.push_back(SpecificComponent("R1", "Resistor", 100, "Ohm", "Germany", 0.5));
    components.push_back(SpecificComponent("C1", "Capacitor", 50, "pF", "China", 1.2));
    components.push_back(SpecificComponent("C2", "Capacitor", 200, "pF", "USA", 2.5));

    // Извеждане на всички компоненти
    cout << "All components:\n";
    for (auto& comp : components) {
        cout << comp << endl;
    }

    // Търсене на кондензатори в зададен диапазон
    double minVal = 30, maxVal = 150;
    cout << "\nCapacitors with value between " << minVal << " and " << maxVal << ":\n";
    for (auto& comp : components) {
        if (comp.getName() == "Capacitor" && comp.getValue() >= minVal && comp.getValue() <= maxVal) {
            cout << comp << endl;
        }
    }

    // Запис във файл
    ofstream outFile("components.txt");
    if (outFile.is_open()) {
        for (auto& comp : components) {
            comp.saveToFile(outFile);
        }
        outFile.close();
        cout << "\nData saved to components.txt\n";
    } else {
        cout << "Cannot open file for writing!\n";
    }

    // Изтриване на елемент (например първия)
    if (!components.empty()) {
        components.erase(components.begin());
        cout << "\nAfter deleting first element:\n";
        for (auto& comp : components) {
            cout << comp << endl;
        }
    }

    return 0;
}
