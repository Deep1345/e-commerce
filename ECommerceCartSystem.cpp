#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>

// Base class for products
class Product {
private:
    std::string name;
    double price;
    bool available;

public:
    Product(std::string name, double price, bool available) : name(name), price(price), available(available) {}

    std::string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    bool isAvailable() {
        return available;
    }

    std::string toString() {
        return name + " - $" + std::to_string(price);
    }
};

// Concrete product classes
class Laptop : public Product {
public:
    Laptop(std::string name, double price, bool available) : Product(name, price, available) {}
};

class Headphones : public Product {
public:
    Headphones(std::string name, double price, bool available) : Product(name, price, available) {}
};

// Shopping cart
class ShoppingCart {
private:
    std::unordered_map<Product*, int> cartItems;

public:
    void addToCart(Product* product, int quantity) {
        if (product->isAvailable()) {
            cartItems[product] += quantity;
        } else {
            std::cout << product->getName() << " is not available." << std::endl;
        }
    }

    void removeFromCart(Product* product, int quantity) {
        if (cartItems.find(product) != cartItems.end()) {
            int currentQuantity = cartItems[product];
            if (currentQuantity <= quantity) {
                cartItems.erase(product);
            } else {
                cartItems[product] = currentQuantity - quantity;
            }
        }
    }

    double calculateTotalBill() {
        double totalBill = 0;
        for (auto entry : cartItems) {
            Product* product = entry.first;
            int quantity = entry.second;
            totalBill += product->getPrice() * quantity;
        }
        return totalBill;
    }

    void displayCart() {
        std::cout << "Cart Items:" << std::endl;
        for (auto entry : cartItems) {
            Product* product = entry.first;
            int quantity = entry.second;
            std::cout << "You have " << quantity << " " << product->getName() << " in your cart." << std::endl;
        }
        std::cout << "Total Bill: Your total bill is $" << std::fixed << std::setprecision(2) << calculateTotalBill() << std::endl;
    }
};

int main() {
    Laptop laptop("Laptop", 1000, true);
    Headphones headphones("Headphones", 50, true);

    ShoppingCart cart;
    cart.addToCart(&laptop, 2);
    cart.addToCart(&headphones, 1);
    cart.displayCart();

    return 0;
}