/*** FORWARD CHAINING ***/
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Forward.h"

using namespace std;

int flag;
vector<string> cndvar(13);
vector<string> varlt(13);
vector<string> clvarlt(72);

string c, vp, v;
int stage;
string health, leukemia, radiation, chemo, stem;
vector<int> instlt(13);
int f, i, j, k, s, fp   /* front pointer */;
int  bp  /* back pointer */,  gr,  sn; /* statement number */
int cn;  /* clause number */
bool complete = false;
ofstream output_file;


void search(void);
void check_instantiation(void);
void instantiate(void);

Forward::Forward() {

}

void Forward::run_forward()
{
    output_file.open("forward_log.txt");

    /******** INITIALIZATION SECTION ***********/
    fp=1;
    bp=1;

    for (i=1;i < 41; i++)
        clvarlt.push_back("");
   for (i=1;i < 11; i++)
        cndvar.push_back("");
    for (i=1;i < 11; i++)
        instlt[i] = 0;
    for (i=1;i < 11; i++)
        varlt.push_back("");


    for (i=1;i < 11; i++)
    {
        cndvar[i] = "";
        varlt[i] = "";
        instlt[i] = 0;
    }

    /* enter variables which are in the IF part, 1 at a time in
    the exact order that they occur. Up to 3 variables per
    IF statement. Do not duplicate any variable names. Any
    name is used only once. If no more variables left, just
    hit return key */
    /****** comment 367 *************/
    varlt[1] = "STA"; //STAGE
    varlt[2] = "HEA"; //Health
    varlt[3] = "LEU"; // Leukemia
    varlt[4] = "RAD"; // Radiation
    varlt[5] = "CHEM"; // Chemo
    varlt[6] = "STEM"; // Stem cells

    output_file << "*** VARIABLE LIST ***\n";
    for (i=1;i < 11; i++)
    {
        output_file << "VARIABLE " << i << " " << varlt[i] << endl;
    }
    output_file << "\nClause Variable List\n";

    /* enter variables as they appear in the IF clauses, Up to 3
    variables per IF statement.
    /****** comment 407, 408 *************/
    // statement 1
    clvarlt[1] = "STA";
    // statement 2
    clvarlt[7] = "STA";
    // statement 3
    clvarlt[13] = "STA";
    clvarlt[14] = "HEA";
    // statement 4
    clvarlt[19] = "STA";
    clvarlt[20] = "HEA";
    // statement 5
    clvarlt[25] = "STA";
    clvarlt[26] = "HEA";
    clvarlt[27] = "LEU";

    // statement 6
    clvarlt[31] = "STA";
    clvarlt[32] = "HEA";
    clvarlt[33] = "LEU";

    // statement 7
    clvarlt[37] = "STA";
    clvarlt[38] = "HEA";
    clvarlt[39] = "LEU";
    clvarlt[40] = "RAD";

    // statement 8
    clvarlt[43] = "STA";
    clvarlt[44] = "HEA";
    clvarlt[45] = "LEU";
    clvarlt[46] = "RAD";

    // statement 9
    clvarlt[49] = "STA";
    clvarlt[50] = "HEA";
    clvarlt[51] = "LEU";
    clvarlt[52] = "RAD";
    clvarlt[53] = "CHEM";

    // statement 10
    clvarlt[55] = "STA";
    clvarlt[56] = "HEA";
    clvarlt[57] = "LEU";
    clvarlt[58] = "RAD";
    clvarlt[59] = "CHEM";

    // statement 11
    clvarlt[61] = "STA";
    clvarlt[62] = "HEA";
    clvarlt[63] = "LEU";
    clvarlt[64] = "RAD";
    clvarlt[65] = "CHEM";
    clvarlt[66] = "STEM";

    // statement 12
    clvarlt[67] = "STA";
    clvarlt[68] = "HEA";
    clvarlt[69] = "LEU";
    clvarlt[70] = "RAD";
    clvarlt[71] = "CHEM";
    clvarlt[72] = "STEM";

    output_file << "\n";
    for (i = 1; i < 13; i++)
    {
        output_file << "** CLAUSE " << i << "\n";
        for (j = 1; j < 7; j++)
        {
            k = 6 * (i - 1) + j;
            output_file << "VARIABLE " << j << " " << clvarlt[k] << endl;
        }

        if (i==6)
        {
            //printf("HIT RETURN TO CONTINUE");
            //getchar();
        }
    }

    output_file << "\nBEGIN PROGRAM LOG\n";

    /****** INFERENCE SECTION *****************/

    c = "STA"; //Set condition variable.
    cout << "Input information regarding the patient's treatment options below.\n";
    /* place condition variable c on condition var queue cndvar */
    cndvar[bp] = c;
    /* move backpointer (bp) to back */
    bp = bp + 1;
    /* set the condition variable pointer consisting of the
    statement number (sn) and the clause number (cn) */
    sn = 1; cn = 1;
    /* find the next statement number containing the condition variable
    which is in front of the queue (cndvar), this statement number
    is located in the clause variable list (clvarlt) */
    /* start at the beginning */
    f=1;

    //outer loop to move fp < bp
    do
    {
        //inner IF loop
            search();
            /* point to first clause in statement */
            cn=1;
            if (sn != 0)
                /* more statements */
            {
                /* locate the clause */
                i = 6 * (sn-1) + cn;
                /* clause variable */
                v = clvarlt[i];
                /* are there any more clauses for this statement */
                while(v != "")
                    /* more clauses */
                {
                    /* check instantiation of this clause */
                    check_instantiation();
                    cn = cn+1;
                    /* check next clause */
                    i = 6 * (sn-1) + cn;
                    v = clvarlt[i];
                }

                /* no more clauses - check IF part of statement */
                s = 0;
                /* sample IF-THEN statements from the position knowledge base */

                switch(sn){
                    case 1: if(stage <= 1) s=1;
                        break;
                    case 2: if(stage > 1) s=1;
                        break;
                    case 3: if( health == "YES" && (stage == 0)) s=1;
                        break;
                    case 4: if(health == "NO" && (stage == 0)) s=1;
                        break;
                    case 5: if(leukemia == "YES") s=1;
                        break;
                    case 6: if(leukemia == "NO") s=1;
                        break;
                    case 7: if(radiation == "YES" && (leukemia == "NO")) s =1;
                        break;
                    case 8: if(radiation == "NO") s =1;
                        break;
                    case 9: if(chemo == "YES" && (leukemia == "NO")) s=1;
                        break;
                    case 10: if(chemo == "NO") s=1;
                        break;
                    case 11: if(stem == "YES") s=1;
                        break;
                    case 12: if(stem == "NO") s=1;
                        break;

                }
                /* see if the THEN part should be inovked, i.e., s=1 */
                if (s != 1)
                {
                    f = sn + 1;
                    continue;
                }
            }

    //this also requires a second IF to check to the same conditions for the THEN loop
     if (sn != 0)
     {

            /* invoke THEN part */
                //stage = 0 or stage = 1. 0 - surgery possible. 1 - no surgery possible
                switch(sn){
                    case 1:
                        output_file << "Stage = " << stage << endl;
                        stage = 0;
                        v = "STA";
                        instantiate();
                        break;
                    case 2:
                        output_file << "Stage = " << stage << endl;
                        stage = 1;
                        v = "STA";
                        instantiate();
                        break;
                    case 3:
                        health = "YES";
                        v = "HEA";
                        complete = true;
                        cout << "We recommend surgery." << endl;
                        output_file << "We recommend surgery." << endl;
                        instantiate();
                        break;
                    case 4:
                        health = "NO";
                        v = "HEA";
                        cout << "We recomend drug treatment" << endl;
                        output_file << "We recomend drug treatment" << endl;
                        complete = true;
                        instantiate();
                        break;
                    case 5:
                        leukemia = "YES";
                        v = "LEU";
                        instantiate();
                        break;
                    case 6:
                        leukemia = "NO";
                        v = "LEU";
                        instantiate();
                        break;
                    case 7:
                        radiation = "YES";
                        v = "RAD";
                        cout << "We recommend radiation." << endl;
                        output_file << "We recommend radiation." << endl;
                        complete = true;
                        instantiate();
                        break;
                    case 8:
                        radiation = "NO";
                        v = "RAD";
                        instantiate();
                        break;
                    case 9:
                        chemo = "YES";
                        v = "CHEM";
                        cout << "We recommend chemotherapy." << endl;
                        output_file << "We recommend chemotherapy." << endl;
                        complete = true;
                        instantiate();
                        break;
                    case 10:
                        chemo = "NO";
                        v = "CHEM";
                        instantiate();
                        break;
                    case 11:
                        stem = "YES";
                        v = "STEM";
                        cout << "We recommend stem cell treatment." << endl;
                        output_file << "We recommend stem cell treatment." << endl;
                        complete = true;
                        instantiate();
                        break;
                    case 12:
                        stem = "NO";
                        v = "STEM";
                        cout << "We recommend drug treatment." << endl;
                        output_file << "We recommend stem cell treatment." << endl;
                        complete = true;
                        instantiate();
                        break;
                }
            f = sn + 1;
            continue;

     }


        /* no more clauses in the clause variable list (clvarlt)
        containing the variable in front of the queue (cndvar(fp))
        then remove front variable (cndvar(fp)) and replace it by
        the next variable (cndvar(fp+1)). If no more variables are
        at the front of the queue, stop. */
        /* next queue variable */
        fp = fp+1;
        if (fp < bp)
        {
            /* check out the condition variable */
        f = 1;
            continue;
        }
        /* no more conclusion variables on queue */
        complete = true;
        //changed to outer while loop for entire main, instead of these 2 checks
    }while (complete == false);

}

