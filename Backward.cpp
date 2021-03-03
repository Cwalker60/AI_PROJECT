#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include "Backward.h"

using namespace std;
//Enclosed a program, which comprises the inference engine based on backward chaining.  You need it for your
//project #1.  The program contains some errors and it is not designed to be efficient.
//Modify the program to make it better and efficient.  Explain in your report how you have modified the
//program to make it better.
//MODIFICATIONS: Moved goto statements into functions -
//-could possibly use dynamic allocation for the character arrays instead
//-pass by reference would require a lot of refactoring by is more efficient as well



/*****backward chaining *******/
/* Install your IF clauses in sequence in the first case
   statement of the main program
   example: if((a1==2) && (a2==6)) s=1;
                      if(strcmp(j,NO") != 0) s=1;
   the then part of the above construction always
   contains s=1;
   install your the clauses in sequence in the second
   case statement of the main program
   example strcpy(po,"YES");
*/

/*  conclusion list */
// OLD char conclt[10][3];
vector<string> conclt(2);
/*  variable list */
// OLD char bvarlt[10][3];
vector<string> bvarlt(2);
/*  clause vairable list */
vector<string> clbvarlt(240);
string varble;
//char /* qualify */ qu[4], /* degree*/ de[4];
//char /* discovery */ di[4], /* position */ po[4];
string cancer, skin_issuse, change_skin, dry_skin,
       lump_breast, mole_change, persistant_cough,
       resp_infect, cough_blood, diff_swallow,
       weight_loss, swol_lymph, bone_pain,
       rectal_bleed, mouth_ulcer, abdominal_pain,
       nausea, headache, yellow_skin, trouble_urine,
       blood_urine, lower_back_pain;

char buff[128];

/* instantiated list */
//int instlt[11];
vector<int> binstlt(1);
/* statement stack */
//int statsk[11];
vector<int> statsk(1);
/* clause stack */
//int clausk[11];
vector<int> clausk(1);

int statenum, bf, bi, bj, bs, bk, /*stack pointer */ bsp;
ofstream out_file;
bool recursion;

void determine_member_concl_list(void);
void push_on_stack(void);
void instantiate(void);
void ifSwitch();
void thenSwitch(void);

