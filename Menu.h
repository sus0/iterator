#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

#include "MenuComponent.h"
#include "Iterator.h"

class Menu : public MenuComponent {
public:
    // constructor
	Menu (const std::string);
	virtual ~Menu();
	
	// implement composite
	virtual void add( MenuComponent* newEntry );
    virtual void remove( std::string name );
	virtual int numChildren() const;
	virtual MenuComponent* getChild(int i) const;
	
	// implement shared operations
    virtual void menuDepthInc();
    virtual int size() const;
	class MenuIterator;
	virtual Iterator begin();
	virtual Iterator end();
protected:
    virtual void print ( std::ostream& ) const;
    
private:
	std::vector<MenuComponent*> entries_;
};



#endif
