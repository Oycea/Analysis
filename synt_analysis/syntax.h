#ifndef SYNTAX_H
#define SYNTAX_H

#include<iostream>
#include<fstream>
#include<string>
#include"dka.h"

#define PROGRAM 7
#define INTEGER 2
#define COMPLEX 3
#define CABS 4
#define CMPLX 5
#define END 6

#define LPAREN 11    /* ( */
#define RPAREN 12   /* ) */
#define ASSIGN 13  /* = */
#define PLUS 14 /* + */
#define MINUS 18 /* - */
#define APPERAND 19 /* , */

#define REALDIG 101
#define INTDIG 102
#define ID 103

#define SYN_ERR 301
#define LEX_ERR 302

#define EXPECTED_IDENTIFIER 111
#define EXPECTED_ASSIGN 112
#define EXPECTED_SEPARATOR 113
#define EXPECTED_RPAREN 114
#define EXPECTED_LPAREN 115
#define UNRECOGNIZED_STATEMENT 116
#define EXPECTED_DESCRIPTION 117
#define EXPECTED_APPERAND 118
#define EXPECTED_PROGRAM 119
#define SUP_RPAREN 120
#define SUP_ASSIGN 121

#define TYPE 200
#define EXPR 201
#define SEXPR 202
#define DESCRIPTION 203
#define DESCR 204
#define OPERS 205
#define OP 206
#define BEGIN 207
#define FUNCTION 208
#define VAR_LIST 209
#define EXPECTED_END 210

#define OK 1
string trans(int num) {
    switch (num) {
    case EXPECTED_IDENTIFIER:
        return "EXPECTED IDENTIFIER";
    case EXPECTED_ASSIGN:
        return "EXPECTED ASSIGN";
    case EXPECTED_SEPARATOR:
        return "EXPECTED SEPARATOR";
    case EXPECTED_RPAREN:
        return "EXPECTED RPAREN";
    case EXPECTED_LPAREN:
        return "EXPECTED LPAREN";
    case UNRECOGNIZED_STATEMENT:
        return "UNRECOGNIZED STATEMENT";
    case EXPECTED_DESCRIPTION:
        return "EXPECTED DESCRIPTION";
    case EXPECTED_APPERAND:
        return "EXPECTED APPERAND";
    case EXPECTED_PROGRAM:
        return "EXPECTED PROGRAM";
    case SUP_RPAREN:
        return "EXTRA RPAREN";
    case SUP_ASSIGN:
        return "EXTRA ASSIGN";
    case LEX_ERR:
        return "LEXICAL ERROR";
    case ID:
        return "ID";
    case TYPE:
        return "TYPE";
    case EXPR:
        return "EXPR";
    case SEXPR:
        return "SIMPLE EXPR";
    case DESCRIPTION:
        return "DESCRIPTION";
    case DESCR:
        return "DESCR";
    case OPERS:
        return "OPERATORS";
    case OP:
        return "OP";
    case BEGIN:
        return "BEGIN";
    case FUNCTION:
        return "FUNCTION";
    case VAR_LIST:
        return "VARLIST";
    case INTEGER:
        return "INTEGER";
    case PROGRAM:
        return "PROGRAM";
    case APPERAND:
        return "APPERAND";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case ASSIGN:
        return "ASSIGN";
    case LPAREN:
        return "LEFT BRACKET";
    case RPAREN:
        return "RIGHT BRACKET";
    case INTDIG:
        return "INT NUM";
    case REALDIG:
        return "COMPLEX NUM";
    case END:
        return "END";
    case EXPECTED_END:
        return "EXPECTED_END";
    default:
        return "OK";
    }
}

int get_lexem(ifstream& fin, Checker& gg, Hash_table& gg_2, Element& el) {
    char ch;
    fin.get(ch);
    std::string buffer;
    if ((int)ch == -52)
        return LEX_ERR;
    /* пропускаем все пробелы, табуляции и символы новой строки */
    while (ch == ' ' || ch == '\n')
        fin.get(ch);
    if (ch == '(') {
        string word = "(";
        Element a(word, "LPAREN");
        el = a;
        gg_2.insert(a);
        return LPAREN;
    }
    if (ch == ')') {
        string word = ")";
        Element a(word, "RPAREN");
        el = a;
        gg_2.insert(a);
        return RPAREN;
    }

    if (ch == '=') {
        string word = "=";
        Element a(word, "ASSIGN");
        el = a;
        gg_2.insert(a);
        return ASSIGN;
    }

    if (ch == ',') {
        string word = ",";
        Element a(word, "APPERAND");
        el = a;
        gg_2.insert(a);
        return APPERAND;
    }

    if (ch == '+') {
        string word = "+";
        Element a(word, "PLUS");
        el = a;
        gg_2.insert(a);
        return PLUS;
    }

    if (ch == '-') {
        string word = "-";
        Element a(word, "MINUS");
        el = a;
        gg_2.insert(a);
        return MINUS;
    }

    /* сложный случай 3: идентификатор или ключевое слово */
    if (isalpha(ch) || ch == '_') {
        int i = 0;

        do {
            buffer += ch;
        } while ((fin.get(ch) && (isalpha(ch) || isdigit(ch)) && ch != ' '));
        fin.putback(ch);

        if ("PROGRAM" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return PROGRAM;
        }

        if ("INTEGER" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return INTEGER;
        }

        if ("COMPLEX" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return COMPLEX;
        }

        if ("CABS" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return CABS;
        }

        if ("CMPLX" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return CMPLX;
        }

        if ("END" == buffer) {
            Element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return END;
        }

        if (gg.check_word(buffer) == "id") {
            Element a(buffer, "id");
            el = a;
            gg_2.insert(a);
            return ID;
        }
        else {
            Element a(buffer, "LEX_ERR");
            el = a;
            return LEX_ERR;
        }
    }

    /* сложный случай 4: число */
    if (isdigit(ch)) {
        int i = 0;
        do {
            buffer += ch;
        } while ((fin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '.') && ch != ' '));
        fin.putback(ch);
        string stat = gg.check_word(buffer);
        if (stat == "complexNum") {
            Element a(buffer, "COMPLEX NUM");
            el = a;
            gg_2.insert(a);
            return REALDIG;
        }
        else if (stat == "intNum") {
            Element a(buffer, "INT NUM");
            el = a;
            gg_2.insert(a);
            return INTDIG;
        }
        Element a(buffer, "LEX_ERR");
        el = a;
    }

    return LEX_ERR;
}
#endif