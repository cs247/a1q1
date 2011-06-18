/*
 *  main.cpp
 *  
 *
 *  Created by Joanne Atlee on 08/05/11.
 *
 */


#include <iostream>
#include <string>
#include <sstream>

using namespace std;



//************************************************************************
//  MONEY ADT
//************************************************************************

class Money {
public:
	explicit Money( long dollars = 0, long cents = 0);	// Constructor with specified money value
	~Money();						// Destructor 
	Money dollars() const;					// Accessor - dollar value
	Money cents() const;					// Accessor - cents value
	string str() const;					// Return value as string (e.g., $123,456.78)
	Money operator+ (const Money& n) const;			// Add two money values; return result
	Money operator- (const Money& n) const;			// Subtract n; return result 
	Money operator* (int f) const;				// Multiply by f%; return result
private:
	// << YOUR IMPLEMENTATION HERE >>

	
};

bool operator== (const Money& m, const Money &n);	// Test if m==n
bool operator!= (const Money& m, const Money &n);	// Test if m!=n
bool operator<  (const Money& m, const Money &n);	// Test if m<n
bool operator<= (const Money& m, const Money &n);	// Test if m<=n
bool operator>  (const Money& m, const Money &n);	// Test if m>n
bool operator>= (const Money& m, const Money &n);	// Test if m>=n	


istream& operator>> (istream&, Money&);		   // read money value from input stream
ostream& operator<< (ostream&, const Money&);      // write money value to output stream


//************************************************************************
//  MONEY IMPLEMENTATION
//************************************************************************

// << YOUR IMPLEMENTATION HERE >>



//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

//  operators
enum Op {EQ, NEQ, GT, GTE, LT, LTE, PLUS, MINUS, MULT, DIV, DOLLARS, CENTS, AMT, STR, NONE};


Op convertOp(string opStr) {
	switch (opStr[0]) {
		case 'd': return DOLLARS; 
		case 'c': return CENTS;
		case 's': return STR;
		case '+': return PLUS; 
		case '-': return MINUS; 
		case '*': return MULT; 
		case '=': return EQ; 
		case '!': return NEQ; 
		case '<': {
			if ( opStr[1] == '=' ) {
				return LTE;
			}
			else {
				return LT;
			}
		}
		case '>': {
			if ( opStr[1] == '=' ) {
				return GTE;
			}
			else {
				return GT;
			}
		}
		default: return NONE;
	}
}
	
//*******************
// main()
//*******************


int main() {
	cout << "Test harness for Money ADT" << endl << endl;
	
	cout << "Command: ";

	// read whole input line into string, then "stream" from string
	string input;
	while ( getline(cin, input) ) {		
		stringstream inputSS(input);
		
		// parse first operand
		Money m1;
		inputSS >> m1;
		
		if ( inputSS.fail() ) {
			cout << "Invalid first operand." << endl;
		}
		
		
		// check whether expression is lone operand
		else {
			if ( inputSS.eof() ) {
				cout << "== " << m1 << endl;
			}
			
			// parse operator
			else {
				string opStr;
				inputSS >> opStr;
								
				Op op = convertOp(opStr);
		
				if ( op == NONE ) {
					cout << "Invalid expression." << endl;
				}
						
				// parse second operand
				else {		
					Money m2, result;

					switch (op) {
						case DOLLARS: 
							result = m1.dollars();	
							cout << "== " << result << endl;
							break;
						case CENTS:
							result = m1.cents();
							cout << "== " << result << endl;
							break;
						case STR: {
							string value;
							value = m1.str();
							cout << "== " << value << endl;
							break;
						}
							
						case EQ: case NEQ: case LT: case LTE: case GT: case GTE: 
						{
							inputSS >> m2;
							if (inputSS.fail() ) {
								cout << "Invalid second operand." << endl;
								break;
							}
						
							string boolResult;
							switch (op) {
								case EQ:
									boolResult = (m1 == m2) ? "true" : "false";
									break;
								case NEQ:
									boolResult = (m1 != m2) ? "true" : "false";
									break;
								case LT:
									boolResult = (m1 < m2) ? "true" : "false";
									break;
								case LTE:
									boolResult = (m1 <= m2) ? "true" : "false";
									break;
								case GT:
									boolResult = (m1 > m2) ? "true" : "false";
									break;
								case GTE:
									boolResult = (m1 >= m2) ? "true" : "false";
									break;
							}
						
							cout << "== " << boolResult << endl;
							break;
						}
						case PLUS: case MINUS:
							inputSS >> m2;
							if (inputSS.fail() ) {
								cout << "Invalid second operand." << endl;
								break;
							}

							switch (op) {
								case PLUS: result = m1 + m2; break;
								case MINUS: result = m1 - m2; break;
							}
							cout << "== " << result << endl;
							break;
						case MULT:
							int factor;
							inputSS >> factor;
							if ( inputSS.fail() ) {
								cout << "Invalid second operand." << endl;
							}
							else {
								result = m1 * factor;
								cout << "== " << result << endl;
							}
							break;
					} // switch
				} // else second operand
			} // else exists operator
		} // else first operand OK
						
		
		cout << endl << "Command: ";
	}
	
	
}
