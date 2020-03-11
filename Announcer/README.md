# Announcer

Class to act as a mediator to ```std::cout```.

Could also be used as a base class for a type flexible logger.

## How to use

An object of this class has the following public function and operator:

- ```operator << (const T&)```
- ```now(void)```

## Why?

You could simply do the following..

```std::cout << [stuff] << std::endl```

..and achieve the same thing the class does.

My purpose was to be able to have **control between** the point I **create the message**, and I **print the message**.

I could now edit the function ```now(void)``` to do other things other than just print the ```[stuff]``` into the terminal.

## Sample

#### AnnouncerTest.cpp
```
#include "../Announcer/Announcer.hpp"

int main() {
    Announcer announce;

    (announce << "This " << 15 << " the message " << 1.0 << " want to print.").now();

    return 0;
}
```

#### Output:
```
This 15 the message 1 want to print.
```
