//� ������ ������ ����������� ������ ������������ � ������ ������.
#include <iostream>
#include <conio.h>
#define NO -1				//������ "�������� ���������"
#define DATA 1
#define LEFT 2
#define RIGHT 3
#define PREV 4
using namespace std;
const int m=15;				//���������, ������� ������������ ������ �������
bool isodd(int n)			//�������� ����� �� ����������
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
	int get(int what)		//���� �� ������ �� ���������� ������ ��������� ��� ������� ����, ���������� ����
	{						//� ��������� ����, ��� �������� � ������ ���������� ������.
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
	void set(int what, int l)		//����������� ��������
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
	int weight;					//�������, ��� ��� == ����� ���������� ���������� ��������
	element elem[m];
public:
	tree()
	{
		weight=0;
		for (int i=1; i<m; i++)
		{
			elem[i].set(PREV,(i-1)/2);
			if (isodd(i))					//����������, ����� ��� ��� ��� ������
			elem[elem[i].get(PREV)].set(LEFT,i);
			else
			elem[elem[i].get(PREV)].set(RIGHT,i);
		}
	}
	void add(int d)				//���������� ��������
	{
		if (weight<m)		//���� ������ �� ����� � � �� ��� ���� ��������� �����
		{
			elem[weight].set(DATA,d);	
			weight++;		//��������� ����������� ������ ��� ����������, �� ������ ����������
		}					//������ � ��������� ��������� ������.
	}
	void del()				//�������� ��������
	{
		if (weight)			//���� ������ �� �����
		{
			weight--;		//��������� ����� ������ �� ����� ������� ������ ������, �������
		}					//������ �� ����� ������. ������ ��� �� ��������� � ��� ��� ����� 
	}						//������, ���� ��� "�����" - �� ����� ��������. ������� �� ������
};							//"��������" ��� ��������� �������.
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