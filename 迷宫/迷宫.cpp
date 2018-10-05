#include<iostream>
#include <string>
using namespace std;

typedef struct Position {
	int x, y, dir;															//λ��x,y��ǰ������direction
	Position* nextP;

	Position() {
		dir = x = y = -1;
		nextP = NULL;
	}
}*pos;
//-----------����ջ-----------------
typedef class LinkStark {

private:
	pos top;																//��һ��λ��
	int length;																//����

public:
	LinkStark(pos entrance) {												//����ջ���������λ��
		top = entrance;
		length = 1;
	}
	~LinkStark() {
		delete top;
	}
	pos getTop() {
		return top;
	}
	int getLength() {
		return length;
	}
	void push(pos);
	void pop();
	bool empty() {															//ջ���п�
		return top == NULL;
	}
}*StarkNode;

void LinkStark::push(pos in) {												//��ջ����
	in->nextP = top;
	top = in;
	length++;
}

void LinkStark::pop() {														//��ջ
	pos out = top;
	top = top->nextP;
	delete out;
	length--;
}

bool reachExit(StarkNode path, pos exit) {									//�ж��Ƿ񵽴��յ�
	return path->getTop()->x == exit->x&&path->getTop()->y == exit->y;
}
//---------�����Թ�-----------------
int** setMize() {
	int m, n;
	cout << "�����Թ���С��m,n��" << endl;
	cin >> m >> n;
	int**maze = new int*[m + 2];
	for (int i = 0; i <= m + 1; i++) {
		maze[i] = new int[n + 2];
	}

	for (int i = 0; i <= m + 1; i++)
		for (int j = 0; j <= n + 1; j++) {
			cout << "������" << "(" << i << "," << j
				<< ") ��״̬.0��ʾͨ·,1��ʾǽ,��i����0��" << m + 1
				<< "��j����0��" << n + 1 << "ʱ��������1" << endl;
			cin >> maze[i][j];
		}

	return maze;
}
//---------Ѱ���Թ�·��---------------
StarkNode findPath(int** maze) {
	pos ent = new Position;																//���
	pos exit = new Position;															//����
	bool flag;																			//ǰ����־
	int i;
	cout << "���������λ���Լ�����λ��:(x,y)" << endl;
	cout << "entrance : " ;
	cin >> ent->x >> ent->y;
	cout << "exit : " ;
	cin >> exit->x >> exit->y;
	maze[ent->x][ent->y] = 2;
	maze[exit->x][exit->y] = 0;

	StarkNode path = new LinkStark(ent); 
	while (!reachExit(path, exit)) {													//δ�������ʱһֱִ��
		flag = false;

		for (i = 1; i <= 4; i++) {														//������������4�������˳��ǰ��
			pos step = new Position;
			switch (i)
			{
			case 1: {
				step->y = path->getTop()->y;
				step->x = path->getTop()->x - 1;
				break;
			}
			case 2: {
				step->y = path->getTop()->y + 1;
				step->x = path->getTop()->x;
				break;
			}
			case 3: {
				step->y = path->getTop()->y;
				step->x = path->getTop()->x + 1;
				break;
			}
			case 4: {
				step->y = path->getTop()->y - 1;
				step->x = path->getTop()->x;
				break;
			}
			}

			if (maze[step->x][step->y] == 0) {									//�����һλ��û�߹��ͼ���ջ�����Ϊ�߹������������һ������
				path->getTop()->dir = i;
				path->push(step);
				flag = true;
				maze[step->x][step->y] = 2;
				break;
			}
			else { delete step; }
		}
		if (!flag) {															//�������ԭ�أ���ص���һ��
			path->pop();
		}
		if (path->empty()) {													//ջΪ�����ʾû��ͨ·
			cout << "û��ͨ·" << endl;
			return NULL;
		}
	}
	cout << "�����յ�" << endl;

	delete exit;
	return path;
}
int main() {
	int** maze = setMize();
	StarkNode path = findPath(maze);
//-----��ջ�Խ�ԭջ����------
	if (path) {
		pos top = new Position;												
		top->x = path->getTop()->x;
		top->y = path->getTop()->y;
		top->nextP = path->getTop()->nextP;

		StarkNode box = new LinkStark(top);									//������ջ�������������ڵ����ڵ�·��

		int theLength = path->getLength();
		path->pop();
		for (int i = 1; i < theLength; i++) {								
			top = new Position;
			top->x = path->getTop()->x;
			top->y = path->getTop()->y;
			top->nextP = path->getTop()->nextP;
			top->dir = path->getTop()->dir;
			box->push(top);
			path->pop();
		}

		cout << "·����";
		for (int i = 1; i < theLength; i++) {								//���·��
			cout << "(" << box->getTop()->x << "," << box->getTop()->y << "," << box->getTop()->dir << ") --> ";
			box->pop();
		}
		cout << "(" << box->getTop()->x << "," << box->getTop()->y << ",-"  << ")"<<endl;
		delete box;
	}
	else {
		cout << "�Թ���ͨ" << endl;
	}

	delete path;
	system("pause");
	return 0;
}
