#include <iostream>
#include <string>
#include <vector> 
using namespace std; 
#include "val.h"


void ExecuteMult(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " * " << val2 << " is " <<  val1 * val2 << endl;
}

void ExecuteLThan(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " < " << val2 << " is " <<  (val1 < val2 ) << endl;
}

void ExecuteCatenate(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " // " << val2 << " is " <<  (val1.Catenate(val2)) << endl;
}

void ExecutePower(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " ** " << val2 << " is " <<  (val1.Power(val2)) << endl; 
}


	
int main(int argc, char *argv[])
{
	Value ErrorVal;
	double num1 = 7.25;
	Value doubleVal1(num1);
	double num2 = 3;
	Value doubleVal2(num2);
	string str1 = "CS280";
	Value StrVal1(str1); 
	string str2 = "Spring 2023";
	Value StrVal2(str2);
	
	int intval1 = 25;
	Value intVal1(intval1);
	int intval2 = 4;
	Value intVal2(intval2);
	
	
	vector<Value> vals( {ErrorVal, intVal1, intVal2, doubleVal1, doubleVal2, StrVal1, StrVal2} );
	bool multflag = false, lthanflag = false, catflag = false, powflag = false;
	
	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}
	
	string arg( argv[1] );
	if( arg == "-mult" )
		multflag = true;
	else if( arg == "-lthan" )
		lthanflag = true;
	else if( arg == "-cat" )
		catflag = true;		
	else if( arg == "-pow" )
		powflag = true;
	
	else {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
	}
		
	
	cout << "ErrorVal=" << ErrorVal << endl; 
	//cout << "IntVal=" << IntVal << endl; 
	cout << "intVal1=" << intVal1 << endl; 
	cout << "intVal2=" << intVal2 << endl;
	cout << "doubleVal1=" << doubleVal1 << endl; 
	cout << "doubleVal2=" << doubleVal2 << endl;
	cout << "StrVal1=" << StrVal1 << endl; 
	cout << "StrVal2=" <<  StrVal2 << endl;
	
	
	if(multflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
			for( int j = 0; j < vals.size(); j++ )
				if( i != j )
					ExecuteMult( vals[i], vals[j] );
	}
	
	if(lthanflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteLThan( vals[i], vals[j] );
	}	
	
	if(catflag)
	{				
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteCatenate( vals[i], vals[j] );
	}
	if(powflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecutePower( vals[i], vals[j] );
	}
	
	
	return 0;
}

