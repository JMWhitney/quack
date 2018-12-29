// add code to these functions to make Quack do something useful

#include "quack.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Quack::YOUR_NAME[]{"Justin Whitney"};

// change the value of this variable to true if you're doing the Premium version
const bool	Quack::PREMIUM_VERSION{true};

Quack::Quack(int capacity, int growBy) :
	// replace these initializations with the ones you actually need
	items{new char[capacity+1]}, //It must be capacity+1 to account for null terminator.
	capacity{capacity},
	growBy{growBy},
	count{0},
	front{0},
	back{0}
{
	initArray();	// you are required to call this function here, and
					// it must be the first thing in the constructor body
}

Quack::~Quack(void)
{
	delete[] items;
}

int Quack::incr(int i) 
{
	i++;
	if (i >= capacity) //wrap around
		return 0;
	 else 
		return i;
	
}

int Quack::decr(int i) 
{
	i--;
	if(i < 0) //wrap around
		return capacity -1;
	else
		return i;
}

void Quack::growArray(void) 
{
	//Rotate array elements so front is at the first array index
	while(front != 0) {
		char ch = items[0];
		for(int i = 0; i < capacity; i++) {
			items[i] = items[incr(i)];
		}
		items[capacity-1] = ch;
		front = incr(front);
		back = incr(back);
	}
	char* temp = new char[capacity+growBy];			//Create new larger array

	strcpy(temp, items);							//Copy contents of old array

	for(int i = capacity; i < capacity+growBy; i++) {//Clear garbage values from end of array
		temp[i] = '\0';
	}
	capacity = capacity + growBy;					//Indicate quack size has grown
	delete[] items;									//delete old array
	items = temp;									//Point private data to new array
	return;
}

// items are pushed to successively LOWER slots in the circular array
// (except for when the beginning of the array "wraps around" to the end)
bool Quack::pushFront(const char ch)
{	
	//If array is full grow the quack and push
	if(count == capacity){
		growArray();
	}

	if(count == 0) {	//Initial condition if quack is empty
		items[front] = ch;
		count++;
		return true;
	}
	//Push onto quack
	front = decr(front); 
	items[front] = ch;
	count++;
	
	return true;
}

// items are pushed to successively HIGHER slots in the circular array
// (except for when the end of the array "wraps around" to the beginning)
bool Quack::pushBack(const char ch)
{
	//If array is full grow the array
	if(count == capacity){
		growArray();
	}
	if(count == 0) { 	//Initial Condition if quack is empty
		items[back] = ch;
		count++;
		return true;
	}

	//Push onto stack
	back = incr(back);
	items[back] = ch;
	count++;

	return true;
}

bool Quack::popFront(char& ch)
{
	//If array is empty 
	if(count == 0) {
		return false;
	} else {
		ch = items[front]; 
		front = incr(front); //Shrink the size of the quack
		count--;
	}
	return true;
}

bool Quack::popBack(char& ch)
{
	//If array is empty 
	if(count == 0) {
		return false;
	} else {
		ch = items[back];
		back = decr(back); //Shrink the size of the quack
		count--;
	}
	return true;
}

void Quack::rotate(int r)
{
	if (r > 0) { //rotate left
		for(int i = 0; i < r; i++) {
			 back = incr(back); 
			 items[back] = items[front]; 
			 front = incr(front);
		}
		return;
	}
	if (r < 0) { //rotate right
		for(int i = 0; i > r; i--) {
			front = decr(front);
			items[front] = items[back];
			back = decr(back);
		}
		return;
	}
	if(r == 0) { //Do nothing
		return;
	}
	return;
}

void Quack::reverse(void)
{
	//vars
	int first = front;
	int second = back;
	char temp;
	int i = count / 2;

	//Loop to swap corresponding quack elements
	//It achieves this by swapping the outer most elements
	//Moving towards the center of the quack swapping elements along the way
	while(i) { 
		temp = items[first]; 
		items[first] = items[second];
		items[second] = temp;
		first = incr(first);
		second = decr(second);
		i--;
	}
	return;
}

int	Quack::itemCount(void)
{
	return count;
}

ostream& operator<<(ostream& out, Quack *q)
{
	char ch;
	int i = q->front;
	if(q->count == 0) {						
		out << "quack: empty" << endl << endl;	 
	} else  {
		out << "quack: "; 
		 while(i != q->back) {			//Access each element of quack except last
			ch = q->items[i];
			out << ch << ", ";			//Print
			i = q->incr(i);
		}
		ch = q->items[q->back];			//Print last element
		out << ch << endl << endl;
	}
	// returning out is ALWAYS required for an operator<< overload
	return out;
}