//==========================================================================
/* Routine to instantiate a variable (v) if it isn't already.
The instantiate indication (instlt) is a 0 if not, a 1 if it is.
The vriable list (varlt) contains the variable (v) */
void Forward::check_instantiation()
{
    i=1;
    /* find variable in the variable list */
    while( (v != varlt[i]) && i<varlt.size() -1) i = i+1;
    /* check if already instantiated */
    if (instlt[i] != 1)
    {
        /* mark instantiated */
        instlt[i] = 1;
        /* the designer of this knowledge base places the input
        statements to instantiate the variables in this case
        statement */

        switch (i)
        {
            /* input statements for sample position knowledge base */
        case 1:
            printf("What stage is the cancer? ");
                cin >> stage;
                output_file << "What stage is the cancer? : " << stage << endl;
            break;
        case 2:
            printf("Are you healthy enough for surgery?");
                cin >> health;
                output_file << "Are you healthy enough for surgery? : " << health << endl;
            break;
        case 3:
            printf("Is the cancer Leukemia? ");
                cin >> leukemia;
                output_file << "Is the cancer Leukemia? : " << leukemia << endl;
                break;
        case 4:
            printf("Can you do radiation? ");
                cin >> radiation;
                output_file << "Can you do radiation? : " << radiation << endl;
            break;
        case 5:
            printf("Can you do chemo? ");
                cin >> chemo;
                output_file << "Can you do chemo? : " << chemo << endl;
            break;
            case 6: printf("Can you do stem cell treatment? " );
                cin >> stem;
                output_file << "Can you do stem cell treatment? : " << stem << endl;
                break;
        }
    }
    /* end of input statements for the position knowledge base */
}

