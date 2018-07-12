#include <fstream>
#include <iostream>
using namespace std;

class stack{
public:
	void push(char num, char flower){
		array[size] = num;
		array[size + 1] = flower;
		size += 2;
	};
	void pop(char &num, char &flower){
		if (size != 0){
			num = array[size - 2];
			flower = array[size - 1];
			size -= 2;
		}
	};
	int stack_size(){
		return size / 2;
	};
	void print_stack(){
		for (int j = 0; j < size; j++)
			cout << array[j];
	};
private:
	char array[100];
	int size=0;
};

class queue{
public:
	void push(char num, char flower){
		array[size] = num;
		array[size + 1] = flower;
		size += 2;
	};
	void pop(char &num, char &flower){
		if (size != 0){
			num = array[0];
			flower = array[1];
			size -= 2;
			for (int j = 0; j < size; j++)
			{
				array[j] = array[j + 2];
			}	
		}
	};
	int queue_size(){
		return size / 2;
	};
	void print_queue(){
		for (int j = 0; j < size; j++)
			cout << array[j];
	};
private:
	char array[100];
	int size = 0;
};

class deque{
public:
	void push_front(char num, char flower){
		size += 2;
		for (int j = size - 1; j > 1; j--){
			array[j] = array[j - 2];
		}
		array[0] = num;
		array[1] = flower;
	};
	void push_back(char num, char flower){
		array[size] = num;
		array[size + 1] = flower;
		size += 2;
	};
	void pop(char &num, char &flower){
		if (size != 0){
			num = array[0];
			flower = array[1];
			size -= 2;
			for (int j = 0; j < size; j++)
			{
				array[j] = array[j + 2];
			}
		}
	};
	void pop_back(char &num, char &flower){
		if (size != 0){
			num = array[size - 2];
			flower = array[size - 1];
			size -= 2;
		}
	};
	int deque_size(){
		return size / 2;
	};
	void print_deque(){
		for (int j = 0; j < size; j++)
			cout << array[j];
	};
private:
	char array[100];
	int size = 0;
};

char get_op(ifstream &fin){
	char op_code;
	while(fin){
		op_code = fin.get();
		if ((op_code == ' ') || (int(op_code) == 10));
		else return op_code;
	}
};

