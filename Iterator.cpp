#include "Iterator.h"

Iterator::Iterator(MenuComponent* root) : root_(root) {}
Iterator::Iterator(MenuComponent* root, MenuComponent* cursor) : root_(root), cursor_(cursor) {}
//Iterator::Iterator() : root_(NULL), cursor_(NULL) {}

bool Iterator::operator==(const Iterator& other) const {
	return (cursor_ == other.cursor_);
}

bool Iterator::operator!=(const Iterator& other) const {
	return !(cursor_ == other.cursor_);
}
MenuComponent* Iterator::operator*() const{
	return cursor_;
}

MenuComponent* Iterator::operator->() const{
	return cursor_;
}

Iterator& Iterator::operator++() {
	if (cursor_ == root_) {
		cursor_ = NULL;
	}
	return *this;

}

Iterator& Iterator::operator++(int) {
	Iterator old = Iterator(root_, cursor_);
	++(*this);
	return old;
}