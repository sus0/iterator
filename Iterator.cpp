#include "Iterator.h"
#include "MenuComponent.h"

using namespace std;

Iterator::Iterator(MenuComponent* root) : root_(root) {
	//processRoot(root);
}
Iterator::Iterator(MenuComponent* root, MenuComponent* cursor) : root_(root), cursor_(cursor){}

Iterator::Iterator(MenuComponent* root, MenuComponent* cursor, stack< pair< MenuComponent*, int> > buff) : root_(root), cursor_(cursor), buf_(buff){}
bool Iterator::operator==(const Iterator& other) const {
	return (cursor_ == other.cursor_);
}

bool Iterator::operator!=(const Iterator& other) const {
	return (cursor_ != other.cursor_);
}
MenuComponent* Iterator::operator*() const{
	return cursor_;
}

MenuComponent* Iterator::operator->() const{
	return cursor_;
}

Iterator& Iterator::operator++() {
	while (!buf_.empty()) {
		pair<MenuComponent*, int> curr = buf_.top();
		buf_.pop();
		MenuComponent* currItem = curr.first;
		int count = curr.second;
		if (count >= 0) {
			if (count >= currItem->numChildren()) continue;
			MenuComponent* childItem = currItem->getChild(count);
			buf_.push(pair<MenuComponent*, int>(currItem, (count + 1)));
			buf_.push(pair<MenuComponent*, int>(childItem, 0));
			cursor_ = childItem;
			return *this;
		}
		else {
			buf_.push(pair<MenuComponent*, int>(currItem, (count+1)));
			cursor_ = currItem;
			return *this;
		}
	}
	cursor_ = NULL;
	return *this;
}


Iterator& Iterator::operator++(int) {
	Iterator old(root_, cursor_, buf_);
	++(*this);
	return old;
}

void Iterator::processRoot() {
	buf_.push(pair<MenuComponent*, int>(root_, 0));
}
