#include <Menu.h>


int main() {


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Dialog dialog;
    dialog.start();




    return 0;
}