Backward::Backward() {

}
void Backward::run_backward()
{
        /***** initialization section ******/
        /* stack space is 10 we initially place stack space at 10+1 */
        out_file.open("backward_log.txt");

        bsp=11;
        for (int i=1; i<11; i++)
        {
                // OLDstrcpy(conclt[i],"");
                // OLD strcpy(bvarlt[i],"");
                ///*
                binstlt.push_back(0);
                statsk.push_back(0);
                clausk.push_back(0);
                //*/
                /*
                instlt[i] = 0;
                statsk[i] = 0;
                clausk[i] = 0;
                */
        }
        //for (i=1; i<41; i++)  //OLDstrcpy(clbvarlt[i],"");
        /* enter conclusions which are the variables in the then part,
        1 at a time.  enter the conclusions in exact order starting at the 1st
        if-then.  after last conclusion hit return key for rest of
        conclusions */
        init();

        /*** comment 305 *****/
        /*
        strcpy(conclt[1], "PO");
        strcpy(conclt[2], "QU");
        strcpy(conclt[3], "PO");
        strcpy(conclt[4], "PO");
        strcpy(conclt[5], "PO");
        strcpy(conclt[6], "PO");
        old code

        conclt[1] = "PO";
        conclt.push_back("QU");
        conclt.push_back("PO");
        conclt.push_back("PO");
        conclt.push_back("PO");
        conclt.push_back("PO");
        conclt.push_back("");
        */

        //cout << ("*** CONCLUSION LIST ***\n");
        out_file << "*** CONCLUSION LIST ***\n";
        for (int i=1; i<conclt.size(); i++)
        {
            //cout << "CONCLUSION #" << i << " ";
            //cout << conclt[i] << endl;
            out_file << "CONCLUSION #" << i << " " << conclt[i] << "\n";
        }


        //cout << ("HIT RETURN TO CONTINUE");
        //gets(buff);
        /* enter variables which are in the if part, 1 at a time in the
        exact order that they occur, up to 3 variables per if statement.  do not
        duplicate any variable names.  any name is used only once.  if no
        more variables left just hit return key. */
        //printf("*** VARIABLE LIST *\n");
        out_file << "*** VARIABLE LIST *\n";
        /**** comment 367 *****/
        /*OLD
        strcpy(bvarlt[1], "DE");
        strcpy(bvarlt[2], "DI");
        strcpy(bvarlt[3], "EX");
        strcpy(bvarlt[4], "GR");

        bvarlt[1] = "DE";
        bvarlt.push_back("DI");
        bvarlt.push_back("EX");
        bvarlt.push_back("GR");
        //*/

        for(int i=1; i<bvarlt.size(); i++) { // OLD printf("VARIABLE %d %s\n", i, bvarlt[i]);
         //cout << "VARIABLE " << i << "\t" << bvarlt[i] << "\n";
         out_file << "VARIABLE " << i << "\t" << bvarlt[i] << "\n";
        }
        //printf("HIT RETURN KEY TO CONTINUE");
        //gets(buff);
        /* enter variables as they appear in the if clauses.  a maximum
        of 3 variables per if statement.  if no more variables hit return key. */
        //printf("*** CLAUSE VARIABLE LIST ***\n");
        /***** comment 407 through 409 ***/
        /* OLD
        strcpy(clbvarlt[1], "DE");
        strcpy(clbvarlt[5], "DE");
        strcpy(clbvarlt[9], "DE");
        strcpy(clbvarlt[10], "DI");
        strcpy(clbvarlt[13], "QU");
        strcpy(clbvarlt[14], "GR");
        strcpy(clbvarlt[15], "EX");
        strcpy(clbvarlt[17], "QU");
        strcpy(clbvarlt[18], "GR");
        strcpy(clbvarlt[19], "EX");
        strcpy(clbvarlt[21], "QU");
        strcpy(clbvarlt[22], "GR");

        clbvarlt[1] = "DE";
        clbvarlt[3] = " ";
        clbvarlt[5] = "DE";
        clbvarlt[9] = "DE";
        clbvarlt[10]= "DI";
        clbvarlt[13]= "QU";
        clbvarlt[14]= "GR";
        clbvarlt[15]= "EX";
        clbvarlt[17]= "QU";
        clbvarlt[18]= "GR";
        clbvarlt[19]= "EX";
        clbvarlt[21]= "QU";
        clbvarlt[22]= "GR";
        */

        /*//OLD
        for(i=1; i<clbvarlt.size(); i++)
        {
                printf("** CLAUSE %d\n", i);
                for(j=1; j<5; j++)
                { k = 4 * (i-1) + j;
                  printf("VARIABLE %d  %s\n", j, clbvarlt[k]); }
                if (i==4)
                { printf("HIT RETURN KEY TO CONTINUE"); gets(buff); }
        }
        */
        ///*
        //cout << "** CLAUSE VARIABLES ** \n";
        out_file << "** CLAUSE VARIABLES ** \n";
        for (int i = 1; i < clbvarlt.size(); i++) {
            //cout << "VARIABLE " << i << "\t " <<  clbvarlt[i] << "\n";
            out_file << "VARIABLE"  << i << "\t " <<  clbvarlt[i] << "\n";
        }
        //*/

        /****** inference section *****/
        varble = "cancer";
        cout << "Input information regarding the patient's symptoms below.\n";
        /* get conclusion statement number (statenum) from the conclusion list
           (conclt) */
        /* first statement starts search */
        // OLD GOTO 1 ---------
        bf=1;
        determine_member_concl_list();
        recursion = false;
        out_file << "\nBEGIN BACKWARD PROGRAM\n";
        recursive_search();
        out_file.close();


}

