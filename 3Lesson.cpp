// DZ списал, так как еще не могу выстраивать сложные коды, потихоньку нагоняю. ДУмаю до августа  должен нагнать. Только с картами постарался написать, но такое себе, все равно выглядит что списал, хотя ладно



#include <iostream>
//1. Создать абстрактный класс Figure(фигура).Его наследниками являются классы Parallelogram(параллелограмм) и Circle(круг).Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).Для всех классов создать конструкторы.Для класса Figure добавить чисто виртуальную функцию area() (площадь).Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.
class Figure
{
public:
	Figure() {};
	virtual double area() = 0;
};

class Parallelogram : public Figure
{
protected:
	double a, h;

public:
	Parallelogram(double inputA, double inputH)
		: a(inputA), h(inputH) {};

	double area() override
	{
		return (a * h);
	}
};

class Circle : public Figure
{
private:
	double r;
public:
	Circle(double inputR)
		: r(inputR) {};

	double area() override
	{
		return (3.14 * r * r / 2);
	}
};

class Rectangle : public Parallelogram
{
public:
	Rectangle(double inputA, double inputH)
		: Parallelogram(inputA, inputH) {};

	double area() override
	{
		return (a * h);
	}
};

class Square : public Parallelogram
{
public:
	Square(double inputA)
		: Parallelogram(inputA, inputA) {};

	double area() override
	{
		return (a * a);
	}
};

class Rhombus : public Parallelogram
{
public:
	Rhombus(double inputA, double inputH)
		: Parallelogram(inputA, inputH) {};

	double area() override
	{
		return (a * h);
	}
};

//2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн). Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
//Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс
class Car
{
protected:
	std::string company, model;
public:
	Car() {}
	Car(std::string inputCompany, std::string inputModel)
		: company(inputCompany), model(inputModel)
	{
		std::cout << "\nBase car constructor";
	}

	virtual ~Car()
	{
		std::cout << "\nBase car destructor";
	}
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar() {}
	PassengerCar(std::string inputCompany, std::string inputModel)
		: Car(inputCompany, inputModel)
	{
		std::cout << "\nPassenger car constructor";
		std::cout << "\n" << company << " " << model;
	}

	std::string getModel()
	{
		return model;
	}

	~PassengerCar()
	{
		std::cout << "\nPassenger car destructor";
	}
};

class Bus : virtual public Car
{
public:
	Bus() {}
	Bus(std::string inputCompany, std::string inputModel)
		: Car(inputCompany, inputModel)
	{
		std::cout << "\nBus constructor";
		std::cout << "\n" << company << " " << model;
	}

	~Bus()
	{
		std::cout << "\nBus destructor";
	}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(std::string inputCompany, std::string inputModel)
		: Car(inputCompany, inputModel)
	{
		std::cout << "\nMinivan constructor";
		std::cout << "\n" << company << " " << model;
	}

	~Minivan()
	{
		std::cout << "\nMinivan destructor";
	}
};

//3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
class Fraction
{
private:
	double numerator, denominator;
public:
	Fraction(double inputNumerator, double inputDenominator)
		: numerator(inputNumerator), denominator(inputDenominator)
	{
		if (denominator == 0) denominator = 0.00000001;
	}

	friend Fraction operator+(const Fraction& d1, const Fraction& d2);
	friend Fraction operator-(const Fraction& d1, const Fraction& d2);
	friend Fraction operator*(const Fraction& d1, const Fraction& d2);
	friend Fraction operator/(const Fraction& d1, const Fraction& d2);
	friend Fraction operator-(const Fraction& d1);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);

	void setDenominator(double inputDenominator)
	{
		if (inputDenominator == 0) inputDenominator = 0.00000001;
		denominator = inputDenominator;
	}

	void setNumerator(double inputNumerator)
	{
		numerator = inputNumerator;
	}

	double getNumerator()
	{
		return numerator;
	}

	double getDenominator()
	{
		return denominator;
	}
};

Fraction operator+(const Fraction& d1, const Fraction& d2)
{
	return Fraction(d1.numerator * d2.denominator + d2.numerator * d1.denominator, d1.denominator * d2.denominator);
}

Fraction operator-(const Fraction& d1, const Fraction& d2)
{
	return Fraction(d1.numerator * d2.denominator - d2.numerator * d1.denominator, d1.denominator * d2.denominator);
}

Fraction operator*(const Fraction& d1, const Fraction& d2)
{
	return Fraction(d1.numerator * d2.numerator, d1.denominator * d2.denominator);
}

