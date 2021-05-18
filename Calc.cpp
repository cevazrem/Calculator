#include <iostream>
#include <stack>

class LexAnalyser {
private:
    int cur;
public:
    int get_lex();
};

int LexAnalyser::get_lex() {
    while ((cur = getchar()) && (isspace(cur)) && (cur != ';')) {}
    return cur;
}

class Parser {
private:
    LexAnalyser scanner;
    int cur;
    
    std::stack <int> result;

    void get_lex();
    
    void L();
    void C();
    void A();
    void M();
    void K();
 //   void num();
public:
    int calculate();
};

void Parser::get_lex() {
    cur = scanner.get_lex();
}

//L -> C {+ C}
void Parser::L() {
    C();
    while (cur == '+') {
        get_lex();
        C();
        int second_val = result.top();
        result.pop();
        int first_val = result.top();
        result.pop();

        result.push(first_val + second_val);
    }
}

//C -> A {- A}
void Parser::C() {
    A();
    while (cur == '-') {
        get_lex();
        C();
        int second_val = result.top();
        result.pop();
        int first_val = result.top();
        result.pop();

        result.push(first_val - second_val);
    }
}

//A -> M {* M}
void Parser::A() {
    M();
    while (cur == '*') {
        get_lex();
        C();
        int second_val = result.top();
        result.pop();
        int first_val = result.top();
        result.pop();

        result.push(first_val * second_val);
    }
}

//M -> K {/ K}
void Parser::M() {
    K();
    while (cur == '/') {
        get_lex();
        C();
        int second_val = result.top();
        result.pop();
        int first_val = result.top();
        result.pop();

        result.push(first_val / second_val);
    }
}

//K -> num | (L)
void Parser::K() {
	if (isdigit(cur)) {
		int val = 0, i = 1;
		while (isdigit(cur)) {
			val = val * 10 + (cur - '0');
//			std::cout << "val:" << val;
			i++;
			get_lex();
		}
//		std::cout << val << std::endl;
		result.push(val);
	//	get_lex();
	} else if (cur == '(') {
		get_lex();
		L();
		if (cur != ')') throw "Syntax error: wrong usage of ()";
		get_lex();
	} else {
		throw "Syntax error: undefined symbol";
	}
}


int Parser::calculate() {
	get_lex();
	L();
//	std::cout << cur;
	if (cur != ';') throw "Syntax error wrong end of string";
	return result.top();
}

int main(void) {
	try {
		Parser my_pars;
		std::cout << my_pars.calculate() << std::endl;
	} catch (const char *err) {
		std::cerr << err << std::endl;
	}
}