void Backward::init() {
    //----------- CONCLUSION LIST ----------------------

        conclt[1] = "cancer";
        for (int i = 0; i < 26; i++) {
            conclt.push_back("cancer");
        }

    //------------------------------------------------


    //----------- VARIABLE LIST ----------------------
        bvarlt[1] = "skin_issuse";
        bvarlt.push_back("change_skin");
        bvarlt.push_back("dry_skin");
        bvarlt.push_back("lump_breast");
        bvarlt.push_back("mole_change");
        bvarlt.push_back("persistant_cough");
        bvarlt.push_back("resp_infect");
        bvarlt.push_back("cough_blood");
        bvarlt.push_back("diff_swallow");
        bvarlt.push_back("weight_loss");
        bvarlt.push_back("swol_lymph");
        bvarlt.push_back("bone_pain");
        bvarlt.push_back("rectal_bleed");
        bvarlt.push_back("mouth_ulcer");
        bvarlt.push_back("abdominal_pain");
        bvarlt.push_back("nausea");
        bvarlt.push_back("headache");
        bvarlt.push_back("yellow_skin");
        bvarlt.push_back("trouble_urine");
        bvarlt.push_back("blood_urine");
        bvarlt.push_back("lower_back_pain");

    //------------------------------------------------


    //----------CLAUSE VARIABLE LIST -----------------
        // Clause 1
        clbvarlt[1] = "skin_issuse";
        clbvarlt[2] = "change_skin";
        clbvarlt[3] = "dry_skin";
        clbvarlt[4] = "lump_breast";
        clbvarlt[5] = "";
        // Clause 2
        clbvarlt[9]= "skin_issuse";
        clbvarlt[10]= "change_skin";
        clbvarlt[11]= "dry_skin";
        clbvarlt[12]= "mole_change";
        // Clause 3
        clbvarlt[17]= "skin_issuse";
        clbvarlt[18]= "change_skin";
        clbvarlt[19]= "dry_skin";
        clbvarlt[20]= "lump_breast";
        clbvarlt[21]= "mole_change";
        // Clause 4
        clbvarlt[25]= "skin_issuse";
        clbvarlt[26]= "persistant_cough";
        clbvarlt[27]= "resp_infect";
        clbvarlt[28]= "cough_blood";
        // Clause 5
        clbvarlt[33]= "skin_issuse";
        clbvarlt[34]= "persistant_cough";
        clbvarlt[35]= "resp_infect";
        clbvarlt[36]= "cough_blood";
        // Clause 6
        clbvarlt[41]= "skin_issuse";
        clbvarlt[42]= "persistant_cough";
        clbvarlt[43]= "resp_infect";
        clbvarlt[44]= "cough_blood";
        clbvarlt[45]= "diff_swallow";
        // Clause 7
        clbvarlt[49]= "skin_issuse";
        clbvarlt[50]= "persistant_cough";
        clbvarlt[51]= "resp_infect";
        clbvarlt[52]= "cough_blood";
        clbvarlt[53]= "diff_swallow";
        // Clause 8
        clbvarlt[57]= "skin_issuse";
        clbvarlt[58]= "persistant_cough";
        clbvarlt[59]= "weight_loss";
        clbvarlt[60]= "swol_lymph";
        // Clause 9
        clbvarlt[65]= "skin_issuse";
        clbvarlt[66]= "persistant_cough";
        clbvarlt[67]= "weight_loss";
        clbvarlt[68]= "swol_lymph";
        clbvarlt[69]= "bone_pain";
        clbvarlt[70]= "rectal_bleed";
        clbvarlt[71]= "mouth_ulcer";
        // Clause 10
        clbvarlt[73]= "skin_issuse";
        clbvarlt[74]= "persistant_cough";
        clbvarlt[75]= "weight_loss";
        clbvarlt[76]= "swol_lymph";
        clbvarlt[77]= "bone_pain";
        clbvarlt[78]= "rectal_bleed";
        clbvarlt[79]= "mouth_ulcer";
        // Clause 11
        clbvarlt[81]= "skin_issuse";
        clbvarlt[82]= "persistant_cough";
        clbvarlt[83]= "weight_loss";
        clbvarlt[84]= "swol_lymph";
        clbvarlt[85]= "bone_pain";
        clbvarlt[86]= "rectal_bleed";
        clbvarlt[87]= "abdominal_pain";
        // Clause 12
        clbvarlt[89]= "skin_issuse";
        clbvarlt[90]= "persistant_cough";
        clbvarlt[91]= "weight_loss";
        clbvarlt[92]= "swol_lymph";
        clbvarlt[93]= "bone_pain";
        clbvarlt[94]= "rectal_bleed";
        clbvarlt[95]= "abdominal_pain";
        // Clause 13
        clbvarlt[97]= "skin_issuse";
        clbvarlt[98]= "persistant_cough";
        clbvarlt[99]= "weight_loss";
        clbvarlt[100]= "swol_lymph";
        clbvarlt[101]= "bone_pain";
        clbvarlt[102]= "trouble_urine";
        // Clause 14
        clbvarlt[105]= "skin_issuse";
        clbvarlt[106]= "persistant_cough";
        clbvarlt[107]= "weight_loss";
        clbvarlt[108]= "swol_lymph";
        clbvarlt[109]= "bone_pain";
        clbvarlt[110]= "trouble_urine";
        clbvarlt[111]= "blood_urine";
        // Clause 15
        clbvarlt[113]= "skin_issuse";
        clbvarlt[114]= "persistant_cough";
        clbvarlt[115]= "weight_loss";
        clbvarlt[116]= "swol_lymph";
        clbvarlt[117]= "bone_pain";
        clbvarlt[118]= "trouble_urine";
        clbvarlt[119]= "blood_urine";
        clbvarlt[120]= "lower_back_pain";
        // Clause 16
        clbvarlt[121]= "skin_issuse";
        clbvarlt[122]= "persistant_cough";
        clbvarlt[123]= "weight_loss";
        clbvarlt[124]= "swol_lymph";
        clbvarlt[125]= "bone_pain";
        clbvarlt[126]= "trouble_urine";
        clbvarlt[127]= "blood_urine";
        clbvarlt[128]= "lower_back_pain";
        // Clause 17
        clbvarlt[129]= "skin_issuse";
        clbvarlt[130]= "persistant_cough";
        clbvarlt[131]= "weight_loss";
        clbvarlt[132]= "nausea";
        clbvarlt[133]= "bone_pain";
        clbvarlt[134]= "rectal_bleed";
        clbvarlt[135]= "mouth_ulcer";
        // Clause 18
        clbvarlt[137]= "skin_issuse";
        clbvarlt[138]= "persistant_cough";
        clbvarlt[139]= "weight_loss";
        clbvarlt[140]= "nausea";
        clbvarlt[141]= "bone_pain";
        clbvarlt[142]= "rectal_bleed";
        clbvarlt[143]= "mouth_ulcer";
        // Clause 19
        clbvarlt[145]= "skin_issuse";
        clbvarlt[146]= "persistant_cough";
        clbvarlt[147]= "weight_loss";
        clbvarlt[148]= "nausea";
        clbvarlt[149]= "bone_pain";
        clbvarlt[150]= "rectal_bleed";
        // Clause 20
        clbvarlt[153]= "skin_issuse";
        clbvarlt[154]= "persistant_cough";
        clbvarlt[155]= "weight_loss";
        clbvarlt[156]= "nausea";
        clbvarlt[157]= "bone_pain";
        clbvarlt[158]= "rectal_bleed";
        // Clause 21
        clbvarlt[161]= "skin_issuse";
        clbvarlt[162]= "persistant_cough";
        clbvarlt[163]= "weight_loss";
        clbvarlt[164]= "nausea";
        clbvarlt[165]= "bone_pain";
        clbvarlt[166]= "trouble_urine";
        clbvarlt[167]= "blood_urine";
        // Clause 22
        clbvarlt[169]= "skin_issuse";
        clbvarlt[170]= "persistant_cough";
        clbvarlt[171]= "weight_loss";
        clbvarlt[172]= "nausea";
        clbvarlt[173]= "bone_pain";
        clbvarlt[174]= "trouble_urine";
        clbvarlt[175]= "blood_urine";
        clbvarlt[176]= "lower_back_pain";
        // Clause 23
        clbvarlt[177]= "skin_issuse";
        clbvarlt[178]= "persistant_cough";
        clbvarlt[179]= "weight_loss";
        clbvarlt[180]= "nausea";
        clbvarlt[181]= "bone_pain";
        clbvarlt[182]= "trouble_urine";
        clbvarlt[183]= "blood_urine";
        clbvarlt[184]= "lower_back_pain";
        // Clause 24
        clbvarlt[185]= "skin_issuse";
        clbvarlt[186]= "persistant_cough";
        clbvarlt[187]= "weight_loss";
        clbvarlt[188]= "nausea";
        clbvarlt[189]= "headache";
        // Clause 25
        clbvarlt[193]= "skin_issuse";
        clbvarlt[194]= "persistant_cough";
        clbvarlt[195]= "weight_loss";
        clbvarlt[196]= "nausea";
        clbvarlt[197]= "headache";
        clbvarlt[198]= "yellow_skin";
        // Clause 26
        clbvarlt[201]= "skin_issuse";
        clbvarlt[202]= "persistant_cough";
        clbvarlt[203]= "weight_loss";
        clbvarlt[204]= "nausea";
        clbvarlt[205]= "headache";
        clbvarlt[206]= "yellow_skin";

 //------------------------------------------------

}


