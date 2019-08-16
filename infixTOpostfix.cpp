#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

class Stack
{
	public:
			 char stack[50];
			 int top=-1;
			 
	
		
		
		bool push(char val)
		{
			if(top==sizeof(stack)-1)
			{
				cout<<"max";
				return false;
			}
			
			top++;
			
			stack[top]=val;
			
			
			return true;
		}
		char pop()
		{
			if(top==-1)
			{
				cout<<"Min";
				return ' ';
			}
			char c=stack[top];
			stack[top]=0;
			top--;
			return c;
		}
};
class DisplayManager
{
	private:
				Stack *ary1,*ary2;
	public:
				string EXPr;
				void Display(Stack A,Stack B)
				{
					cout<<"Expression:"+EXPr;
					cout<<"\nOperator on Stack \t\t\t\tPostfix String\n";
					
					for(int x=0;x<=A.top;x++)
					{
						cout<<"-";
					}
					int space=47;
					space-=A.top;
					for(int s=0;s<space;s++)
						cout<<" ";
						
					for(int x=0;x<=B.top;x++)
					{
						cout<<"-";
					}
						
					cout<<"\n";
					
					for(int i=0;i<=A.top;i++)
						cout<<A.stack[i];
					for(int s=0;s<space;s++)
						cout<<" ";
					for(int i=0;i<=B.top;i++)
						cout<<B.stack[i];
					
					cout<<"\n";
					for(int x=0;x<=A.top;x++)
					{
						cout<<"-";
					}
					for(int s=0;s<space;s++)
						cout<<" ";
						
					for(int x=0;x<=B.top;x++)
					{
						cout<<"-";
					}	
					cout<<"\n";
					
					
				}
};
class Priority
{
	public:
	int Of(char symb)
	{
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
main()
{
	Stack OperatorStack, PostfixString;
	Priority priority;
	string INfx;
	cout<<"Enter infix expression:";
	cin>>INfx;
	DisplayManager DSP;
	DSP.EXPr=INfx;
	char c;
	int i=0;
	bool open=false;
	bool end=false;
	while (INfx[i] != '\0') 
	{
		if(OperatorStack.stack[OperatorStack.top]==')')
			OperatorStack.pop();
			
			system("cls");
			DSP.Display(OperatorStack,PostfixString);
					
			if(INfx[i]=='(')
			{
					OperatorStack.push(INfx[i]);
					open=true;
					end=false;
			}
				
			
			else if(INfx[i]=='+'||INfx[i]=='-'||INfx[i]=='*'||INfx[i]=='/'||INfx[i]=='^'||INfx[i]=='$'||INfx[i]=='%'||INfx[i] == ')')
			{
				if(INfx[i]==')')
				{
				
					end=true;
					open=true;		
				//	cout<<"end here"		;
				}
			//	if(!open)//priority logics
				{
					bool repeat=true;
					int T=OperatorStack.top;
					do
					{
						if(end && open )
						{		
						//	cout<<"clear here";
							char tmp=OperatorStack.pop();
							while(tmp!='(')
							{
								Sleep(1000);
								system("cls");
								DSP.Display(OperatorStack,PostfixString);
								
								PostfixString.push(tmp);
								tmp=OperatorStack.pop();								
								
								
							}
								
							T=OperatorStack.top;
							open=false;
							end=false;
							repeat=false;
						}
						
					   else if( priority.Of(OperatorStack.stack[T]) >priority.Of(INfx[i]) && !end)	
						{
							PostfixString.push(OperatorStack.pop());
							T--;
						}
						
						else repeat= false;
						
					
					}
					while(repeat);					
				}
					OperatorStack.push(INfx[i]);	
					
					
				
			}
			
	
			else//alphabet or number
				PostfixString.push(INfx[i]);
			Sleep(1000);
			i++;
	}
	
	
	
	//cout<<"CLean UP";
	
	int T=OperatorStack.top;
	while(T>=0)
	{	
		
		if(OperatorStack.stack[OperatorStack.top]==')')
			OperatorStack.pop();
		else
			PostfixString.push(OperatorStack.pop());
		T--;
			Sleep(1000);
		system("cls");		
		DSP.Display(OperatorStack,PostfixString);	
	}
	
	getch();
}
