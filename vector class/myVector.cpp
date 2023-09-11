#include <iostream>

using namespace std;

template <typename T>
class MyVector {
public:
	//-------------Constructors & Destructor -------------
	MyVector();	//default constructor					
	MyVector(int sz); //constructor with size
	MyVector(const MyVector<T>& vin); //copy constructor
	~MyVector(); //Destructor

	//Overloaded Operator []
	T operator[](int i);

	//Copy assignment operator
	void operator=(const MyVector<T>& vin);

	//-------------Accessors-------------
	int Size();
	int getCapacity();
	const T& at(int i);
	bool empty();
	//-------------Mutators-------------
	void insert(int i, T ele);
	void erase(int i);
	void pushBack(const T& ele);

private:
	T* data;
	int capacity;
	int size;

	void resize(int newSize) {
		//allocate a new block of data
		//copy and move data into the new block
		//delete previous data
		T* newBlock = new T[newSize];

		if (newSize < size) {
			size = newSize;
		}
		for (int i = 0; i < size; i++) {
			newBlock[i] = data[i];
		}
		delete[] data;
		data = newBlock;
		capacity = newSize;
	}
};
//-------------Constructors & Destructor-------------
template <typename T>
MyVector<T>::MyVector() {
	cout << "Default constructor called\n";
	capacity = 1;
	size = 0;
	data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(int sz) {
	cout << "Constructor with input sz called\n";
	size = 0;
	capacity = sz;
	data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& vin) {
	cout << "Copy constructor called\n";
	size = vin.size;
	capacity = vin.capacity;
	data = new T[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = vin.data[i];
	}
}

template <typename T>
MyVector<T>::~MyVector() {
	delete[] data;
	cout << "Destructor called\n";
}

//-------------Overloaded Operator-------------
template <typename T>
T MyVector<T>::operator[](int i) {
	return data[i];
}
//-------------Copy Assignment Operator-------------
template <typename T>
void MyVector<T>::operator=(const MyVector<T>& vin) {
	cout << "Copy assignment operator called\n";
	capacity = vin.capacity;
	size = vin.size;
	data = new T[capacity];

	for (int i = 0; i < size; i++) {
		data[i] = vin.data[i];
	}
}

//-------------Mutators-------------
template <typename T>
void MyVector<T>::pushBack(const T& ele) {
	if (size >= capacity) {
		//Doubles the capacity of the vector
		resize(capacity * 2);
	}
	data[size] = ele;
	size++;
}

template <typename T>
void MyVector<T>::erase(int i) {
	if (i < 0 || i >= size) {
		cout << i << " is an invalid index" << endl;
		return;
	}
	if (i == (size - 1)) {
		size--;
		//resize(size);
		return;
	}
	for (int temp = i; temp < size - 1; temp++) {
		data[temp] = data[temp + 1];
	}
	size--;
}

template <typename T>
void MyVector<T>::insert(int i, T ele) {
	//Returns if "i" is not a valid index number
	if ((i < 0) || (i > size)) {
		cout << i << " is not a valid index number" << endl;
		return;
	}

	if (size >= capacity) {
		resize(capacity * 2);
	}
	data[i] = ele;
}

//-------------Accessors-------------
template <typename T>
const T& MyVector<T>::at(int i) {
	return data[i];
}

template <typename T>
int MyVector<T>::Size() {
	return size;
}

template <typename T>
bool MyVector<T>::empty() {
	if (size > 0) {
		return false;
	}
	return true;
}

template <typename T>
int MyVector<T>::getCapacity() {
	return capacity;
}

int main() {
	MyVector<int> v1; //Calls Default constructor

	MyVector<char> v2(2); //Calls Constructor with "sz" input
	
	MyVector<int> v3 = v1; //Calls Copy constructor
	
	MyVector<int> v4;
	
	MyVector<float> emptyVector;
	
	//-----pushBack function demonstrated-----
	v1.pushBack(1);
	v1.pushBack(2);
	v1.pushBack(3);
	cout << endl << "The size of v1 is: " << v1.Size() << endl;

	v2.pushBack('a');
	v2.pushBack('b');
	v2.pushBack('c');

	//-----Demonstrates the "at" function and templated class-----
	for (int i = 0; i < v2.Size(); i++) {
		cout << v2.at(i) << endl;
	}
	cout << "-------------------------\n";

	v4 = v1; //Calls copy assignment operator

	//-----Demonstrates the "at" function-----
	for (int i = 0; i < v1.Size(); i++) {
		cout << v1.at(i) << endl;
	}
	cout << "-------------------------\n";

	//-----Demonstrates insert function-----
	v4.insert(1, 22);

	//-----Demonstrates the overloaded operator "[]"-----
	for (int i = 0; i < v4.Size(); i++) {
		cout << v4[i] << endl;
	}
	cout << "-------------------------\n";
	
	//-----Empty function demonstrated-----
	cout << "Empty vector value printed (1 = true) : " << emptyVector.empty() << endl;
	cout << "Non-empty vector result printed (0 = false) : " << v1.empty() << endl;
	cout << "-------------------------\n";

	//-----erase function demonstrated-----
	v1.erase(0);

	//-----Prints only 2 and 3-----
	for (int i = 0; i < v1.Size(); i++) {
		cout << v1.at(i) << endl;
	}
	cout << "-------------------------\n";

	return 0;
}