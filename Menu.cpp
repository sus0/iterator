#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>
#include "Menu.h"

using namespace std;


//****************************************************************************
// MENU
//****************************************************************************

Menu::Menu (const string name) : MenuComponent(name) {}

Menu::~Menu() {
	for (vector<MenuComponent*>::iterator i = entries_.begin(); i != entries_.end(); ++i) {
        if ( *i ) {
            delete *i;
            *i = NULL;
        }
    }
}


void Menu::add( MenuComponent* newEntry ) {
    newEntry->menuDepthInc();
    entries_.push_back( newEntry );
}


void Menu::remove( string name ) {
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        if ( (*it)->name() == name ) {
            delete *it;
            entries_.erase( it );
            return;
        }
    }
}


int Menu::numChildren() const {
    return entries_.size();
}


int Menu::size() const {
    int size = 1;
    
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        size += (*it)->size();
    }
    
    return size;
}


MenuComponent* Menu::getChild( int i ) const {
    return entries_.at(i);
}


void Menu::menuDepthInc() {
    vector<MenuComponent*>::iterator it;
    
    MenuComponent::menuDepthInc();
    for (it = entries_.begin(); it != entries_.end(); it++ ) {
        (*it)->menuDepthInc();
    }
}


void Menu::print ( ostream& sout ) const {
    sout << "\n" << menuDepth() << name() << ":";
}

class Menu::MenuIterator : public Iterator {
public: 
	MenuIterator(MenuComponent* root) : Iterator(root) {
		processNewRoot(root);
	}
	MenuIterator(MenuComponent* root, MenuComponent* cursor, stack< pair< MenuComponent*, int> > buf):
		Iterator(root, cursor), buf_(buf) {}
	virtual Iterator& operator++() {
		while (!buf_.empty()) {
			pair<MenuComponent*, int> curr = buf_.top();
			buf_.pop();
			int size = curr.first->numChildren();
			if (size == 0) {
				cursor_ = curr.first;
				return *this;
			}
			// it's a root
			else {
				int count = curr.second;
				if (count == size) {
					continue;
				}
				else {
					buf_.push(pair<MenuComponent*, int>(curr.first, (count + 1)));
					MenuComponent* temp;
					temp = curr.first->getChild(count);
					processNewRoot(temp);
					return *this;
				}
			}
		}
		cursor_ = NULL;
		return *this;
	}
	virtual Iterator& operator++(int) {
		MenuIterator old(root_, cursor_, buf_);
		++(*this);
		return old;
	}

private:
	stack< pair< MenuComponent*, int> > buf_;
	void processNewRoot(MenuComponent* root) {
		MenuComponent* comp = root;
		while (comp->numChildren() != 0) {
			buf_.push(pair<MenuComponent*, int>(comp, 1));
			comp = comp->getChild(0);
		}
		cursor_ = comp;
	}
};

Iterator Menu::begin() {
	return MenuIterator(this);
}

Iterator Menu::end() {
	return Iterator(this, NULL);
}
