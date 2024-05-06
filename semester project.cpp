#include <iostream>
#include <string>
using namespace std;

// Define Structures and Menu Management
const int MAX_ITEMS = 50;  // Maximum number of menu items and cart items

struct MenuItem {
    int id;
    string name;
    double price;
    bool isAvailable;
};

struct CartItem {
    int id;
    string name;
    double price;
};

struct Order {
    int orderID;
    double totalPrice;
    int itemCount;
};

MenuItem menu[MAX_ITEMS];
CartItem cart[MAX_ITEMS];
Order orderQueue[MAX_ITEMS];
int menuCount = 0, cartSize = 0, front = 0, rear = -1, orderCount = 0, nextOrderID = 1;

// Menu management functions
void addItem(int id, string name, double price, bool isAvailable) {
    if (menuCount < MAX_ITEMS) {
        menu[menuCount++] = { id, name, price, isAvailable };
    }
    else {
        cout << "Menu is full, cannot add more items." << endl;
    }
}

void displayMenu() {
    for (int i = 0; i < menuCount; i++) {
        cout << "ID: " << menu[i].id << ", Name: " << menu[i].name
            << ", Price: $" << menu[i].price
            << ", Available: " << (menu[i].isAvailable ? "Yes" : "No") << endl;
    }
}

// User Cart with Stack
void addToCart(string name) {
    if (cartSize >= MAX_ITEMS) {
        cout << "Cart is full." << endl;
        return;
    }

    // Search for the item by name in the menu
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].name == name && menu[i].isAvailable) {
            cart[cartSize++] = { menu[i].id, menu[i].name, menu[i].price };
            cout << name << " added to cart." << endl;
            return;
        }
    }

    // If the item is not found or not available
    cout << "Item not found or not available." << endl;
}


void removeFromCart() {
    if (cartSize > 0) {
        cout << "Removing: " << cart[cartSize - 1].name << endl;
        cartSize--;
    }
    else {
        cout << "Cart is empty." << endl;
    }
}

void displayCart() {
    for (int i = 0; i < cartSize; i++) {
        cout << "ID: " << cart[i].id << ", Name: " << cart[i].name
            << ", Price: $" << cart[i].price << endl;
    }
}

// Order Processing with Queue
void enqueueOrder(double totalPrice, int itemCount) {
    if (orderCount < MAX_ITEMS) {
        rear = (rear + 1) % MAX_ITEMS;
        orderQueue[rear] = { nextOrderID++, totalPrice, itemCount };
        orderCount++;
    }
    else {
        cout << "Order queue is full." << endl;
    }
}

void dequeueOrder() {
    if (orderCount > 0) {
        cout << "Processing Order ID: " << orderQueue[front].orderID
            << ", Total Price: $" << orderQueue[front].totalPrice
            << ", Item Count: " << orderQueue[front].itemCount << endl;
        front = (front + 1) % MAX_ITEMS;
        orderCount--;
    }
    else {
        cout << "No orders to process." << endl;
    }
}

// User interface functions
void userInterface() {
    int choice, id;
    double price;
    bool isAvailable;
    string name;

    while (true) {
        cout << "\n1. Display Menu\n2. Add Item to Cart\n3. Remove Item from Cart\n";
        cout << "4. Display Cart\n5. Place Order\n6. Process Orders\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayMenu();
            break;
        case 2:
            cout << "Enter the name of the item to add to cart: ";
            cin.ignore();  // Clear the input buffer to handle strings properly after integer input
            getline(cin, name);  // Use getline to allow names with spaces
            addToCart(name);
            break;

        case 3:
            removeFromCart();
            break;
        case 4:
            displayCart();
            break;
        case 5:
            if (cartSize > 0) {
                double totalPrice = 0;
                for (int i = 0; i < cartSize; i++) {
                    totalPrice += cart[i].price;
                }
                cout << "your order is places\n";
                enqueueOrder(totalPrice, cartSize);
                
                cartSize = 0;  // Empty the cart after placing the order
            }
            else {
                cout << "Cart is empty.\n";
            }
            break;
        case 6:
            dequeueOrder();
            break;
        case 7:
            cout << "Exiting program.\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void populateMenu() {
    addItem(0, "Burger", 5.99, true);
    addItem(1, { "Pizza" }, 11.99, true);
    addItem(2, { "Taco" }, 2.99, false);   // Not available
}

int main() {
    // Populate menu with some items
    populateMenu();

    userInterface();
    return 0;
}
