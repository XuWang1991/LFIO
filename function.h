#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;
char* clone_string(const char *st);
enum ParseType {
	argu, atom, rule, exam, tail, out, in
};

class ParseNode
{
public:
	ParseNode() { left = NULL; right = NULL; }
	~ParseNode() { delete left; delete right; sval=""; }
	ParseNode(ParseType, char *, ParseNode *, ParseNode *);

public:
	ParseNode *left;
	ParseNode *right;
	ParseType	type;
    //void *item;
	string sval;
	bool neg = 0;
};

class ch
{
public:
	string data;
	ch(string);
	~ch();
};


//class Predicate;
//class Argument;
//class Atom;
//class Rule;
//class Example;
//class List;
//class Pre_list;
//class Argu_list;
//class Atom_list;
//class Rule_list;
//class Ex_list;
//class Program;

enum AtomType { NORMAL, NO_ARGU };

struct ListNode {
	void *item;
	ListNode *next;
};

class List{
public:
	ListNode *items, *current, *last;

	void Insert(void *item);
	void Append(void *item);
	void Remove(void *item);

	ListNode *CreateEmptyNode();
	void *Iterate();
	void ClearIterator() { current = items->next;}
	//bool operator==(List*);
        bool is_last(){if(current == NULL)return 1;else return 0;}
	List();
	~List();
};

class Predicate{
public:
	string data;
    Predicate(string);
    ~Predicate();
	void Print();
	bool operator==(Predicate*);
};

//class Pre_list:public List{
//public:
//	Pre_list();
//	~Pre_list();
//
//	void Insert(Predicate *item);
//	void Append(Predicate *item);
//	Predicate *Iterate();
//};

class Str_list :public List {
public:
	Str_list();
	~Str_list();

	void Insert(ch *item);
	void Append(ch *item);
	void Remove(ch *item);
	void clearall();
	ch *Iterate();
	bool is_subset(ch *item);
        void Print();
};

class theta {
public:
	theta(string, string);
	~theta();
	string var;
	string term;
        void Print();
};

class theta_list :public List {
public:
	theta_list();
	~theta_list();

	void Insert(theta *item);
	void Append(theta *item);
	void Remove(theta *item);
	theta *Iterate();
};

class substitution {
public:
	substitution();
	~substitution();
	theta_list *tl;
        void Print();
};

class substitution_list :public List {
public:
	substitution_list();
	~substitution_list();

	void Insert(substitution *item);
	void Append(substitution *item);
	void Remove(substitution *item);
	substitution *Iterate();
};

class Theta {
public:
	Theta();
	~Theta();
	string var;
	Str_list *term;

        void Print();
};

class Theta_list :public List {
public:
	Theta_list();
	~Theta_list();

	void Insert(Theta *item);
	void Append(Theta *item);
	void Remove(Theta *item);
	Theta *Iterate();
};

class Argument {
public:
	string data;
	string ground_data="";
    string general_data="";
	bool is_variable = 0;
	bool is_general = 1;
	Argument *argu_of_lgg = NULL;
	void Print();
	bool operator==(Argument*);
	Argument(string);
	~Argument();

	Str_list *sl = NULL;

	/*ch *items, *current, *last;
	ch* init(void);
	void add(ch *item);
	void remove(ch *item);*/
};

class Argu_list :public List {
public:
	Argu_list();
	~Argu_list();

	void Insert(Argument *item);
	void Append(Argument *item);
	Argument *Iterate();
	bool is_subset(Argument *ar);
};

class Atom {
public:
	Predicate *pre;
	Argu_list *al;
	AtomType type;
	bool neg=0;
	theta_list *tl=NULL;
	substitution_list *sl = NULL;
	bool consider = 0;
	void Print();
	bool operator==(Atom*);
	Atom(Predicate*, Argu_list*);
	~Atom();
};

class Atom_list :public List {
public:
	Atom_list();
	~Atom_list();

	void Insert(Atom *item);
	void Append(Atom *item);
	Atom *Iterate();
	theta_list *tl = NULL;
        void Print();
};

class Rule {
public:
	Atom *head;
	Atom_list *positive, *negative;
	bool enable;
	bool is_remove = 0;
	bool consider = 0;

	void Print();
	Rule(Atom*, Atom_list*, Atom_list*);
	~Rule();
};

class Rule_list :public List {
public:
	Rule_list();
	~Rule_list();

	void Insert(Rule *item);
	void Append(Rule *item);
	void Remove(Rule *item);
	Rule *Iterate();
};

class Example {
public:
	Atom_list *input, *output;

	void Print();
	Example(Atom_list*, Atom_list*);
	~Example();
};

class Ex_list :public List {
public:
	Ex_list();
	~Ex_list();

	void Insert(Example *item);
	void Append(Example *item);
	void Remove(Example *item);
	Example *Iterate();
};



class Program {
public:
	//Pre_list *predicate;
	Argu_list *argument;
	Atom_list *atoms;
	Rule_list *rules;
	Ex_list *examples;

	Rule_list *B;
	Rule_list *P;
	Ex_list *E;
	Rule_list *B_P = new Rule_list();

    void processArgu(ParseNode*,Argu_list*);
	Atom* processAtom(ParseNode*);
	Atom_list* processTail(ParseNode*);
	void processBody(Atom_list*,Atom_list*,Atom_list*);
    Rule* processRule(ParseNode*);
    Atom_list* processIn(ParseNode*);
    Atom_list* processOut(ParseNode*);
    Example* processExam(ParseNode*);

    void add(ParseNode*);
	Program();
	~Program();
};

#endif // FUNCTION_H