void Backward::determine_member_concl_list() {
/* routine to determine if a variable (varble) is a member of the
   conclusion list (conclt).  if yes return statenum != 0.
   if not a member statenum=0;
*/
        /* initially set to not a member */
        statenum = 0;
        /* member of conclusion list to be searched is f */
        bi = bf;
        // OLD while((strcmp(varble, conclt[i]) != 0) && (i<8))
        while ((varble != conclt[bi]) && (bi < (conclt.size() - 1 ))) {
            bi = bi + 1;
            //cout << "Comparing " << varble << ": " << conclt[i] << "\n";
        }
                /* test for membership */

        //if (strcmp(varble, conclt[i]) == 0) statenum = i;  /* a member */
        if (varble == conclt[bi]) statenum = bi;
        //cout << "statenum : " << statenum << "\n";
        //cout << "i : " << i << "\n";
}

void Backward::push_on_stack()
/* routine to push statement number (statenum) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statsk) and the
clause stack (clausk)..to push decrement stack pointer (sp) */
{
        bsp=bsp-1;
        statsk[bsp] = statenum;
        clausk[bsp] = 1;
}

void Backward::printStack() {
    cout << "---------------------\n";
    cout << "sp at : " << bsp << "\n";
    cout << "stack top : " << statsk[bsp] << "\n";
    cout << "claus top : " << clausk[bsp] << "\n";
    cout << "---------------------\n";
}