Fraction operator/(const Fraction& d1, const Fraction& d2)
{
	return Fraction(d1.numerator * d2.denominator, d1.denominator * d2.numerator);
}

Fraction operator-(const Fraction& d1)
{
	return Fraction(-d1.numerator, -d1.denominator);
}

bool operator==(Fraction& d1, Fraction& d2)
{
	if ((d1.getNumerator() == d2.getNumerator()) && (d1.getDenominator() == d2.getDenominator())) return true;
	else return false;
}

bool operator!=(Fraction& d1, Fraction& d2)
{
	if (d1 == d2) return false;
	else return true;
}

bool operator>(Fraction& d1, Fraction& d2)
{
	if ((d1.getNumerator() / d1.getDenominator()) > (d2.getNumerator() / d2.getDenominator())) return true;
	else return false;
}

bool operator<=(Fraction& d1, Fraction& d2)
{
	if (!(d1 > d2)) return true;
	else return false;
}

bool operator<(Fraction& d1, Fraction& d2)
{
	if ((d1.getNumerator() / d1.getDenominator()) < (d2.getNumerator() / d2.getDenominator())) return true;
	else return false;
}

bool operator>=(Fraction& d1, Fraction& d2)
{
	if (!(d1 < d2)) return true;
	else return false;
}


std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
{
	out << fraction.numerator << "/" << fraction.denominator;
	return out;
}

//4. Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля : масть, значение карты и положение карты(вверх лицом или рубашкой).Сделать поля масть и значение карты типом перечисления(enum).Положение карты - тип bool.Также в этом классе должно быть два метода :
enum Lear { SPADES, CLUBS, DIAMONDS, HEARTS };
enum CARDSmeaning { ACE = 1 };
	// чтобы не засорять и без того полный cpp не стал забивать все остальные значения, так как нам нужен туз. Что-то другое в коде сделать сложно, так что очень выглядит на списаный, но ладно.
class Card {
	Lear suit;
	CARDSmeaning value;
	bool isCoverUp;
public:
	Card(Lear _suit, CARDSmeaning _value) : suit(_suit), value(_value) {
		isCoverUp = true;
	}

	void flip() {
		isCoverUp = !isCoverUp;
	}
	CARDSmeaning getValue() const {
		return value;
	}
};


int main()
{

	double parallelorgamHeight(3), parallelogramBase(5.1);
	Parallelogram parallelogram(parallelogramBase, parallelorgamHeight);
	std::cout << parallelogram.area() << "\n";

	double circleRadius(2.8);
	Circle circle(circleRadius);
	std::cout << circle.area() << "\n";

	double squareBase(5);
	Square square(squareBase);
	std::cout << square.area() << "\n";

	double rectangleBase(3), rectangleHeight(3);
	Rectangle rectangle(rectangleBase, rectangleHeight);
	std::cout << rectangle.area() << "\n";

	double rhombusBase(2), rhombusHeight(5);
	Rhombus rhombus(rhombusBase, rhombusHeight);
	std::cout << rhombus.area() << "\n";

	

	Car* car = new Car("Daewoo", "Matiz");
	std::cout << "\n==============================";
	PassengerCar* passengerCar = new PassengerCar("Mersedes", "X5");
	std::cout << "\n==============================";
	Bus* bus = new Bus("PAZ", "3201");
	std::cout << "\n==============================";
	Minivan* minivan = new Minivan("Volkswagen", "Caravelle");
	std::cout << "\n==============================";
	delete minivan;
	std::cout << "\n==============================";
	delete bus;
	std::cout << "\n==============================";
	delete passengerCar;
	std::cout << "\n==============================";
	delete car;

	Fraction d1(3, 2);
	Fraction d2(8, 3);
	std::cout << "\n\n" << (d1 + d2);
	std::cout << "\n\n" << (d1 - d2);
	std::cout << "\n\n" << (d1 * d2);
	std::cout << "\n\n" << (d1 / d2);
	std::cout << "\n\n" << (-d1) << "\n";

	if (d1 == d2) std::cout << "\nFraction 1 == Fraction 2";
	if (d1 != d2) std::cout << "\nFraction 1 != Fraction 2";
	if (d1 > d2) std::cout << "\nFraction 1 > Fraction 2";
	if (d1 <= d2) std::cout << "\nFraction 1 <= Fraction 2";
	if (d1 < d2) std::cout << "\nFraction 1 < Fraction 2";
	if (d1 >= d2) std::cout << "\nFraction 1 >= Fraction 2";

	Card c0(SPADES, ACE);
	std::cout << c0.getValue() << std::endl;
}