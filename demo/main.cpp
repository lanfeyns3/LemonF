#include "../include/lemon-parser.h"
#include "../include/lemon-serializer.h"

#include <iostream>

int main() {
    auto* lemonObject = lemon::parser::create("./myTest.scene");

    lemonObject->SwitchMode();
    lemonObject->AddVariable("This is a Lemon Object Variable");
    lemonObject->SwitchMode();
    lemonObject->AddVariable("Variables are used for the user and will be neglected by the serializer");

    lemonObject->PreBodyTag("World");
    lemonObject->AddBody();

    lemonObject->AddVariable("This is a Body. Bodies are used for splitting sections off when serializing. To make the process of searching faster you can add a tag and use the .find() function to make it faster to find the body");

    lemonObject->PreBodyTag("Player");
    lemonObject->AddBody();



    lemonObject->EndBody();

    lemonObject->EndBody();


    delete lemonObject;
}