void Backward::instantiate()
/* routine to instantiate a variable (varble) if it istatenum't already.  the
instantiate indication (instlt) is a 0 if not, a 1 if it is.  the
variable list (bvarlt) contains the variable (varble). */
{

        bi=1;

        /* find variable in the list */
        //OLD while((strcmp(varble, bvarlt[i]) != 0) && (i<10)) i=i+1;
        while ((varble != bvarlt[bi]) && (bi < bvarlt.size())) {
                bi++;
        }
        //OLD if((strcmp(varble, bvarlt[i]) == 0) && (instlt[i] != 1))
        if ((varble == bvarlt[bi]) && (binstlt[bi] != 1))
                /*found variable and not already instantiated */
        {
                binstlt[bi]=1; /*mark instantiated */
                /* the designer of the
               knowledge base places the input statements to
               instantiate the variables below in the case statement */
                switch (bi)
                {
                        /***** input statement *****/
                        /* input statements for sample position knowledge
                           base */
                        /***** comment 1700 ******/
                /* OLD
                case 1: printf("INPUT YES OR NOW FOR DE-? ");
                        cin >> de;
                        break;
                case 2: printf("INPUT YES OR NO FOR DI-? ");
                        cin >> di;
                        break;
                case 3: printf("INPUT A REAL NUMBER FOR EX-? ");
                        cin >>  ex;
                        break;
                case 4: printf("INPUT A REAL NUMBER FOR GR-? ");
                        cin >>  gr;
                        break;
                */

                ///*
                case 1: printf("Does your skin have abnormal issues? (YES/NO) ");
                        cin >> skin_issuse;
                        out_file << "Does your skin have abnormal issues? (YES/NO) : "
                                    << skin_issuse << endl;
                        break;

                case 2: printf("Do you feel like your skin has changed? (YES/NO) ");
                        cin >> change_skin;
                        out_file << "Do you feel like your skin has changed? (YES/NO) : "
                                    << change_skin << endl;
                        break;
                case 3: printf("Do you have dry skin? (YES/NO) ");
                        cin >> dry_skin;
                        out_file << "Do you have dry skin? (YES/NO) : "
                                    << dry_skin << endl;
                        break;
                case 4: printf("Do you feel a lump in your breast? (YES/NO) ");
                        cin >>  lump_breast;
                        out_file << "Do you feel a lump in your breast? (YES/NO) : "
                                    << lump_breast << endl;
                        break;
                case 5: printf("Do you feel like your moles have gotten worse? (YES/NO) ");
                        cin >>  mole_change;
                        out_file << "Do you feel like your moles have gotten worse? (YES/NO) : "
                                    << mole_change << endl;
                        break;
                case 6: printf("Are you coughing persistently? (YES/NO) ");
                        cin >> persistant_cough;
                        out_file << "Are you coughing persistently? (YES/NO) : "
                                    << persistant_cough << endl;
                        break;
                case 7: printf("Were you diagnosed with a respiratory infection? (YES/NO) ");
                        cin >> resp_infect;
                        out_file << "Were you diagnosed with a respiratory infection? (YES/NO) : "
                                    << resp_infect << endl;
                        break;
                case 8: printf("Do you cough up blood? (YES/NO) ");
                        cin >>  cough_blood;
                        out_file << "Do you cough up blood? (YES/NO) : "
                                    << cough_blood << endl;
                        break;
                case 9: printf("Do you feel like you have difficulty swallowing? (YES/NO) ");
                        cin >>  diff_swallow;
                        out_file << "Do you feel like you have difficulty swallowing? (YES/NO) : "
                                    << diff_swallow << endl;
                        break;

                case 10: printf("Have you experienced sudden weight loss? (YES/NO) ");
                        cin >> weight_loss;
                        out_file << "Have you experienced sudden weight loss? (YES/NO) : "
                                    << weight_loss << endl;
                        break;
                case 11: printf("Do you have any swollen lymph nodes? (YES/NO) ");
                        cin >> swol_lymph;
                        out_file << "Do you have any swollen lymph nodes? (YES/NO) : "
                                    << swol_lymph << endl;
                        break;
                case 12: printf("Do experience pain deep within your bones? (YES/NO) ");
                        cin >>  bone_pain;
                        out_file << "Do experience pain deep within your bones? (YES/NO) : "
                                    << bone_pain << endl;
                        break;
                case 13: printf("Do you have rectal bleeding or blood after bowel movements? (YES/NO) ");
                        cin >>  rectal_bleed;
                        out_file << "Do you have rectal bleeding or blood after bowel movements? (YES/NO) : "
                                    << rectal_bleed << endl;
                        break;

                case 14: printf("Do you have severe or moderate mouth ulcers? (YES/NO) ");
                        cin >> mouth_ulcer;
                        out_file << "Do you have severe or moderate mouth ulcers? (YES/NO) : "
                                    << mouth_ulcer << endl;
                        break;
                case 15: printf("Do you experience frequent abdominal pain? (YES/NO) ");
                        cin >> abdominal_pain;
                        out_file << "Do you experience frequent abdominal pain? (YES/NO) : "
                                    << abdominal_pain << endl;
                        break;
                case 16: printf("Do experience frequent nausea? (YES/NO) ");
                        cin >>  nausea;
                        out_file << "Do experience frequent nausea? (YES/NO) : "
                                    << nausea << endl;
                        break;
                case 17: printf("Do you experience headaches? (YES/NO) ");
                        cin >>  headache;
                        out_file << "Do you experience headaches? (YES/NO) : "
                                    << headache << endl;
                        break;

                case 18: printf("Has your skin changed to a yellow? (YES/NO) ");
                        cin >> yellow_skin;
                        out_file << "Has your skin changed to a yellow? (YES/NO) : "
                                    << yellow_skin << endl;
                        break;
                case 19: printf("Do you experience problems urinating? (YES/NO) ");
                        cin >> trouble_urine;
                        out_file << "Do you experience problems urinating? (YES/NO) : "
                                    << trouble_urine << endl;
                        break;
                case 20: printf("Do have blood in your urine? (YES/NO) ");
                        cin >>  blood_urine;
                        out_file << "Do have blood in your urine? (YES/NO) : "
                                    << blood_urine << endl;
                        break;
                case 21: printf("Do you experience lower back pain? (YES/NO) ");
                        cin >>  lower_back_pain;
                        out_file << "Do you experience lower back pain? (YES/NO) "
                                    << lower_back_pain << endl;
                        break;
                        //*/

                }
                /* end of inputs statements for sample position knowledge
                   base */
        }
}

