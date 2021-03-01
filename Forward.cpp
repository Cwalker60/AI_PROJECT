/*  Enclosed a program, which comprises the inference engine based on Forward chaining.  You need it for your
    project #1.  The program contains some errors and it is not designed to be efficient.
    Modify the program to make it better and efficient.  Explain in your report how you have modified the
    program to make it better.
*/

/*** FORWARD CHAINING ***/
/************************/
/* Install your IF clauses in sequence in the middle of
the program within the first case statement.
EXAMPLE: IF ((A1==2) && (A2==6) || (A3 == 'YES')) S-1;
IF (J=='NO') S-1;
The THEN part of the above construction always contains
S-1. Install your THEN clauses in sequence in the middle
of the progrram within the second case statement. */

#include <stdio.h>
#include <cstdlib>
#include <string.h> //strcpy
#include <iostream>  //cout
#include <vector>
#include "Forward.h"

using namespace std;

int flag;
//char cndvar[10][3];
vector<string> cndvar(10);
//char varlt[10][3], /* variable list*/ clvarlt[40][3]; /* clause var list */
vector<string> varlt(10);
vector<string> clvarlt(50);

//char c[3], vp[3], /* condition variable */  v[3]; /*variable */
string c, vp, v;
//char fedint[10], interest[10], stock[10], dollar[10], fedmon[10];
//string fedint, interest, stock, dollar, fedmon;
int stage;
string health, leukemia, radiation, chemo, stem;
//char po[10], /* position */  qu[10]; /* qualify */
string po, qu;
//int instlt[10];         /* instantiated list*/
vector<int> instlt(10);
int f, i, j, k, s, fp   /* front pointer */;
int  bp  /* back pointer */,  gr /* grade */,  sn; /* statement number */
int cn;  /* clause number */
bool complete = false;


void search(void);
void check_instantiation(void);
void instantiate(void);

Forward::Forward() {

}

