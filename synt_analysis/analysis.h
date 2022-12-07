#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <string>
#include <iostream>
#include <fstream>
#include "hash_table.h"
#include "syntax.h"
#include "incident.h"
#include "dka.h"
#include "tree.h"
#include "element.h"

class syntax_anal {
public:
    Hash_table table() { return gg_2; }
    string lexem() { return _lexem.get_lexem(); }
    string lexem2() { return pref_lexem.get_lexem(); }
private:
    ifstream stream;
    Hash_table gg_2;
    Checker gg;
    int pref;
    int _pref;
    int flag_lparen;
    int flag_rparen;
    node* _root;
    Element _lexem;
    Element pref_lexem;
    //����������� ������� ������� ������
    int expression(node* _son) {
        int statement_result;
        //����� ��������� �������
        pref_lexem = _lexem;
        int lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        //���� �� ������ ��������� ����� ������ ������ �������
        if (lexem == END) {
            //�� ����� ��������� �� ���� ��� �����
            if (pref == PLUS || pref == MINUS || pref == ITOR || pref == CABS)
                return UNRECOGNIZED_STATEMENT;
            pref = lexem;
            return OK;
        }
        if (lexem == RPAREN) {
            //��������� ������� ����� ����� ������� ����� (-+
            if (pref == 0 || pref == MINUS || pref == PLUS)
                return EXPECTED_IDENTIFIER;
            pref = lexem;
            if (flag_lparen > 0) {
                flag_rparen += 1;
                pref = RPAREN;
                return OK;
            }
            else
                return EXPECTED_LPAREN;
        }
        if (lexem == LPAREN) {
            //��������� ������� ����� ����� ������� ����� ����� ��� ���������
            if (pref == INTDIG || pref == REAL || pref == ID)
                return EXPECTED_SEPARATOR;
            if (pref != CABS && pref != ITOR) {
                _son = _son->add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
            }
            _son->add(_son, _lexem);
            pref = 0;
            flag_lparen += 1;
            //���� ��������� ��� �������� ������ ������
            statement_result = expression(_son);

            //�������� ��� �� ������ ������ ��������
            if (statement_result != OK) {
                return UNRECOGNIZED_STATEMENT;
            }

            if (flag_rparen == 0)
                return EXPECTED_RPAREN;

            flag_lparen -= 1;
            flag_rparen -= 1;
            _son->add(_son, _lexem);
            //��������� ����� ����� ������ ��� ��� ����� �� �� �������� ������
            pref_lexem = _lexem;
            lexem = get_lexem(stream, gg, gg_2, _lexem);
            if (lexem == LEX_ERR)
                return LEX_ERR;
            if (lexem == PLUS || lexem == MINUS) {
                pref = lexem;
                _son->add(_son, _lexem);
                return expression(_son);
            }
            else if (lexem == RPAREN) {
                flag_rparen += 1;
                if (flag_lparen == 0)
                    return SUP_RPAREN;
            }
            else if (lexem == REALDIG || lexem == INTDIG || lexem == CABS || lexem == ITOR)
                return UNRECOGNIZED_STATEMENT;
            else if (lexem == ID && flag_lparen == flag_rparen && flag_lparen == 0)
                return EXPECTED_ASSIGN;
            else if (lexem == ASSIGN)
                return SUP_ASSIGN;
            pref = lexem;
            if (lexem == LEX_ERR)
                return UNRECOGNIZED_STATEMENT;
            return OK;
        }
        //���� �������� ���������� ������ ������
        else if (pref == 0) {
            if (lexem == PLUS || lexem == MINUS)
                return EXPECTED_IDENTIFIER;
            pref = lexem;
            if (lexem != CABS and lexem != ITOR) {
                _son = _son->add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
                _son = _son->add(_son, lexem);
                _son = _son->add(_son, _lexem);
                return expression(_son->parent->parent->parent);
            }
            else {
                _son = _son->add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
                _son = _son->add(_son, _lexem);
                return expression(_son->parent);
            }
        }
        else if (pref == ID || pref == REALDIG || pref == INTDIG) {
            if (lexem == REALDIG || lexem == INTDIG || lexem == CABS || lexem == ITOR)
                return EXPECTED_SEPARATOR;
            if (lexem == ID)
                return EXPECTED_ASSIGN;
            pref = lexem;
            if (lexem == PLUS || lexem == MINUS) {
                _son->add(_son, _lexem);
                return expression(_son);
            }
            else
                return UNRECOGNIZED_STATEMENT;
        }
        else if (pref == PLUS || pref == MINUS) {
            if (lexem == PLUS || lexem == MINUS)
                return EXPECTED_IDENTIFIER;
            pref = lexem;
            if (lexem == INTDIG || lexem == REALDIG || lexem == ID) {
                _son = _son->add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
                _son = _son->add(_son, lexem);
                _son = _son->add(_son, _lexem);
                return expression(_son->parent->parent->parent);
            }
            else if (lexem == CABS || lexem == ITOR) {
                _son = _son->add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
                _son = _son->add(_son, _lexem);
                return expression(_son->parent);
            }
            else
                return UNRECOGNIZED_STATEMENT;
        }
        return UNRECOGNIZED_STATEMENT;
    }