void Backward::ifSwitch()
{
    switch (statenum)
    {

        /* if part of statement 1 */
        /* OLD
        case 1: if(de == "NO") s = 1;
                break;
        case 2: if(de == "YES") s = 1;
                break;
        case 3: if((de == "YES") && (di == "YES")) s =1;
                break;
        case 4: if((qu == "YES") && (gr <3.5) && (ex >= 2)) s = 1;
        case 5: if((qu == "YES") && (gr<3) && (ex<2)) s = 1;
                break;
        case 6: if((qu == "YES") && (gr >=3.5)) s = 1;
                break;
        */

        ///* NEW RULES
        // RULE 10
        case 1: if((skin_issuse == "YES") && (lump_breast == "YES") /*&& (mole_change == "NO")*/ ) {
            bs = 1;
        }
                break;
        // RULE 30
        case 2: if((skin_issuse == "YES") && (mole_change == "YES") && (lump_breast == "NO")) {
                bs = 1;
                }
                break;
        // RULE 50
        case 3: if((dry_skin == "YES") && (mole_change == "NO") && (lump_breast == "NO"))  {
                bs = 1;
                }
                break;
        // RULE 70
        case 4: if((skin_issuse == "YES") && (persistant_cough == "YES") && (resp_infect == "YES") && (cough_blood == "NO")) {
                bs = 1;
                }
                break;
        // RULE 80
        case 5: if((skin_issuse == "NO") && (persistant_cough == "YES") && (resp_infect == "YES") &&
                    (cough_blood == "YES")) {
                bs = 1;
                }
                break;
        // RULE 100
        case 6: if((skin_issuse == "NO") && (persistant_cough == "YES") && (resp_infect == "NO") &&
                    (cough_blood == "NO") && (diff_swallow == "NO")) {
                bs = 1;
                }
                break;
        // RULE 120
        case 7: if((skin_issuse == "NO") && (persistant_cough == "YES") && (resp_infect == "NO") &&
                    (cough_blood == "NO") && (diff_swallow == "YES")) {
                bs = 1;
                }
                break;
        // RULE 140
        case 8: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                    (swol_lymph == "YES")) {
                bs = 1;
                }
                break;
        // RULE 160
        case 9: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "NO") && (rectal_bleed == "NO") &&
                   (mouth_ulcer == "YES")) {
                bs = 1;
                }
                break;
        // RULE 180
        case 10: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "NO") && (rectal_bleed == "NO") &&
                   (mouth_ulcer == "YES")) {
                bs = 1;
                }
                break;
        // RULE 200
        case 11: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "NO") && (rectal_bleed == "YES") &&
                   (abdominal_pain == "YES")) {
                bs = 1;
                }
                break;
        // RULE 220
        case 12: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "NO") && (rectal_bleed == "YES") &&
                   (abdominal_pain == "NO")) {
                bs = 1;
                }
                break;
        // RULE 240
        case 13: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "YES") && (trouble_urine == "NO")) {
                bs = 1;
                }
                break;
        // RULE 260
        case 14: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "YES") && (trouble_urine == "YES") &&
                   (blood_urine == "NO")) {
                bs = 1;
                }
                break;
        // RULE 280
        case 15: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "YES") && (trouble_urine == "YES") &&
                   (blood_urine == "YES") && (lower_back_pain == "YES")) {
                bs = 1;
                }
                break;
        // RULE 310
        case 16: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "YES") &&
                   (swol_lymph == "NO") && (bone_pain == "YES") && (trouble_urine == "YES") &&
                   (blood_urine == "YES") && (lower_back_pain == "NO")) {
                bs = 1;
                }
                break;
        // RULE 340
        case 17: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "NO") && (rectal_bleed == "NO") &&
                   (mouth_ulcer == "YES")) {
                bs = 1;
                }
                break;
        // RULE 360
        case 18: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "NO") && (rectal_bleed == "YES") &&
                   (abdominal_pain == "YES")) {
                bs = 1;
                }
                break;
        // RULE 380
        case 19: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "NO") && (rectal_bleed == "NO")) {
                bs = 1;
                }
                break;
        // RULE 400
        case 20: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "YES") && (trouble_urine == "NO")) {
                bs = 1;
                }
                break;
        // RULE 430
        case 21: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "YES") && (trouble_urine == "YES")
                && (blood_urine == "NO")) {
                bs = 1;
                }
                break;
        // RULE 450
        case 22: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "YES") && (trouble_urine == "YES")
                && (blood_urine == "YES") && (lower_back_pain == "YES")) {
                bs = 1;
                }
                break;
        // RULE 480
        case 23: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "NO") && (bone_pain == "YES") && (trouble_urine == "YES")
                && (blood_urine == "YES") && (lower_back_pain == "NO")) {
                bs = 1;
                }
                break;
        // RULE 510
        case 24: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "YES") && (headache == "YES")) {
                bs = 1;
                }
                break;
        // RULE 530
        case 25: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "YES") && (headache == "NO") && (yellow_skin == "YES")) {
                bs = 1;
                }
                break;
        // RULE 550
        case 26: if((skin_issuse == "NO") && (persistant_cough == "NO") && (weight_loss == "NO") &&
                   (nausea == "YES") && (headache == "NO") && (yellow_skin == "NO")) {
                bs = 1;
                }
                break;
        //*/
    }

}

