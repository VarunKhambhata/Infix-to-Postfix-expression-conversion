#include <iostream>
#include <chrono>
#include <thread>

class Stack {
public:
	char stack[50];
	int top=-1;

	bool push(char val) {
		if(top == sizeof(stack)-1) {
			std::cout<<"max";
			return false;
		}			
		top++;
		stack[top] = val;
		return true;
	}

	char pop() {
		if(top == -1) {
			std::cout<<"Min";
			return ' ';
		}
		char c = stack[top];
		stack[top] = 0;
		top--;
		return c;
	}
};

class DisplayManager {
private:
	Stack *ary1,*ary2;
public:
	std::string EXPr;

	void Display(Stack A,Stack B) {
		std::cout << "Expression:" + EXPr;
		std::cout << "\nOperator on Stack \t\t\t\tPostfix String\n";

		for(int x=0; x <= A.top; x++) std::cout<<"-";

		int space = 47;
		space -= A.top;

		for(int s=0; s < space; s++) std::cout<<" ";
					
		for(int x=0; x <= B.top; x++) std::cout<<"-";
		std::cout<<"\n";
				
		for(int i=0; i <= A.top; i++) std::cout<<A.stack[i];
		for(int s=0; s < space; s++)  std::cout<<" ";
		for(int i=0; i <= B.top; i++) std::cout<<B.stack[i];
				
		std::cout<<"\n";
		for(int x=0; x <= A.top; x++) std::cout<<"-";
		for(int s=0; s < space; s++)  std::cout<<" ";
		for(int x=0; x <= B.top; x++) std::cout<<"-";
		std::cout<<"\n";	
	}
};

class Priority {
public:
	int Of(char symb) {
		if(symb=='-'||symb=='+')
			return 1;
		if(symb=='*'||symb=='/'||symb=='%')
			return 2;
		if(symb=='$'||symb=='^')
			return 3;
		if(symb=='('||symb==')')
			return 0;
	}
};

void clear() {
	#ifdef _WIN32
		std::system("cls");
	#else
		std::system("clear");
	#endif
}

void sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
	Stack OperatorStack, PostfixString;
	Priority priority;

	std::string INfx;
	std::cout << "Enter infix expression:";
	std::cin >> INfx;
	
	DisplayManager DSP;
	DSP.EXPr = INfx;

	char c;
	int i = 0;
	bool open=false;
	bool end=false;

	while (INfx[i] != '\0') {
		if(OperatorStack.stack[OperatorStack.top] == ')')
			OperatorStack.pop();

			clear();
			DSP.Display(OperatorStack,PostfixString);
					
			if(INfx[i] == '(') {
					OperatorStack.push(INfx[i]);
					open = true;
					end = false;
			}
			else if(INfx[i] == '+'|| INfx[i] == '-' || INfx[i] == '*' || INfx[i] == '/' || INfx[i] == '^' || INfx[i] == '$' || INfx[i] == '%' || INfx[i] == ')') {
				if(INfx[i]==')') {
					end = true;
					open = true;
				//	cout<<"end here"		;
				}
				//	if(!open)//priority logics
				{
					bool repeat = true;
					int T = OperatorStack.top;
					do {
						if(end && open ) {		
						//	cout<<"clear here";
							char tmp = OperatorStack.pop();
							while(tmp != '(') {
								sleep();
								clear();
								DSP.Display(OperatorStack,PostfixString);
								
								PostfixString.push(tmp);
								tmp=OperatorStack.pop();
							}
								
							T = OperatorStack.top;
							open = false;
							end = false;
							repeat = false;
						}
						else if( priority.Of(OperatorStack.stack[T]) > priority.Of(INfx[i]) && !end) {
							PostfixString.push(OperatorStack.pop());
							T--;
						}
						else
							repeat = false;
					}
					while(repeat);
				}
				OperatorStack.push(INfx[i]);
			}
			else //alphabet or number
				PostfixString.push(INfx[i]);
			sleep();
			i++;
	}

	//cout<<"CLean UP";
	int T = OperatorStack.top;
	while(T >= 0) {			
		if(OperatorStack.stack[OperatorStack.top] == ')')
			OperatorStack.pop();
		else
			PostfixString.push(OperatorStack.pop());
		T--;
		sleep();
		clear();
		DSP.Display(OperatorStack,PostfixString);
	}

	return 0;
}