    int description(node* _son, node* _description) {
        pref_lexem = _lexem;
        int lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem == ID) {
            if (_pref == APPERAND || _pref == INTEGER || _pref == REAL) {
                _son = _son->add(_son, VAR_LIST);
                _pref = lexem;
                _son = _son->add(_son, ID);
                _son = _son->add(_son, _lexem);
                return description(_son->parent, _description);
            }
            else if (_pref == ID) {
                return EXPECTED_SEPARATOR;
            }
        }
        if (lexem == APPERAND) {
            if (_pref == APPERAND || _pref == INTEGER || _pref == REAL) {
                return EXPECTED_IDENTIFIER;
            }
            else if (_pref == ID) {
                _pref = lexem;
                _son->add(_son, _lexem);
                return description(_son, _description);
            }
        }
        if (lexem == PLUS || lexem == MINUS || lexem == ASSIGN || lexem == RPAREN || lexem == CABS || lexem == ITOR
            || lexem == LPAREN) {
            return UNRECOGNIZED_STATEMENT;
        }
        if (lexem == REAL || lexem == INTEGER) {
            _pref = lexem;
            _son = _description->add(_description, DESCRIPTION);
            _description = _son;
            _son = _son->add(_son, DESCR);
            _son = _son->add(_son, TYPE);
            _son = _son->add(_son, _lexem);
            return description(_son->parent->parent, _description);
        }
    }
public:
    node* root() { return _root; }
    syntax_anal(string _stream) {
        stream.open(_stream);
        pref = 0;
        _pref = 0;
        flag_lparen = 0;
        flag_rparen = 0;
        _root = new node(PROGRAM);
    }
    int program()
    {
        int statement_result;
        int lexem;
        node* _son = _root->add(_root, BEGIN);
        pref_lexem = _lexem;
        lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;

        if (lexem != PROGRAM)
            return EXPECTED_PROGRAM;
        _son->add(_son, _lexem);
        pref_lexem = _lexem;
        lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem != ID)
            return EXPECTED_IDENTIFIER;
        _son = _root->add(_son, lexem);
        _son = _root->add(_son, _lexem);
        pref_lexem = _lexem;
        lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem != INTEGER && lexem != REAL) {
            return EXPECTED_DESCRIPTION;
        }
        else {
            _pref = lexem;
            _son = _root->add(_root, DESCRIPTION);
            _son = _son->add(_son, DESCR);
            _son = _son->add(_son, TYPE);
            _son = _son->add(_son, _lexem);
            statement_result = description(_son->parent->parent, _root->arr[1]);
        }

        if (statement_result == EXPECTED_SEPARATOR) {
            pref_lexem = _lexem;
            lexem = get_lexem(stream, gg, gg_2, _lexem);
            if (lexem == LEX_ERR)
                return LEX_ERR;
            if (lexem != ASSIGN)
                return EXPECTED_ASSIGN;
            _son = _root->add(_root, OPERS);
            _son = _son->add(_son, OP);
            _son = _son->add(_son, ID);
            _son = _son->add(_son, pref_lexem);
            _son = _son->add(_son->parent->parent, _lexem);
        }
        else
            return statement_result;

        statement_result = expression(_son->parent);
        node* _opers = _root->arr[2];
        while (statement_result != OK) {
            if (statement_result == EXPECTED_ASSIGN) {
                pref_lexem = _lexem;
                lexem = get_lexem(stream, gg, gg_2, _lexem);
                if (lexem == LEX_ERR)
                    return LEX_ERR;
                if (lexem == ASSIGN) {
                    pref = 0;
                    _son = _opers->add(_opers, OPERS);
                    _opers = _son;
                    _son = _son->add(_son, OP);
                    _son = _son->add(_son, ID);
                    _son = _son->add(_son, pref_lexem);
                    _son = _son->add(_son->parent->parent, _lexem);
                    statement_result = expression(_son->parent);
                }
                else
                    return EXPECTED_SEPARATOR;
            }
            else
                return statement_result;
        }
        _son = _root->add(_root, END);
        if (pref != END)
            return EXPECTED_END;
        _son->add(_son, _lexem);
        pref_lexem = _lexem;
        lexem = get_lexem(stream, gg, gg_2, _lexem);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem != ID)
            return EXPECTED_IDENTIFIER;
        _son = _root->add(_son, lexem);
        _son = _root->add(_son, _lexem);
        return OK;
    }
};

#endif