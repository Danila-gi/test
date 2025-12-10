#include <bdd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#define N 9
#define M 4
#define LOG_N 4
#define IS_GLUING true

std::ofstream out;

void fun(char* varset, int size);

// Свойства
// k = 0
const std::vector<std::string> M_colors = {"красные", "синие", "белые", "оранжевые", "черные", "фиолетовые", "голубые", "зеленые", "желтые"};
// k = 1
const std::vector<std::string> M_drinks = {"вино", "пиво", "пепси", "колу", "воду", "лимонад", "тархун", "коктель", "молоко"};
// k = 2
const std::vector<std::string> M_brends = {"demix", "nike", "puma", "adidas", "under armour", "boxraw", "dali", "EA7", "FN"};
// k = 3
const std::vector<std::string> M_languages = {"русский", "английский", "португальский", "испанский", "китайский", "французский",
                                                "казахский", "японский", "корейский"};

void limitN1(bdd &result, const bdd (&p)[M][N][N]) {
    // 7 штук ограничений n1
  
    // Игрок под номером 3 носит красные бутсы
    result &= p[0][3][0];

    // Игрок под номером 5 пьет после игры пиво
    result &= p[1][5][1];

    // Игрок под номером 1 говорит на английском
    result &= p[3][1][1];

    // Игрок под нмоером 6 после игры пьет лимонад
    result &= p[1][6][5];

    // Игрок под номером 0 носит черные бутсы
    result &= p[0][0][4];

    // Игрок под номером 0 говорит на русском
    result &= p[3][0][0];

    // Игрок под номером 7 заключил контракт с dali
    result &= p[2][7][6];
}

void limitN2(bdd &result, const bdd (&p)[M][N][N]) {
    // 5 штук ограничений n2
    for (unsigned i = 0; i < N; i++) {
        // Любитель тархуна носит зеленые бутсы
        result &= bdd_apply(p[0][i][7], p[1][i][6], bddop_biimp);

        // Любитель молока носит оранжевые бутсы
        result &= bdd_apply(p[1][i][8], p[0][i][3], bddop_biimp);

        // Тот, кто носит голубые бутсы заключил контракт с EA7
        result &= bdd_apply(p[0][i][6], p[2][i][7], bddop_biimp);

        // Любитель коктеля говорит на португальском
        result &= bdd_apply(p[3][i][2], p[1][i][7], bddop_biimp);

        // Любитель лимонада заключил контракт с boxraw
        result &= bdd_apply(p[2][i][5], p[1][i][5], bddop_biimp);
    }
}

void limitN3(bdd &result, const bdd (&p)[M][N][N]) {
    // 5 штук ограничений n3
    // Соседи: сверху-слева, снизу-слева
    const int squareSize = (int)std::sqrt(N);
    for (unsigned i = 0; i < N; i++) {
        if (i >= squareSize) {
            if (i % squareSize != 0){  
                // Кореец имеет соседа сверху-слева, который сотрудничает с puma
                result &= bdd_apply(p[2][i - squareSize - 1][2], p[3][i][8], bddop_biimp);

                // Китаец имеет соседа сверху-слева, который пьет пепси
                result &= bdd_apply(p[1][i - squareSize - 1][2], p[3][i][4], bddop_biimp);  
            }
            else if (IS_GLUING){
                result &= bdd_apply(p[2][i - 1][2], p[3][i][8], bddop_biimp);
                result &= bdd_apply(p[1][i - 1][2], p[3][i][4], bddop_biimp);
            }
            else {
                result &= !p[3][i][8];
                result &= !p[3][i][4];
                result &= !p[2][i - 1][2];
                result &= !p[1][i - 1][2];
            }
        }

        else {
            result &= !p[3][i][8];
            result &= !p[3][i][4];
            result &= !p[2][N - squareSize + i][2];
            result &= !p[1][N - squareSize + i][2];
        }

        if (i < N - squareSize) { 
            if (i % squareSize != 0){
                // Владелец желтых бутс имеет соседа снизу-слева, который пьет колу          
                result &= bdd_apply(p[1][i + squareSize - 1][3], p[0][i][8], bddop_biimp);

                // Владелец фиолетовых бутс имеет соседа снизу-слева, который сотрудничает с boxraw
                result &= bdd_apply(p[2][i + squareSize - 1][5], p[0][i][5], bddop_biimp);

                // Партнер nike имеет соседа снизу-слева, который носит фиолетовые бутсы    
                result &= bdd_apply(p[0][i + squareSize - 1][5], p[2][i][1], bddop_biimp);
            }
            else if (IS_GLUING){
                result &= bdd_apply(p[1][i + 2 * squareSize - 1][3], p[0][i][8], bddop_biimp);
                result &= bdd_apply(p[2][i + 2 * squareSize - 1][5], p[0][i][5], bddop_biimp);
                result &= bdd_apply(p[0][i + 2 * squareSize - 1][5], p[2][i][1], bddop_biimp);
            }
            else {
                result &= !p[0][i][8];
                result &= !p[0][i][5];
                result &= !p[2][i][1];
                result &= !p[1][i + 2 * squareSize - 1][3];
                result &= !p[2][i + 2 * squareSize - 1][5];
                result &= !p[0][i + 2 * squareSize - 1][5];
            }
        }
        else {
            result &= !p[0][i][5];
            result &= !p[0][i][8];
            result &= !p[2][i][1];
            result &= !p[1][i - N + squareSize][3];
            result &= !p[2][i - N + squareSize][5];
            result &= !p[0][i - N + squareSize][5];
        }
    }
}

