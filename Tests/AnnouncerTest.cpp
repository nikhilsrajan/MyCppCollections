#include "../Announcer/Announcer.hpp"

int main() {
    Announcer announce;

    (announce << "This " << 15 << " the message " << 1.0 << " want to print.").now();

    return 0;
}