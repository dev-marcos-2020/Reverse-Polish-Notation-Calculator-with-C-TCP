#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <cmath>

#define MX 10005

using namespace std;

char infix[MX], str[11];

stack <int> calc;
stack <char> operate;
vector <string> outputList;

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int Priority(char ch) {
    if(ch == '^') return 3;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '+' || ch == '-') return 1;
    else return 0;
}

int __pow(int x, int y) {
	int i, ret;
	for (i = ret = 1; i <= y; i ++) ret *= x;
	return ret;
}

int Calc(int x, int y, char op) {
	switch(op) {
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '*':
			return x * y;
		case '/':
			return floor(x / (double)y);
		case '^':
			return __pow(x, y);
		default:
			return 0;
	}
}

void push_operate() {
	str[0] = operate.top(), str[1] = 0;
	outputList.push_back(str);
}

bool check(char ch) {
	return ch == '(' || ch == ')' || isdigit(ch) || isOperator(ch);
}

int main() {
	
	int idx = 0, tmp, x, y;
	
	strcpy(infix, "3 ^ 4 + ( 11 - ( 3 * 2 ) ) / 2");
//	strcpy(infix, "(8 + 3 * 2 - 4 ) / ( 4 * ( 1 + 3 ) / 2)");
//	cin>>infix;
	
	while(infix[idx]) {
		if(isdigit(infix[idx])) {
			tmp = infix[idx] - '0';
			while(isdigit(infix[idx + 1])) {
				tmp = tmp * 10 + (infix[++idx] - '0');
			}
			sprintf(str, "%d", tmp);
			outputList.push_back(str);
		}
		
		if(infix[idx] == '(') operate.push(infix[idx]);
		if(infix[idx] == ')') {
			while(!operate.empty() && operate.top() != '(') {
				push_operate();
                operate.pop();
            }
            operate.pop();
		}
		
		if(isOperator(infix[idx]) == true) {
            while(!operate.empty() && Priority(operate.top()) >= Priority(infix[idx])) {
            	push_operate();
                operate.pop();
            }
            operate.push(infix[idx]);
        }
        
		idx ++;
	}
	
	while(!operate.empty()) {
		push_operate();
        operate.pop();
    }
    
    for(int i = 0; i < outputList.size(); i ++) {
        strcpy(str, outputList[i].c_str());
        
        if(isOperator(str[0])) {
        	y = calc.top(); calc.pop();
        	x = calc.top(); calc.pop();
			calc.push(Calc(x, y, str[0]));
		}
		else sscanf(str, "%d", &tmp); calc.push(tmp);
    }
    
    cout<<calc.top()<<endl;
    
	return 0;
}

