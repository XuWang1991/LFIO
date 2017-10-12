#include "function.h"

#ifndef ALGORITHM_H
#define ALGORITHM_H

Str_list *termlist = new Str_list;
Str_list *predicatelist = new Str_list;

Argument *copy_argument(Argument *ar){
  Argument *temp=new Argument(ar->data);
  return temp;
}

Argu_list *copy_argu_list(Argu_list *al){
  Argu_list *temp=new Argu_list();
  Argument *ar=NULL;
  al->ClearIterator();
  ar=al->Iterate();
  while(ar){
    temp->Append(ar);
    ar=al->Iterate();
  }
  al->ClearIterator();
  return temp;
}

Predicate *copy_predicate(Predicate *p){
  Predicate *temp=new Predicate(p->data);
  return temp;
}

Atom *copy_atom(Atom *a){
  Atom *temp=new Atom(a->pre,copy_argu_list(a->al));
  return temp;
}
Atom_list *copy_atom_list(Atom_list *al){
    Atom_list *temp=new Atom_list();
    Atom *a=NULL;
    al->ClearIterator();
    a=al->Iterate();
    while(a){
        //a->Print();cout<<endl;
        temp->Append(copy_atom(a));
        a=al->Iterate();
    }
    al->ClearIterator();
    return temp;
}

bool is_equal_al(Argu_list *al1,Argu_list *al2)
{
    if (al1 && al2)
    {
        Argument *tp1 = NULL, *tp2 = NULL;
        al1->ClearIterator();
        tp1 = al1->Iterate();
        al2->ClearIterator();
        tp2 = al2->Iterate();
        while (tp1 != NULL&&tp2 != NULL)
        {
            if (tp1->data != tp2->data)
            {
                al1->ClearIterator();
                al2->ClearIterator();
                return 0;
            }
            tp1 = al1->Iterate();
            tp2 = al2->Iterate();
        }
        al1->ClearIterator();
        al2->ClearIterator();
        if (tp1 == NULL && tp2 == NULL)
            return 1;
        else
        {
            return 0;
        }
    }
    else if (!(al1) && !(al2))
    {
        return 1;
    }
}

//bool is_subset(Argument *ar, Argu_list *al) {
//	Argument *temp = NULL;
//	al->ClearIterator();
//	temp = al->Iterate();
//	while (temp) {
//		if (ar->data == temp->data) {
//			al->ClearIterator();
//			return 1;
//		}
//		temp = al->Iterate();
//	}
//	al->ClearIterator();
//	return 0;
//}

bool is_equal_atom(Atom *at1, Atom *at2)
{
    if (at1->pre->data == at2->pre->data /*&& at1->al && at2->al */)
    {
        if(at1->al==at2->al)
            return 1;
		if (is_equal_al(at1->al, at2->al) == 1)
			return 1;
    }
//    else if (at1->pre->data == at2->pre->data && !(at1->al) && !(at2->al))
//    {
//        return 1;
//    }
    return 0;
}

bool is_belong(Atom *p, Atom_list *ap)  //if e belong to the set ae of examples
{
    Atom *temp=NULL;
    ap->ClearIterator();
    temp = ap->Iterate();
    while (temp != NULL)
    {
        if (is_equal_atom(p,temp)==1)
        {
            return 1;
        }
        temp = ap->Iterate();
    }
    ap->ClearIterator();
    return 0;
}

bool is_subset(Atom_list *ap1, Atom_list *ap2)  //if ap1 is the subset of ap2
{
    Atom *temp = NULL;
    ap1->ClearIterator();
    ap2->ClearIterator();
    temp=ap1->Iterate();
    while(temp != NULL)
    {
        /*if(is_belong(temp,ap2)==1&&temp)
        {
            temp=ap1->Iterate();
        }
        else */if(is_belong(temp,ap2)==0&&temp)
        {
            ap1->ClearIterator();
            return 0;
        }
//        else
//        {
            temp=ap1->Iterate();
//        }
    }
    ap1->ClearIterator();
    return 1;
}

bool is_belong_without_argu(Atom *p, Atom_list *ap)  //if e belong to the set ae of examples
{
    Atom *temp=NULL;
    temp = ap->Iterate();
    while (temp != NULL)
    {
        if (p->pre->data==temp->pre->data && p)
        {
            return 1;
        }
        temp = ap->Iterate();
    }
    ap->ClearIterator();
    return 0;
}

bool is_subset_without_argu(Atom_list *ap1, Atom_list *ap2)  //if ap1 is the subset of ap2
{
    Atom *temp = NULL;

    ap1->ClearIterator();
    temp = ap1->Iterate();

    while(temp != NULL)
    {
        if(is_belong_without_argu(temp,ap2)==1&&temp)
        {
            temp=ap1->Iterate();
        }
        else if(is_belong_without_argu(temp,ap2)==0&&temp)
        {
            ap1->ClearIterator();
            return 0;
        }
        else
        {
            temp=ap1->Iterate();
        }
    }
    ap1->ClearIterator();
    return 1;
}


bool cheak_is_satisfied_by_condition(Ex_list *ae)
{
    Example *e1 = NULL, *e2 = NULL;
    Ex_list *temp = ae;

    e1 = ae->Iterate();
    while (e1 != NULL)
    {
        if (e1->input&&e1->output&&is_subset(e1->input, e1->output) == 0)
        {
            cout << "The example: ";
            e1->Print();
            cout<< "Without coherent." << endl;
            throw 0;
        }
        e1 = ae->Iterate();
    }
    ae->ClearIterator();

    e1 = ae->Iterate();
    while (e1 != NULL)
    {
        e2 = ae->Iterate();
        while (e2 != NULL)
        {
            if (e1 != e2)
            {
                if (is_subset(e1->input, e2->input) == 1 && is_subset(e1->output, e2->output) == 0)
                {
                    cout << "The example: ";
                    e1->Print();
                    cout << "The example: ";
                    e2->Print();
                    cout << "Without monotonicity." << endl;
                    throw 0;
                }
            }
            if (e1 != e2)
            {
                if (is_subset(e1->input, e2->output) == 1 && is_subset(e1->output, e2->output) == 0)
                {
                    cout << "The example: ";
                    e1->Print();
                    cout << "The example: ";
                    e2->Print();
                    cout << "Without convergence." << endl;
                    throw 0;
                }
            }
            e2 = ae->Iterate();
        }
        ae->ClearIterator();
        while (e1 != e2)
        {
            e2 = ae->Iterate();
        }
        e1 = ae->Iterate();
        ae->ClearIterator();
    }
    ae->ClearIterator();

}

void remove_waste_rule(Rule *r, Rule_list *arr/*, Array_substitution s[]*/)
{
    Rule *temp = NULL;
    arr->ClearIterator();
    temp = arr->Iterate();
    while (temp != NULL)
    {
        if (is_equal_atom(r->head,temp->head)==1 && is_subset(r->positive, temp->positive) == 1)
        {
            //arr->Remove(temp);
            //temp->enable = 0;
            arr->Remove(temp);
        }
        temp = arr->Iterate();
    }
    arr->ClearIterator();
}

bool  is_include_var_argu(Atom *at)
{
	Argument *temp = NULL;
	at->al->ClearIterator();
	temp = at->al->Iterate();
	while (temp)
	{
		if (temp->data[0] <= 'Z' && temp->data[0] >= 'A')
		{
			at->al->ClearIterator();
			return 1;
		}
		temp = at->al->Iterate();
	}
	at->al->ClearIterator();
	return 0;
}

theta *add_theta(string v, string t)
{
    theta *temp = new theta(v, t);
    return temp;
}

theta_list *copy_thetalist(theta_list *tl) {
	theta *t = NULL;
	theta_list *temp = new theta_list();
	tl->ClearIterator();
	t = tl->Iterate();
	while (t) {
		temp->Append(t);
		t = tl->Iterate();
	}
	tl->ClearIterator();
	return temp;
}

bool match_argument_in_step_of_check_subsume(Atom *a1, Atom *a2, theta_list *tl) { //a2 includes variables and a1 is ground
	Argument *ar1 = NULL, *ar2 = NULL;
	theta_list *temp = new theta_list();
	theta *t = NULL;

	if (a1->pre->data != a2->pre->data) {
		return 0;
	}

	a1->al->ClearIterator();
	a2->al->ClearIterator();
	ar1 = a1->al->Iterate();
	ar2 = a2->al->Iterate();
	while (ar1 && ar2) {
		tl->ClearIterator();
		t = tl->Iterate();
		while (t) {
			if (ar2->data == t->var && ar1->data != t->term) {
				a1->al->ClearIterator();
				a2->al->ClearIterator();
				tl->ClearIterator();
				return 0;
			}
			if (ar2->data == t->var && ar1->data == t->term) {
				goto br1;
			}
			t = tl->Iterate();
		}
		tl->ClearIterator();

		temp->ClearIterator();
		t = temp->Iterate();
		while (t) {
			if (ar2->data == t->var && ar1->data != t->term) {
				a1->al->ClearIterator();
				a2->al->ClearIterator();
				temp->ClearIterator();
				return 0;
			}
			if (ar2->data == t->var && ar1->data == t->term) {
				goto br1;
			}
			t = temp->Iterate();
		}
		temp->ClearIterator();
		if (!t) {
			temp->Append(add_theta(ar2->data, ar1->data));
		}
	br1:
		ar1 = a1->al->Iterate();
		ar2 = a2->al->Iterate();
	}
	a1->al->ClearIterator();
	a2->al->ClearIterator();

	temp->ClearIterator();
	t = temp->Iterate();
	while (t) {
		tl->Append(t);
		t = temp->Iterate();
	}
	temp->ClearIterator();
	return 1;
}

