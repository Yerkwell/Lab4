#include <iostream>
#include <conio.h>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
//Ручная реализация списка как шаблонного класса
template <typename type>				//Объявляем класс "элемент" (т.к. к нему будет обращение в классе "список")
class element;							//Описание будет дальше
template <typename type>				//Класс "список объявляем шаблонным, т.к. будем создавать списки
class list								//элементов разных типов
{
	element<type>* first;				//Указатели на первый и последний элементы списка
	element<type>* last;
	int length;							//Количество элементов в списке
public:
	list()								//Конструктор. Обнуляем список при создании
	{
		first=last=0;
		length=0;
	}
	~list()
	{
		erase();						//Поскольку список использует динамическую память, при его уничтожении
	}									//надо эту память освободить
	void erase()
	{
		while(length)
			pop();
	}
	void push(type n)					//Добавление элемента в конец (в произвольное место добавлять не придётся)
	{									//При этом на входе получаем не элемент, а только его данные.
		element<type> *newel = new element<type>;		//Сам элемент генерируется на этом этапе
		newel->data=n;
		if (!length)
		{
			first=last=newel;							//Если список пуст, просто вставляем элемент в начало
		}
		else
		{
			last->next=newel;							//Иначе объявляем его последним 
			newel->prev=last;							//и передвигаем указатель последнего на него
			last=newel;
		}
		length++;
	}
	void pop()							//Удаление последнего элемента из списка
	{
		if (length)
		{
			element<type> *tek=last;
			last=last->prev;
			delete tek;
			if (length==1)
				first=NULL;
			length--;
		}
	}
	void del(type wh)					//Удаление из списка элемента, содержащего данные wh
	{
		element<type> *tek=first;
		for (int i=0; i<length; i++)
		{
			if ((*this)[i]==wh)
			{
				if (tek->next)
				tek->next->prev=tek->prev;
				else
					last=tek->prev;
				if (tek->prev)
				tek->prev->next=tek->next;
				else
					first=tek->next;
				delete tek;
				length--;
				break;
			}
			tek=tek->next;
		}
	}
	void print()					//Вывод на экран всего списка, при условии, что данные имеют тип, 
	{								//совместимый с cout
		if (length)
		{
		element<type> *tek = first;
		while(tek!=last)
		{
			cout<<tek->data<<endl;
			tek=tek->next;
		}
		cout<<last->data<<endl;
		}
	}
	void print_class()				//Вывод на экран всего списка, при условии, что данные представляют собой
	{								//экземпляры класса, имеющего метод print() для вывода себя на экран
		if (length)
		{
		element<type> *tek = first;
		while(tek!=last)
		{
			tek->data.print();
			tek=tek->next;
		}
		last->data.print();
		}
	}
	type& operator[](int i)		//Обращение к конкретному элементу списка по его номеру (причём по ссылке)
	{
		element<type> *tek=first;
		for (int j=0; j<i; j++)
		{
			tek=tek->next;
		}
		return tek->data;
	}
	list<type>(const list<type>& b):first(first),last(last),length(length){};	//Конструктор копирования
	list<type>& operator=(list<type>& b)						//Оператор присваивания
	{
		erase();
		for (int i=0; i<b.getLength(); i++)
			push(b[i]);
		return *this;
	}
	int getLength()												//Получение длины списка
	{
		return length;
	}
	bool exist(type find)				//Проверка, есть ли элемент с данными find в списке. Работает,
	{									//если определена операция сравнения == для данного типа данных			
		for (int i=0; i<length; i++)	
		{
			if ((*this)[i]==find)
				return 1;
		}
		return 0;
	}
};
template <typename type>				//Описание шаблонного класса "элемент"
class element
{
	type data;
	element* next;
	element* prev;
public:
	element()
	{
		next=prev=NULL;
	}
	friend class list<type>;			//Для прямого доступа к полям из класса "список" делаем его дружественным
};
///////////////////////////////////////////////////////////////////////////////////
class rib								//Класс "ребро"
{	
	int length;							//Длина (вес) ребра
	int start;							//Начальный узел
	int end;							//Конечный узел
public:
	rib():start(0),end(0),length(0){};	//Конструктор "по-умолчанию"
	rib(int start,int end,int length):start(start),end(end),length(length){};	//Конструктор, инициализирующий все поля класса
	bool operator==(rib a)				//Оператор сравнения двух рёбер. В данной реализации равными
	{									//считаем рёбра, совпадающие по началу и концу.
		if ((this->start==a.start)&&(this->end==a.end))
			return 1;
		else 
			return 0;
	}
	void print()						//Вывод ребра на экран
	{
		cout<<start<<" - "<<end<<":"<<length<<endl;		//<начало> - <конец>:<вес>
	}
	friend class graph;					//Опять же, для прямого обращения к полям класса из класса "граф"
};
class graph								//Класс "граф"
{
	list<int> nodes;					//Список узлов графа. Содержит только их номера для проверки наличия такого узла в графе
	list<rib> ribs;						//Список рёбер графа
public:
	void addNode()						//Добавление узла
	{
		nodes.push(nodes.getLength());	//Поскольку нумерация узлов не принципиальна, добавляем их по порядку
		addRib((nodes.getLength())-1,(nodes.getLength())-1,0);	//Для каждого узла тут же создаём ребро "из себя в себя" нулевого веса
	}
	void addRib(int start,int end,int length)	//Добавление ребра
	{
		rib a=rib(start,end,length);			//Создаём ребро
		if (!ribs.exist(a)&&nodes.exist(a.start)&&nodes.exist(a.end))	//Добавляем его в список только если там ещё нет ребра
			ribs.push(a);												//с теми же началом и концом, а также есть узлы, которые
	}																	//это ребро должно соединять
	void print()								//Вывод графа на экран
	{
		cout<<"Vershiny:\n";					//Сперва список вершин (узлов), затем список рёбер.
		nodes.print();
		cout<<"Ryobra:\n";
		ribs.print_class();
	}
	int* Dijkstra(int st)		//Собственно, алгоритм Дейкстры. st - вершина, для которой ищем минимальные расстояния
	{
		list <int> dots;		//dots - список ещё не обойдённых вершин
			dots=nodes;
		int l=nodes.getLength();
		int *path = new int[l];			//Создаём массив расстояний от заданной вершины до остальных
		for (int i=0; i<l; i++)
			path[i]=-1;					//Если вершина недостижима, расстояние будет отрицательным
		for (int i=0; i<ribs.getLength(); i++)
		{
			if (ribs[i].start==st)		//Ищем все рёбра с началом в st
			{
				path[ribs[i].end]=ribs[i].length;		//Изначально заполняем массив расстояний длинами прямых путей из st
			}
		}
		dots.del(st);					//st обойдена - удаляем из списка dots
		while (dots.getLength())
		{
			int t_dot=dots[0], min_path=path[dots[0]];			//Находим вершину из её не пройдённых, известное расстояние
			for (int i=0; i<dots.getLength(); i++)							//до которой минимально
				{
					if (path[dots[i]]!=-1&&path[dots[i]]<min_path)
					{
						t_dot=dots[i];
						min_path=path[dots[i]];
					}
				}
			dots.del(t_dot);									//Вершина обойдена, удаляем из списка
			for (int i=0; i<ribs.getLength(); i++)				//В цикле ищем рёбра, выходящие из вершины t_dot
				{												//и сравниваем расстояния напрямую с расстояниями через неё
					if (ribs[i].start==t_dot)
						{
							if (path[ribs[i].end]==-1)
								path[ribs[i].end]=path[ribs[i].start]+ribs[i].length;
							else
							{
								if (path[ribs[i].end]>path[ribs[i].start]+ribs[i].length)
								path[ribs[i].end]=path[ribs[i].start]+ribs[i].length;
							}
						}
				}
		}
		return path;
	}
	int getLength()								//"Длина" графа в данном случае - количество узлов
	{
		return nodes.getLength();
	}
	void erase()								//Очистка графа - сперва удаляем все узлы, затем все рёбра.
	{											//Следует заметить, что память, занимаемая графом очищается
		nodes.erase();							//при вызове деструкторов входящих в него списков, поэтому
		ribs.erase();							//вручную её освобождать не придётся.
	}
};
void main()
{
	graph gr1;
	gr1.addNode();
	gr1.addNode();
	gr1.addNode();
	gr1.addNode();
	gr1.addNode();
	gr1.addRib(0,1,10);
	gr1.addRib(0,3,30);
	gr1.addRib(0,4,100);
	gr1.addRib(1,2,50);
	gr1.addRib(2,4,10);
	gr1.addRib(3,2,20);
	gr1.addRib(3,4,60);
	gr1.print();
	int* test = gr1.Dijkstra(0);				//Массив, в который будем получать минимальные расстояния
	for (int i=0; i<gr1.getLength(); i++)		//Длина массива известна - это количество узлов графа.
		cout<<test[i]<<"\t";
	getch();
	delete [] test;								//После окончания работы освобождаем память, выделенную под массив
}