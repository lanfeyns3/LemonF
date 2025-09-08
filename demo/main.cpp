#include "../include/lemon-parser.h"
#include "../include/lemon-serializer.h"

#include <iostream>

class Time
{
public:
    int start,end;
    
    uint32_t LemonLengthRead() {
        return 2;
    }

    std::any LemonRead(uint32_t index) {
        int retValue = 0;
        switch (index)
        {
        case 0:
            retValue = start;
            break;
        case 1:
            retValue = end;
            break;
        default:
            break;
        }

        return retValue;
    }
};


int main() {
    auto* lemonObject = lemon::parser::create("./myTest.scene");

    lemonObject->SwitchMode();
    lemonObject->AddVariable("This is a Lemon Object Variable");
    lemonObject->SwitchMode();
    lemonObject->AddVariable("Variables are used for the user and will be neglected by the serializer");
    lemonObject->AddVariable("By default there will always be a new line on everything but you can use the SwitchMode() function to disable that");

    lemonObject->PreBodyTag("World");
    lemonObject->AddBody();

    lemonObject->AddVariable("This is a Body. Bodies are used for splitting sections off when serializing. To make the process of searching faster you can add a tag and use the .find() function to make it faster to find the body");

    lemonObject->PreBodyTag("Player");
    lemonObject->AddBody();

    lemonObject->AddVariable("Nesting is also possible, it'll be weird if it wasnt");

    lemonObject->AddItem("Life",100);
    lemonObject->AddItem("MaxLife",200);
    lemonObject->AddItem("Name","Hello, World!");
    lemonObject->AddItem("First letter in name",'H');
    lemonObject->AddItem("Alive",true);
    lemonObject->AddItem("Last Name",std::string("Hello this is the last name"));

    Time time;
    time.end = 42;
    time.start = 0;

    lemonObject->AddItem("Time",time);

    lemonObject->EndBody();

    lemonObject->EndBody();

    lemonObject->AddSeparator();
    lemonObject->AddSeparator("-----------------------------------");

    lemonObject->AddVariable("That is all for now here is for speed of 500 items in a body");

    lemonObject->AddBody();

    for (int i = 0; i < 501; i++) {
        lemonObject->AddItem(std::to_string(i).c_str(),i);
    }

    lemonObject->EndBody();

    delete lemonObject;
}