//В данном случае положение элемента в дереве определяется при его добавлении.

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
	}
	void add(int d)				//Добавление элемента
	{
		if (!weight)			//Если дерево пусто, просто добавляем ему корень
		{
			elem[weight].set(DATA,d);
			weight++;
		}
		else if (weight<m)		//Если дерево не пусто и в нём ещё есть свободные места
		{
			elem[weight].set(DATA,d);	//Записываем данные
			elem[weight].set(PREV,(weight-1)/2);		//Вычисляем номер родительского элемента
			if (isodd(weight))					//Определяем, левый это сын или правый
			elem[elem[weight].get(PREV)].set(LEFT,weight);
			else
			elem[elem[weight].get(PREV)].set(RIGHT,weight);
			weight++;
		}
	}
	void del()				//Удаление элемента
	{
		if (weight)			//Если дерево не пусто
		{
			if (weight==1)	//Если в нём только корень, просто его обнуляем
			{
				elem[0].set(DATA,0);
			}
			else			//Если в дереве не только корень, делаем все операции обратные добавлению
			{
			if (isodd(weight-1))
			elem[elem[weight-1].get(PREV)].set(LEFT,NO);
			else
			elem[elem[weight-1].get(PREV)].set(RIGHT,NO);
			elem[weight-1].set(PREV,NO);
			elem[weight-1].set(DATA,0);
			}
			weight--;
		}
	}
};
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
	getch();
}
//								0
//				1								2
//		3				4				5				6
//	7		8		9		10		11		12		13		14