bool check_subsume_with_background_between_rules(Rule *r1, Rule *r2) { //where r1 is ground and r2 is belong to background
	theta_list *tl = new theta_list();
	Atom *a1 = NULL, *a2 = NULL;
	//theta *t = NULL;
	if (match_argument_in_step_of_check_subsume(r1->head, r2->head, tl) == 1) {
		r2->positive->ClearIterator();
		a2 = r2->positive->Iterate();
		while (a2) {
			r1->positive->ClearIterator();
			a1 = r1->positive->Iterate();
			while (a1) {
				if (match_argument_in_step_of_check_subsume(a1, a2, tl) == 1) {
					r1->positive->ClearIterator();
					break;
				}
				a1 = r1->positive->Iterate();
			}
			r1->positive->ClearIterator();
			if (!a1) {
				r2->positive->ClearIterator();
				return 0;
			}
			a2 = r2->positive->Iterate();
		}
		r2->positive->ClearIterator();
		return 1;
	}
	return 0;
}

bool bool_subsume_with_background(Rule *r,Rule_list *rl){
	Rule *temp=NULL;
	//theta_list *tl = new theta_list();
	//theta *t = NULL;

	rl->ClearIterator();
	temp = rl->Iterate();
	while (temp) {
		//if (is_include_var_argu(temp->head) == 1) {
			if (check_subsume_with_background_between_rules(r, temp) == 1) {
				rl->ClearIterator();
				return 1;
			}
		//}
		temp = rl->Iterate();
	}
	rl->ClearIterator();
	return 0;
}

bool bool_subsume(Rule *r, Rule_list *arr/*, Array_substitution s[]*/)
{
    Rule *temp = NULL;
    arr->ClearIterator();
    temp = arr->Iterate();
    while (temp != NULL)
    {
		if (is_include_var_argu(temp->head) == 1 && check_subsume_with_background_between_rules(r, temp) == 1) {
			arr->ClearIterator();
			return 1;
		}
        if (is_equal_atom(r->head, temp->head) == 1 && is_subset(temp->positive, r->positive) == 1)
        {
            arr->ClearIterator();
            return 1;
        }
        else
            temp=arr->Iterate();
    }
    arr->ClearIterator();
    return 0;
}

void rule_add(Atom *a, Rule_list *P, Rule_list *B_P, Atom_list *in)
{
    Rule *r = new Rule(a, copy_atom_list(in), NULL);
    if (bool_subsume(r, B_P) == 0)
    {
        remove_waste_rule(r, P);
        P->Append(r);
        B_P->Append(r);
    }
}

void for_each_loop(Example *E, Rule_list *P, Rule_list *B_P)
{
    Atom *temp;
    temp = E->output->Iterate();
    while (temp != NULL)
    {
        rule_add(temp, P, B_P, E->input);
        temp = E->output->Iterate();
    }
    E->output->ClearIterator();
}

void optimization(Example *E)
{
    Atom *ta = NULL, *tp = NULL;
    E->input->ClearIterator();
    E->output->ClearIterator();
    tp = E->input->Atom_list::Iterate();
    while (tp != NULL)
    {
        if (is_belong(tp, E->output) == 1 /*&&ta*/)
        {
            ta = E->output->Atom_list::Iterate();
            while (ta != NULL)
            {
                if (ta->pre->data == tp->pre->data && is_equal_al(ta->al, tp->al)==1)
                {
                    E->output->Atom_list::Remove(ta);
                    break;
                }
                else
                {
                    ta = E->output->Atom_list::Iterate();
                }
            }
            E->output->Atom_list::ClearIterator();
            tp = E->input->Atom_list::Iterate();
        }

        else
        {
            tp = E->input->Atom_list::Iterate();
        }
    }
    E->input->Atom_list::ClearIterator();
    E->output->Atom_list::ClearIterator();
}

void is_enable(Rule_list *P)
{
    Rule *temp = P->Rule_list::Iterate();
    while (temp != NULL)
    {
        if (is_belong(temp->head, temp->positive) == 1)
        {
            temp->enable = 0;
        }
        temp = P->Rule_list::Iterate();
    }
    P->Rule_list::ClearIterator();
}

bool check_argu_is_belong_arlist(Argument *ar,Argu_list *al)
{
    Argument *temp=NULL;
    al->ClearIterator();
    temp=al->Iterate();
    while(temp)
    {
        if(ar && temp->data==ar->data)
        {
            al->ClearIterator();
            return 1;
        }
        temp=al->Iterate();
    }
    al->ClearIterator();
    return 0;
}

Argu_list* collect_ground(Ex_list *el)
{
    Argu_list *temp=new Argu_list;
    Example *tpex=NULL;
    Atom *tpat=NULL;
    Argument *tpar=NULL;
    el->ClearIterator();
    tpex=el->Iterate();
    while(tpex)
    {
        tpex->input->ClearIterator();
        tpat=tpex->input->Iterate();
        while(tpat)
        {
            tpat->al->ClearIterator();
            tpar=tpat->al->Iterate();
            while(tpar)
            {
                if(check_argu_is_belong_arlist(tpar,temp)==0)
                {
                    temp->Append(tpar);
                }
                tpar=tpat->al->Iterate();
            }
            tpat->al->ClearIterator();
            tpat=tpex->input->Iterate();
        }
        tpex->input->ClearIterator();

        tpex->output->ClearIterator();
        tpat=tpex->output->Iterate();
        while(tpat)
        {
            tpat->al->ClearIterator();
            tpar=tpat->al->Iterate();
            while(tpar)
            {
                if(check_argu_is_belong_arlist(tpar,temp)==0)
                {
                    temp->Append(tpar);
                }
                tpar=tpat->al->Iterate();
            }
            tpat->al->ClearIterator();
            tpat=tpex->output->Iterate();
        }
        tpex->output->ClearIterator();

        tpex=el->Iterate();
    }
    el->ClearIterator();
}

//void ground_of_general_rule(Rule *r,Argu_list *al){
//    Atom *at1=NULL,*at2=NULL;
//    Argument *tp1=NULL,*tp2=NULL;
//    Argument *temp=NULL;

//    al->ClearIterator();

//    r->head->al->ClearIterator();
//    tp1 = r->head->al->Iterate();
//    if (tp1) {
//        temp=al->Iterate();
//        if(temp){
//            tp1->general_data=temp->data;
//        }
//        tp1 = r->head->al->Iterate();
//        while (tp1) {
//            r->head->al->ClearIterator();
//            tp2 = r->head->al->Iterate();
//            while (tp2 != tp1) {
//                if (tp2->data == tp1->data)
//                    tp1->general_data = tp2->general_data;
//                tp2 = r->head->al->Iterate();
//            }
//            if (tp2 == tp1) {
//                temp=al->Iterate();
//                if(temp){
//                    tp1->general_data=temp->data;
//                }
//                else{
//                    al->ClearIterator();
//                    temp=al->ClearIterator();
//                    if(temp){
//                        tp1->general_data=temp->data;
//                    }
//                }
//                tp1 = r->head->al->Iterate();
//            }
//        }
//        r->head->al->ClearIterator();
//    }
//    r->head->al->ClearIterator();

//    r->positive->ClearIterator();
//    at1 = r->positive->Iterate();
//    if (at1) {
//        at1->al->ClearIterator();
//        tp1 = at1->al->Iterate();
//        while (tp1) {
//            r->head->al->ClearIterator();
//            tp2 = r->head->al->Iterate();
//            while (tp2) {
//                if (tp1->data == tp2->data) {
//                    tp1->general_data = tp2->general_data;
//                    r->head->al->ClearIterator();
//                    goto br;
//                }
//                tp2 = r->head->al->Iterate();
//            }
//            r->head->al->ClearIterator();

//            at1->al->ClearIterator();
//            tp2 = at1->al->Iterate();
//            while (tp2 != tp1) {
//                if (tp2->data == tp1->data)
//                    tp1->general_data = tp2->general_data;
//                tp2 = at1->al->Iterate();
//            }
//            if (tp2 == tp1) {
//                temp=al->Iterate();
//                if(temp){
//                    tp1->general_data=temp->data;
//                }
//                else{
//                    al->ClearIterator();
//                    temp=al->ClearIterator();
//                    if(temp){
//                        tp1->general_data=temp->data;
//                    }
//                }
//                tp1 = at1->al->Iterate();
//            }

//            if (1 < 0) {
//br:
//                tp1 = at1->al->Iterate();
//            }
//        }
//        at1->al->ClearIterator();

//        at1 = r->positive->Iterate();
//        while (at1) {
//            at1->al->ClearIterator();
//            tp1 = at1->al->Iterate();
//            while (tp1) {
//                r->head->al->ClearIterator();
//                tp2 = r->head->al->Iterate();
//                while (tp2) {
//                    if (tp1->data == tp2->data) {
//                        tp1->general_data = tp2->general_data;
//                        r->head->al->ClearIterator();
//                        goto br1;
//                    }
//                    tp2 = r->head->al->Iterate();
//                }
//                r->head->al->ClearIterator();

//                r->positive->ClearIterator();
//                at2 = r->positive->Iterate();
//                while (at2 != at1) {
//                    at2->al->ClearIterator();
//                    tp2 = at2->al->Iterate();
//                    while (tp2) {
//                        if (tp1->data == tp2->data) {
//                            tp1->general_data = tp2->general_data;
//                            at2->al->ClearIterator();
//                            goto br1;
//                        }
//                        tp2 = at2->al->Iterate();
//                    }
//                    at2->al->ClearIterator();
//                    at2 = r->positive->Iterate();
//                }
//                if (at2 == at1) {
//                    at1->al->ClearIterator();
//                    tp2 = at1->al->Iterate();
//                    while (tp2 != tp1) {
//                        if (tp2->data == tp1->data)
//                            tp1->general_data = tp2->general_data;
//                        tp2 = at1->al->Iterate();
//                    }
//                    if (tp2 == tp1) {
//                        temp=al->Iterate();
//                        if(temp){
//                            tp1->general_data=temp->data;
//                        }
//                        else{
//                            al->ClearIterator();
//                            temp=al->ClearIterator();
//                            if(temp){
//                                tp1->general_data=temp->data;
//                            }
//                        }
//                        tp1 = at1->al->Iterate();
//                    }
//                }

