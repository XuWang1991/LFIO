#include "function.h"

ParseNode::ParseNode(ParseType t, char * p, ParseNode * l, ParseNode * r)
{
	type = t;
	left = l;
	right = r;
	switch (type) {
	case argu: {
        sval = p;
        //Argument *ta=new Argument(p);
        //item=(void*)ta;
	}break;
	case atom: {
        sval = p;
        //Predicate *tp=new Predicate(p);
        //item = (void*)tp;
	}break;
	case rule: {
		//sval = p;
	}break;
	case exam: {
		//sval = p;
	}break;
	case tail: {
		//sval = p;
	}break;
	case out: {
		//sval = p;
	}break;
	case in: {
		//sval = p;
	}break;
	}
	//sval = p;
}

Predicate::Predicate(string v)
{
	data = v;
}

Predicate::~Predicate()
{
}

void Predicate::Print()
{
	if (!(cout << data)) {
		cout << "Error in Predicat::Print()" << endl;
		throw 0;
	}
}

bool Predicate::operator==(Predicate *p)
{
	if (data == p->data) {
		return 1;
	}
	else {
		return 0;
	}
}

List::List()
{
	last = items = CreateEmptyNode();
	current = NULL;
}

List::~List()
{
	ListNode *tmp = NULL;

	while (items) {
		tmp = items;
		items = items->next;
		delete tmp;
	}
}

ListNode * List::CreateEmptyNode()
{
	ListNode *new_node = NULL;

	new_node = new ListNode;
	new_node->item = NULL;
	new_node->next = new ListNode;;
	new_node->next = NULL;
	return new_node;
}

void List::Insert(void *item)
{
	ListNode *new_node = CreateEmptyNode();
	//ListNode *tmp = items;
	if (item)
		new_node->item = item;
	new_node->next = NULL;

	new_node->next = items->next;
	items->next = new_node;
	current = items->next;
	if (new_node->next == NULL) {
		last = new_node;
	}
	return;
}

void List::Append(void *item)
{
	ListNode *new_node = NULL;
	new_node = new ListNode;
	new_node->item = item;
	new_node->next = NULL;

	last->next = new_node;
	last = new_node;
	current = items->next;
}

void List::Remove(void *item)
{
	ListNode *tmp1 = NULL;
	ListNode *tmp2 = NULL;


	tmp1 = items->next;
	tmp2 = items;

	while (tmp1 && (tmp1->item != item)) {
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp1) {
		tmp2->next = tmp1->next;
		if (current == tmp1)
			current = tmp2->next;
		delete tmp1;
	}
}



void * List::Iterate()
{
	ListNode *tmp = new ListNode;
	tmp = current;
	//string a;
	if (!current) {
		current = items->next;
		//cout << "BREAK" << endl;
		//cin >> a;
		return NULL;
	}
	current = current->next;
	return tmp->item;
}



//Pre_list::Pre_list()
//{
//}
//
//Pre_list::~Pre_list()
//{
//}
//
//void Pre_list::Insert(Predicate * item)
//{
//	List::Insert((void *)item);
//}
//
//void Pre_list::Append(Predicate * item)
//{
//	List::Append((void *)item);
//}
//
//Predicate * Pre_list::Iterate()
//{
//	return (Predicate *)List::Iterate();
//}

void Argument::Print()
{
    cout << data;
}

bool Argument::operator==(Argument *a)
{
	if (data == a->data) {
		return 1;
	}
	else {
		return 0;
	}
}

Argument::Argument(string v)
{
	data = v;
}

Argument::~Argument()
{
}

//ch* Argument::init(void) {
//	ch* node = (ch*)malloc(sizeof(ch));
//	node->data = "";
//	node->next = NULL;
//	return node;
//}
//
//void Argument::add(ch * item)
//{
//	ch *new_node = NULL;
//	new_node = new ch;
//	new_node->data = item->data;
//	new_node->next = NULL;
//
//	last->next = new_node;
//	last = new_node;
//	current = items->next;
//}
//
//void Argument::remove(ch * item)
//{
//	ch *tmp1 = NULL;
//	ch *tmp2 = NULL;
//
//
//	tmp1 = items->next;
//	tmp2 = items;
//
//	while (tmp1 && (tmp1->data != item->data)) {
//		tmp2 = tmp1;
//		tmp1 = tmp1->next;
//	}
//	if (tmp1) {
//		tmp2->next = tmp1->next;
//		if (current == tmp1)
//			current = tmp2->next;
//		delete tmp1;
//	}
//}

Argu_list::Argu_list()
{
}

