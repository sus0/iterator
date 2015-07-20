#include <string>
#include "MenuComponent.h"

using namespace std;

MenuComponent::MenuComponent( std::string name ) : name_(name), menuDepth_("") {}

void MenuComponent::menuDepthInc () {
    menuDepth_ = "\t" + menuDepth();
}


// operator<< simply calls mc->print(), and the different subclasses will override print() to specialize what is actually printed
ostream& operator<< ( ostream& sout, const MenuComponent* mc ) {
    mc->print(sout);
    return sout;
}