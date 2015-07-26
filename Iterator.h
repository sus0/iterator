#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <utility>

#define NULL 0
class MenuComponent;

class Iterator {
public:
	virtual bool operator==(const Iterator&) const; //to be able to compare iterator values
	virtual bool operator!=(const Iterator&) const; //to be able to compare iterator values
	virtual MenuComponent* operator*() const; // 0; //to be able to dereference an iterator, to retrieve a MenuComponent*
	virtual MenuComponent* operator->() const;// = 0; //to be able to dereference an iterator, to retrieve a MenuComponent*
	virtual Iterator& operator++();  //prefix - to be able to advance the iterator
	virtual Iterator& operator++(int); //postfix - to be able to advance the iterator

	Iterator(MenuComponent*);
	Iterator(MenuComponent*, MenuComponent*);
	Iterator(MenuComponent*, MenuComponent*, std::stack< std::pair< MenuComponent*, int> >);
	void processRoot();
	//Iterator();
	//virtual ~Iterator();

protected:
	MenuComponent* root_;
	MenuComponent* cursor_;
	std::stack< std::pair< MenuComponent*, int> > buf_;
private:
	
};

#endif