Argu_list::~Argu_list()
{
}

void Argu_list::Insert(Argument *item)
{
	Argument *fun = NULL;
	while ((fun = Iterate())) {
		if (fun == item)
			return;
	}
	List::Insert((void*)item);
}

void Argu_list::Append(Argument *item)
{
	List::Append((void*)item);
}

Argument *Argu_list::Iterate()
{
	return (Argument*)List::Iterate();
	//return (Argument*)(List*)this->Iterate();
}

bool Argu_list::is_subset(Argument * ar)
{
	Argument *temp = NULL;
	ClearIterator();
	temp = Iterate();
	while (temp) {
		if (ar->data == temp->data) {
			ClearIterator();
			return 1;
		}
		temp = Iterate();
	}
	ClearIterator();
	return 0;
}

//bool List::operator==(List *al)
//{
//	void *tp1 = NULL, *tp2 = NULL;
//	tp1 = Iterate();
//	tp2 = al->Iterate();
//	while (tp1&&tp2) {
//		if (tp1 != tp2) {
//			ClearIterator();
//			al->ClearIterator();
//			return 0;
//		}
//		tp1 = Iterate();
//		tp2 = al->Iterate();
//	}
//	ClearIterator();
//	al->ClearIterator();
//	if (tp1 == NULL && tp2 == NULL)
//		return 1;
//	else {
//		return 0;
//	}
//}

void Atom::Print()
{
	pre->Print();
	Argument *temp = NULL;
	//temp=al->Iterate();
    if(al){
    al->ClearIterator();
    temp = al->Iterate();
    if (temp) {
		cout << "(";
		temp->Print();
        temp = al->Iterate();
		while (temp) {
			cout << ",";
			temp->Print();
			temp = al->Iterate();
		}
		cout << ")";
		al->ClearIterator();
	}
    }
}

bool Atom::operator==(Atom *a)
{
	bool tb = 0;
	Argument *tp1=NULL,*tp2=NULL;
    a->al->ClearIterator();
    al->ClearIterator();
	tp2 = a->al->Iterate();
	tp1 = al->Iterate();
	if (pre == a->pre) {
		while (tp2&&tp1) {
			if (tp2->data == tp1->data) {
				tb = 1;
				tp1 = al->Iterate();
				tp2 = a->al->Iterate();
			}
			else {
                a->al->ClearIterator();
                al->ClearIterator();
				return 0;
			}
		}
	}
    a->al->ClearIterator();
    al->ClearIterator();
	return tb;
}

Atom::Atom(Predicate *p, Argu_list *a)
{
	pre = p;
	if (a) {
		al = a;
		type = NORMAL;
	}
	else {
		al = NULL;
		type = NO_ARGU;
	}
}

Atom::~Atom()
{
	if (pre) {
		delete[] pre;
	}
	if (al) {
		delete[] al;
	}
}

Atom_list::Atom_list()
{
}

Atom_list::~Atom_list()
{
}

void Atom_list::Insert(Atom *item)
{
	Atom *fun = NULL;
	// removes duplicates
	while ((fun = Iterate())) {
		if (fun == item)
			return;
	}
	List::Insert((void*)item);
}

void Atom_list::Append(Atom *item)
{
	List::Append((void *)item);
}

Atom *Atom_list::Iterate()
{
	return (Atom*)List::Iterate();
}

void Atom_list::Print(){
    Atom *temp=NULL;
    ClearIterator();
    temp=Iterate();
    while(temp){
        temp->Print();
        temp=Iterate();
    }
    ClearIterator();
    cout<<endl;
}

void Rule::Print()
{
	head->Print();
	positive->ClearIterator();
	Atom *temp = positive->Iterate();
	if (temp) {
		cout << ":-";
		temp->Print();
		temp = positive->Iterate();
		while (temp) {
			cout << ",";
			temp->Print();
			temp = positive->Iterate();
		}

	}
	cout << "." << endl;
	positive->ClearIterator();
}

Rule::Rule(Atom *h, Atom_list *p, Atom_list *n)
{
	head = h;
	enable = 1;
	if (p)
		positive = p;
	else {
		positive = NULL;
	}
	if (n)
		negative = n;
	else {
		negative = NULL;
	}
}

Rule::~Rule()
{
	if (head) {
		delete[] head;
	}
	if (positive) {
		delete[] positive;
	}
	if (negative) {
		delete[] negative;
	}
}

Rule_list::Rule_list()
{
}

Rule_list::~Rule_list()
{
}

