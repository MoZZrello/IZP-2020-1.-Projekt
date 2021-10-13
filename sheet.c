#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define DLZKA_RIADKA 10242
#define VELKOST_BUNKY 102

typedef struct{
    char delim[VELKOST_BUNKY];
    char cset_char[VELKOST_BUNKY];
    char bwChar[VELKOST_BUNKY];
    char contChar[VELKOST_BUNKY];
    int first_del;
    int del;
    int rows_num ;
    int irow_row;
    int drow_row;
    int drows_start;
    int drows_end;
    int icol_colm;
    int dcol_colm;
    int dcols_colm1;
    int dcols_colm2;
    int cset_colm;
    int tl_colm;
    int tp_colm;
    int r_colm;
    int int_colm;
    int whereCopy;
    int toCopy;
    int firstSwap;
    int secondSwap;
    int firstMove;
    int secondMove;
    int fromRows;
    int toRows;
    int bwColumn;
    int contColumn;
}params_place_t;
typedef struct {
    char BWChar[VELKOST_BUNKY];
    char CTChar[VELKOST_BUNKY];
    int startRows;
    int endRows;
    int BWColm;
    int CTColm;
}select_row_t;
typedef struct{
    bool delim_found;
    bool irow_true;
    bool arow_true;
    bool drow_true;
    bool drows_true;
    bool icol_true;
    bool acol_true;
    bool dcol_true;
    bool dcols_true;
    bool cset_true;
    bool tl_true;
    bool tp_true;
    bool r_true;
    bool int_true;
    bool copy_true;
    bool once;
    bool swap_true;
    bool move_true;
    bool rows_true;
    bool beginswith_true;
    bool contains_true;
}params_bool_t;

void params_bool_init(params_bool_t *params);
void params_place(int argc, char *argv[],params_bool_t *paramsBool,params_place_t *paramsPlace,select_row_t *selectRows);
void fget(params_bool_t *paramsBool,params_place_t *paramsPlace,select_row_t *selectRows);
int DelCount(char *tabulka,char delim);

//Príkazy na úpravu tabulky
void irow(int row, int row_count, int del,  bool acol_true,char delim);
void arow(int del,char delim[]);
void drow(char *tabulka, int drow, int current_row);
void drows(char *tabulka, int drow1, int drow2, int row);
void icol(char *tabulka, int colm, char delim);
void dcol(char *tabulka, int colm,char delim);
void dcols(char *tabulka, int colm1,int colm2, char delim);
//Príkazy na zpracovanie dát
void cset(char *tabulka,int cset_colm, char cset_char[VELKOST_BUNKY], char delim);
void my_tolower(char *tabulka,int tl_colm, char delim);
void my_toupper(char *tabulka,int tl_colm, char delim);
void my_round(char *tabulka,int r_colm, char delim);
void my_int(char *tabulka,int int_colm, char delim);
void copy(char *tabulka,int whereCopy, int toCopy, char delim);
void swap(char *tabulka,int firstSwap, int secondSwap, char delim);
void move(char *tabulka,int firstMove, int secondMove, char delim);
//Selekcia riadkov
bool rows(int startRows, int endRows, int actualRow);
bool beginswith(char *tabulka,int BWColm,char BWChar[VELKOST_BUNKY],char delim);
bool contains(char *tabulka,int CTColm,char CTChar[VELKOST_BUNKY],char delim);

int main(int argc, char *argv[])
{
    if(argc == 0){
        fprintf(stderr,"\nChyba vstupu, nedefinovane spravanie.");
        return 1;
    }
    params_bool_t paramsBool;
    params_place_t paramsPlace;
    select_row_t selectRows;
    params_bool_init(&paramsBool);
    params_place(argc, argv, &paramsBool,&paramsPlace,&selectRows);
    fget(&paramsBool,&paramsPlace,&selectRows);
    return 0;
}

