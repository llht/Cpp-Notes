//C++ primer note for chapter 7
//create a new class
#include<string>
#include<iostream>
using namespace std;


//The main practicing class in this chapter, shows many new features in constructing a C++ class
//practice 7.5 create a new class named Person
class Person 
{
private:
    std::string name;
    std::string address;
public:
	//the 1st const means this is const
	//the 2nd const means return type is string const&
    auto get_name() const -> std::string const& { return name; }
    auto get_addr() const -> std::string const& { return address; }
	Person() = default;
	//constructor can be defined like this without function body 
	Person(const string &n, const string &add) :name(n), address(add) {};
	Person(istream &is) { read (is, *this); };
};

//use non-member function to create read and print functions
friend istream &read (istream &is, Person &item){
	return is >> item.name >> item.address;
}

friend ostream &print (ostream &os, const Person &person){
	return os << person.name << " " << person.address;
	
}



//7.1.3 non-member function
//finds a new ways to define the non-member function 
//we can use cin in this function , I have never seen before!!!
read(cin, Person); // we can use cin like this.
istream &read (istream &is, Sales_data &item){
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}


//7.14 constructor
//constructor cannnot be defined as const function  
//" constructor() = default; " to explicitly define the constructor
//we can also use " : " to initialize the parameters

//7.15 copy, assign and destruct
// ? ? ? where is the main content? Are you joking ? ? ?


//7.2 access control and packaging
//constructor and destructor are public function
//the interface should be defined as public, the private data shouldn't expose to outside of the class.

//7.2.1
//note friend to use the private data
//declare the friend function to use the private data
//in order to allow user use the friends , we should declare the function twice outside the class in the header

//1st
friend auto friend_function(A);
class A {
//2nd
friend auto friend_function(A);
private:
	int a;
}
friend auto friend_function( A object ) { return object.a; }


//Additional class features
making members inline
//7.3.1 
//mutable Data Members
class Screen {
public:
	void some_member() const;
private:
	mutable size_t access_ctr; //may change even in a const object
	//other members as before
};

void Screen::some_member() const {
	++ access_ctr;
}
//initializers for Data Members of Class Type
class Window_mgr {
	private:
		std::vector<Screen> screens {Screen(24, 80, ' ')} ;
};

//7.3.2
//7.3.2 
//functions that return *this
// return *this as reference in order to return the object itself 
inline Screen &Screen::set (pos r, pos col, char ch)
{
	contents[r*width + col] = ch;
	return *this;
}
//as above, we can use  these function like this
Screen.move().set();
//move and set the value of the cursor after moved

class Screen {
public:
	Screen &display(std::ostream &os) { do_display(os); return *this; }
	const Screen &display(std::ostream &os) const {os << contents; return *this; }
private:
	void do_display(std::ostream &os) const {os << contents;}
}
//the compiler can choose either const or non-const function to use
//but actually I think this action is redundant

//7.3.3
//7.3.3
//The defination and declaration of class
class Screen; //the declaration of class screen
//We can use an incomplete type in only limited ways: We can define pointers or
//references to such types, and we can declare (but not define) functions that use an incomplete type as a parameter or return type.

//7.3.4
//7.3.4
//there are friendships between classes, for example
class Screen {
	friend class Windows_mgr;
}
//Each class controls which classes or functions are its friends

//Making A Member Function a Friend, for example
class Screen {
	friend void Windows_mgr::clear(ScreenIndex);
}


//7.4
//7.4
//class scope
Because the return type appears before the name of the class is seen, 
it appears outside the scope of class Window_mgr. To use ScreenIndex for the return type, 
we must specify the class in which that type is defined.
// like this
Window_mgr::ScreenIndex
Window_mgr::addScreen( const Screen &s ) {
	screen.push_back(s);
	return screens.size() - 1;
}

//7.4.1
//7.4.1
//you cannot redefine a  val inside the class clope.
//like this 
typedef double money;
class Acount {
public:
	money balance() {return val;}
private:
	typedef double money; //error
	money bal;
}