//                if (1 < 0) {
//br1:
//                    tp1 = at1->al->Iterate();
//                }
//            }
//            at1->al->ClearIterator();
//            r->positive->ClearIterator();
//            at2 = r->positive->Iterate();
//            while (at2 != at1) {
//                at2 = r->positive->Iterate();
//            }
//            at1 = r->positive->Iterate();
//        }
//        r->positive->ClearIterator();
//    }
//    r->positive->ClearIterator();
//}

void ground_of_background(Program p)
{
    Rule *temp=NULL;
    Argu_list *altemp=collect_ground(p.examples);

    p.B->ClearIterator();
    temp=p.B->Iterate();
    while(temp)
    {
//        ground_of_general_rule(temp,altemp);

        temp=p.B->Iterate();
    }
    p.B->ClearIterator();
}

void set_arity_to_subsume(Rule *r)
{
    string s = "A";
    Argument *tp1 = NULL, *tp2 = NULL;
    Atom *at1 = NULL, *at2 = NULL;
    r->head->al->ClearIterator();
    tp1 = r->head->al->Iterate();
    if (tp1)
    {
        tp1->general_data = s;
        s[0] += 1;
        tp1 = r->head->al->Iterate();
        while (tp1)
        {
            r->head->al->ClearIterator();
            tp2 = r->head->al->Iterate();
            while (tp2 != tp1)
            {
                if (tp2->data == tp1->data)
                    tp1->general_data = tp2->general_data;
                tp2 = r->head->al->Iterate();
            }
            if (tp2 == tp1)
            {
                tp1->general_data = s;
                s[0] += 1;
                tp1 = r->head->al->Iterate();
            }
        }
        r->head->al->ClearIterator();
    }
    r->head->al->ClearIterator();

    r->positive->ClearIterator();
    at1 = r->positive->Iterate();
    if (at1)
    {
        at1->al->ClearIterator();
        tp1 = at1->al->Iterate();
        while (tp1)
        {
            r->head->al->ClearIterator();
            tp2 = r->head->al->Iterate();
            while (tp2)
            {
                if (tp1->data == tp2->data)
                {
                    tp1->general_data = tp2->general_data;
                    r->head->al->ClearIterator();
                    goto br;
                }
                tp2 = r->head->al->Iterate();
            }
            r->head->al->ClearIterator();

            at1->al->ClearIterator();
            tp2 = at1->al->Iterate();
            while (tp2 != tp1)
            {
                if (tp2->data == tp1->data)
                    tp1->general_data = tp2->general_data;
                tp2 = at1->al->Iterate();
            }
            if (tp2 == tp1)
            {
                tp1->general_data = s;
                s[0] += 1;
                tp1 = at1->al->Iterate();
            }

            if (1 < 0)
            {
br:
                tp1 = at1->al->Iterate();
            }
        }
        at1->al->ClearIterator();

        at1 = r->positive->Iterate();
        while (at1)
        {
            at1->al->ClearIterator();
            tp1 = at1->al->Iterate();
            while (tp1)
            {
                r->head->al->ClearIterator();
                tp2 = r->head->al->Iterate();
                while (tp2)
                {
                    if (tp1->data == tp2->data)
                    {
                        tp1->general_data = tp2->general_data;
                        r->head->al->ClearIterator();
                        goto br1;
                    }
                    tp2 = r->head->al->Iterate();
                }
                r->head->al->ClearIterator();

                r->positive->ClearIterator();
                at2 = r->positive->Iterate();
                while (at2 != at1)
                {
                    at2->al->ClearIterator();
                    tp2 = at2->al->Iterate();
                    while (tp2)
                    {
                        if (tp1->data == tp2->data)
                        {
                            tp1->general_data = tp2->general_data;
                            at2->al->ClearIterator();
                            goto br1;
                        }
                        tp2 = at2->al->Iterate();
                    }
                    at2->al->ClearIterator();
                    at2 = r->positive->Iterate();
                }
                if (at2 == at1)
                {
                    at1->al->ClearIterator();
                    tp2 = at1->al->Iterate();
                    while (tp2 != tp1)
                    {
                        if (tp2->data == tp1->data)
                            tp1->general_data = tp2->general_data;
                        tp2 = at1->al->Iterate();
                    }
                    if (tp2 == tp1)
                    {
                        tp1->general_data = s;
                        s[0] += 1;
                        tp1 = at1->al->Iterate();
                    }
                }

                if (1 < 0)
                {
br1:
                    tp1 = at1->al->Iterate();
                }
            }
            at1->al->ClearIterator();
            r->positive->ClearIterator();
            at2 = r->positive->Iterate();
            while (at2 != at1)
            {
                at2 = r->positive->Iterate();
            }
            at1 = r->positive->Iterate();
        }
        r->positive->ClearIterator();
    }
    r->positive->ClearIterator();
}

void add_to_theta(Argu_list *al, string data, string general_data)
{
    Argument *temp = new Argument(data);
    temp->general_data = general_data;
    al->Append(temp);
}

void set_arity_to_atomlist(Atom_list *al)
{
    string s = "A";
    Argument *tp1 = NULL, *tp2 = NULL;
    Atom *at1 = NULL, *at2 = NULL;
    al->ClearIterator();
    at1 = al->Iterate();
    if (at1)
    {
        at1->al->ClearIterator();
        tp1 = at1->al->Iterate();
        if (tp1)
        {
            tp1->general_data = s;
            s[0] += 1;
            tp1 = at1->al->Iterate();
            while (tp1)
            {
                at1->al->ClearIterator();
                tp2 = at1->al->Iterate();
                while (tp2 != tp1)
                {
                    if (tp2->data == tp1->data)
                        tp1->general_data = tp2->general_data;
                    tp2 = at1->al->Iterate();
                }
                if (tp2 == tp1)
                {
                    tp1->general_data = s;
                    s[0] += 1;
                    tp1 = at1->al->Iterate();
                }
            }
        }
        at1->al->ClearIterator();

        at1 = al->Iterate();
        while (at1)
        {
            at1->al->ClearIterator();
            tp1 = at1->al->Iterate();
            while (tp1)
            {
                al->ClearIterator();
                at2 = al->Iterate();
                while (at2 != at1)
                {
                    at2->al->ClearIterator();
                    tp2 = at2->al->Iterate();
                    while (tp2)
                    {
                        if (tp1->data == tp2->data)
                        {
                            tp1->general_data = tp2->general_data;
                            at2->al->ClearIterator();
                            goto br1;
                        }
                        tp2 = at2->al->Iterate();
                    }
                    at2->al->ClearIterator();
                    at2 = al->Iterate();
                }
                if (at2 == at1)
                {
                    at1->al->ClearIterator();
                    tp2 = at1->al->Iterate();
                    while (tp2 != tp1)
                    {
                        if (tp2->data == tp1->data)
                            tp1->general_data = tp2->general_data;
                        tp2 = at1->al->Iterate();
                    }
                    if (tp2 == tp1)
                    {
                        tp1->general_data = s;
                        s[0] += 1;
                        tp1 = at1->al->Iterate();
                    }
                }
                if (1 < 0)
                {
br1:
                    tp1 = at1->al->Iterate();
                }
            }
            at1->al->ClearIterator();
            al->ClearIterator();
            at2 = al->Iterate();
            while (at2 != at1)
            {
                at2 = al->Iterate();
            }
            at1 = al->Iterate();
        }
        al->ClearIterator();
    }
    al->ClearIterator();
}

bool is_equal_al_by_general(Argu_list *al1, Argu_list *al2, theta_list *tl)
{
    Argument *tp1 = NULL, *tp2 = NULL;
    al1->ClearIterator();
    al2->ClearIterator();
    tp1 = al1->Iterate();
    tp2 = al2->Iterate();
    while (tp1&&tp2)
    {
        //tp1->Print();tp2->Print();cout<<endl;
        if (tp1->data[0] >= 'a' && tp1->data[0]<= 'z' && tp1->data != tp2->data)
        {
            al1->ClearIterator();
            al2->ClearIterator();
            return 0;
        }
        tp1 = al1->Iterate();
        tp2 = al2->Iterate();
    }
    al1->ClearIterator();
    al2->ClearIterator();
    tp1 = al1->Iterate();
    tp2 = al2->Iterate();
    while (tp1&&tp2)
    {
        //tp1->Print();tp2->Print();cout<<endl;
        if (tp1->data[0] >= 'A' && tp1->data[0]<= 'Z' && tp2->is_variable == 0)
        {
            if (tp1->data[0] >= 'A' && tp1->data[0]<= 'Z')
            {
                tl->Append(add_theta(tp1->data, tp2->data));
            }
            else
            {
                cout << "Error in input.(any atom in input or output can't include the argument with variable)" << endl;
                throw 0;
            }
        }
        /*else if (tp1->is_variable==1 && tp1->is_variable == tp2->is_variable && tp1->data == tp2->data) {
        	ch *temp = NULL;
        	termlist->ClearIterator();
        	temp = termlist->Iterate();
        	while (temp) {
        		tl->Append(add_theta(tp1->data, temp->data));
        		temp = termlist->Iterate();
        	}
        }*/
        tp1 = al1->Iterate();
        tp2 = al2->Iterate();
    }
    al1->ClearIterator();
    al2->ClearIterator();
    if (!tp1 && !tp2)
        return 1;
}

