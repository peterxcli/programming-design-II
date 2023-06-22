#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    int a = std::atoi(argv[1]);
    for (int i = 0; i <= a; i++) {
        std::cout << '(' << i << ',' << a - i << ")\n";
    }
    std::cout << (a / 2) * (a - a / 2) << "\n";
	
    return 0;
}

