#include "function.h"
#include "algorithm.h"
#include "parse.hh"
#include "lex.hh"
#include <fstream>
#include <ctime>
#include <signal.h>
#include <zlib.h>
#include <errno.h>
#include <fpu_control.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include <linux/unistd.h>

char version[] = "LFIO_v0.1  build: " __DATE__;
char *clone_string(const char *st)
{
    char *new_st = (char *) malloc(strlen(st)+1);

    if (!new_st)  perror("malloc error");
    strcpy(new_st, st);

    return new_st;
}
extern Program lfio;
extern int yyparse(void *);
extern Str_list *termlist;
extern Str_list *predicatelist;

static inline int memReadPeak(void)
{
	char  name[256];
	pid_t pid = getpid();

	sprintf(name, "/proc/%d/status", pid);
	FILE* in = fopen(name, "rb");
	if (in == NULL) return 0;

	// Find the correct line, beginning with "VmPeak:":
	int peak_kb = 0;
	while (!feof(in) && fscanf(in, "VmPeak: %d kB", &peak_kb) != 1)
		while (!feof(in) && fgetc(in) != '\n')
			;
	fclose(in);

	return peak_kb;
}

double memUsedPeak() {
	double peak = memReadPeak() / 1024;
	return peak;
}

void usage(char *argv[]) //help function
{
    cerr << "Usage: " << argv[0] << " [options] file" << endl
         << "options:" << endl
         << "-v             Print the version number of make and exit." << endl
         << "-h, --help     Print this message and exit." << endl
         << "-g             Print the output of LFIO with generalizing by least general generalization." << endl
         << "-f             Print the result of checking over-generalization " << endl
	       << "-p             Print the result of LFIO with generalizing by V-operator" << endl;
        //  << "-r             Print the result of LFIO with the redundant" << endl;
}


int main(int argc, char **argv) {
	struct sysinfo s_info;
	double mem_used = memUsedPeak();
    clock_t start, finish;
    start = clock();
    int i; bool gene = 0; bool over = 0; bool voperator = 0; bool redundant = 0;
    for (i = 1; i <= argc - 1; i++)
    {
        if (strcmp(argv[i], "-v") == 0) { cout << "The version of LFIO: " << version << endl; exit(0); }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) { usage(argv); exit(0); }
        if (strcmp(argv[i], "-g") == 0) {
			/*if (voperator == 1) {
				cout << "Notice: You can only choose one way to generalize the result"
					 << "(least general generalization or V-operator)." << endl;
				exit(0);
			}*/
            gene = 1;continue;
        }
        if (strcmp(argv[i], "-f") == 0) {
			gene = 1; over = 1; continue;
        }
        if (strcmp(argv[i], "-p") == 0) {
			voperator = 1; continue;
		}
        if (strcmp(argv[i], "-r") == 0) { redundant = 1; continue; }
    }

    if (argc > 1) {
        FILE *f = fopen(argv[argc-1], "r");
        if (!(yyin = fopen(argv[argc-1], "r")))
        {
            perror(argv[argc-1]);
            return (1);
        }
    }
    yyparse();
    Rule *tr = NULL;
    lfio.B->ClearIterator();
    tr = lfio.B->Iterate();
    if (tr)
        cout << "Background rule :" << endl;
    while (tr) {
        tr->Print();
        tr = lfio.B->Iterate();
    }
    lfio.B->ClearIterator();

    Example *te=NULL;
    te = lfio.E->Iterate();
    if (te)
        cout << "Example :" << endl;
    lfio.E->ClearIterator();
    te=lfio.E->Iterate();
    while(te){
      te->Print();
      te=lfio.E->Iterate();
    }
    lfio.E->ClearIterator();

    lfio.B->ClearIterator();
    tr = lfio.B->Iterate();
    while (tr) {
        lfio.B_P->Append(tr);
        tr = lfio.B->Iterate();
    }
    lfio.B->ClearIterator();

    algorithm(lfio.B, lfio.E, lfio.P, lfio.B_P);
    Program pp;



	if (voperator == 1) {
		compute_voperator(lfio);
	}
  if (redundant == 1) {
		redundant_of_atom(lfio.P);
		redundant_of_rule(lfio.P);
	}
    // if (gene == 0){
        lfio.P->ClearIterator();
        tr = lfio.P->Iterate();
        if (tr)
            cout << "Output of LFIO :" << endl;
        while (tr /*&& tr->enable!=0*/) {
            tr->Print();
            tr = lfio.P->Iterate();
        }
        lfio.P->ClearIterator();
    // }

    if (gene == 1){

        lgg_program(lfio,pp);
        lfio.P->ClearIterator();
        tr = lfio.P->Iterate();
        if (tr)
            cout << "Output of LFIO by generalization :" << endl;
        while (tr) {
            tr->Print();
            tr = lfio.P->Iterate();
        }
        lfio.P->ClearIterator();
        cout<<endl;
    }

    if(over == 1){
        pp.E=lfio.E;
        lfio.B->ClearIterator();
        tr=lfio.B->Iterate();
        while(tr){
            pp.B_P->Append(tr);
            tr=lfio.B->Iterate();
        }
        lfio.B->ClearIterator();
        pp.P->ClearIterator();
        tr=pp.P->Iterate();
        while(tr){
            pp.B_P->Append(tr);
            tr=pp.P->Iterate();
        }
        pp.P->ClearIterator();
        check_over_general(pp);
    }

	if (voperator == 1) {

	}


    finish = clock();
    cout << endl
		 << "Running time is  : " << static_cast<double>(finish - start)/1000  << "ms" << endl
	     << "Memory used      : " << (double)mem_used << "MB\n";

	/*ch *temp = NULL;
	termlist->ClearIterator();
	temp = termlist->Iterate();
	while (temp) {
		cout << temp->data << " ";
		temp = termlist->Iterate();
	}
	termlist->ClearIterator();
	cout << endl;

	predicatelist->ClearIterator();
	temp = predicatelist->Iterate();
	while (temp) {
		cout << temp->data << " ";
		temp = predicatelist->Iterate();
	}
	predicatelist->ClearIterator();
	cout << endl;*/
	return 0;
}