bool    is_equal_atom_by_general(Atom *at1, Atom *at2, theta_list *tl)
{
    if (at1->pre->data == at2->pre->data &&at1->al==at2->al)
        return 1;
    if (at1->pre->data == at2->pre->data /*&& at1->al && at2->al*/ && is_equal_al_by_general(at1->al, at2->al,tl) == 1)
    {
        return 1;
    }
    /*else if (at1->pre->data == at2->pre->data && !(at1->al) && !(at2->al))
    {
        return 1;
    }*/
    return 0;
}

bool is_belong_by_general(Atom *p, Atom_list *ap, theta_list *tl)
{

    Atom *temp = NULL;
    ap->ClearIterator();
    temp = ap->Iterate();
    while (temp)
    {
//        p->Print();temp->Print();cout<<endl;
        if (is_equal_atom_by_general(p, temp,tl) == 1)
        {
            return 1;
        }
        temp = ap->Iterate();
    }
    ap->ClearIterator();
    return 0;
}

bool is_subset_by_general(Atom_list *ap1, Atom_list *ap2)   //ap1 is positive body and ap2 is input
{
    theta_list *tl = new theta_list();
    theta *t = NULL;
    /*set_arity_to_atomlist(ap1);
    set_arity_to_atomlist(ap2);*/

    Atom *at=NULL;
    ap2->ClearIterator();
    at=ap2->Iterate();
    while(at){
//        at->Print();
        at=ap2->Iterate();
    }
//    cout<<endl;
    ap2->ClearIterator();

    ap1->ClearIterator();
    ap2->ClearIterator();
    Atom *temp = ap1->Iterate();
    while (temp)
    {
        /*if (is_belong_by_general(temp, ap2,tl) == 1 && temp && is_include_var_argu(temp) == 1) {

        }*/
        if (is_belong_by_general(temp, ap2,tl) == 1)
        {
            temp = ap1->Iterate();
        }
        else if (is_belong_by_general(temp, ap2,tl) == 0)
        {
            ap1->ClearIterator();
            return 0;
        }
        else
        {
            temp = ap1->Iterate();
        }
    }
    ap1->tl = tl;
    ap1->ClearIterator();
    return 1;
}

bool is_subsume_by_general_rule(Rule *r1,Rule *r2)  //check if ground rule r2 is subsumed by general rule r1
{
    Atom *at1 = NULL, *at2 = NULL, *at3 = NULL;
    Argument *tp1=NULL,*tp2=NULL;
    Argu_list *theta = new Argu_list;
    Argument *temp = NULL;

    set_arity_to_subsume(r1);
    set_arity_to_subsume(r2);

    if (r1->head->pre->data == r2->head->pre->data)
    {
        r1->positive->ClearIterator();
        at1 = r1->positive->Iterate();
        while (at1)
        {
            r2->positive->ClearIterator();
            at2 = r2->positive->Iterate();
            while (at2)
            {
                if (at2->pre->data == at1->pre->data)
                {
                    break;
                }
                at2 = r2->positive->Iterate();
            }
            r2->positive->ClearIterator();
            if (at2 == NULL)
                goto br1;
            at1 = r1->positive->Iterate();
        }
        r1->positive->ClearIterator();

        r1->head->al->ClearIterator();
        r2->head->al->ClearIterator();
        tp1 = r1->head->al->Iterate();
        tp2 = r2->head->al->Iterate();
        while (tp1 && tp2)
        {
            if (tp1->general_data != tp2->general_data)
            {
                goto br1;
            }
            tp1 = r1->head->al->Iterate();
            tp2 = r2->head->al->Iterate();
        }
        r1->head->al->ClearIterator();
        r2->head->al->ClearIterator();

        r1->positive->ClearIterator();
        at1 = r1->positive->Iterate();
        while (at1)
        {
            r2->positive->ClearIterator();
            at2 = r2->positive->Iterate();
            while (at2)
            {
                if (at2->pre->data == at1->pre->data)
                {
                    at2->al->ClearIterator();
                    at1->al->ClearIterator();
                    tp1 = at1->al->Iterate();
                    tp2 = at2->al->Iterate();
                    while (tp1 && tp2)
                    {
                        if (tp1->general_data != tp2->general_data)
                        {
                            break;
                        }
                        tp1 = at1->al->Iterate();
                        tp2 = at2->al->Iterate();
                    }
                    at2->al->ClearIterator();
                    at1->al->ClearIterator();

                    if (tp1 == NULL && tp2 == NULL)
                    {
                        break;
                    }
                }
                at2 = r2->positive->Iterate();
            }
            r2->positive->ClearIterator();
            if (at2 == NULL)
            {
                goto br1;
            }

            at1 = r1->positive->Iterate();
        }
        r1->positive->ClearIterator();
        if (at1 == NULL)
        {
            return 1;
        }
    }

    /*if(r1->head->pre->data==r2->head->pre->data){
        r1->positive->ClearIterator();
        at1=r1->positive->Iterate();
        while(at1){
            r2->positive->ClearIterator();
            at2=r2->positive->Iterate();
            while(at2){
                if(at2->pre->data==at1->pre->data){
                    break;
                }
                at2=r2->positive->Iterate();
            }
            r2->positive->ClearIterator();
            if(at2==NULL)
                goto br1;
            at1=r1->positive->Iterate();
        }
        r1->positive->ClearIterator();

        r1->head->al->ClearIterator();
        r2->head->al->ClearIterator();
        tp1=r1->head->al->Iterate();
        tp2=r2->head->al->Iterate();
        if(tp1 && tp2){
    		add_to_theta(theta, tp1->data, tp2->data);

            tp1=r1->head->al->Iterate();
            tp2=r2->head->al->Iterate();
    		while (tp1 && tp2) {
    			theta->ClearIterator();
    			temp = theta->Iterate();
    			while (temp) {
    				if (temp->data == tp1->data && temp->general_data != tp2->data) {
    					goto br1;
    				}
    				if (temp->data == tp1->data && temp->general_data == tp2->data) {
    					theta->ClearIterator();
    					break;
    				}
    				temp = theta->Iterate();
    			}
    			theta->ClearIterator();
    			if (temp == NULL) {
    				add_to_theta(theta, tp1->data, tp2->data);
    			}
    			tp1 = r1->head->al->Iterate();
    			tp2 = r2->head->al->Iterate();
    		}
        }
        r1->head->al->ClearIterator();
        r2->head->al->ClearIterator();


    }*/

br1:
    return 0;

}

Argument *lgg_term(Argument *a, Argument *b){
  if(a->data==b->data){
    return a;
  }
  else{
    string str = a->data + b->data;
    Argument *temp=new Argument(str);
    temp->consider=1;
    return temp;
  }
}

// void lgg_term(Argument *a, Argument *b)
// {
//     Argument *temp;
//     if (a->data == b->data)
//     {
//         a->argu_of_lgg = a;
//         a->argu_of_lgg->is_general = 0;
//         b->argu_of_lgg = a;
//         b->argu_of_lgg->is_general = 0;
//     }
//     else
//     {
//         string str = a->data + b->data;
//         temp = new Argument(str);
//         temp->consider=1;
//         a->argu_of_lgg = temp;
//         a->argu_of_lgg->ground_data = str;
//         b->argu_of_lgg = temp;
//         b->argu_of_lgg->ground_data = str;
//         //a->consider=1;b->consider=1;
//     }
// }

Argu_list *lgg_arlist(Argu_list *a, Argu_list *b)
{
    Argu_list *temp = new Argu_list;
    a->ClearIterator();
    b->ClearIterator();

    Argument *tp1 = a->Iterate();
    Argument *tp2 = b->Iterate();

    while (tp1 && tp2)
    {
        //if (tp1->argu_of_lgg == NULL && tp2->argu_of_lgg == NULL) {
        // lgg_term(tp1, tp2);
        temp->Append(lgg_term(tp1,tp2));
        //}
        tp1 = a->Iterate();
        tp2 = b->Iterate();
    }

    a->ClearIterator();
    b->ClearIterator();
    return temp;
}

Atom *lgg_atom(Atom *a, Atom *b)
{
    Atom *temp = NULL;
    if(a->pre->data==b->pre->data)
    {
        temp = new Atom(a->pre,lgg_arlist(a->al,b->al));
        return temp;
    }
}

Atom_list *lgg_atlist(Atom_list *a,Atom_list *b)
{
    Atom_list *temp = new Atom_list;
    a->ClearIterator();
    b->ClearIterator();

    Atom *tp1 = a->Iterate();
    Atom *tp2 = b->Iterate();

    while(tp1 && tp2)
    {
        temp->Append(lgg_atom(tp1,tp2));
        tp1 = a->Iterate();
        tp2 = b->Iterate();
    }
    a->ClearIterator();
    b->ClearIterator();
    return temp;
}

void print_consider(Rule *r){
  Atom *a=NULL;
  Argument *ar=NULL;
  r->head->al->ClearIterator();
  ar=r->head->al->Iterate();
  while(ar){
    if(ar->consider==1)
      cout<<ar->data<<" ";
    ar=r->head->al->Iterate();
  }
  r->head->al->ClearIterator();

  r->positive->ClearIterator();
  a=r->positive->Iterate();
  while(a){
    a->al->ClearIterator();
    ar=a->al->Iterate();
    while(ar){
      if(ar->consider==1)
        cout<<ar->data<<" ";
      ar=a->al->Iterate();
    }
    a->al->ClearIterator();
    a=r->positive->Iterate();
  }
  r->positive->ClearIterator();
  cout<<endl;
}

