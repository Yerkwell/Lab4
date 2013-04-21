//В данном случае архитектура дерева определяется с самого начала.
#include <iostream>
#include <conio.h>
#define NO -1				//Аналог "нулевого указателя"
#define DATA 1
#define LEFT 2
#define RIGHT 3
#define PREV 4
using namespace std;
const int m=15;				//Константа, заранее определяющая размер массива
bool isodd(int n)			//Проверка числа на нечётность
{
	return ((n+1)/2-n/2);
}
class element
{
	int data;
	int left;
	int right;
	int prev;
public:
	element()
	{
		data=0;
		left=NO;
		right=NO;
		prev=NO;
	}
	int get(int what)		//Дабы не писать по отдельному методу получения для каждого поля, используем один
	{						//С указанием того, что получать в каждом конкретном случае.
		switch (what)
		{
		case DATA:
			return data;
		case LEFT:
			return left;
		case RIGHT:
			return right;
		case PREV:
			return prev;
		}
	}
	void set(int what, int l)		//Аналогичная ситуация
	{
		switch (what)
		{
		case DATA:
			data=l;
			break;
		case LEFT:
			left=l;
			break;
		case RIGHT:
			right=l;
			break;
		case PREV:
			prev=l;
			break;
		}
	}
};
class tree
{
	int weight;					//Выходит, что вес == номер последнего свободного элемента
	element elem[m];
public:
	tree()
	{
		weight=0;
		for (int i=1; i<m; i++)
		{
			elem[i].set(PREV,(i-1)/2);
			if (isodd(i))					//Определяем, левый это сын или правый
			elem[elem[i].get(PREV)].set(LEFT,i);
			else
			elem[elem[i].get(PREV)].set(RIGHT,i);
		}
	}
	void add(int d)				//Добавление элемента
	{
		if (weight<m)		//Если дерево не пусто и в нём ещё есть свободные места
		{
			elem[weight].set(DATA,d);	
			weight++;		//Поскольку архитектура дерева уже определена, мы просто записываем
		}					//данные в последнюю свободную ячейку.
	}
	void del()				//Удаление элемента
	{
		if (weight)			//Если дерево не пусто
		{
			weight--;		//Поскольку новые данные всё равно пишутся поверх старых, удалять
		}					//старые не имеет смысла. Память это не освободит а что там будет 
	}						//лежать, ноль или "мусор" - не имеет значения. Поэтому мы просто
};							//"забываем" про последний элемент.
void main()
{
	tree tr1;
	tr1.add(1);
	tr1.add(1);
	tr1.add(1);
	tr1.add(1);
	tr1.add(1);
	tr1.del();
	tr1.del();
	tr1.del();
	tr1.add(2);
	tr1.add(2);
	tr1.add(2);
	getch();
}
//								0
//				1								2
//		3				4				5				6
//	7		8		9		10		11		12		13		14