# Stopwatch

Class to time sections of code.

## How to use

Object of this class has 4 public member functions:

- ```Start(const std::string& segment_name, const bool& announce=True)```
- ```Stop(const std::string& segment_name, const bool& announce=True)```
- ```Summary(void)```
- ```Clear(void)```

## Sample 

#### StopwatchTest.cpp
```
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
```

#### Output:
```
Segment 1 starting...
Iteration starting...
Iteration done
Iteration starting...
Iteration done
Iteration starting...
Iteration done
Iteration starting...
Iteration done
Iteration starting...
Iteration done
Segement 2 starting...
Segement 2 done
Segment 1 done
--------------------
Summary:
Segment 1: 7.00076 seconds
Segement 2: 1.00009 seconds
Iteration: 5.00049 seconds
For iteration4: 1.00009 seconds
For iteration3: 1.00009 seconds
For iteration2: 1.00009 seconds
For iteration1: 1.00009 seconds
For iteration0: 1.0001 seconds
--------------------
Segment 3 starting...
Segment 3 done
--------------------
Summary:
Segment 3: 1.00009 seconds
--------------------
```