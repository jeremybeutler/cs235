#ifndef EXPRESSION_MANAGER
#define EXPRESSION_MANAGER
#include "ExpressionManagerInterface.h"
#include "Stack.h"
#include <ctype.h>

const string OPEN = "([{";	// set of opening parentheses
const string CLOSE = ")]}";	// corresponding closing parentheses.
const string OPERATOR = "*/%+-";
const string IMMEDIATE = ")]}";
const string HIGH = "*/%";
const string LOW = "+-";
const string WILD = "([{";
const string NUMBER = "1234567890";

int do_op(char op, int a, int b)
{
	switch (op)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	case '%':
		return a % b;
		break;
	default:
		throw std::runtime_error("unknown op");
	}
}

/** Function to determine if open parentheses */
bool isOpen(char ch)
{
	return OPEN.find(ch) != string::npos;
}

/** Function to determine if closing parentheses */
bool isClose(char ch)
{
	return CLOSE.find(ch) != string::npos;
}

bool isLeftParen(char t)
{
	return t == '(';
}

bool isRightParen(char t)
{
	return t == ')';
}

bool isPair(char left, char right)
{
	//std::cout << "( " << left << " and " << right << " )";
	return (left == '(' && right == ')') || (left == '{' && right == '}') || (left == '[' && right == ']');
}

bool isOperator(char ch)
{
	return OPERATOR.find(ch) != string::npos;
}

bool isNumber(char ch)
{
	return NUMBER.find(ch) != string::npos;
}

int precedence(char ch)
{
	return (IMMEDIATE.find(ch) != string::npos) ? 3
		: (HIGH.find(ch) != string::npos) ? 2
		: (LOW.find(ch) != string::npos) ? 1
		: (WILD.find(ch) != string::npos) ? 0
		: -1;
}

class ExpressionManager
{
private:
	std::string expression;

public:
	ExpressionManager(void) {};
	virtual ~ExpressionManager(void) {};

	void setExpression(std::string exp)
	{
		expression = exp;
	}

	std::string getExpression()
	{
		return expression;
	}

	virtual int value(void)
	{
		Stack<int> stack;
		int right;
		int left;
		int result;
		std::stringstream ss;
		ss << postfix();
		string temp;
		int next_num;
		char next_ch;
		while (ss >> temp)
		{
			if (std::stringstream(temp) >> next_num)
			{
				stack.push(next_num);
			}
			else if (std::stringstream(temp) >> next_ch)
			{
				right = stack.top();
				if (!stack.empty()) stack.pop();
				left = stack.top();
				if (!stack.empty()) stack.pop();
				result = do_op(next_ch, left, right);
				stack.push(result);
			}
		}
		return stack.top();
	}

	int checkCleanInput()
	{
		Stack<int> stack;
		int numOperators = 0;
		int numOperands = 0;
		std::stringstream ss;
		ss << postfix();
		string temp;
		int next_num;
		char next_ch;
		while (ss >> temp)
		{
			if (std::stringstream(temp) >> next_num)
			{
				if (isNumber('0' + next_num))
				{
					numOperands++;
					numOperators = 0;
				}
			}
			else if (std::stringstream(temp) >> next_ch)
			{
				if (isOperator(next_ch))
				{
					numOperands = 0;
					numOperators++;
				}
				else
				{
					return 1;
				}
			}

			if (numOperators > 2) { std::cout << "operators: " << numOperators << " "; return 2; }
			if (numOperands > 2) { std::cout << "operands: " << numOperands << " "; return 3; }
		}
		return 0;
	}

	bool isBalanced(void)
	{
		Stack<char> stack;
		bool balanced = true;
		for (unsigned int i = 0; i < expression.length(); i++)
		{
			char next_ch = expression[i];
			if (isOpen(next_ch)) stack.push(next_ch);
			else
			{
				if (isClose(next_ch))
				{
					if (stack.empty()) balanced = false;
					else
					{
						char top_ch = stack.top();
						stack.pop();
						balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
					}
				}
			}
		}
		return balanced && stack.empty();
	}

	virtual string infix(void)
	{
		return expression;
	}

	/** Return a postfix representation of the infix expression */
	virtual string postfix(void)
	{
		Stack<char> stack;
		string postfixStr;
		std::stringstream ss;
		ss << expression;
		string temp;
		int next_num;
		char next_ch;
		if (!isBalanced()) return "Unbalanced";
		while (ss >> temp)
		{
			if (std::stringstream(temp) >> next_num)
			{
				postfixStr += std::to_string(next_num);
				postfixStr += " ";
				//std::cout << std::to_string(next_num) << " ";
			}
			else if (std::stringstream(temp) >> next_ch)
			{
				//std::cout << next_ch << " ";
				if (isOpen(next_ch))
				{
					stack.push(next_ch);
					//std::cout << "push: " << next_ch << std::endl;
				}
				else if (isClose(next_ch))
				{
					//std::cout << "one ";
					//stack.push(next_ch);
					while (!isPair(stack.top(), next_ch))
					{
						//std::cout << "two ";
						postfixStr += stack.top();
						postfixStr += " ";
						stack.pop();
						//std::cout << "pop: " << next_ch << std::endl;
						if (stack.empty()) break;
					}
					if (!stack.empty())
					{
						stack.pop();
						//std::cout << "pop: " << next_ch << std::endl;
					}
				}
				else if (isOperator(next_ch))
				{
					if (precedence(next_ch) == 2)
					{
						if (stack.empty())
						{
							//std::cout << "push: " << next_ch << std::endl;
							stack.push(next_ch);
						}
						else if (precedence(stack.top()) < 2)
						{
							stack.push(next_ch);
							//std::cout << "push: " << next_ch << std::endl;
						}
						else
						{
							while (precedence(stack.top()) >= 2)
							{
								postfixStr += stack.top();
								postfixStr += " ";
								stack.pop();
								//std::cout << "pop: " << next_ch << std::endl;
								if (stack.empty()) break;
							}
							stack.push(next_ch);
							//std::cout << "push: " << next_ch << std::endl;
						}
					}
					else if (precedence(next_ch) == 1)
					{
						//std::cout << "minus ";
						if (stack.empty())
						{
							stack.push(next_ch);
							//std::cout << "push: " << next_ch << std::endl;
						}
						else if (precedence(stack.top()) < 1)
						{
							stack.push(next_ch);
							//std::cout << "push: " << next_ch << std::endl;
						}
						else
						{
							while (precedence(stack.top()) >= 1)
							{
								postfixStr += stack.top();
								postfixStr += " ";
								stack.pop();
								//std::cout << "pop: " << next_ch << std::endl;
								if (stack.empty()) break;
							}
							stack.push(next_ch);
							//std::cout << "push: " << next_ch << std::endl;
						}
					}
				}
			}

			temp = "";
		}
		while (!stack.empty())
		{
			postfixStr += stack.top();
			postfixStr += " ";
			//std::cout << "pop: " << stack.top() << std::endl;
			stack.pop();

		}

		//std::cout << std::endl;
		postfixStr = postfixStr.substr(0, postfixStr.size() - 1);
		return postfixStr;
	}
	/** (BONUS) Return a prefix representation of the infix expression */
	virtual string prefix(void)
	{
		return "NOT IMPLEMENTED";
	}

	/** Return the infix vector'd expression items */
	virtual string toString() const
	{
		return "asdf";
	}

};

#endif