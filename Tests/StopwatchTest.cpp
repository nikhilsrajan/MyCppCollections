#include "../Stopwatch/Stopwatch.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void DoSomethingForSeconds(const int& seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main() {
    Stopwatch sw;
    
    sw.Start("Segment 1");
    DoSomethingForSeconds(1);

    for(int i = 0; i < 5; ++i) {
        sw.Start("Iteration");      // cummulative
        sw.Start("For iteration" + std::to_string(i) , false);
        DoSomethingForSeconds(1);
        sw.Stop("For iteration" + std::to_string(i), false);
        sw.Stop("Iteration");
    }

    sw.Start("Segement 2");
    DoSomethingForSeconds(1);
    sw.Stop("Segement 2");
    sw.Stop("Segment 1");

    std::cout << "--------------------" << std::endl;
    std::cout << "Summary:\n";
    sw.Summary();
    std::cout << "--------------------" << std::endl;

    sw.Clear();

    sw.Start("Segment 3");
    DoSomethingForSeconds(1);
    sw.Stop("Segment 3");

    std::cout << "--------------------" << std::endl;
    std::cout << "Summary:\n";
    sw.Summary();
    std::cout << "--------------------" << std::endl;

    return 0;
}