void set_arity(Rule *r)
{
  // r->Print();
  // print_consider(r);
    theta_list *tl=new theta_list();
    theta *t=NULL;
    string s = "A";
    Argument *tp1 = NULL, *tp2 = NULL;
    Atom *at1 = NULL, *at2 = NULL;
    r->head->al->ClearIterator();
    tp1 = r->head->al->Iterate();
    while (tp1)
    {
      // cout<<tp1->data<<endl;
      if(tp1->consider==1){
        tl->ClearIterator();
        t=tl->Iterate();
        while(t){
          // t->Print();
          // cout<<tp1->data<<endl;
          if(t->term==tp1->data){
            tp1->data=t->var;
            tl->ClearIterator();
            break;
          }
          t=tl->Iterate();
        }
        tl->ClearIterator();
        if(!t){
          // cout<<tp1->data<<endl;
          tl->Insert(add_theta(s,tp1->data));
          tp1->data=s;
          // cout<<s<<endl;

          s[0] += 1;
        }
      }
      tp1 = r->head->al->Iterate();

      //cout<<tp1->data<<endl;
        // if (tp1->is_general == 1)
        // {
        //     tp1->data = s;
        //     tp1->sl = termlist;
        //     s[0] += 1;
        // }
        // tp1 = r->head->al->Iterate();
        // while (tp1)
        // {
        //     r->head->al->ClearIterator();
        //     tp2 = r->head->al->Iterate();
        //     while (tp2 != tp1)
        //     {
        //         if (tp2->ground_data == tp1->ground_data)
        //             tp1->data = tp2->data;
        //         tp2 = r->head->al->Iterate();
        //     }
        //     if (tp2 == tp1)
        //     {
        //         if (tp1->is_general == 1)
        //         {
        //             tp1->data = s;
        //             tp1->sl = termlist;
        //             s[0] += 1;
        //         }
        //         tp1 = r->head->al->Iterate();
        //     }
        // }
        // r->head->al->ClearIterator();
    }
    r->head->al->ClearIterator();

    r->positive->ClearIterator();
    at1 = r->positive->Iterate();
    while (at1)
    {
        at1->al->ClearIterator();
        tp1 = at1->al->Iterate();
        while (tp1){
          // cout<<tp1->data<<endl;
          if(tp1->consider==1){
            tl->ClearIterator();
            t=tl->Iterate();
            while(t){
              // t->Print();
              // cout<<tp1->data<<endl;
              if(t->term==tp1->data){
                tp1->data=t->var;
                tl->ClearIterator();
                break;
              }
              t=tl->Iterate();
            }
            tl->ClearIterator();
            if(!t){
              // cout<<tp1->data<<endl;
              tl->Insert(add_theta(s,tp1->data));
              tp1->data=s;
              // cout<<s<<endl;

              s[0] += 1;
            }
          }
          tp1 = at1->al->Iterate();
        }
        at1->al->ClearIterator();
        at1 = r->positive->Iterate();
    }
    r->positive->ClearIterator();

//     r->positive->ClearIterator();
//     at1 = r->positive->Iterate();
//     if (at1)
//     {
//         at1->al->ClearIterator();
//         tp1 = at1->al->Iterate();
//         while (tp1)
//         {
//             r->head->al->ClearIterator();
//             tp2 = r->head->al->Iterate();
//             while (tp2)
//             {
//                 if (tp1->ground_data == tp2->ground_data)
//                 {
//                     tp1->data = tp2->data;
//                     r->head->al->ClearIterator();
//                     goto br;
//                 }
//                 tp2 = r->head->al->Iterate();
//             }
//             r->head->al->ClearIterator();
//
//             at1->al->ClearIterator();
//             tp2 = at1->al->Iterate();
//             while (tp2 != tp1)
//             {
//                 if (tp2->ground_data == tp1->ground_data)
//                     tp1->data = tp2->data;
//                 tp2 = at1->al->Iterate();
//             }
//             if (tp2 == tp1)
//             {
//                 if (tp1->is_general == 1)
//                 {
//                     tp1->data = s;
//                     tp1->sl = termlist;
//                     s[0] += 1;
//                 }
//                 tp1 = at1->al->Iterate();
//             }
//
//             if (1 < 0)
//             {
// br:
//                 tp1 = at1->al->Iterate();
//             }
//         }
//         at1->al->ClearIterator();
//
//         at1 = r->positive->Iterate();
//         while (at1)
//         {
//             at1->al->ClearIterator();
//             tp1 = at1->al->Iterate();
//             while (tp1)
//             {
//                 r->head->al->ClearIterator();
//                 tp2 = r->head->al->Iterate();
//                 while (tp2)
//                 {
//                     if (tp1->ground_data == tp2->ground_data)
//                     {
//                         tp1->data = tp2->data;
//                         r->head->al->ClearIterator();
//                         goto br1;
//                     }
//                     tp2 = r->head->al->Iterate();
//                 }
//                 r->head->al->ClearIterator();
//
//                 r->positive->ClearIterator();
//                 at2 = r->positive->Iterate();
//                 while (at2 != at1)
//                 {
//                     at2->al->ClearIterator();
//                     tp2 = at2->al->Iterate();
//                     while (tp2)
//                     {
//                         if (tp1->ground_data == tp2->ground_data)
//                         {
//                             tp1->data = tp2->data;
//                             at2->al->ClearIterator();
//                             goto br1;
//                         }
//                         tp2 = at2->al->Iterate();
//                     }
//                     at2->al->ClearIterator();
//                     at2 = r->positive->Iterate();
//                 }
//                 if (at2 == at1)
//                 {
//                     at1->al->ClearIterator();
//                     tp2 = at1->al->Iterate();
//                     while (tp2 != tp1)
//                     {
//                         if (tp2->ground_data == tp1->ground_data)
//                             tp1->data = tp2->data;
//                         tp2 = at1->al->Iterate();
//                     }
//                     if (tp2 == tp1)
//                     {
//                         if (tp1->is_general == 1)
//                         {
//                             tp1->data = s;
//                             tp1->sl = termlist;
//                             s[0] += 1;
//                         }
//                         tp1 = at1->al->Iterate();
//                     }
//                 }
//
//                 if (1 < 0)
//                 {
// br1:
//                     tp1 = at1->al->Iterate();
//                 }
//             }
//             at1->al->ClearIterator();
//             r->positive->ClearIterator();
//             at2 = r->positive->Iterate();
//             while (at2 != at1)
//             {
//                 at2 = r->positive->Iterate();
//             }
//             at1 = r->positive->Iterate();
//         }
//         r->positive->ClearIterator();
//     }
//     r->positive->ClearIterator();
}

Rule *lgg_rule(Rule *a, Rule *b)
{


    Rule *temp = NULL;
    temp = new Rule(lgg_atom(a->head,b->head),lgg_atlist(a->positive,b->positive),NULL);
    //temp->Print();
    set_arity(temp);
    //temp->Print();
    a->is_remove = 1;
    b->is_remove = 1;
    return temp;
}

bool is_same_length(Atom_list *a, Atom_list *b)
{
    int i=0,j=0;
    Atom *tp1 = NULL, *tp2 = NULL;
    a->ClearIterator();
    tp1 = a->Iterate();
    while (tp1)
    {
        i++;
        tp1 = a->Iterate();
    }
    a->ClearIterator();

    b->ClearIterator();
    tp2 = b->Iterate();
    while(tp2){
        j++;
        tp2 = b->Iterate();
    }
    b->ClearIterator();

    if (i==j)
    {
        return 1;
    }
    else
        return 0;
}

//void add_to_least_model(Rule *r, Atom_list *al) {
//	if (!(r->positive) && !(r->negative)) {
//		ch *temp = NULL;
//		Argument *ar = NULL;
//		termlist->ClearIterator();
//		temp = termlist->Iterate();
//		while (temp) {
//			r->head->al->ClearIterator();
//			ar = r->head->al->Iterate();
//			while (ar) {
//				if (ar->is_variable == 1) {
//
//				}
//			}
//		}
//	}
//}

void get_least_withot_body(Rule *tmp)
{
    theta_list *tl = new theta_list();
    ch *ct = NULL;
    Argument *ar = NULL;
    tmp->head->al->ClearIterator();
    ar = tmp->head->al->Iterate();
    while (ar)
    {
        if (ar->is_variable == 1)
        {
            termlist->ClearIterator();
            ct = termlist->Iterate();
            while (ct)
            {
                tl->Append(add_theta(ar->data, ct->data));
                ct = termlist->Iterate();
            }
            termlist->ClearIterator();
        }
        ar = tmp->head->al->Iterate();
    }
    tmp->head->al->ClearIterator();
    tmp->head->tl = tl;
}

void remove_waste_theta(Atom *a)
{
    theta *t=NULL;
    Argument *ar=NULL;
    a->tl->ClearIterator();
    t=a->tl->Iterate();
    while(t)
    {
        a->al->ClearIterator();
        ar=a->al->Iterate();
        while(ar)
        {
            if(ar->data==t->var)
            {
                break;
            }
            ar=a->al->Iterate();
        }
        a->al->ClearIterator();
        if(!(ar))
        {
            a->tl->Remove(t);
            a->tl->ClearIterator();
        }
        t=a->tl->Iterate();
    }
    a->tl->ClearIterator();
}

void add_theta_to_Theta_list(Theta_list *tl, theta *t) {
	Theta *temp = NULL;
	tl->ClearIterator();
	temp = tl->Iterate();
	while (temp) {
		if (temp->var == t->var) {
			ch *c = new ch(t->term);
			temp->term->Append(c);
			tl->ClearIterator();
			return;
		}
                temp = tl->Iterate();
	}
        tl->ClearIterator();
	temp = new Theta();
	ch *c = new ch(t->term);
	temp->var = t->var;
	temp->term->Append(c);
	tl->Append(temp);
	tl->ClearIterator();
	return;
}

