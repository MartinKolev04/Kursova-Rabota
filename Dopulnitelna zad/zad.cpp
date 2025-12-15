#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Component {
protected:
    string code;        
    string name;        
    double value;       
    string unit;        

public:
   
    Component(string c = "", string n = "", double v = 0, string u = "")
        : code(c), name(n), value(v), unit(u) {}

  
    virtual ~Component() {}

 
    virtual void print() const {
        cout << "Code: " << code << ", Name: " << name
             << ", Value: " << value << " " << unit;
    }


    string getName() const { return name; }
    double getValue() const { return value; }


    friend ostream& operator<<(ostream& os, const Component& comp) {
        comp.print();
        return os;
    }


    virtual void saveToFile(ofstream& out) const {
        out << code << " " << name << " " << value << " " << unit;
    }
};

class SpecificComponent : public Component {
private:
    string country;    
    double price;     

public:
    SpecificComponent(string c = "", string n = "", double v = 0, string u = "",
                      string country = "", double price = 0)
        : Component(c, n, v, u), country(country), price(price) {}

  
    ~SpecificComponent() {}

    void print() const override {
        Component::print();
        cout << ", Country: " << country << ", Price: " << price;
    }

    void saveToFile(ofstream& out) const override {
        Component::saveToFile(out);
        out << " " << country << " " << price << endl;
    }
};

int main() {
    vector<SpecificComponent> components;


    components.push_back(SpecificComponent("R1", "Resistor", 100, "Ohm", "Germany", 0.5));
    components.push_back(SpecificComponent("C1", "Capacitor", 50, "pF", "China", 1.2));
    components.push_back(SpecificComponent("C2", "Capacitor", 200, "pF", "USA", 2.5));


    cout << "All components:\n";
    for (auto& comp : components) {
        cout << comp << endl;
    }

    
    double minVal = 30, maxVal = 150;
    cout << "\nCapacitors with value between " << minVal << " and " << maxVal << ":\n";
    for (auto& comp : components) {
        if (comp.getName() == "Capacitor" && comp.getValue() >= minVal && comp.getValue() <= maxVal) {
            cout << comp << endl;
        }
    }


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

    if (!components.empty()) {
        components.erase(components.begin());
        cout << "\nAfter deleting first element:\n";
        for (auto& comp : components) {
            cout << comp << endl;
        }
    }

    return 0;
}