void Forward::run_forward()
{
    /******** INITIALIZATION SECTION ***********/
    fp=1;
    bp=1;

    for (i=1;i < 41; i++)
        //strcpy(clvarlt[i], "");
        clvarlt.push_back("");
   for (i=1;i < 11; i++)
        //strcpy(cndvar[i], "");
        cndvar.push_back("");
    for (i=1;i < 11; i++)
        instlt[i] = 0;
    for (i=1;i < 11; i++)
        //strcpy(varlt[i], "");
        varlt.push_back("");


    for (i=1;i < 11; i++)
    {
        //strcpy(cndvar[i], "");
        cndvar[i] = "";
        //strcpy(varlt[i], "");
        varlt[i] = "";
        instlt[0] = 0;
    }

    /* enter variables which are in the IF part, 1 at a time in
    the exact order that they occur. Up to 3 variables per
    IF statement. Do not duplicate any variable names. Any
    name is used only once. If no more variables left, just
    hit return key */
    /****** comment 367 *************/
    //strcpy(varlt[1], "DO");
    //strcpy(varlt[2], "FT");
    //strcpy(varlt[3], "FM");
    //strcpy(varlt[4], "IN");
    //strcpy(varlt[5], "ST");
    varlt[1] = "STA"; //STAGE
    varlt[2] = "HEA"; //Health
    varlt[3] = "LEU"; // Leukemia
    varlt[4] = "RAD"; // Radiation
    varlt[5] = "CHEM"; // Chemo
    varlt[6] = "STEM"; // Stem cells

    printf("*** VARIABLE LIST ***\n");
    for (i=1;i < 11; i++)
    {
        //printf("ENTER VARIABLE   %d   %s\n", i, varlt[i]);   //added brackets around for loop
        cout << "ENTER VARIABLE " << i << " " << varlt[i] << endl;
    }
    printf("HIT RETURN TO CONTINUE");

    getchar();

    /* enter variables as they appear in the IF clauses, Up to 3
    variables per IF statement. If no more variables left, just
    hit return key */
    /****** comment 407, 408 *************/
    //strcpy(clvarlt[1], "IN");
    //strcpy(clvarlt[5], "IN");
    //strcpy(clvarlt[9], "DO");
    //strcpy(clvarlt[13], "DO");
    //strcpy(clvarlt[17], "FT");
    //strcpy(clvarlt[18], "FM");
    /*
    clvarlt[1] = "STA";
    clvarlt[2] = "HEA";

    clvarlt[4] = "STA";
    clvarlt[5] = "HEA";

    clvarlt[8] = "STA";
    clvarlt[9] = "LEU";
    clvarlt[10] = "RAD";

    clvarlt[12] = "STA";
    clvarlt[13] = "LEU";
    clvarlt[14] = "RAD";
    clvarlt[15] = "CHEM";

    clvarlt[18] = "STA";
    clvarlt[19] = "LEU";
    clvarlt[20] = "RAD";
    clvarlt[21] = "CHEM";
    clvarlt[22] = "STEM";

    clvarlt[24] = "STA";
    clvarlt[25] = "LEU";
    clvarlt[26] = "RAD";
    clvarlt[27] = "CHEM";
    clvarlt[28] = "STEM";

    clvarlt[30] = "STA";
    clvarlt[31] = "LEU";
    clvarlt[32] = "CHEM";

    clvarlt[36] = "STA";
    clvarlt[37] = "LEU";
    clvarlt[38] = "CHEM";
    clvarlt[39] = "STEM";

    clvarlt[41] = "STA";
    clvarlt[42] = "LEU";
    clvarlt[43] = "CHEM";
    clvarlt[44] = "STEM";
    */
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


    printf("*** CLAUSE-VARIABLE LIST ***\n");
    for (i = 1; i < 13; i++)
    {
        printf("** CLAUSE %d\n", i);
        for (j = 1; j < 7; j++)
        {
            k = 6 * (i - 1) + j;
            //printf("VARIABLE %d  %s\n", j, clvarlt[k]);
            cout << "VARIABLE " << j << " " << clvarlt[k] << endl;
        }

        if (i==6)
        {
            printf("HIT RETURN TO CONTINUE");
            getchar();
        }
    }

    /****** INFERENCE SECTION *****************/
    printf("ENTER CONDITION VARIABLE? ");
    //gets(c);
    getline(cin, c);

    /* place condition variable c on condition var queue cndvar */
    //strcpy(cndvar[bp], c);
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


//b496:

    //outer loop to move fp < bp
    do
    {
        //inner IF loop
            search();
            //cout << sn << " is the then/if at start" << endl;
            /* point to first clause in statement */
            cn=1;
            if (sn != 0)
                /* more statements */
            {
                /* locate the clause */
                i = 6 * (sn-1) + cn;
                //cout << "clause var at " << i << endl;
                /* clause variable */
                //strcpy(v, clvarlt[i]);
                v = clvarlt[i];
                /* are there any more clauses for this statement */
               // while (strcmp(v, ""))
                while(v != "")
                    /* more clauses */
                {
                    /* check instantiation of this clause */
                    check_instantiation();
                    cn = cn+1;
                    /* check next clause */
                    i = 6 * (sn-1) + cn;
                    //strcpy(v, clvarlt[i]);
                    v = clvarlt[i];
                }

                /* no more clauses - check IF part of statement */
                s = 0;
                /* sample IF-THEN statements from the position knowledge base */


              // switch(sn)
               // {
                    /* statement 1 */
                    /***** comment 1500 *****/
                //case 1: if (strcmp(interest, "FALL") == 0) s=1;
                 //   case 1: if (interest == "FALL") s=1;
                   // break;
                    /* statement 2 */
                    /***** comment 1510 *****/
                //case 2: if (strcmp(interest, "RISE") == 0) s=1;
                    //case 2: if (interest == "RISE") s=1;
                    //break;
                    /* statement 3 */
                    /***** comment 1540 *****/
                //case 3: if (strcmp(dollar, "FALL") == 0) s=1;
                    //case 3: if (dollar == "FALL") s=1;
                    //break;
                    /* statement 4 */
                    /***** comment 1550 *****/
                //case 4: if (strcmp(dollar, "RISE") == 0) s=1;
                    //case 4: if (dollar == "RISE") s=1;
                    //break;
                    /* statement 5 */
                //case 5: if ((strcmp(fedint, "FALL") == 0) && (strcmp(fedmon, "ADD")) == 0) s=1;
                  //  case 5: if ((fedint == "FALL") && (fedmon =="ADD")) s=1;
                   // break;
                    /* statement 6 */
                //case 6: if ((strcmp(qu, "YES") == 0) && (gr >= 3.5) == 0) s=1;
                    //case 6: if((qu == "YES") && (gr>=3.5) == 0) s=1;
                    //break;
                    /***** comment 1610 *****/
                //}

                /*
                switch(sn){
                    case 1: if ((stage <= 1) && (health == "YES")) s=1;
                        break;
                    case 2: if ((stage <= 1) && (health == "NO")) s=1;
                        break;
                    case 3: if((stage > 1) && (leukemia == "NO") && (radiation == "YES")) s=1;
                        break;
                    case 4: if ((stage > 1) && (leukemia == "NO") && (radiation == "NO") && (chemo == "YES")) s=1;
                        break;
                    case 5: if ((stage > 1) && (leukemia == "NO") && (radiation == "NO") && (chemo == "NO") && (stem == "NO")) s=1;
                        break;
                    case 6: if ((stage > 1) && (leukemia == "NO") && (radiation == "NO") && (chemo == "NO") && (stem == "YES")) s=1;
                        break;
                    case 7: if( (stage > 1) && (leukemia == "YES") && (chemo == "NO") && (stem == "NO") ) s =1;
                        break;
                    case 8: if( (stage > 1) && (leukemia == "YES") && (chemo == "NO") && (stem == "YES") ) s =1;
                        break;

                }
                 */

                //stage = 0 or stage = 1. 0 - surgery possible. 1 - no surgery possible
                //cout << "sn : " << sn << endl;

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
                //cout << "value of s : " << s << endl;
                /* see if the THEN part should be inovked, i.e., s=1 */
                if (s != 1)
                {
                    f = sn + 1;
                    //goto b496;
                    continue;
                }
                //f = sn+1;
            }
            //changed initial if/goto statement into a do while loop with the same check


    //this also requires a second IF to check to the same conditions for the THEN loop
     if (sn != 0)
     {

            /* invoke THEN part */
           // switch (sn)
            //{
                /*********** comment 1500 ***********/
                /* put variable on the conclusion variable queue */
           // case 1:
                //strcpy(stock, "RISE");
             //       stock = "RISE";
               // printf("ST=RISE\n");
                //strcpy(v, "ST");
                //v = "ST";
                //instantiate();
                //break;
                /*********** comment 1510 ***********/
                /* put variable on the conclusion variable queue */
            //case 2:
                //strcpy(stock, "FALL");
              //      stock = "FALL";
               // printf("ST=FALL\n");
                //strcpy(v, "ST");
               // v = "ST";
               // instantiate();
              //  break;
                /*********** comment 1540 ***********/
                /* put variable on the conclusion variable queue */
           // case 3:
                //strcpy(interest, "RISE");
                //    interest = "RISE";
               // printf("IN=RISE\n");
                //strcpy(v, "IN");
                //    v = "IN";
                //instantiate();
               // break;
                /*********** comment 1550 ***********/
                /* put variable on the conclusion variable queue */
           // case 4:
               // strcpy(interest, "FALL");
             //       interest = "FALL";
             //   printf("IN=FALL\n");
                //strcpy(v, "IN");
               // v = "IN";
               // instantiate();
               // break;
                /* put variable on the conclusion variable queue */
           // case 5:
                //strcpy(interest, "FALL");
               //     interest = "FALL";
               // printf("IN=FALL\n");
                //strcpy(v, "IN");
               //     v = "IN";
                //instantiate();
                //break;
            //case 6:
                //strcpy(po, "YES");
              //      po = "YES";
              //  printf("PO=YES\n");
              //
                /*********** comment 1610 ***********/
          // }

                //stage = 0 or stage = 1. 0 - surgery possible. 1 - no surgery possible
                switch(sn){
                    case 1:
                        cout << "Stage = " << stage << endl;
                        stage = 0;
                        v = "STA";
                        instantiate();
                        break;
                    case 2:
                        cout << "Stage = " << stage << endl;
                        stage = 1;
                        v = "STA";
                        instantiate();
                        break;
                    case 3:
                        health = "YES";
                        v = "HEA";
                        complete = true;
                        cout << "We recommend surgery." << endl;
                        instantiate();
                        break;
                    case 4:
                        health = "NO";
                        v = "HEA";
                        cout << "We recomend drug treatment" << endl;
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
                        complete = true;
                        instantiate();
                        break;
                    case 12:
                        stem = "NO";
                        v = "STEM";
                        cout << "We recommend drug treatment." << endl;
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
        //cout << "fp : " << fp;
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
   // while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i+1;
    while( (v != varlt[i]) && i<varlt.size()) i = i+1;
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
            //gets(dollar);
                cin >> stage;
            break;
        case 2:
            printf("Are you healthy enough  for surgery?");
            //gets(fedint);
                cin >> health;
            break;
        case 3:
            printf("Is the cancer Leukemia? ");
            //gets(fedmon);
                cin >> leukemia;
                break;
        case 4:
            printf("Can you do radiation? ");
            //gets(interest);
                cin >> radiation;
            break;
        case 5:
            printf("Can you do chemo? ");
            //gets(stock);
                cin >> chemo;
            break;
            case 6: printf("Can you do stem cell treatment? " );
                cin >> stem;
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
        //while ((strcmp(clvarlt[k], cndvar[fp]) != 0) && (cn < 4))
        while((clvarlt[k] != cndvar[fp]) && (cn < 4))
        {
            cn = cn+1;
            k = (sn-1)*4+cn;
        }

        //if (strcmp(clvarlt[k], cndvar[fp]) == 0) flag = 1;
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
    //while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i=i+1;
    while((v != varlt[i]) && i <= varlt.size()) i = i+1;
    /* instantiate it */
    instlt[i] = 1;
    i = 1;

    /* determine if (v) is or already has been on the queue (cndvar) */
    //while ((strcmp(v, cndvar[i]) != 0) && (i <= 10)) i=i+1;
    while((v != cndvar[i]) && i<=cndvar.size()) i = i+1;
    /* variable has not been on the queue. Store it in the back of the queue */
    //if (strcmp(v, cndvar[i]) != 0)
    if(v != cndvar[i])
    {
        //strcpy(cndvar[bp], v);
        cndvar[bp] = v;
        bp=bp+1;
    }
}