//to better understand the class scope
//we have a good example here
typedef string Type;
Type initval(); //use 'string'
class Exersice {
public:
	typedef double Type;
	Type setVal(Type);//use 'double'
	Type initval();//use 'double'
private:
	int val;
};
Type Exersice::setVal(Type parm) { //use 'string', use 'double'
	val = parm + initVal();
	return val;
}


//7.5
//7.5
//Constructors Revisited
/*members that are const or references must be initialized*/
class ConstRef {
public:
	ConstRef(int ii);
private:
	int i;
	const int ci;
	int &ri;
}
/*
By the time the body of the constructor begins executing, 
initialization is complete. Our only chance to initialize const or
reference data members is in the constructor initializer. 
The correct way to write this constructor is*/
ConstRef::ConstRef(int ii) : i(ii), ci(ii), ri(i) { }

/*Form a habit to use constructor to initialize the vals*/
/*Constructors that do not need a parameter are also defalut constructors*/
Sales_data(std::istream &is = std::cin) { read(is, *this); }

/*intersting thing*/
/*delegating constructor*/
//for example
class Sales_data {
public:
	Sales_data(std::string s, unsigned cnt, double price) :
		bookNo(s), units_Sold(cnt), revenue(cnt *price) { }
	Sales_data() : Sales_data("", 0, 0) { }
	Sales_data(std::stirng s) : Sales_data(s, 0, 0) { }
	Sales_data(std::istream &is) : Sales_data() { read(is, *this ); }
}

//7.5.3
//7.5.3
//The Role of the Default Constructor 
The role of the default constructor cannot be ignored.

//7.5.4
//7.5.4
//Implicit Class-Type Conversions
/*we can convert string to Sales_data like this*/
string num_book = "99999999";
item.combine(null_book);
/*The compiler will automaticly apply only one class-type conversion*/
/*For example we can't act like this*/
item.combine("23232");
//this, otherwise, is correct
item.combine(string("4434343"));
item.combinr(Sales_data("23121"));


/*suppressing implicit conversions defined by constructors*/
//by using explicit
explicit Sales_data(const std::string &s) : bookNo(s) {}
//wrong example 
item.combine(null);
item.combine(cin);


/*explicit constructors can be used only for direct initialization*/
/*we can still use constructors explicitly conversions*/

/*verctor is expilict but string is not explicit*/

//7.5.5
//7.5.5
//Aggregate Classes

/*the features of an aggragate class*/
//1.All of its data members are public
//2.It does not define any constructors
//3.It has no in-class intilizers
//4.It has no base classes or virtual functions, which are class-related features
/*We can define an aggregate classes like this*/
struct Data{
		int val;
		string s;
}
/*And we can initial the data members like this*/
Data vall = { 0, "Anna" };

//7.5.6
//7.5.6
//Literal classes
/*The defination: An aggragate class whose data members are all of literal type is a literal class*/
/* Not a aggragate class, that meets the following restrictions, also literal*/
//1.all literal type
//2.at least one constexpr constrctor
//3.Constant expresion!!!!
//4.default destructor
/*here is an example of literal class*/
class Debug{
public:
	constexpr Debug(bool b = true) : hw(b), io(b), other(b) { }
	...
private:
	bool hw;
	bool io;
	bool other;
}


//7.6
//7.6
//static Class Members
/*Member that are assiocioted with classsed not objects*/
/*declare a static member*/
//just add static key word
class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double rate() { return interestRate; }
	static void rate(double) ;
private:
	std::string owner;
	static double interestRate;
	static double initRate();
}

/*using a class static member*/
//we can using the static member even if it's not instantiated
double r;
r = Account::rate();
//the member functio can use static members directly


/*if you want to initialize a static member, you have to add constexpr*/
class n{
	static constexpr int period = 30;
}


/*static members can be used in ways ordinary members can't*/
//1.static members can have imcomplete type
//2.we can use a static member as a default argument 
	



