void limitN4(bdd &result, const bdd (&p)[M][N][N]) {
    // 4 штуки ограничений n4
    // Соседи: сверху-слева, снизу-слева
    const int squareSize = (int)std::sqrt(N);
  
    for (unsigned i = 0; i < N; i++) {
        // Владелец голубых бутс имеет соседа француза
        bdd eq_1 = bddfalse;
        // Владелец фиолетовых бутс имеет соседа японца
        bdd eq_2 = bddfalse;
        // Владелец голубых бутс имеет соседа с желтыми бутсами
        bdd eq_3 = bddfalse;
        // Испанец имеет соседа с оранжевыми бутсами
        bdd eq_4 = bddfalse;
    
        if ((i < N - squareSize) && (i % squareSize != 0)) {            
            eq_1 |= bdd_apply(p[0][i][6], p[3][i + squareSize - 1][5], bddop_biimp);
            
            eq_2 |= bdd_apply(p[0][i][5], p[3][i + squareSize - 1][7], bddop_biimp);
            
            eq_3 |= bdd_apply(p[0][i][6], p[0][i + squareSize - 1][8], bddop_biimp);

            eq_4 |= bdd_apply(p[3][i][3], p[0][i + squareSize - 1][3], bddop_biimp);
        }
    
        if ((i >= squareSize) && (i % squareSize != 0)) {            
            eq_1 |= bdd_apply(p[0][i][6], p[3][i - squareSize - 1][5], bddop_biimp);
            
            eq_2 |= bdd_apply(p[0][i][5], p[3][i - squareSize - 1][7], bddop_biimp);
            
            eq_3 |= bdd_apply(p[0][i][6], p[0][i - squareSize - 1][8], bddop_biimp);

            eq_4 |= bdd_apply(p[3][i][3], p[0][i - squareSize - 1][3], bddop_biimp);
        }
        bdd eq_all = eq_1 & eq_2 & eq_3 & eq_4;

        if (eq_all != bddfalse){
            result &= eq_all;
        }
    
        if (IS_GLUING && (eq_all == bddfalse)) {
            eq_1 = bddfalse;
            eq_2 = bddfalse;
            eq_3 = bddfalse;
            eq_4 = bddfalse;
            if (i < N - squareSize) {
                eq_1 |= bdd_apply(p[0][i][6], p[3][i + 2 * squareSize - 1][5], bddop_biimp);
            
                eq_2 |= bdd_apply(p[0][i][5], p[3][i + 2 * squareSize - 1][7], bddop_biimp);
                
                eq_3 |= bdd_apply(p[0][i][6], p[0][i + 2 * squareSize - 1][8], bddop_biimp);

                eq_4 |= bdd_apply(p[3][i][3], p[0][i + 2 * squareSize - 1][3], bddop_biimp);
            }
            if (i >= squareSize) {
                eq_1 |= bdd_apply(p[0][i][6], p[3][i - 1][5], bddop_biimp);
            
                eq_2 |= bdd_apply(p[0][i][5], p[3][i - 1][7], bddop_biimp);
                
                eq_3 |= bdd_apply(p[0][i][6], p[0][i - 1][8], bddop_biimp);

                eq_4 |= bdd_apply(p[3][i][3], p[0][i - 1][3], bddop_biimp);
            }

            eq_all = eq_1 & eq_2 & eq_3 & eq_4;

            if (eq_all != bddfalse){
                result &= eq_all;
            }
        }
        else if (!IS_GLUING && (eq_all == bddfalse)) {
            result &= !p[0][i][6];
            result &= !p[0][i][5];
            result &= !p[3][i][3];
            if (i < N - squareSize) {
                result &= !p[3][i + 2 * squareSize - 1][5];
                result &= !p[3][i + 2 * squareSize - 1][7];
                result &= !p[0][i + 2 * squareSize - 1][8];
                result &= !p[0][i + 2 * squareSize - 1][3];
            }
            else if (i >= squareSize) {
                result &= !p[3][i - 1][5];
                result &= !p[3][i - 1][7];
                result &= !p[0][i - 1][8];
                result &= !p[0][i - 1][3];
            }
        }
    }
}

