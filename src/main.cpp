#include "RunSession.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {
    srand(time(nullptr));

    RunSession run;
    run.start();

    std::cout << "\nTekan Enter untuk keluar...";
    std::cin.get();
    return 0;
}
