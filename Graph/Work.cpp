#include <iostream>
#include <conio.h>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
//������ ���������� ������ ��� ���������� ������
template <typename type>				//��������� ����� "�������" (�.�. � ���� ����� ��������� � ������ "������")
class element;							//�������� ����� ������
template <typename type>				//����� "������ ��������� ���������, �.�. ����� ��������� ������
class list								//��������� ������ �����
{
	element<type>* first;				//��������� �� ������ � ��������� �������� ������
	element<type>* last;
	int length;							//���������� ��������� � ������
public:
	list()								//�����������. �������� ������ ��� ��������
	{
		first=last=0;
		length=0;
	}
	~list()
	{
		erase();						//��������� ������ ���������� ������������ ������, ��� ��� �����������
	}									//���� ��� ������ ����������
	void erase()
	{
		while(length)
			pop();
	}
	void push(type n)					//���������� �������� � ����� (� ������������ ����� ��������� �� �������)
	{									//��� ���� �� ����� �������� �� �������, � ������ ��� ������.
		element<type> *newel = new element<type>;		//��� ������� ������������ �� ���� �����
		newel->data=n;
		if (!length)
		{
			first=last=newel;							//���� ������ ����, ������ ��������� ������� � ������
		}
		else
		{
			last->next=newel;							//����� ��������� ��� ��������� 
			newel->prev=last;							//� ����������� ��������� ���������� �� ����
			last=newel;
		}
		length++;
	}
	void pop()							//�������� ���������� �������� �� ������
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
	void del(type wh)					//�������� �� ������ ��������, ����������� ������ wh
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
	void print()					//����� �� ����� ����� ������, ��� �������, ��� ������ ����� ���, 
	{								//����������� � cout
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
	void print_class()				//����� �� ����� ����� ������, ��� �������, ��� ������ ������������ �����
	{								//���������� ������, �������� ����� print() ��� ������ ���� �� �����
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
	type& operator[](int i)		//��������� � ����������� �������� ������ �� ��� ������ (������ �� ������)
	{
		element<type> *tek=first;
		for (int j=0; j<i; j++)
		{
			tek=tek->next;
		}
		return tek->data;
	}
	list<type>(const list<type>& b):first(first),last(last),length(length){};	//����������� �����������
	list<type>& operator=(list<type>& b)						//�������� ������������
	{
		erase();
		for (int i=0; i<b.getLength(); i++)
			push(b[i]);
		return *this;
	}
	int getLength()												//��������� ����� ������
	{
		return length;
	}
	bool exist(type find)				//��������, ���� �� ������� � ������� find � ������. ��������,
	{									//���� ���������� �������� ��������� == ��� ������� ���� ������			
		for (int i=0; i<length; i++)	
		{
			if ((*this)[i]==find)
				return 1;
		}
		return 0;
	}
};
template <typename type>				//�������� ���������� ������ "�������"
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
	friend class list<type>;			//��� ������� ������� � ����� �� ������ "������" ������ ��� �������������
};
///////////////////////////////////////////////////////////////////////////////////
class rib								//����� "�����"
{	
	int length;							//����� (���) �����
	int start;							//��������� ����
	int end;							//�������� ����
public:
	rib():start(0),end(0),length(0){};	//����������� "��-���������"
	rib(int start,int end,int length):start(start),end(end),length(length){};	//�����������, ���������������� ��� ���� ������
	bool operator==(rib a)				//�������� ��������� ���� ����. � ������ ���������� �������
	{									//������� ����, ����������� �� ������ � �����.
		if ((this->start==a.start)&&(this->end==a.end))
			return 1;
		else 
			return 0;
	}
	void print()						//����� ����� �� �����
	{
		cout<<start<<" - "<<end<<":"<<length<<endl;		//<������> - <�����>:<���>
	}
	friend class graph;					//����� ��, ��� ������� ��������� � ����� ������ �� ������ "����"
};
class graph								//����� "����"
{
	list<int> nodes;					//������ ����� �����. �������� ������ �� ������ ��� �������� ������� ������ ���� � �����
	list<rib> ribs;						//������ ���� �����
public:
	void addNode()						//���������� ����
	{
		nodes.push(nodes.getLength());	//��������� ��������� ����� �� �������������, ��������� �� �� �������
		addRib((nodes.getLength())-1,(nodes.getLength())-1,0);	//��� ������� ���� ��� �� ������ ����� "�� ���� � ����" �������� ����
	}
	void addRib(int start,int end,int length)	//���������� �����
	{
		rib a=rib(start,end,length);			//������ �����
		if (!ribs.exist(a)&&nodes.exist(a.start)&&nodes.exist(a.end))	//��������� ��� � ������ ������ ���� ��� ��� ��� �����
			ribs.push(a);												//� ���� �� ������� � ������, � ����� ���� ����, �������
	}																	//��� ����� ������ ���������
	void print()								//����� ����� �� �����
	{
		cout<<"Vershiny:\n";					//������ ������ ������ (�����), ����� ������ ����.
		nodes.print();
		cout<<"Ryobra:\n";
		ribs.print_class();
	}
	int* Dijkstra(int st)		//����������, �������� ��������. st - �������, ��� ������� ���� ����������� ����������
	{
		list <int> dots;		//dots - ������ ��� �� ��������� ������
			dots=nodes;
		int l=nodes.getLength();
		int *path = new int[l];			//������ ������ ���������� �� �������� ������� �� ���������
		for (int i=0; i<l; i++)
			path[i]=-1;					//���� ������� �����������, ���������� ����� �������������
		for (int i=0; i<ribs.getLength(); i++)
		{
			if (ribs[i].start==st)		//���� ��� ���� � ������� � st
			{
				path[ribs[i].end]=ribs[i].length;		//���������� ��������� ������ ���������� ������� ������ ����� �� st
			}
		}
		dots.del(st);					//st �������� - ������� �� ������ dots
		while (dots.getLength())
		{
			int t_dot=dots[0], min_path=path[dots[0]];			//������� ������� �� � �� ���������, ��������� ����������
			for (int i=0; i<dots.getLength(); i++)							//�� ������� ����������
				{
					if (path[dots[i]]!=-1&&path[dots[i]]<min_path)
					{
						t_dot=dots[i];
						min_path=path[dots[i]];
					}
				}
			dots.del(t_dot);									//������� ��������, ������� �� ������
			for (int i=0; i<ribs.getLength(); i++)				//� ����� ���� ����, ��������� �� ������� t_dot
				{												//� ���������� ���������� �������� � ������������ ����� ��
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
	int getLength()								//"�����" ����� � ������ ������ - ���������� �����
	{
		return nodes.getLength();
	}
	void erase()								//������� ����� - ������ ������� ��� ����, ����� ��� ����.
	{											//������� ��������, ��� ������, ���������� ������ ���������
		nodes.erase();							//��� ������ ������������ �������� � ���� �������, �������
		ribs.erase();							//������� � ����������� �� �������.
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
	int* test = gr1.Dijkstra(0);				//������, � ������� ����� �������� ����������� ����������
	for (int i=0; i<gr1.getLength(); i++)		//����� ������� �������� - ��� ���������� ����� �����.
		cout<<test[i]<<"\t";
	getch();
	delete [] test;								//����� ��������� ������ ����������� ������, ���������� ��� ������
}