Theta_list * from_theta_to_Theta(theta_list *tl) {
	Theta_list *temp = new Theta_list();
	theta *tt = NULL;
	tl->ClearIterator();
	tt = tl->Iterate();
	while (tt) {
		add_theta_to_Theta_list(temp, tt);
                tt = tl->Iterate();
	}
        tl->ClearIterator();
	return temp;
}

substitution *cpy_substitution(substitution *s) {
	substitution *temp = new substitution();
	theta *t = NULL;
	s->tl->ClearIterator();
	t = s->tl->Iterate();
	while (t) {
		temp->tl->Append(add_theta(t->var, t->term));
		t = s->tl->Iterate();
	}
	s->tl->ClearIterator();
	return temp;
}

void replace_theta_in_substitution(substitution *s, theta *t) {
	theta *temp = NULL;
	s->tl->ClearIterator();
	temp = s->tl->Iterate();
	while (temp) {
//                temp->Print();cout<<endl;
                if(temp->var==t->var && temp->term==t->term){
                    return;
                }
		if (temp->var == t->var) {
//                        temp->Print();
			s->tl->Remove(temp);
                        s->tl->ClearIterator();
//                        t->Print();
			s->tl->Append(t);
			s->tl->ClearIterator();
			return;
		}
		temp = s->tl->Iterate();
	}
	s->tl->ClearIterator();
	if (!temp) {
//                t->Print();cout<<endl;
                s->tl->Append(t);
                return;
//		cout << "Error in the step of replace single_theta in substitution." << endl;
//                exit(0);
	}
}

bool is_equal_substitution(substitution *s1, substitution *s2) {
	theta *t1 = NULL, *t2 = NULL;
	s1->tl->ClearIterator();
	s2->tl->ClearIterator();
	t1 = s1->tl->Iterate();
	while (t1) {
		t2 = s2->tl->Iterate();
		while (t2) {
			if (t1->var == t2->var && t1->term == t2->term) {
				s2->tl->ClearIterator();
				break;
			}
			t2 = s2->tl->Iterate();
		}
		s2->tl->ClearIterator();
		if (!t2) {
			s1->tl->ClearIterator();
			s2->tl->ClearIterator();
			return 0;
		}
		t1 = s1->tl->Iterate();
	}
	s1->tl->ClearIterator();
	s2->tl->ClearIterator();
	if (!t1) {
		s1->tl->ClearIterator();
		s2->tl->ClearIterator();
		return 1;
	}
}

bool is_exist_in_substitutionlist(substitution *s, substitution_list *sl) {
	substitution *temp = NULL;
	sl->ClearIterator();
	temp = sl->Iterate();
	while (temp) {
		if (is_equal_substitution(s, temp) == 1) {
			return 1;
		}
		temp = sl->Iterate();
	}
	sl->ClearIterator();
	if (temp == NULL) {
		return 0;
	}
}

void process_T_to_s(Theta_list *tl, substitution_list *sl, substitution* s){
        Theta *T1 = NULL;
        ch *c1=NULL;
        if(tl->is_last()==1){
//            T1=tl->Iterate();
//            if(T1){
//                T1->term->ClearIterator();
//                c1=T1->term->Iterate();
//                while(c1){
//                    replace_theta_in_substitution(s,add_theta(T1->var,c1->data));
                    sl->Append(cpy_substitution(s));
//                    c1=T1->term->Iterate();
//                }
//                T1->term->ClearIterator();
//            }
        }
        else {
            T1=tl->Iterate();
            if(T1){
                T1->term->ClearIterator();
                c1=T1->term->Iterate();
                while(c1){
                    replace_theta_in_substitution(s,add_theta(T1->var,c1->data));
                    process_T_to_s(tl,sl,s);
                    c1=T1->term->Iterate();
                }
                T1->term->ClearIterator();
            }
        }
}

void from_Theta_to_substitution(Theta_list *tl, substitution_list *sl) {
	Theta *T1 = NULL;
        ch *c1=NULL;
        substitution *s = new substitution();
        tl->ClearIterator();
        T1=tl->Iterate();
        if(T1){
            T1->term->ClearIterator();
            c1=T1->term->Iterate();
            while(c1){
//                cout<<c1->data<<endl;
                replace_theta_in_substitution(s,add_theta(T1->var,c1->data));
                process_T_to_s(tl,sl,s);
                c1=T1->term->Iterate();
            }
            T1->term->ClearIterator();
        }
        tl->ClearIterator();
}

void from_Thetalist_to_substitutionlist(Theta_list *tl, substitution_list *sl) {
	Theta *temp = NULL;
	Theta *pre = NULL, *current = NULL;
	ch *c = NULL;
	substitution *s = new substitution();
	tl->ClearIterator();
	temp = tl->Iterate();
	while (temp) {
		temp->term->ClearIterator();
		c = temp->term->Iterate();
		if (c)
			s->tl->Append(add_theta(temp->var, c->data));
		temp = tl->Iterate();
	}
	tl->ClearIterator();
	sl->Append(cpy_substitution(s));
	tl->ClearIterator();
	pre = current = tl->Iterate();
	while (current) {
		pre = current;
		current = tl->Iterate();
	}
	tl->ClearIterator();
	temp = pre;

	if (temp) {
		c = temp->term->Iterate();
                while (c) {
			replace_theta_in_substitution(s, add_theta(temp->var, c->data));
			sl->Append(cpy_substitution(s));
			c = temp->term->Iterate();
		}
		temp->term->ClearIterator();
	}
br1:
	tl->ClearIterator();
	current = tl->Iterate();
	while (current != temp) {
		pre = current;
		current = tl->Iterate();
	}
	tl->ClearIterator();
	temp = pre;

	if (temp) {
		c = temp->term->Iterate();
		while (c) {
			replace_theta_in_substitution(s, add_theta(temp->var, c->data));
			temp = tl->Iterate();
			if (temp) {
				c = temp->term->Iterate();
			}
			else {
				if (is_exist_in_substitutionlist(s, sl) == 1)
					return;
				else
					sl->Append(cpy_substitution(s));
				break;
			}
		}
		temp->term->ClearIterator();
		goto br1;
	}
}

bool is_substitution_equal(Atom *c, Atom *v, substitution *s) {
	Argument *a1 = NULL, *a2 = NULL;
	theta *t = NULL;

	if (c->pre->data == v->pre->data) {
		c->al->ClearIterator();
		v->al->ClearIterator();
		a1 = c->al->Iterate();
		a2 = v->al->Iterate();
		while (a1 && a2) {
//                        a1->Print();a2->Print();cout<<endl;
			if ((a1->data[0] <= 'z' && a1->data[0] >= 'a') && (a2->data[0] <= 'z' && a2->data[0] >= 'a')) {
				if (a1->data != a2->data) {
					c->al->ClearIterator();
					v->al->ClearIterator();
					return 0;
				}
			}
			else if ((a1->data[0] <= 'z' && a1->data[0] >= 'a') && (a2->data[0] <= 'Z' && a2->data[0] >= 'A')) {
				s->tl->ClearIterator();
				t = s->tl->Iterate();
				while (t) {
					if (t->var == a2->data && t->term == a1->data) {
						s->tl->ClearIterator();
						break;
					}
					else if (t->var == a2->data && t->term != a1->data) {
						c->al->ClearIterator();
						v->al->ClearIterator();
						s->tl->ClearIterator();
						return 0;
					}
					t = s->tl->Iterate();
				}
				s->tl->ClearIterator();
			}
			a1 = c->al->Iterate();
			a2 = v->al->Iterate();
		}
		c->al->ClearIterator();
		v->al->ClearIterator();
		if (!a1 && !a2) {
			return 1;
		}
	}
	else
		return 0;
}

void remove_waste_substitution(substitution_list *sl, Atom_list *al, Atom_list *b) {
	Atom *a1 = NULL, *a2 = NULL;
	substitution *s = NULL;

	sl->ClearIterator();
	s = sl->Iterate();
	while (s) {
		al->ClearIterator();
		a1 = al->Iterate();
		while (a1) {
			b->ClearIterator();
			a2 = b->Iterate();
			while (a2) {
				if (is_substitution_equal(a1, a2, s) == 1) {
					b->ClearIterator();
					break;
				}
				a2 = b->Iterate();
			}
			b->ClearIterator();
			if (!a2) {
				al->ClearIterator();
				sl->Remove(s);
				goto br1;
			}
			a1 = al->Iterate();
		}
		al->ClearIterator();
	br1:
		s = sl->Iterate();
	}
}

substitution_list * transform_thetalist(theta_list *tl) {
	substitution_list *temp = new substitution_list();
	Theta_list *Tl = from_theta_to_Theta(tl);

        from_Theta_to_substitution(Tl, temp);

//        substitution *s=NULL;
//        temp->ClearIterator();
//        s=temp->Iterate();
//        while(s){
//            s->Print();
//            s=temp->Iterate();
//        }
//        cout<<endl;
//        temp->ClearIterator();

	return temp;
}



Atom_list *get_least_model(Rule_list *rl, Atom_list *e)
{
    Atom_list *temp = new Atom_list();
    Rule *tmp = NULL;
    rl->ClearIterator();
    while ((tmp = rl->Iterate()))
    {
        if (!(tmp->positive) && !(tmp->negative))
        {
            if (is_include_var_argu(tmp->head) == 1)
            {
                get_least_withot_body(tmp);
            }
            temp->Append(tmp->head);
        }
        if (tmp->positive && temp && is_subset_by_general(tmp->positive, e)==1)
        {
//                        theta *t=NULL;
//                        tmp->positive->tl->ClearIterator();
//                        t=tmp->positive->tl->Iterate();
//                        while(t){
//                            t->Print();
//                            t=tmp->positive->tl->Iterate();
//                        }
//                        cout<<endl;
//                        tmp->positive->tl->ClearIterator();
			tmp->head->sl = transform_thetalist(tmp->positive->tl);
//                        tmp->head->Print();cout<<endl;
//                        substitution *s=NULL;
//                        tmp->head->sl->ClearIterator();
//                        s=tmp->head->sl->Iterate();
//                        while(s){
//                            s->Print();
//                            s=tmp->head->sl->Iterate();
//                        }
//                        tmp->head->sl->ClearIterator();
            //remove_waste_substitution(tmp->head->sl, e, tmp->positive);
            temp->Append(tmp->head);
        }
    }
    rl->ClearIterator();
    return temp;
}

