#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "What's your age?" << std::endl;
    int age;
    std::cin >> age;
    std::cout << "You are " << age << " years old." << std::endl;
    std::cout << "What's your name?" << std::endl;
    std::string name;
    std::getline(std::cin >> std::ws, name);
    std::cout << "Hello, " << name << "!" << std::endl;
    
    return 0;
} 