void limitUniqOfProperties(bdd &result, const bdd (&p)[M][N][N]) {
    for (unsigned j = 0; j < N; j++) {
        for (unsigned i1 = 0; i1 < N - 1; i1++) {
            for (unsigned i2 = i1 + 1; i2 < N; i2++) {
                for (unsigned k = 0; k < M; k++) {
                    result &= p[k][i1][j] >> !p[k][i2][j];
                }
            }
        }
    }
}

void limitCompletenessOfProperties(bdd &result, const bdd (&p)[M][N][N]) {
    for (unsigned i = 0; i < N; i++) {
        std::vector<bdd> properties(M, bddfalse);
        for (unsigned j = 0; j < N; j++) {
            for (unsigned k = 0; k < M; k++){
                properties[k] |= p[k][i][j];
            }
        }
        for (unsigned k = 0; k < M; k++){
            result &= properties[k];
        }
    }
}

int main(){
    bdd_init(500000000, 2000000);
    bdd_setvarnum(LOG_N * N * M);

    bdd result = bddtrue;
    
    bdd p[M][N][N];
    unsigned I;
    for (unsigned i = 0; i < N; i++){
        for (unsigned j = 0; j < N; j++){
            for (unsigned k = 0; k < M; k++){
                p[k][i][j] = bddtrue;
                for (unsigned t = 0; t < LOG_N; t++){
                    I = LOG_N * M * i + LOG_N * k + t;
                    p[k][i][j] &= (((j >> t) & 1) ? bdd_ithvar((int)I) : bdd_nithvar((int)I));
                }
            }
        }
    }

    limitN1(result, p);
    limitN2(result, p);
    limitN3(result, p);
    limitN4(result, p);
    limitCompletenessOfProperties(result, p);
    limitUniqOfProperties(result, p);

    out.open("out.txt");
    unsigned satcount = (unsigned)bdd_satcount(result);
    out << satcount << " solutions:\n" << std::endl;
    if (satcount){
        bdd_allsat(result, fun);
    }
    out.close();
    
    bdd_done();
    return 0;
}

char var[LOG_N * N * M];

void print()
{
    for (unsigned i = 0; i < N; i++){
        out << i << ": ";
        for (unsigned j = 0; j < M; j++){
            unsigned J = i * M * LOG_N + j * LOG_N;
            unsigned num = 0;
            for (unsigned k = 0; k < LOG_N; k++){
                num += (unsigned)(var[J + k] << k);
            }
            if (j == 0)
                out << std::setw(30) << std::left << M_colors[num];
            if (j == 1)
                out << std::setw(30) << std::left << M_drinks[num]; 
            if (j == 2)
                out << std::setw(30) << std::left << M_brends[num]; 
            if (j == 3)
                out << std::setw(30) << std::left << M_languages[num];
        }
        out << std::endl;
    }
    out << std::endl;
}

void build(char* varset, unsigned n, unsigned I)
{
    if (I == n - 1){
        if (varset[I] >= 0){
            var[I] = varset[I];
            print();
            return;
        }
        var[I] = 0;
        print();
        var[I] = 1;
        print();
        return;
    }
    if (varset[I] >= 0){
        var[I] = varset[I];
        build(varset, n, I + 1);
        return;
    }
    var[I] = 0;
    build(varset, n, I + 1);
    var[I] = 1;
    build(varset, n, I + 1);
}

void fun(char* varset, int size)
{
    build(varset, size, 0);
}