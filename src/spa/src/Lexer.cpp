#include<stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

#include "Lexer.h"
#include "PKB.h"

Lexer::Lexer(string input) {
	code = input;
	tokenize(input);
}

int Lexer::tokenize(string input) {

	input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	vector<string> tokens = vectorize(input);

	//identifying different types of statement
	if (find(tokens.begin(), tokens.end(), "procedure") != tokens.end()) {
		tokenizeProcedure(tokens);
	}
	else if (find(tokens.begin(), tokens.end(), "=") != tokens.end()) {
		tokenizeAssignment(tokens);
	}
	else if (find(tokens.begin(), tokens.end(), "read") != tokens.end()) {
		tokenizeRead(tokens);
	}
	else if (find(tokens.begin(), tokens.end(), "print") != tokens.end()) {
		tokenizePrint(tokens);
	}
	else {
		throw "Invalid statement";
	}

	return 0;

}
vector<string> Lexer::vectorize(string input) {
	vector<string> tokens;
	string curr = "";
	for (char& c : input) {
		string temp;
		temp.push_back(c);
		if (isOperator(temp) || isSeparator(temp)) {
			if (curr.length() != 0) {
				tokens.push_back(curr);
				curr = "";
			}
			tokens.push_back(temp);
		}
		else if (curr == "procedure" || curr == "read" || curr == "print") {
			tokens.push_back(curr);
			curr = temp;
		}
		else {
			curr.push_back(c);
		}
	}

	return tokens;
}

void Lexer::tokenizeProcedure(vector<string> tokens) {
	vector<Token*> toAST;
	toAST.push_back(new Token(TokenType::Procedure, "procedure"));
	toAST.push_back(pushIdentifier(tokens[1]));
	toAST.push_back(new Token(TokenType::Separator, "{"));

	print(toAST);
}

void Lexer::tokenizeAssignment(vector<string> tokens) {
	vector<Token*> toAST;
	toAST.push_back(new Token(TokenType::Assign, "assign"));

	for (auto i : tokens) {
		toAST.push_back(pushToken(i));
	}
	
	print(toAST);
}

void Lexer::tokenizeRead(vector<string> tokens) {
	vector<Token*> toAST;
	toAST.push_back(new Token(TokenType::Read, "read"));
	tokens.erase(tokens.begin());

	for (auto i : tokens) {
		toAST.push_back(pushToken(i));
	}

	print(toAST);

}

void Lexer::tokenizePrint(vector<string> tokens) {
	vector<Token*> toAST;
	toAST.push_back(new Token(TokenType::Print, "print"));
	tokens.erase(tokens.begin());

	for (auto i : tokens) {
		toAST.push_back(pushToken(i));
	}

	print(toAST);
}

queue<pair<TokenType, string>> Lexer::getTokenQueue() {
	return tokenQueue;
}

Token* Lexer::pushToken(string s) {
	if (isConstant(s)) {
		return new Token(TokenType::Constant, s);
	}
	else if (isSeparator(s)) {
		return new Token(TokenType::Separator, s);
	}
	else if (isOperator(s)) {
		return pushOperator(s);
	}
	else if (isIdentifier(s)) {
		return new Token(TokenType::Identifier, s);
	}
	else {
		throw "Invalid Identifier";
	}
}

Token* Lexer::pushIdentifier(string s) {

	if (isIdentifier(s)) {
		return new Token(TokenType::Identifier, s);
	}
	else {
		throw "Invalid Identifier";
	}


}

Token* Lexer::pushOperator(string s) {
	if (s == "+") {
		return new Token(TokenType::Plus, s);
	}
	else if (s == "-") {
		return new Token(TokenType::Minus, s);
	}
	else if (s == "*") {
		return new Token(TokenType::Multiply, s);
	}
	else if (s == "/") {
		return new Token(TokenType::Divide, s);
	}
	else if (s == "=") {
		return new Token(TokenType::Equal, s);
	}
	else if (s == "(") {
		return new Token(TokenType::OpenParenthesis, s);
	}
	else if (s == ")") {
		return new Token(TokenType::CloseParenthesis, s);
	}

}

bool Lexer::isIdentifier(string s) {
	if (isConstant(s.substr(0))) {
		return false;
	}
	else {
		return (!onlyContainDigits(s));
	}
}

bool Lexer::isSeparator(string s) {
	return (s == ";" || s == "{" || s == "}");

}

bool Lexer::isOperator(string s) {
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "=" || s == "(" || s == ")");
}

bool Lexer::isConstant(string s) {
	if (s == "true" || s == "false") {
		return true;
	}
	else if (s[0] == '"') {
		return true;
	}
	else {
		return onlyContainDigits(s);
	}
}

bool Lexer::onlyContainDigits(string s) {
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
		return false;
	}

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

void Lexer::print(vector<Token*> tokens) {
	vector<Token*>::iterator iter, end;
	for (iter = tokens.begin(), end = tokens.end(); iter != end; ++iter) {
		string type;
		TokenType t = (*iter)->getType();
		switch (t) {
		case TokenType::Procedure: type = "procedure"; break;
		case TokenType::Assign: type = "assign"; break;
		case TokenType::Print: type = "print"; break;
		case TokenType::Read: type = "read"; break;
		case TokenType::Identifier: type = "identifier"; break;
		case TokenType::Constant: type = "constant"; break;
		case TokenType::Separator: type = "separator"; break;
		case TokenType::Plus: type = "plus"; break;
		case TokenType::Minus: type = "minus"; break;
		case TokenType::Equal: type = "equal"; break;
		case TokenType::OpenParenthesis: type = "open paranthesis"; break;
		case TokenType::CloseParenthesis: type = "close paranthesis"; break;
		default: cout << "fail";
		}
		cout << type << " " << (*iter)->getName() << endl;
	}
}