int main(int argc, char* argv[]){
	ifstream fin;
	ofstream fout;
	//fin.open("case.txt");
	//fout.open("ans.txt");
	fin.open(argv[1]);
	fout.open(argv[2]);
	stack stack1;
	queue queue1;
	deque deque1, deque2,deque_temp;
	int deque_first=0;

	if (!fin)
	{
		cout << "檔案讀取失敗" << endl;
		system("pause");
		return 0;
	}
	char input, save[100];
	int i = 0;
	while (true)//取出card數值
	{
		input = fin.get();
		if (input == '#')
			break;
		if (input != ' ')
		{
			save[i] = input;
			i++;
		}
	}
	int stack_num[100], stack_temp[100], stack_count = 0, a = 0;//得到每一層stack數目
	for (int j = 0; j < i; j++)
	{
		if (int(save[j]) != 10)
			a++;
		else
		{
			stack_temp[stack_count] = a / 2;
			stack_count++;
			a = 0;
		}
	}
	int b = 0;
	for (int j = stack_count - 1; j >= 0; j--){
		stack_num[b] = stack_temp[j];
		b++;
	}
	/*for (int j = 0; j < stack_count; j++)
	{
		cout << stack_num[j] << endl;
	}*/

	char array[100];
	int array_i = 0;
	for (int j = 0; j < i; j++)//去除輸入資料的換行
	{
		if (int(save[j]) != 10){
			array[array_i] = save[j];
			array_i++;
		}
	}
	/*for (int j = 0; j < array_i; j++)
	{
		cout << array[j];
	}*/
	for (int j = 0; j < array_i; j+=2)//把所有數值push到stack
	{
		stack1.push(array[j], array[j+1]);
	}
	//stack1.print_stack();
	char op1, op2, card[2], deque1_card[2], deque2_card[2];
	int queue_num[100], queue_count;
	while (1)
	{
		queue_count = 0;
		op1 = get_op(fin);
		op2 = get_op(fin);
		int max;
		if (atoi(&op1) > atoi(&op2))
			max = atoi(&op1);
		else
			max = atoi(&op2);
		for (int j = 0; j < max; j++){//把stack的值pop到queue或deque
			if (j == atoi(&op1)-1)
			{
				for (int n = 0; n < stack_num[j]; n++)
				{
					stack1.pop(card[0], card[1]);
					deque1.push_back(card[0], card[1]);
				}
			}
			else if (j == atoi(&op2)-1)
			{
				for (int n = 0; n < stack_num[j]; n++)
				{
					stack1.pop(card[0], card[1]);
					deque2.push_back(card[0], card[1]);
				}
			}
			else
			{
				for (int n = 0; n < stack_num[j]; n++)
				{
					stack1.pop(card[0], card[1]);
					queue1.push(card[0], card[1]);
				}
				queue_num[queue_count] = stack_num[j];
				queue_count++;
			}
		}
		stack_count = stack_count-max;
		for (int j = 0; j < stack_count; j++)//stack資訊更改
			stack_num[j] = stack_num[j+max];
		for (int j = 0; j < 100; j++)
			stack_temp[j] = stack_num[j];
		int c = 0;
		for (int j = stack_count - 1; j >= 0; j--){
			stack_num[c] = stack_temp[j];
			c++;
		}
		while (deque2.deque_size())//兩個deque合併
		{
			deque1.pop(deque1_card[0], deque1_card[1]);
			deque2.pop(deque2_card[0], deque2_card[1]);
			if (deque1_card[0] == deque2_card[0] || deque1_card[1] == deque2_card[1])
			{
				deque1.push_front(deque1_card[0], deque1_card[1]);
				deque1.push_front(deque2_card[0], deque2_card[1]);
				if (deque2.deque_size() == 0)
					deque_first = 1;
			}
			else
			{
				deque1.push_front(deque1_card[0], deque1_card[1]);
				deque1.push_back(deque2_card[0], deque2_card[1]);
				if (deque2.deque_size() == 0)
					deque_first = 0;
			}
		}
		if (deque_first == 0){//queue先丟回stack
			for (int j = 0; j < queue_count; j++){//將queue資料移回stack
				for (int n = 0; n < queue_num[j]; n++)
				{
					queue1.pop(card[0], card[1]);
					deque_temp.push_back(card[0], card[1]);
				}
				for (int n = 0; n < queue_num[j]; n++)
				{
					deque_temp.pop_back(card[0], card[1]);
					stack1.push(card[0], card[1]);
				}
				stack_num[stack_count] = queue_num[j];
				stack_count++;
			}
			stack_num[stack_count] = deque1.deque_size();
			for (int j = 0; j < stack_num[stack_count]; j++){//將deque1資料移回stack
				deque1.pop_back(card[0], card[1]);
				stack1.push(card[0], card[1]);
			}
			stack_count++;
		}
		else{//deque先丟回stack
			stack_num[stack_count] = deque1.deque_size();
			for (int j = 0; j < stack_num[stack_count]; j++){//將deque1資料移回stack
				deque1.pop_back(card[0], card[1]);
				stack1.push(card[0], card[1]);
			}
			stack_count++;
			for (int j = 0; j < queue_count; j++){//將queue資料移回stack
				for (int n = 0; n < queue_num[j]; n++)
				{
					queue1.pop(card[0], card[1]);
					deque_temp.push_back(card[0], card[1]);
				}
				for (int n = 0; n < queue_num[j]; n++)
				{
					deque_temp.pop_back(card[0], card[1]);
					stack1.push(card[0], card[1]);
				}
				stack_num[stack_count] = queue_num[j];
				stack_count++;
			}
		}
		for (int j = 0; j < 100; j++)
			stack_temp[j] = stack_num[j];
		c = 0;
		for (int j = stack_count - 1; j >= 0; j--){
			stack_num[c] = stack_temp[j];
			c++;
		}
		if (stack_count == 1)//終止條件stack剩下一層
			break;
	}
	/*
		stack1.print_stack();
		cout << endl;
		queue1.print_queue();
		cout << endl;
		deque1.print_deque();
		cout << endl;
		deque2.print_deque();
		cout << endl;
	*/
	int k=stack1.stack_size();//輸出檔案
	for (int j = 0; j < k; j++)
	{
		stack1.pop(card[0], card[1]);
		fout << card[0] << card[1] << ' ';
	}
	fin.close();
	fout.close();
	return 0;
}