void Rule_list::Insert(Rule *item)
{
	Rule *fun = NULL;
	// removes duplicates
	while ((fun = Iterate())) {
		if (fun == item)
			return;
	}
	List::Insert((void*)item);
}

void Rule_list::Append(Rule *item)
{
	List::Append((void*)item);
}

void Rule_list::Remove(Rule *item)
{
	List::Remove((void*)item);
}

Rule * Rule_list::Iterate()
{
	return (Rule*)List::Iterate();
}

void Example::Print()
{
	Atom *tp1=NULL, *tp2=NULL;
	//tp1 = input->Iterate();
	//tp2 = output->Iterate();
	input->ClearIterator();
	if ((tp1 = input->Iterate())) {
		cout << "{";
		tp1->Print();
		//tp1 = input->Iterate();
		while ((tp1 = input->Iterate())) {
			cout << ",";
			tp1->Print();
			//tp1 = input->Iterate();
		}
		//cout << ")";
	}
	input->ClearIterator();
	cout << ";";
	output->ClearIterator();
	if ((tp2 = output->Iterate())) {
		//cout << "(";
		tp2->Print();
		//tp2 = output->Iterate();
		while ((tp2 = output->Iterate())) {
			cout << ",";
			tp2->Print();
			//tp2 = output->Iterate();
		}
		cout << "}";
	}
	output->ClearIterator();
	cout << "." << endl;
}

Example::Example(Atom_list *in, Atom_list *out)
{
	input = new Atom_list();
	output = new Atom_list();
	if (in) {
		input = in;
	}
	if (out) {
		output = out;
	}
}

Example::~Example()
{
	if (input) {
		delete[] input;
	}
	if (output) {
		delete[] output;
	}
}

Ex_list::Ex_list()
{
}

Ex_list::~Ex_list()
{
}

void Ex_list::Insert(Example *item)
{
	Example *fun = NULL;
	// removes duplicates
	while ((fun = Iterate())) {
		if (fun == item)
			return;
	}
	List::Insert((void*)item);
}

void Ex_list::Append(Example *item)
{
	List::Append((void*)item);
}

void Ex_list::Remove(Example *item)
{
	List::Remove((void*)item);
}

Example * Ex_list::Iterate()
{
	return (Example*)List::Iterate();
}

void Program::processArgu(ParseNode *p,Argu_list *temp)
{
    //Argu_list *temp=new Argu_list();
    ParseNode *tp=NULL;
    tp=p;
    if (tp) {
        //Argument *ta;
        //ta=new Argument(p->sval);
        Argument *ta=new Argument(p->sval);
		if (ta->data[0] >= 'A' && ta->data[0] <= 'Z') {
			ta->is_variable = 1;
		}
        temp->Insert(ta);
        if(tp->left){
            processArgu(p->left,temp);
        }
        //free(ta);
        //tp=tp->left;
	}
    //return temp;
}

Atom* Program::processAtom(ParseNode *p)
{
        Atom *at=NULL;
        Predicate *pred=new Predicate(p->sval);
        //Argu_list *temp=new Argu_list();
		if (p->right) {
			Argu_list *tal = new Argu_list();
            //tal = processArgu(p->right,temp);
            processArgu(p->right,tal);
            //at = new Atom((Predicate*)p->item, tal);
            at = new Atom(pred, tal);
			at->neg = p->neg;
		}
        else{
            //at = new Atom((Predicate*)p->item, NULL);
            at = new Atom(pred, NULL);
			at->neg = p->neg;
        }

        return at;
}

Atom_list * Program::processTail(ParseNode *p)
{
	Atom_list *temp = new Atom_list();
    ParseNode *tp=NULL;
	tp = p;
	while (tp) {
        temp->Insert(processAtom(tp->right));
		tp = tp->left;
	}
	return temp;
}

void Program::processBody(Atom_list *p, Atom_list *pos, Atom_list *neg)
{
	Atom *temp = NULL;
	p->ClearIterator();
	temp = p->Iterate();
	while (temp) {
		if (temp->neg == 1) {
			neg->Append(temp);
		}
		else {
			pos->Append(temp);
		}
		temp = p->Iterate();
	}
	p->ClearIterator();
}


Rule * Program::processRule(ParseNode *p) {
    Rule *temp=NULL;
	Atom_list *pos = new Atom_list();
	Atom_list *neg = new Atom_list();
	if (p->right) {
		processBody(processTail(p->right), pos, neg);
		temp = new Rule(processAtom(p->left), pos, neg);
	}
	else {
		temp = new Rule(processAtom(p->left), NULL, NULL);
	}
	return temp;
}