bool check_if_subset_with_theta(Atom_list *a1, Atom_list *a2)  //a1 is the least model while a2 is the output.
{
    Atom *at1 = NULL, *at2 = NULL;
    Argument *ar1 = NULL, *ar2 = NULL;
    theta *t = NULL;
	substitution *s = NULL;
    a1->ClearIterator();
    at1 = a1->Iterate();
    while (at1)
    {
        a2->ClearIterator();
        at2 = a2->Iterate();
        while (at2)
        {
//            at1->Print();at2->Print();cout<<endl;
            if (at1->pre->data == at2->pre->data)
            {
//				at1->Print(); cout << endl; at2->Print(); cout << endl;
				at1->sl->ClearIterator();
				s = at1->sl->Iterate();
				if (s) {
//                                        s->Print(); cout << endl;
                                        while (s) {
                                                if (is_substitution_equal(at2, at1, s) == 1) {
                                                        a2->ClearIterator();
                                                        at1->sl->ClearIterator();
                                                        goto br3;
                                                }
                                                s = at1->sl->Iterate();
                                        }
                                        at1->sl->ClearIterator();
                                        if (!s) {
                                                goto br1;
                                        }
				}
                                else {
                                    if(at1==at2){
                                        a2->ClearIterator();
                                        at1->sl->ClearIterator();
                                        goto br3;
                                    }
                                    else {
                                    at1->sl->ClearIterator();
                                    at1->al->ClearIterator();
                                    at2->al->ClearIterator();
                                    ar1=at1->al->Iterate();
                                    ar2=at2->al->Iterate();
                                    while(ar1 && ar2){
//                                        ar1->Print();ar2->Print();cout<<endl;
                                        if(ar1->data!=ar2->data){
                                            at1->al->ClearIterator();
                                            at2->al->ClearIterator();
                                            goto br1;
                                        }
                                        ar1=at1->al->Iterate();
                                        ar2=at2->al->Iterate();
                                    }
                                    at1->al->ClearIterator();
                                    at2->al->ClearIterator();
                                    if(ar1!=NULL || ar2!=NULL){
                                        a1->ClearIterator();
                                        a2->ClearIterator();
                                        return 0;
                                    }
                                    if(!ar1 &&!ar2){
                                        a2->ClearIterator();
                                        at1->sl->ClearIterator();
                                        goto br3;
                                    }
                                    }
                                }
            }
		br1:
            at2 = a2->Iterate();
            if(1<0){
            br2:
            break;
            }
        }
        a2->ClearIterator();
        if (!(at2))
        {
			a1->ClearIterator();
            return 0;
        }
	br3:
		at1 = a1->Iterate();
    }

    a1->ClearIterator();
    return 1;
}

void extend_tp(Atom_list *least,Atom_list *al)
{
    Atom *temp=NULL;
    least->ClearIterator();
    temp=least->Iterate();
    while(temp)
    {
        al->Append(temp);
        temp=least->Iterate();
    }
    least->ClearIterator();
}

bool is_fix(Atom_list *pre, Atom_list *now)
{
    Atom *at1=NULL,*at2=NULL;
    pre->ClearIterator();
    at1=pre->Iterate();
    while(at1){
        if(is_belong(at1,now)==0){
            pre->ClearIterator();
            return 0;
        }
        at1=pre->Iterate();
    }
    now->ClearIterator();
    return 1;
}





void print_substitution_in_atomlist(Atom_list *al){
    Atom *temp=NULL;
    substitution *s=NULL;
    theta *t=NULL;
    al->ClearIterator();
    temp=al->Iterate();
    while(temp){
        temp->sl->ClearIterator();
        s=temp->sl->Iterate();
        while(s){
            s->tl->ClearIterator();
            t=s->tl->Iterate();
            while(t){
                cout<<t->var<<"/"<<t->term;
                t=s->tl->Iterate();
                if(t){
                    cout<<",";
                }
            }
            cout<<endl;
            s->tl->ClearIterator();
            s=temp->sl->Iterate();
        }
        temp->sl->ClearIterator();
        temp=al->Iterate();
    }
    al->ClearIterator();
}

