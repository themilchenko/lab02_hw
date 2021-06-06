#include <iostream>
#include <string>

int main()
{
    std::string name; // имя пользователя
    std::getline(std::cin, name); // ввод имени с клавиатуры
    std::cout << "Hello world from " << name << std::endl; // вывод имени на экран
    return 0;
}