//==========================================================================
/* Search clause variable list for a varialbe (clvarlt) equal to the
one in front of the conclusion queue (cndvar). Return the statement
number (sn). If there is no match, i.e., sn=0, the first statement
for the space is f. */
void Forward::search()
{
    flag = 0;
    sn = f;

    while ((flag == 0) && (sn <= 12))
    {
        cn=1;
        k = (sn-1)*6+cn;
        while((clvarlt[k] != cndvar[fp]) && (cn < 4))
        {
            cn = cn+1;
            k = (sn-1)*4+cn;
        }
        if( clvarlt[k]==cndvar[fp] ) flag = 1;
        if (flag == 0) sn = sn+1;
    }
    if (flag == 0) sn=0;
}

//==========================================================================
/* Routine to instantiate a varialbe (v) and then place it on the
back of the queu (cndvar[bp]), if it is not already there. */
void Forward::instantiate()
{
    i=1;
    /* find varialbe in the varialbe list (varlt) */
    while((v != varlt[i]) && i <= varlt.size()) i = i+1;
    /* instantiate it */
    instlt[i] = 1;
    i = 1;

    /* determine if (v) is or already has been on the queue (cndvar) */
    while((v != cndvar[i]) && i<=cndvar.size()) i = i+1;
    /* variable has not been on the queue. Store it in the back of the queue */
    if(v != cndvar[i])
    {
        cndvar[bp] = v;
        bp=bp+1;
    }
}