bool check_over_general_of_single_example(Rule_list *rl, Example *e)
{
    Atom_list *temp=NULL;
    Atom_list *now=NULL;
    now = copy_atom_list(e->input);
    temp=get_least_model(rl,now);
    extend_tp(temp,now);
    while(is_fix(temp,now)==0){
        temp=get_least_model(rl,now);
        //temp->Print();
        //now->Print();
        if(is_subset(temp,now)==1)
            break;
        extend_tp(temp,now);
    }
//    print_substitution_in_atomlist(temp);
//	temp->Print(); e->output->Print();
    if(check_if_subset_with_theta(temp,e->output)==1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void check_over_general(Program p)
{
    Example *temp=NULL;
    theta *t = NULL;
    bool check=1;
    p.E->ClearIterator();
    temp=p.E->Iterate();
    while(temp)
    {
        if(check_over_general_of_single_example(p.B_P,temp)==1)
        {
            cout<<"The output of LFIO have been over-generalized for the example: ";
            temp->Print();
            check=0;
        }
        temp=p.E->Iterate();
    }
    p.E->ClearIterator();
    if(check==1)
    {
        cout << "There has no over-generalization in the output of LFIO." << endl;
    }
}

void filling_in_full_of_example(Example *e){
  Atom *a=NULL;
  e->input->ClearIterator();
  a=e->input->Iterate();
  while(a){
    if(is_belong(a,e->output)==0){
      e->output->Append(copy_atom(a));
    }
    a=e->input->Iterate();
  }
  e->input->ClearIterator();
}

void filling_in_full_of_examples(Ex_list *E){
  Example *e=NULL;
  E->ClearIterator();
  e=E->Iterate();
  while(e){
    filling_in_full_of_example(e);
    e=E->Iterate();
  }
  E->ClearIterator();
}

void algorithm(Rule_list *B, Ex_list *E, Rule_list *P, Rule_list *B_P)
{
    filling_in_full_of_examples(E);
    cheak_is_satisfied_by_condition(E);
    Atom *ta = NULL, *tp = NULL;
    Example *temp=NULL;
    //temp = E->Iterate();
    E->ClearIterator();
    while ((temp = E->Ex_list::Iterate()))
    {
        //temp->Print();
        //algorithm1(B, temp, P, B_P);
        //optimization(temp);

        temp->input->ClearIterator();
        temp->output->ClearIterator();
        // temp->Print();
        while ((tp = temp->input->Atom_list::Iterate())&& temp)
        {
            if (is_belong(tp, temp->output) == 1 /*&&ta*/)
            {
                temp->output->ClearIterator();
                while ((ta = temp->output->Atom_list::Iterate()) && temp)
                {
                    if (ta->pre->data == tp->pre->data && is_equal_al(ta->al, tp->al) == 1 && temp)
                    {
                        temp->output->Atom_list::Remove(ta);
                        break;
                    }
                    else
                    {
                        //ta = temp->output->Atom_list::Iterate();
                    }
                }
                temp->output->Atom_list::ClearIterator();
                //tp = temp->input->Atom_list::Iterate();
            }

            else
            {
                //tp = temp->input->Atom_list::Iterate();
            }
        }
        temp->input->Atom_list::ClearIterator();
        temp->output->Atom_list::ClearIterator();

        for_each_loop(temp, P, B_P);
        temp->output->Atom_list::ClearIterator();
        //temp = E->Iterate();
    }
    E->Ex_list::ClearIterator();

    Rule *tp1 = NULL, *tp2 = NULL;
    B->ClearIterator();
    tp1 = B->Iterate();
    while (tp1)
    {
        P->ClearIterator();
        tp2 = P->Iterate();
        while (tp2)
        {
            if (is_subsume_by_general_rule(tp1, tp2) == 1)
            {
                P->Remove(tp2);
                P->ClearIterator();
            }
            tp2 = P->Iterate();
        }
        P->ClearIterator();
        tp1 = B->Iterate();
    }
    B->ClearIterator();
    //is_enable(P);

}

bool check_lgg(Rule *a, Rule *b)
{
    if (a->head->pre->data == b->head->pre->data)
    {
        if (is_same_length(a->positive,b->positive)==1 && is_subset_without_argu(a->positive, b->positive) == 1 && is_subset_without_argu(b->positive, a->positive) == 1)
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

void lgg_program(Program p, Program pp)
{
    Rule *r1 = NULL, *r2 = NULL;
    Rule *temp = NULL;

    p.P->ClearIterator();
    r1 = p.P->Iterate();
    while (r1 != NULL)
    {
      // if(r1->consider==0){
        p.P->ClearIterator();
        r2 = p.P->Iterate();
        while (r2 != NULL)
        {
          // if(r2->consider==0){
            if (r1 != r2)
            {
                if (check_lgg(r1, r2) == 1)
                {
                    // r1->Print();
                    // r2->Print();
                    temp = lgg_rule(r1, r2);
                    // r1->consider=1;r2->consider=1;
                    p.P->Remove(r1);
                    p.P->Remove(r2);
                    // temp->Print();
                    //remove_waste_rule(temp, pp.P);
                    if (bool_subsume(temp, pp.P) == 0)
                        p.P->Insert(temp);
                    p.P->ClearIterator();
                    goto br1;
                }
            }
          // }
          r2 = p.P->Iterate();
        }

        if (r2 == NULL && r1->is_remove == 0)
        {
          r1->consider=1;
            p.P->Insert(r1);
        }
        // p.P->ClearIterator();
        // r2 = p.P->Iterate();
        // while (r2 != r1)
        // {
        //     r2 = p.P->Iterate();
        // }
    // }
    br1:
    r1 = p.P->Iterate();

  }
  p.P->ClearIterator();
}

void reset_consider(Atom_list *al) {
	Atom *temp = NULL;
	al->ClearIterator();
	temp = al->Iterate();
	while (temp) {
		temp->consider = 0;
		temp = al->Iterate();
	}
	al->ClearIterator();
}

bool check_if_variable_exist_in_substitution(substitution *s, theta *t) {
	theta *temp = NULL;
	s->tl->ClearIterator();
	temp = s->tl->Iterate();
	while (temp) {
		if (temp->var == t->var && temp->term != t->term) {
			s->tl->ClearIterator();
			return 1;
		}
		temp = s->tl->Iterate();
	}
	s->tl->ClearIterator();
	return 0;
}

bool check_if_exist_conflict_between_theta(Atom *a1, Atom *a2, substitution *s) {
	theta *temp = NULL;
	Argument *ar1 = NULL, *ar2 = NULL;
	a1->al->ClearIterator();
	a2->al->ClearIterator();
	ar1 = a1->al->Iterate();
	ar2 = a2->al->Iterate();
	while (ar1 && ar2) {
		temp = add_theta(ar1->data, ar2->data);
		if (check_if_variable_exist_in_substitution(s, temp) == 1) {
			a1->al->ClearIterator();
			a2->al->ClearIterator();
			return 1;
		}
		if (check_if_variable_exist_in_substitution(s, temp) == 0) {
			s->tl->Append(temp);
		}
		ar1 = a1->al->Iterate();
		ar2 = a2->al->Iterate();
	}
	a1->al->ClearIterator();
	a2->al->ClearIterator();
	return 0;
}

bool check_if_inverse_resolution(Atom_list *al1, Atom_list *al2) { //al1 is the body of C1 and al2 is the body of R
	reset_consider(al1);
	reset_consider(al2);
	Atom *a1 = NULL, *a2 = NULL;
	substitution *s = new substitution();
	al1->ClearIterator();
	a1 = al1->Iterate();
	while (a1) {
		al2->ClearIterator();
		a2 = al2->Iterate();
		while (a2) {
			if (a1->pre->data == a2->pre->data && a1->consider == 0 && a2->consider == 0) {
				if (check_if_exist_conflict_between_theta(a1, a2, s) == 1) {
					al1->ClearIterator();
					al2->ClearIterator();
					return 0;
				}
				a1->consider = 1;
				a2->consider = 1;
				break;
			}
			a2 = al2->Iterate();
		}
		if (!a2) {
			al1->ClearIterator();
			al2->ClearIterator();
			return 0;
		}
		al2->ClearIterator();
		a1 = al1->Iterate();
	}
	al1->ClearIterator();
	if (!a1) {
		al1->ClearIterator();
		al2->ClearIterator();
		al1->tl = s->tl;
		return 1;
	}
}

Argument *add_argument(string s) {
	Argument *temp = new Argument(s);
	return temp;
}

Atom *construct_head_of_C2(Atom *a, theta_list *tl) {
	Argu_list *al = new Argu_list();
	theta *t = NULL;
	Argument *ar = NULL;
	a->al->ClearIterator();
	ar = a->al->Iterate();
	while (ar) {
		tl->ClearIterator();
		t = tl->Iterate();
		while (t) {
			if (t->var == ar->data) {
				al->Append(add_argument(t->term));
				tl->ClearIterator();
				break;
			}
			t = tl->Iterate();
		}
		tl->ClearIterator();
		ar = a->al->Iterate();
	}
	a->al->ClearIterator();
	Atom *temp = new Atom(a->pre, al);
	return temp;
}

bool is_argument_equal_by_thetalist(Argument *ar1, Argument *ar2, theta_list *tl) {
	theta *t = NULL;
	tl->ClearIterator();
	t = tl->Iterate();
	while (t) {
		if (t->var == ar1->data && t->term == ar2->data) {
			tl->ClearIterator();
			return 1;
		}
		t = tl->Iterate();
	}
	tl->ClearIterator();
	return 0;
}

bool is_atom_equal_by_thetalist(Atom *a1, Atom *a2, theta_list *tl) {
	if (a1->pre->data != a2->pre->data)
		return 0;
	Argument *ar1 = NULL, *ar2 = NULL;
	a1->al->ClearIterator();
	a2->al->ClearIterator();
	ar1 = a1->al->Iterate();
	ar2 = a2->al->Iterate();
	while (ar1 && ar2) {
		if (is_argument_equal_by_thetalist(ar1, ar2, tl) == 0) {
			a1->al->ClearIterator();
			a2->al->ClearIterator();
			return 0;
		}
		ar1 = a1->al->Iterate();
		ar2 = a2->al->Iterate();
	}
	a1->al->ClearIterator();
	a2->al->ClearIterator();
	return 1;
}

Rule *v_operator(Rule *c1, Rule *r) { //c1 is background clause and r is ground clause
	Atom *a1 = NULL, *a2 = NULL;
	Atom_list *al = NULL;
	al = copy_atom_list(r->positive);
	al->Append(construct_head_of_C2(c1->head, c1->positive->tl));
	c1->positive->ClearIterator();
	a1 = c1->positive->Iterate();
	while (a1) {
		r->positive->ClearIterator();
		a2 = r->positive->Iterate();
		while (a2) {
			if (is_atom_equal_by_thetalist(a1, a2, c1->positive->tl) == 1) {
				al->Remove(a2);
				break;
			}
			a2 = r->positive->Iterate();
		}
		r->positive->ClearIterator();
		a1 = c1->positive->Iterate();
	}
	c1->positive->ClearIterator();
	Rule *temp = new Rule(r->head, al, NULL);
	return temp;
}

void compute_voperator(Program p) {
	Rule *r1 = NULL, *r2 = NULL;
	Rule *temp = NULL;

	p.B->ClearIterator();
	r1 = p.B->Iterate();
	while (r1) {
		p.P->ClearIterator();
		r2 = p.P->Iterate();
		while (r2) {
      //r2->Print();
			if (check_if_inverse_resolution(r1->positive, r2->positive) == 1) {
        p.P->Remove(r2);
        temp = v_operator(r1, r2);
        //temp->Print();

        p.P->Insert(temp);
        //continue;
			}
			r2 = p.P->Iterate();
		}
		p.P->ClearIterator();
		r1 = p.B->Iterate();
	}
	p.B->ClearIterator();
}

Rule *inverse_resolution(Rule *c1, Rule *r) { //this function is different from v_operator by adding inverse substitution

}

Rule_list *copy_rule_list(Rule_list *rl) {
	Rule_list *copy = new Rule_list();
	Rule *temp = NULL;
	rl->ClearIterator();
	temp = rl->Iterate();
	while (temp) {
		copy->Append(temp);
		temp = rl->Iterate();
	}
	rl->ClearIterator();
	return copy;
}

Rule *copy_rule(Rule *r) {
	Atom_list *al = copy_atom_list(r->positive);
	Rule *copy = new Rule(r->head, al, NULL);
	return copy;
}

Rule *construct_rule_delete_atom(Rule *r, Atom *a) {
	Atom_list *al = new Atom_list();
	Atom *temp = NULL;
	r->positive->ClearIterator();
	temp = r->positive->Iterate();
	while (temp) {
		if (temp != a) {
			al->Append(temp);
		}
		temp = r->positive->Iterate();
	}
	r->positive->ClearIterator();
	Rule *rule = new Rule(r->head, al, NULL);
	return rule;
}

bool check_uniform_constains(Rule *r, Rule_list *rl){

}

void redundant_of_atom(Rule_list *rl) {
	Rule *temp = NULL;
	Atom *a = NULL, *a1=NULL;
	Rule *r = NULL;
	Rule *copy = NULL;
	rl->ClearIterator();
	temp = rl->Iterate();
	while (temp) {
		copy = copy_rule(temp);
		temp->positive->ClearIterator();
		a = temp->positive->Iterate();
		while (a) {
			if (a->consider == 0) {
				a->consider = 1;
        a1=copy_atom(a);
				r = construct_rule_delete_atom(copy, a);
				if (check_uniform_constains(r, rl) == 1) {
					temp->positive->Remove(a);
					continue;
				}
			}
			a = temp->positive->Iterate();
		}
		temp->positive->ClearIterator();
		temp = rl->Iterate();
	}
	rl->ClearIterator();
}

Rule_list *construct_rulelist_delete_rule(Rule_list *rl, Rule *r) {
	Rule_list *temprl = new Rule_list();
	Rule* temp = NULL;
	rl->ClearIterator();
	temp = rl->Iterate();
	while (temp) {
		if (temp != r) {
			temprl->Append(temp);
		}
		temp = rl->Iterate();
	}
	rl->ClearIterator();
	return temprl;
}

void redundant_of_rule(Rule_list *rl){
	Rule *temp = NULL;
	Rule_list *copy = copy_rule_list(rl);
	Rule_list *temprl = NULL;
	rl->ClearIterator();
	temp = rl->Iterate();
	while (temp) {
		if (temp->consider == 0) {
			temp->consider = 1;
			temprl = construct_rulelist_delete_rule(copy, temp);
			if (check_uniform_constains(temp, temprl) == 1) {
				rl->Remove(temp);
				continue;
			}
		}
		temp = rl->Iterate();
	}
	rl->ClearIterator();
}

#endif


#pragma once