void params_place(int argc, char *argv[],params_bool_t *paramsBool,params_place_t *paramsPlace,select_row_t *selectRows){
    char **trash = NULL;
    char mainDelim = ' ';

    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            paramsBool->delim_found = true;
            strcpy(paramsPlace->delim, argv[i + 1]);
        } else if (strcmp(argv[i], "irow") == 0) {
            paramsBool->irow_true = true;
            paramsPlace->irow_row = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "arow") == 0) {
            paramsBool->arow_true = true;
        } else if (strcmp(argv[i], "drow") == 0) {
            paramsBool->drow_true = true;
            paramsPlace->drow_row = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "drows") == 0) {
            paramsBool->drows_true = true;
            paramsPlace->drows_start = strtol(argv[i + 1], trash,10) - 1;
            paramsPlace->drows_end = strtol(argv[i + 2], trash,10) - 1;
        } else if (strcmp(argv[i], "icol") == 0) {
            paramsBool->icol_true = true;
            paramsPlace->icol_colm = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "acol") == 0) {
            paramsBool->acol_true = true;
        } else if (strcmp(argv[i], "dcol") == 0) {
            paramsBool->dcol_true = true;
            paramsPlace->dcol_colm = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "dcols") == 0) {
            paramsBool->dcols_true = true;
            paramsPlace->dcols_colm1 = strtol(argv[i + 1], trash,10) - 1;
            paramsPlace->dcols_colm2 = strtol(argv[i + 2], trash,10) - 1;
        } else if (strcmp(argv[i], "cset") == 0) {
            paramsBool->cset_true = true;
            paramsPlace->cset_colm = strtol(argv[i + 1], trash,10) - 1;
            strcpy(paramsPlace->cset_char, argv[i + 2]);
        } else if (strcmp(argv[i], "tolower") == 0) {
            paramsBool->tl_true = true;
            paramsPlace->tl_colm = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "toupper") == 0) {
            paramsBool->tp_true = true;
            paramsPlace->tp_colm = strtol(argv[i + 1], trash,10) - 1;
        } else if (strcmp(argv[i], "round") == 0) {
            paramsBool->r_true = true;
            paramsPlace->r_colm = strtol(argv[i + 1], trash,10) - 1;
        }else if (strcmp(argv[i], "int") == 0) {
            paramsBool->int_true = true;
            paramsPlace->int_colm = strtol(argv[i + 1], trash,10) - 1;
        }else if (strcmp(argv[i], "copy") == 0) {
            paramsBool->copy_true = true;
            paramsPlace->whereCopy = strtol(argv[i + 1], trash,10)-1;
            paramsPlace->toCopy = strtol(argv[i + 2], trash,10)-1;
        }else if (strcmp(argv[i], "swap") == 0) {
            paramsBool->swap_true = true;
            paramsPlace->firstSwap = strtol(argv[i + 1], trash,10) - 1;
            paramsPlace->secondSwap = strtol(argv[i + 2], trash,10) - 1;
        }else if (strcmp(argv[i], "move") == 0) {
            paramsBool->move_true = true;
            paramsPlace->firstMove = strtol(argv[i + 1], trash,10) - 1;
            paramsPlace->secondMove = strtol(argv[i + 2], trash,10) - 1;
        }else if (strcmp(argv[i], "rows") == 0) {
            paramsBool->rows_true = true;
            selectRows->startRows= strtol(argv[i + 1], trash,10);
            selectRows->endRows = strtol(argv[i + 2], trash,10);
        }else if (strcmp(argv[i], "beginswith") == 0) {
            paramsBool->beginswith_true = true;
            selectRows->BWColm = strtol(argv[i + 1], trash,10);
            strcpy(selectRows->BWChar, argv[i + 2]);
        }else if (strcmp(argv[i], "contains") == 0) {
            paramsBool->contains_true = true;
            selectRows->CTColm = strtol(argv[i + 1], trash,10);
            strcpy(selectRows->CTChar, argv[i + 2]);
        }
    }
    if(paramsBool->delim_found == false){
        strcpy(paramsPlace->delim, &mainDelim);
    }
}
void params_bool_init(params_bool_t *params){
    params->delim_found = false;
    params->irow_true = false;
    params->arow_true = false;
    params->drow_true = false;
    params->drows_true = false;
    params->icol_true = false;
    params->acol_true = false;
    params->dcol_true = false;
    params->dcols_true = false;
    params->cset_true = false;
    params->tl_true = false;
    params->tp_true = false;
    params->r_true = false;
    params->int_true = false;
    params->copy_true = false;
    params->once = false;
    params->swap_true = false;
    params->move_true = false;
    params->rows_true = false;
    params->beginswith_true = false;
    params->contains_true = false;
}
void fget(params_bool_t *paramsBool,params_place_t *paramsPlace,select_row_t *selectRows){

    char tabulka[DLZKA_RIADKA];
    bool doRow = false;
    paramsPlace->first_del = 0;
    paramsPlace->del = 0;

    while(fgets(tabulka, DLZKA_RIADKA, stdin) != NULL){
            if (paramsPlace->rows_num == 0) {
                paramsPlace->first_del = DelCount(tabulka, paramsPlace->delim[0]);
            } else {
                paramsPlace->del = DelCount(tabulka, paramsPlace->delim[0]);
            }
            if(paramsPlace->first_del == 0){
                fprintf(stderr, "\nERROR: No delim found in row %d.",paramsPlace->rows_num+1);
                return;
            }
            if (paramsPlace->del > paramsPlace->first_del) {
                fprintf(stderr, "\nERROR: Too many columns in row %d.", paramsPlace->rows_num);
                return;
            }

            int char_count = (int)strlen(tabulka);
            if(paramsBool->acol_true == true){
                tabulka[char_count-1] = paramsPlace->delim[0];
            }else{
                tabulka[char_count-1] = ' ';
            }
            tabulka[char_count+1] = '\0';
            if(paramsBool->rows_true == true){doRow = rows(selectRows->startRows,selectRows->endRows,paramsPlace->rows_num);
            }else if(paramsBool->beginswith_true == true){doRow = beginswith(tabulka,selectRows->BWColm,selectRows->BWChar,paramsPlace->delim[0]);
            }else if(paramsBool->contains_true == true){doRow = contains(tabulka,selectRows->CTColm,selectRows->CTChar,paramsPlace->delim[0]);
            }else{doRow = true;}
            if(doRow == true) {
                if (paramsBool->irow_true == true) {irow(paramsPlace->irow_row, paramsPlace->rows_num, paramsPlace->first_del, paramsBool->acol_true,paramsPlace->delim[0]);}
                if (paramsBool->drow_true == true) { drow(tabulka, paramsPlace->drow_row, paramsPlace->rows_num); }
                if (paramsBool->drows_true == true) {drows(tabulka, paramsPlace->drows_start, paramsPlace->drows_end, paramsPlace->rows_num);}
                if (paramsBool->icol_true == true) { icol(tabulka, paramsPlace->icol_colm, paramsPlace->delim[0]); }
                if (paramsBool->dcol_true == true) { dcol(tabulka, paramsPlace->dcol_colm, paramsPlace->delim[0]); }
                if (paramsBool->dcols_true == true) {dcols(tabulka, paramsPlace->dcols_colm1, paramsPlace->dcols_colm2, paramsPlace->delim[0]);}
                if (paramsBool->cset_true == true) {cset(tabulka, paramsPlace->cset_colm, paramsPlace->cset_char, paramsPlace->delim[0]);}
                if (paramsBool->tl_true == true) { my_tolower(tabulka, paramsPlace->tl_colm, paramsPlace->delim[0]); }
                if (paramsBool->tp_true == true) { my_toupper(tabulka, paramsPlace->tp_colm, paramsPlace->delim[0]); }
                if (paramsBool->r_true == true) { my_round(tabulka, paramsPlace->r_colm, paramsPlace->delim[0]); }
                if (paramsBool->int_true == true) { my_int(tabulka, paramsPlace->int_colm, paramsPlace->delim[0]); }
                if (paramsBool->copy_true == true) {copy(tabulka, paramsPlace->whereCopy, paramsPlace->toCopy, paramsPlace->delim[0]);}
                if (paramsBool->swap_true == true) {swap(tabulka, paramsPlace->firstSwap, paramsPlace->secondSwap, paramsPlace->delim[0]);}
                if (paramsBool->move_true == true) {move(tabulka, paramsPlace->firstMove, paramsPlace->secondMove, paramsPlace->delim[0]);}
            }
            if (strlen(tabulka) > 1 && paramsBool->drow_true == true){printf("%s\n",tabulka);
            }else if (strlen(tabulka) > 1 && paramsBool->drows_true == true){printf("%s\n",tabulka);
            }else if(paramsBool->drow_true == false && paramsBool->drows_true == false){printf("%s\n",tabulka);}

            paramsPlace->rows_num++;
    }
        if (paramsBool->arow_true == true) {
            if (paramsBool->acol_true) {
                paramsPlace->first_del++;
            }
            arow(paramsPlace->first_del, paramsPlace->delim);
        }
}
int DelCount(char *tabulka,char delim){
    int delim_count = 0;
    for(int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
        }
    }
    return delim_count;
}
void irow(int row, int row_count, int del,  bool acol_true,char delim){
    if(row_count == row){
        if (acol_true == true){printf("\n");}
        for(int i = 0; i < (del) ; i++){
            printf("%s",&delim);
        }
        if (acol_true == false){printf("\n");}
    }
}
void arow(int del,char delim[]){
    for(int i = 0; i < (del) ; i++){
        printf("%s",delim);
    }
}
void drow(char *tabulka, int drow, int current_row){
    if(current_row == drow) {
        strcpy(tabulka, "");
    }
}
void drows(char *tabulka, int drow1, int drow2, int row){
    if(row >= drow1 && row <= drow2) {
        strcpy(tabulka, "");
    }
}
void icol(char *tabulka, int colm, char delim){
    int delim_count = 0;
    int char_count = 0;
    int position = 0;
    char tabulkavys[DLZKA_RIADKA];
    char *strB = ":";
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }
        if(delim_count == (colm-1)){
            position = char_count;
        }
    }
    strncpy(tabulkavys,tabulka,position);
    tabulkavys[position] = '\0';
    strcat(tabulkavys,strB);
    strcat(tabulkavys,tabulka + position);
    strcpy(&tabulka[0],tabulkavys);
}
void dcol(char *tabulka, int colm,char delim){
    int delim_count = 0;
    int char_count = 0;
    int position1 = 0;
    int position2 = 0;
    int del;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }

        if(tabulka[i+1] != '\n') {
            if (delim_count == (colm - 1)) {
                position1 = char_count;
            } else if (delim_count == colm) {
                position2 = char_count;
            }
        }
    }
    del = position2 - position1;
    if(colm == 0){
        strcpy(&tabulka[position1],&tabulka[position1+del+1]);
    }else {
        strcpy(&tabulka[position1], &tabulka[position1+del]);
    }
}
void dcols(char *tabulka, int colm1,int colm2, char delim){
    int delim_count = 0;
    int char_count = 0;
    int position1 = 0;
    int position2 = 0;
    int del;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }
        if(tabulka[i+1] != '\n') {
            if (delim_count == (colm1- 1)) {
                position1 = char_count;
            } else if (delim_count == (colm2)) {
                position2 = char_count;
            }
        }
    }
    del = position2 - position1;
    if(colm1 == 0){
        strcpy(&tabulka[position1],&tabulka[position1+del+1]);
    }else{
        strcpy(&tabulka[position1],&tabulka[position1+del]);
    }
}
void cset(char *tabulka,int cset_colm, char cset_char[VELKOST_BUNKY], char delim){
    int delim_count = 0;
    int positionStart = 0;
    int positionEnd = 0;
    int end;
    char buffer[DLZKA_RIADKA];
    bool once1 = false;
    bool once2 = false;
    int j = 0;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
        }
        if(delim_count == cset_colm ){
            if(tabulka[i+1] != '\n'){
                if( once1 == false){
                    positionStart = i + 1;
                    once1 = true;
                }
            }
            j++;
        }if(delim_count == cset_colm + 1){

            if( once2 == false){
                positionEnd = i;
                once2 = true;
            }
        }
        end = i;
    }
    if(delim_count == cset_colm){
            positionEnd = end;
    }
    if(cset_colm == 0){
        positionStart = 0;
    }
    if(cset_colm <= delim_count){
        strcpy(buffer, &tabulka[positionEnd]);
        strcpy(&tabulka[positionStart], cset_char);
        strcpy(&tabulka[positionStart + strlen(cset_char)], buffer);
    }
    //printf("|%d|,|%d|",positionStart,positionEnd);

}
void my_tolower(char *tabulka,int tl_colm, char delim){
    int delim_count = 0;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
        }
        if(delim_count == tl_colm){
            tabulka[i+1] = (char)tolower(tabulka[i+1]);
        }
    }
}
void my_toupper(char *tabulka,int tl_colm, char delim){
    int delim_count = 0;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
        }
        if(delim_count == tl_colm){
            tabulka[i+1] = (char)toupper(tabulka[i+1]);
        }
    }
}
void my_round(char *tabulka,int r_colm, char delim){
    int delim_count = 0;
    int j = 0;
    int positionStart;
    float medzivypocet;
    int positionEnd;
    float cislo;
    int cislo_vypis;
    char cislo_char[DLZKA_RIADKA];
    char buffer[DLZKA_RIADKA];
    char cislo_printf[sizeof(cislo_vypis)];
    char **bordel = NULL;
    bool once1 = false;
    bool once2 = false;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
        }
        if(delim_count == r_colm ){
            if(tabulka[i+1] != '\n'){
                cislo_char[j] = tabulka[i+1];
                if( once1 == false){
                    positionStart = i + 1;
                    once1 = true;
                }
            }
            j++;
        }if(delim_count == r_colm + 1){
            if( once2 == false){
                cislo_char[j-1] = '\0';
                positionEnd = i;
                once2 = true;
            }
        }
    }
    cislo = strtof(cislo_char, bordel);
    medzivypocet = cislo - (int)cislo;
    if(medzivypocet >  0.5){
        cislo_vypis = (int)cislo + 1;
    }else{
        cislo_vypis = (int)cislo;
    }
    sprintf(cislo_printf, "%d",cislo_vypis);
    if((float)cislo_vypis != cislo) {
        int dlzkaPrintf = (int)strlen(cislo_printf);
        strcpy(buffer, &tabulka[positionEnd]);
        strcpy(&tabulka[positionStart], cislo_printf);
        strcpy(&tabulka[positionStart + dlzkaPrintf], buffer);
    }
}
void my_int(char *tabulka,int int_colm, char delim){
    int delim_count = 0;
    int j = 0;
    int positionStart;
    int positionEnd;
    float cislo;
    int cislo_vypis;
    char cislo_char[DLZKA_RIADKA];
    char buffer[DLZKA_RIADKA];
    char cislo_printf[sizeof(cislo_vypis)];
    char **bordel = NULL;
    bool once1 = false;
    bool once2 = false;
    for(int i = 0; i < (int)strlen(tabulka); i++){
        if(tabulka[i] == delim){
            delim_count++;
        }
        if(delim_count == int_colm ){
            if(tabulka[i+1] != '\n'){
                cislo_char[j] = tabulka[i+1];
                if( once1 == false){
                    positionStart = i + 1;
                    once1 = true;
                }
            }
            j++;
        }if(delim_count == int_colm + 1){
            if( once2 == false){
                cislo_char[j-1] = '\0';
                positionEnd = i;
                once2 = true;
            }
        }
    }
    cislo = strtof(cislo_char, bordel);
    cislo_vypis = (int)cislo;
    sprintf(cislo_printf, "%d",cislo_vypis);
    if((float)cislo_vypis != cislo) {
        int dlzkaPrintf = (int)strlen(cislo_printf);
        strcpy(buffer, &tabulka[positionEnd]);
        strcpy(&tabulka[positionStart], cislo_printf);
        strcpy(&tabulka[positionStart + dlzkaPrintf], buffer);
    }
}
void copy(char *tabulka,int whereCopy, int toCopy, char delim) {
    int delim_count = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int char_count = 0;
    int positionEndFirst = 0;
    int positionStartSecond = (int)strlen(tabulka);
    int positionEndSecond = 0;
    char copy_char1[VELKOST_BUNKY];
    char between[DLZKA_RIADKA];
    char buffer[DLZKA_RIADKA];
    bool once21 = false;
    bool once12 = false;
    bool once22 = false;

    for (int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }
        if (delim_count == whereCopy) {
            if (tabulka[i + 1] != '\n') {
                if(whereCopy == 0){
                    copy_char1[j] = tabulka[i];
                }else {
                    copy_char1[j] = tabulka[i + 1];
                }
            }
            j++;
        }
        if (delim_count == whereCopy+1) {
            if (once21 == false) {
                if(whereCopy == 0){
                    copy_char1[j] = '\0';
                }else{
                    copy_char1[j-1] = '\0';
                }
                positionEndFirst = i + 1;
                once21 = true;
            }
        }
        if (delim_count == toCopy) {
            if (tabulka[i + 1] != '\n') {
                if (once12 == false) {
                    positionStartSecond = i + 1;
                    once12 = true;
                }
            }
            k++;
        }
        if (delim_count == toCopy+1) {
            if (once22 == false) {
                positionEndSecond = i;
                once22 = true;
            }
        }
        if(once21 == true){
            if(positionEndFirst+1 <= char_count && char_count <= positionStartSecond){
                between[l] = tabulka[i];
                l++;
            }
            if (char_count == positionStartSecond){
                between[l] = '\0';
            }
        }
    }
    if(toCopy <= delim_count) {
        int dlzka_char = (int) strlen(copy_char1);
        int dlzka_between = (int) strlen(between);
        if (toCopy + 1 > delim_count) {
            positionEndSecond = char_count;
        }
        if (positionEndFirst == positionStartSecond) {
            strcpy(buffer, &tabulka[positionEndSecond]);
            strcpy(&tabulka[positionEndFirst], copy_char1);
            strcpy(&tabulka[positionEndFirst + dlzka_char], buffer);
        } else {
            strcpy(buffer, &tabulka[positionEndSecond]);
            strcpy(&tabulka[positionEndFirst], between);
            strcpy(&tabulka[positionEndFirst + dlzka_between], copy_char1);
            strcpy(&tabulka[positionEndFirst + dlzka_between + dlzka_char], buffer);
        }
    }
}
void swap(char *tabulka,int firstSwap, int secondSwap, char delim){
    int delim_count = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int char_count = 0;
    int positionStartFirst;
    int positionEndFirst;
    int positionStartSecond;
    int positionEndSecond;
    char copy_char1[VELKOST_BUNKY];
    char copy_char2[VELKOST_BUNKY];
    char between[DLZKA_RIADKA];
    char buffer[DLZKA_RIADKA];
    bool once11 = false;
    bool once21 = false;
    bool once12 = false;
    bool once22 = false;

    for (int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }
        if (delim_count == firstSwap) {
            if (tabulka[i + 1] != '\n') {
                if(firstSwap == 0){
                    copy_char1[j] = tabulka[i];
                }else {
                    copy_char1[j] = tabulka[i + 1];
                }
                if (once11 == false) {
                    positionStartFirst = i + 1;
                    once11 = true;
                }
            }
            j++;
        }
        if (delim_count == firstSwap + 1) {
            if (once21 == false) {
                if(firstSwap == 0){
                    copy_char1[j] = '\0';
                }else{
                    copy_char1[j-1] = '\0';
                }
                positionEndFirst = i + 1;
                once21 = true;
            }
        }
        if (delim_count == secondSwap) {
            if (tabulka[i + 1] != '\n') {
                copy_char2[k] = tabulka[i + 1];
                if (once12 == false) {
                    positionStartSecond = i + 1;
                    once12 = true;
                }
            }
            k++;
        }
        if (delim_count == secondSwap + 1) {
            if (once22 == false) {
                copy_char2[k] = '\0';
                positionEndSecond = i;
                once22 = true;
            }
        } else {
            positionEndSecond = i;
        }
        if(positionEndFirst < char_count && char_count < positionStartSecond){
            between[l] = tabulka[i];
            l++;
        }else if (char_count == positionStartSecond){
            between[l] = '\0';
        }
    }
    if(secondSwap <= delim_count) {
        int dlzkaPrintfFirst = (int)strlen(copy_char1);
        int dlzkaPrintfSecond = (int)strlen(copy_char2);
        int dlzkaBetween = (int)strlen(between);
        if (copy_char2[dlzkaPrintfSecond - 1] == ' ') {
            copy_char2[dlzkaPrintfSecond - 1] = delim;
            copy_char2[dlzkaPrintfSecond] = '\0';
        }
        if (firstSwap == 0 && positionEndFirst == positionStartSecond) {
            positionStartFirst = 0;
            positionEndSecond = dlzkaPrintfFirst + dlzkaPrintfSecond;
        } else {
            positionStartFirst = 0;
            positionEndSecond = dlzkaPrintfFirst + dlzkaPrintfSecond + dlzkaBetween + 1;
        }
        if (positionEndFirst == positionStartSecond) {
            strcpy(buffer, &tabulka[positionEndSecond]);
            strcpy(&tabulka[positionStartFirst], copy_char2);
            tabulka[positionStartFirst + dlzkaPrintfSecond] = delim;
            strcpy(&tabulka[positionStartFirst + dlzkaPrintfSecond], copy_char1);
            strcpy(&tabulka[positionStartFirst + dlzkaPrintfFirst + dlzkaPrintfSecond], buffer);

        } else {
            //printf("|%d|",positionEndSecond);
            strcpy(buffer, &tabulka[positionEndSecond]);
            strcpy(&tabulka[positionStartFirst], copy_char2);
            strcpy(&tabulka[positionStartFirst + dlzkaPrintfSecond], between);
            tabulka[positionStartFirst + dlzkaPrintfSecond + dlzkaBetween] = delim;
            strcpy(&tabulka[positionStartFirst + dlzkaPrintfSecond + dlzkaBetween + 1], copy_char1);
            strcpy(&tabulka[positionStartFirst + dlzkaPrintfFirst + dlzkaBetween + dlzkaPrintfSecond + 1], buffer);
        }
    }
}
void move(char *tabulka,int firstMove, int secondMove, char delim){
    int delim_count = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int char_count = 0;
    int positionStartFirst;
    int positionEndFirst;
    int positionStartSecond;
    int positionEndSecond;
    char move_char1[VELKOST_BUNKY];
    char move_char2[VELKOST_BUNKY];
    char between[DLZKA_RIADKA] = " ";
    char buffer[DLZKA_RIADKA];
    bool once11 = false;
    bool once21 = false;
    bool once12 = false;
    bool once22 = false;

    for (int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
            char_count++;
        }else{
            char_count++;
        }
        if (delim_count == firstMove) {
            if (tabulka[i + 1] != '\n') {
                if(firstMove == 0){
                    move_char1[j] = tabulka[i];
                }else {
                    move_char1[j] = tabulka[i + 1];
                }
                if (once11 == false) {
                    positionStartFirst = i + 1;
                    once11 = true;
                }
            }
            j++;
        }
        if (delim_count == firstMove + 1) {
            if (once21 == false) {
                if(firstMove == 0){
                    move_char1[j-1] = '\0';
                }else{
                    move_char1[j] = '\0';
                }
                positionEndFirst = i + 1;
                once21 = true;
            }
        }else {
            positionEndFirst = i;
        }
        if (delim_count == secondMove) {
            if (tabulka[i + 1] != '\n') {
                if(secondMove == 0){
                    move_char2[k] = tabulka[i];
                }else{
                    move_char2[k] = tabulka[i+1];
                }
                if (once12 == false) {
                    positionStartSecond = i + 1;
                    once12 = true;
                }
            }
            k++;
        }
        if (delim_count == secondMove + 1) {
            if (once22 == false) {
                if(secondMove == 0){
                    //move_char2[k] = ':';
                    move_char2[k] = '\0';
                }else{
                    move_char2[k-1] = '\0';
                }
                positionEndSecond = i;
                once22 = true;
            }
        }
        if(positionEndSecond < char_count && char_count < positionStartFirst){
            between[l] = tabulka[i+1];
            l++;
        }else if (char_count == positionStartSecond){
            between[l] = '\0';
        }
    }
    //printf("|%d|",positionEndFirst);
    int dlzkaPrintfFirst = (int)strlen(move_char1);
    int dlzkaPrintfSecond = (int)strlen(move_char2);
    int dlzkaBetween = (int)strlen(between);
    if (move_char1[dlzkaPrintfFirst - 1] == ' ') {
        move_char1[dlzkaPrintfFirst - 1] = delim;
        move_char1[dlzkaPrintfFirst] = '\0';
    }
    if (secondMove == 0) {
        positionStartSecond = 0;
        //positionEndFirst = dlzkaPrintfFirst + dlzkaPrintfSecond;
    }
    if(firstMove <= delim_count) {
        if((firstMove - 1) == secondMove ) {
            strcpy(buffer, &tabulka[positionEndFirst]);
            strcpy(&tabulka[positionStartSecond], move_char1);
            if (strlen(buffer) > 2 && secondMove != 0) {
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst], move_char2);
                tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond] = delim;
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond + 1], buffer);
            } else {
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst], move_char2);
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond], buffer);
            }
        }else{
            //printf("|%d|",positionEndFirst);
            strcpy(buffer, &tabulka[positionEndFirst]);
            strcpy(&tabulka[positionStartSecond], move_char1);
            strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst],between);
            if (strlen(buffer) > 2) {
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst+ dlzkaBetween], move_char2);
                tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond + dlzkaBetween] = delim;
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond + dlzkaBetween+1], buffer);
            } else {
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst+dlzkaBetween], move_char2);
                strcpy(&tabulka[positionStartSecond + dlzkaPrintfFirst + dlzkaPrintfSecond + dlzkaBetween], buffer);
            }

        }
    }
}
bool rows(int startRows, int endRows, int actualRow){
    if(endRows != 0) {
        if (actualRow >= startRows && actualRow <= endRows) {
            return true;
        } else {
            return false;
        }
    }else{
        if (actualRow >= startRows) {
            return true;
        } else {
            return false;
        }
    }
}
bool beginswith(char *tabulka,int columnBW,char BWChar[VELKOST_BUNKY],char delim){
    int delim_count = 0;
    int j = 0;
    char bunka[VELKOST_BUNKY];
    bool once;
    for (int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
        }
        if (delim_count == columnBW-1) {
            if (tabulka[i + 1] != '\n') {
                bunka[j] = tabulka[i + 1];
            }
            j++;
        }
        if (delim_count == columnBW) {
            if (once == false) {
                bunka[j - 1] = '\0';
                once = true;
            }
        }
    }
    bunka[strlen(BWChar)]= '\0';
    if(strstr(bunka,BWChar)!= NULL){
        return true;
    }else{
        return false;
    }

}
bool contains(char *tabulka,int CTColm,char CTChar[VELKOST_BUNKY],char delim){
    int delim_count = 0;
    int j = 0;
    char bunka[VELKOST_BUNKY];
    bool once;
    for (int i = 0; i < (int)strlen(tabulka); i++) {
        if (tabulka[i] == delim) {
            delim_count++;
        }
        if (delim_count == CTColm - 1) {
            if (tabulka[i + 1] != '\n') {
                bunka[j] = tabulka[i + 1];
            }
            j++;
        }
        if (delim_count == CTColm) {
            if (once == false) {
                bunka[j - 1] = '\0';
                once = true;
            }
        }
    }
    if(strstr(bunka,CTChar)!= NULL){
        return true;
    }else{
        return false;
    }
}