void Backward::thenSwitch()
{
    switch (statenum)
    {
       /* OLD
        case 1: po = "NO";
                printf("PO=NO\n");
                break;


        case 2: qu = "YES";
                printf("QU=YES\n");
                break;

        case 3: po = "YES";
                printf("PO=RESEARCH\n");
                break;

        case 4: po = "YES";
                printf("PO=SERVICE ENGINEER\n");
                break;

        case 5: po = "NO";
                printf("PO=NO");
                break;

        case 6: po = "YES";
                printf("PO=PRODUCT ENGINEER\n");
                break;
        */

        ///*
        // RULE 10 THEN
        case 1: cancer = "Breast Cancer";
                printf("Patient is diagnosed with Breast Cancer.\n");
                out_file << "Patient is diagnosed with Breast Cancer.\n";
                break;
        // RULE 30 THEN
        case 2: cancer = "Skin Cancer";
                printf("Patient is diagnosed with Skin Cancer.\n");
                out_file << "Patient is diagnosed with Skin Cancer.\n";
                break;
        // RULE 50 THEN
        case 3: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 70 THEN
        case 4: cancer = "Lung Cancer";
                printf("Patient is diagnosed with Lung Cancer.\n");
                out_file << "Patient is diagnosed with Lung Cancer.\n";
                break;
        // RULE 80 THEN
        case 5: cancer = "Tracheal Cancer";
                printf("Patient is diagnosed with Tracheal Cancer.\n");
                out_file << "Patient is diagnosed with Tracheal Cancer.\n";
                break;
        // RULE 100
        case 6: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 120 THEN
        case 7: cancer = "Mouth Cancer";
                printf("Patient is diagnosed with Mouth Cancer.\n");
                out_file << "Patient is diagnosed with Mouth Cancer.\n";
                break;
        // RULE 140 THEN
        case 8: cancer = "Leukemia";
                printf("Patient is diagnosed with Leukemia.\n");
                out_file << "Patient is diagnosed with Leukemia.\n";
                break;
        // RULE 160 THEN
        case 9: cancer = "Mouth Cancer";
                printf("Patient is diagnosed with Mouth Cancer.\n");
                out_file << "Patient is diagnosed with Mouth Cancer.\n";
                break;
        // RULE 180 THEN
        case 10: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 200 THEN
        case 11: cancer = "Colon Cancer";
                printf("Patient is diagnosed with Colon Cancer.\n");
                out_file << "Patient is diagnosed with Colon Cancer.\n";
                break;
        // RULE 220
        case 12: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 240
        case 13: cancer = "Bone Cancer";
                printf("Patient is diagnosed with Bone Cancer.\n");
                out_file << "Patient is diagnosed with Bone Cancer.\n";
                break;
        // RULE 260 THEN
        case 14: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 280 THEN
        case 15: cancer = "Kidney Cancer";
                printf("Patient is diagnosed with Kidney Cancer.\n");
                out_file << "Patient is diagnosed with Kidney Cancer.\n";
                break;
        // RULE 310 THEN
        case 16: cancer = "Bladder Cancer";
                printf("Patient is diagnosed with Bladder Cancer.\n");
                out_file << "Patient is diagnosed with Bladder Cancer.\n";
                break;
        // RULE 340 THEN
        case 17: cancer = "Mouth Cancer";
                printf("Patient is diagnosed with Mouth Cancer.\n");
                out_file << "Patient is diagnosed with Mouth Cancer.\n";
                break;
        // RULE 360
        case 18: cancer = "Colon Cancer";
                printf("Patient is diagnosed with Colon Cancer.\n");
                out_file << "Patient is diagnosed with Colon Cancer.\n";
                break;
        // RULE 380 THEN
        case 19: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 400 THEN
        case 20: cancer = "Bone Cancer";
                printf("Patient is diagnosed with Bone Cancer.\n");
                out_file << "Patient is diagnosed with Bone Cancer.\n";
                break;
        // RULE 430 THEN
        case 21: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        // RULE 450 THEN
        case 22: cancer = "Kidney Cancer";
                printf("Patient is diagnosed with Kidney Cancer.\n");
                out_file << "Patient is diagnosed with Kidney Cancer.\n";
                break;
        // RULE 480 THEN
        case 23: cancer = "Bladder Cancer";
                printf("Patient is diagnosed with Bladder Cancer.\n");
                out_file << "Patient is diagnosed with Bladder Cancer.\n";
                break;
        // RULE 510
        case 24: cancer = "Brain Cancer";
                printf("Patient is diagnosed with Brain Cancer.\n");
                out_file << "Patient is diagnosed with Brain Cancer.\n";
                break;
        // RULE 530
        case 25: cancer = "Liver Cancer";
                printf("Patient is diagnosed with Liver Cancer.\n");
                out_file << "Patient is diagnosed with Liver Cancer.\n";
                break;
        // RULE 550
        case 26: cancer = "None diagnosed";
                printf("Patient is diagnosed with no Cancer.\n");
                out_file << "Patient is diagnosed with no Cancer.\n";
                break;
        //*/

    }
}
void Backward::recursive_search() {
     bool breaks;
        if (statenum != 0) {
             do {
                if (recursion == false) {
                    push_on_stack();
                }
                    recursion = false;
                    breaks = false;
                do {
                    // Loop through to get all conclusions on stack.
                        bi= (statsk[bsp] -1) *8 + clausk[bsp];
                        //cout << "statsk i = " << bi << "\n";
                        /* clause variable */
                        varble = clbvarlt[bi];
                        if(varble != "") {
                      /*is this clause variable a conclusion? */
                            bf = 1;
                            determine_member_concl_list();
                            if (statenum != 0) {

                                bf=1;
                                determine_member_concl_list();
                                breaks = true;
                                //push_on_stack();
                                //printStack();
                                break;
                            }
                            instantiate();
                            clausk[bsp] = clausk[bsp] + 1;
                        }

                } while (varble != "");
                if (breaks == true) {
                    continue;
                }
                statenum = statsk[bsp];
                bs = 0;
                ifSwitch();
                 //cout << bs << " is s after if.\n";
                if( bs != 1) {
                    /* failed..search rest of statements for
                        same conclusion */
                    /* get conclusion */
                    //printStack();
                    bi = statsk[bsp];
                   varble = conclt[bi];
                   /* search for conclusion starting at the
                     next statement number */
                   bf = statsk[bsp] + 1;
                   determine_member_concl_list();
                   bsp = bsp+1;
                  }

            } while ((bs != 1) && (statenum !=0));

            //if (statenum != 0) {
                //cout << "statenum after while is " << statenum << "\n";
                thenSwitch();
                bsp = bsp + 1;
                if ((bsp >= 11)) {
                    //printf("*** SUCCESS\n");
                    if (cancer == "") {
                        cout << "Unable to diagnose.\n";
                        out_file << "Unable to diagnose.\n";
                    }

                } else {
                    clausk[bsp] = clausk[bsp]+1;
                    recursion = true;
                    recursive_search();
                }

            //}
        }
}
