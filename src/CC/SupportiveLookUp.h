#include<bits/stdc++.h>
using namespace std;

bool isDigit( char ch )
{
    return ch >= '0' && ch <= '9';
}

bool operatorCheck( char ch )
{
    if (  ch == '{' || ch == '}' || 
        ch == '[' || ch == ']' || 
        ch == '(' || ch == ')' || 
        ch == '#' || ch == ';' || 
        ch == ':' || ch == '?' || 
        ch == '+' || ch == '-' || 
        ch == '*' || ch == '/' || 
        ch == '%' || ch == '^' || 
        ch == '&' ||ch ==  '|' || 
        ch == '!' || ch == '=' || 
        ch == '<' || ch == '>' || 
        ch == ',' ) {
        return true;
    }
    else {
        return false;
    }
}

bool operatorCheckdup( char ch )
{
    if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' ) {
        return true;
    }
    else {
        return false;
    }
}

bool isItInteger( string check )
{
    for ( int i = 0; i < (int) check.size(); ++i ) {
        if ( !isDigit( check[ i ] ) ) {
                return false;
        }
    }

    return true;
}

bool isItDouble( string check )
{
    int dotCount = 0;

    for ( int i = 0; i < (int) check.size(); ++i ) {
        if ( isDigit( check[ i ] ) ) {
                continue;
        }

        if ( check[ i ] == '.' ) {
                dotCount++;
        }
        else {
                return false;
        }
    }

    return dotCount <= 1;
}