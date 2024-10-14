//Israel Alcantara
// Full Recursive-Descent Parser

#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <map>
#include "lex.h"
#include "parser.h"

using namespace std;

map<string, bool> defVar;

int error_count = 0;

void ParserError(int line, const string& msg) 
{
    cerr << line << ": " << msg << endl;
    error_count++;
}

bool Decl(istream& in, int& line) 
{
    Token tok = GetNextToken(in, line);

    if (tok == INTEGER || tok == REAL || tok == CHARACTER) 
    {
        if (GetNextToken(in, line) != DCOLON) 
        {
            ParserError(line, "Missing '::' in declaration");
            return false;
        }

        if (!VarList(in, line)) 
        {
            ParserError(line, "Invalid variable declaration");
            return false;
        }
        return true;
    }

    ParserError(line, "Invalid declaration type");
    return false;
}

bool VarList(istream& in, int& line) 
{
    Token tok = GetNextToken(in, line);

    if (tok != IDENT) 
    {
        ParserError(line, "Expected an identifier in VarList");
        return false;
    }

    defVar[tok.GetLexeme()] = false;

    tok = GetNextToken(in, line);
    if (tok == ASSOP) 
    {
        if (!Expr(in, line)) 
        {
            ParserError(line, "Invalid initialization in VarList");
            return false;
        }
        cout << "Initialization of variable " << tok.GetLexeme() << " in the declaration statement." << endl;
    } 
    else 
    {
        PushBackToken(tok);
    }

    tok = GetNextToken(in, line);
    if (tok == COMMA) 
    {
        return VarList(in, line);
    } 
    else 
    {
        PushBackToken(tok);
        return true;
    }
}

bool Prog(istream& in, int& line) 
{
    Token tok = GetNextToken(in, line);

    if (tok != PROGRAM) 
    {
        ParserError(line, "Missing PROGRAM keyword");
        return false;
    }

    if (GetNextToken(in, line) != IDENT) 
    {
        ParserError(line, "Expected program identifier");
        return false;
    }

    while (true) 
    {
        tok = GetNextToken(in, line);
        if (tok == END) break;

        PushBackToken(tok);
        if (!Decl(in, line) && !Stmt(in, line)) 
        {
            ParserError(line, "Unrecognized declaration or statement");
            return false;
        }
    }

    if (GetNextToken(in, line) != PROGRAM)
    {
        ParserError(line, "Missing END PROGRAM keyword");
        return false;
    }

    if (GetNextToken(in, line) != IDENT) 
    {
        ParserError(line, "Missing program identifier at end");
        return false;
    }

    cout << "(DONE)" << endl;
    return true;
}

bool Stmt(istream& in, int& line) 
{
    Token tok = GetNextToken(in, line);

    switch (tok.GetToken()) {
        case PRINT:
            if (GetNextToken(in, line) != STAR) 
            {
                ParserError(line, "Expected '*' after PRINT");
                return false;
            }
            if (!ExprList(in, line)) 
            {
                ParserError(line, "Invalid expression in print statement");
                return false;
            }
            cout << "Print statement in program." << endl;
            return true;
        case IF:
            return BlockIfStmt(in, line);
        case IDENT:
            PushBackToken(tok);
            return AssignStmt(in, line);
        default:
            ParserError(line, "Invalid statement");
            return false;
    }
}

bool BlockIfStmt(istream& in, int& line) 
{
    if (GetNextToken(in, line) != LPAREN) 
    {
        ParserError(line, "Expected '(' after IF");
        return false;
    }

    if (!RelExpr(in, line)) 
    {
        ParserError(line, "Invalid relational expression in if statement");
        return false;
    }

    if (GetNextToken(in, line) != RPAREN) 
    {
        ParserError(line, "Missing closing parenthesis in if statement");
        return false;
    }

    if (GetNextToken(in, line) != THEN) 
    {
        ParserError(line, "Missing THEN in if statement");
        return false;
    }

    while (true) 
    {
        Token tok = GetNextToken(in, line);
        if (tok == ELSE || tok == END) 
        {
            PushBackToken(tok);
            break;
        }

        PushBackToken(tok);
        if (!Stmt(in, line)) 
        {
            ParserError(line, "Invalid statement inside if block");
            return false;
        }
    }

    tok = GetNextToken(in, line);
    if (tok == ELSE) 
    {
        while (true) 
        {
            tok = GetNextToken(in, line);
            if (tok == END) break;

            PushBackToken(tok);
            if (!Stmt(in, line)) 
            {
                ParserError(line, "Invalid statement inside else block");
                return false;
            }
        }
    }

    if (GetNextToken(in, line) != END || GetNextToken(in, line) != IF) 
    {
        ParserError(line, "Missing END IF");
        return false;
    }

    cout << "End of Block If statement." << endl;
    return true;
}

bool AssignStmt(istream& in, int& line) 
{
    Token tok = GetNextToken(in, line);

    if (tok != IDENT) 
    {
        ParserError(line, "Expected identifier for assignment");
        return false;
    }

    if (GetNextToken(in, line) != ASSOP) 
    {
        ParserError(line, "Missing assignment operator");
        return false;
    }

    if (!Expr(in, line)) 
    {
        ParserError(line, "Invalid expression in assignment");
        return false;
    }

    defVar[tok.GetLexeme()] = true;
    return true;
}

bool RelExpr(istream& in, int& line) 
{
    if (!Expr(in, line)) 
    {
        return false;
    }

    Token tok = GetNextToken(in, line);
    if (tok == EQ || tok == LTHAN || tok == GTHAN) 
    {
        if (!Expr(in, line)) 
        {
            ParserError(line, "Invalid expression in relational expression");
            return false;
        }
    } 
    else 
    {
        PushBackToken(tok);
    }

    return true;
}

bool Expr(istream& in, int& line) 
{
    return MultExpr(in, line);
}

bool MultExpr(istream& in, int& line) 
{
    return true; 
}

bool ExprList(istream& in, int& line) 
{
    if (!Expr(in, line)) 
    {
        return false;
    }

    Token tok = GetNextToken(in, line);
    if (tok == COMMA) 
    {
        return ExprList(in, line);
    }

    PushBackToken(tok);  
    return true;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        cerr << "Usage: prog2 filename" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) 
    {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    int line = 1;
    if (!Prog(infile, line)) 
    {
        cerr << "Unsuccessful Parsing" << endl;
        cerr << "Number of Syntax Errors: " << error_count << endl;
        return 1;
    }

    cout << "Successful Parsing" << endl;
    return 0;
}