Atom_list * Program::processIn(ParseNode *p)
{
	Atom_list *temp = new Atom_list();
    ParseNode *tp=NULL;
	tp = p;
	while (tp) {
        temp->Insert(processAtom(tp->right));
		tp = tp->left;
	}
	return temp;
}

Atom_list * Program::processOut(ParseNode *p)
{
	Atom_list *temp = new Atom_list();
    ParseNode *tp=NULL;
	tp = p;
	while (tp) {
        temp->Insert(processAtom(tp->right));
		tp = tp->left;
	}
	return temp;
}

Example * Program::processExam(ParseNode *p)
{
    Example *temp=NULL;
	if (p) {
		temp = new Example(processIn(p->left), processOut(p->right));
	}
	return temp;
}

void Program::add(ParseNode *p)
{
	if (p) {
		switch (p->type) {
		case rule: B->Append(processRule(p)); break;
		case exam: E->Append(processExam(p)); break;
		}
	}
}

Program::Program()
{
	//predicate = new Pre_list();
	argument = new Argu_list();
	atoms = new Atom_list();
	rules = new Rule_list();
	examples = new Ex_list();
	B = new Rule_list();
	P = new Rule_list();
	E = new Ex_list();
}

Program::~Program()
{
}

Str_list::~Str_list()
{
}

void Str_list::Insert(ch * item)
{
	List::Insert((void*)item);
}

void Str_list::Append(ch * item)
{
	List::Append((void*)item);
}

void Str_list::Remove(ch * item)
{
	List::Remove((void*)item);
}

void Str_list::clearall()
{
	ch *temp = NULL;
	ClearIterator();
	temp = Iterate();
	while (temp) {
		Remove(temp);
		ClearIterator();
		temp = Iterate();
	}
	ClearIterator();
}

ch * Str_list::Iterate()
{
	return (ch*)List::Iterate();
}

bool Str_list::is_subset(ch * item)
{
	ch *temp = NULL;
	ClearIterator();
	temp = Iterate();
	while (temp) {
		if (item->data == temp->data) {
			ClearIterator();
			return 1;
		}
		temp = Iterate();
	}
	ClearIterator();
	return 0;
}

Str_list::Str_list()
{
}

ch::ch(string item){
data=item;
}

void Str_list::Print(){
    ch *c=NULL;
    ClearIterator();
    c=Iterate();
    while(c){
        cout<<c->data<<" ";
        c=Iterate();
    }
    ClearIterator();
}

ch::~ch(){
}

theta::theta(string v, string t)
{
	var = v;
	term = t;
}

theta::~theta()
{
}

void theta::Print(){
    cout << var << "/" << term<<endl;
}

theta_list::theta_list()
{
}

theta_list::~theta_list()
{
}

void theta_list::Insert(theta * item)
{
	List::Insert((void*)item);
}

void theta_list::Append(theta * item)
{
	List::Append((void*)item);
}

void theta_list::Remove(theta * item)
{
	List::Remove((void*)item);
}

theta * theta_list::Iterate()
{
	return (theta*)List::Iterate();
}

substitution_list::substitution_list()
{
}

substitution_list::~substitution_list()
{
}

void substitution_list::Insert(substitution * item)
{
	List::Insert((void*)item);
}

void substitution_list::Append(substitution * item)
{
	List::Append((void*)item);
}

void substitution_list::Remove(substitution * item)
{
	List::Remove((void*)item);
}

substitution * substitution_list::Iterate()
{
	return (substitution*)List::Iterate();
}

substitution::substitution()
{
	tl = new theta_list();
}

substitution::~substitution()
{
}

void substitution::Print(){
    theta *t=NULL;
    tl->ClearIterator();
    t=tl->Iterate();
    cout<<"{";
    while(t){
        cout<<t->var<<"/"<<t->term;
        t=tl->Iterate();
        if(t)
            cout<<",";
    }
    tl->ClearIterator();
    cout<<"}"<<endl;
}

Theta::Theta()
{
	var = "";
	term = new Str_list();
}

Theta::~Theta()
{
}

Theta_list::Theta_list()
{
}

Theta_list::~Theta_list()
{
}

void Theta_list::Insert(Theta * item)
{
	List::Insert((void*)item);
}

void Theta_list::Append(Theta * item)
{
	List::Append((void*)item);
}

void Theta_list::Remove(Theta * item)
{
	List::Remove((void*)item);
}

Theta * Theta_list::Iterate()
{
	return (Theta*)List::Iterate();
}

void Theta::Print(){
    cout<<var;
    term->Print();
}
