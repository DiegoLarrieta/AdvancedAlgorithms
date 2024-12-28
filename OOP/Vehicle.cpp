#include <iostream>
#include <string>

using namespace std;

// Clase base: Vehicle
// Esta clase representa un vehículo genérico.
class Vehicle {
protected: 
    // Los atributos protected permiten que las clases derivadas accedan a ellos directamente
    string brand;
    int year;

public:
    // Constructor por defecto
    Vehicle() = default;

    // Constructor parametrizado
    Vehicle(string brand, int year) {
        this->brand = brand;
        this->year = year;
    }

    // Método setter para la marca del vehículo
    void setBrand(string brand) {
        this->brand = brand;
    }

    // Método setter para el año del vehículo
    void setYear(int year) {
        this->year = year;
    }

    // Método getter para la marca del vehículo
    string getBrand() {
        return brand;
    }

    // Método getter para el año del vehículo
    int getYear() {
        return year;
    }

    // Método virtual puro (abstracción): debe ser implementado por las clases derivadas
    virtual void showInfo() = 0; // Polimorfismo
};

// Clase derivada: Car
// Hereda de Vehicle y representa un coche.
class Car : public Vehicle {
private:
    int doors; // Número de puertas, atributo específico de Car

public:
    // Constructor de Car que utiliza el constructor de Vehicle
    Car(string brand, int year, int doors) : Vehicle(brand, year) {
        this->doors = doors;
    }

    // Implementación del método virtual showInfo
    void showInfo() override {
        cout << "Car Brand: " << brand << ", Year: " << year << ", Doors: " << doors << endl;
    }
};

// Clase derivada: Motorcycle
// Hereda de Vehicle y representa una motocicleta.
class Motorcycle : public Vehicle {
private:
    bool hasSidecar; // Atributo específico de Motorcycle

public:
    // Constructor de Motorcycle que utiliza el constructor de Vehicle
    Motorcycle(string brand, int year, bool hasSidecar) : Vehicle(brand, year) {
        this->hasSidecar = hasSidecar;
    }

    // Implementación del método virtual showInfo
    void showInfo() override {
        cout << "Motorcycle Brand: " << brand << ", Year: " << year << ", Sidecar: " 
             << (hasSidecar ? "Yes" : "No") << endl;
    }
};

int main() {
    // Creando un objeto de la clase Car
    Car car("Toyota", 2020, 4);
    car.showInfo(); // Salida: Car Brand: Toyota, Year: 2020, Doors: 4

    // Creando un objeto de la clase Motorcycle
    Motorcycle moto("Harley-Davidson", 2022, true);
    moto.showInfo(); // Salida: Motorcycle Brand: Harley-Davidson, Year: 2022, Sidecar: Yes

    // Puntero de tipo Vehicle para demostrar polimorfismo
    Vehicle* vehiclePtr;

    // Asignamos el puntero a un objeto Car
    vehiclePtr = &car;
    vehiclePtr->showInfo(); // Polimorfismo: llama a showInfo de Car

    // Asignamos el puntero a un objeto Motorcycle
    vehiclePtr = &moto;
    vehiclePtr->showInfo(); // Polimorfismo: llama a showInfo de Motorcycle

    return 0;
}
