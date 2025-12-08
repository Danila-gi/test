#include <bdd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#define N 9
#define M 4
#define LOG_N 4
#define IS_GLUING false

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
  
    // Игрок под номером 7 носит зеленые бутсы
    result &= p[0][7][7];

    // Игрок под номером 4 носит голубые бутсы
    result &= p[0][4][6];

    // Игрок под номером 0 пьет воду
    result &= p[1][0][4];

    // Игрок под номером 1 носит синие бутсы
    result &= p[0][1][1];

    // Игрок под номером 2 заключил контракт с demix
    result &= p[2][2][0];

    // Игрок под номером 2 говорит на русском
    result &= p[3][2][0];

    // Игрок под номером 1 говорит на английском
    result &= p[3][1][1];

    // Дополнительные ограничения

    //result &= p[1][4][6];

    //result &= p[0][0][2];

    //result &= p[1][2][8];

    //result &= p[3][8][8];

    //result &= p[1][8][7];

    //result &= p[1][8][5];

    //result &= p[3][7][4];

    //result &= p[1][1][3];

    //result &= p[2][0][4];

    //result &= p[0][5][0];
}

void limitN2(bdd &result, const bdd (&p)[M][N][N]) {
    // 5 штук ограничений n2
    for (unsigned i = 0; i < N; i++) {
        // Любитель колы говорит на английском
        result &= bdd_apply(p[1][i][3], p[3][i][1], bddop_biimp);

        // Любитель пива партнер puma
        result &= bdd_apply(p[1][i][1], p[2][i][2], bddop_biimp);

        // Обладатель фиолетовых бутс говорит на испанском
        result &= bdd_apply(p[0][i][5], p[3][i][3], bddop_biimp);

        // Партнер boxraw носит фиолетовые бутсы
        result &= bdd_apply(p[2][i][5], p[0][i][5], bddop_biimp);

        // Англичанин заключил контракт с FN
        result &= bdd_apply(p[3][i][1], p[2][i][8], bddop_biimp);
    }
}

void limitN3(bdd &result, const bdd (&p)[M][N][N]) {
    // 5 штук
    // Соседи: сверху-слева, снизу-слева
    const int squareSize = (int)std::sqrt(N);
    for (unsigned i = 0; i < N; i++) {
        if (!(i < squareSize || i % squareSize == 0)){
            // Партнер puma имеет соседа сверху-слева с красными бутсами
            result &= bdd_apply(p[0][i - squareSize - 1][0], p[2][i][2], bddop_biimp);
            
            // Любитель вина имеет испанского соседа сверху-слева
            result &= bdd_apply(p[3][i - squareSize - 1][3], p[1][i][0], bddop_biimp);
            
            // Партнер nike имеет соседа сверху-слева, говорящего на казахском
            result &= bdd_apply(p[3][i - squareSize - 1][6], p[2][i][1], bddop_biimp);

        } else if (IS_GLUING) {
            int index = -1;
            if (i % squareSize == 0){
                if (i >= squareSize){
                    index = i - 1;
                }
            }
            if (index != -1){
                result &= bdd_apply(p[0][index][0], p[2][i][2], bddop_biimp);
                result &= bdd_apply(p[3][index][3], p[1][i][0], bddop_biimp);
                result &= bdd_apply(p[3][index][6], p[2][i][1], bddop_biimp);
            }
            else {
                std::cout << i << std::endl;
                result &= !p[2][i][2];
                result &= !p[1][i][0];
                result &= !p[2][i][1];
            }
        }
        else {
            result &= !p[2][i][2];
            result &= !p[1][i][0];
            result &= !p[2][i][1];
        }

        if (!(i >= N - squareSize || i % squareSize == 0)){
            // Казах имеет соседа снизу-слева, который любит пепси
            result &= bdd_apply(p[1][i + squareSize - 1][2], p[3][i][6], bddop_biimp);
            
            // Партнер EA7 имеет соседа снизу-слева, который носит фиолетовые бутсы
            result &= bdd_apply(p[0][i + squareSize - 1][5], p[2][i][7], bddop_biimp);
        } else if (IS_GLUING) {
            int index= -1;
            if (i % squareSize == 0){
                if (i < N - squareSize){
                    index = i + squareSize * 2 - 1;
                }
            }
            if (index != -1){
                result &= bdd_apply(p[1][index][2], p[3][i][6], bddop_biimp);
                result &= bdd_apply(p[0][index][5], p[2][i][7], bddop_biimp);
            }
        }
        else {
            result &= !p[3][i][6];
            result &= !p[2][i][7];
        }


    }
}

void limitN4(bdd &result, const bdd (&p)[M][N][N])
{
    // 4 штуки ограничения n4
    // Соседи: сверху-слева, снизу-слева
    const int squareSize = (int)std::sqrt(N);

    for (unsigned i = 0; i < N; i++){
        bdd all_conditions = bddtrue;
        
        // Партнер adidas имеет хотя бы одного соседа с черными бутсами
        bdd eq_1 = bddfalse;

        // Японец имеет хотя бы одного соседа, который заключил контракт с EA7  
        bdd eq_2 = bddfalse;

        // Обладатель фиолетовых бутс имеет хотя бы одного соседа со знаниями французского
        bdd eq_3 = bddfalse;

        // Любитель пива имеет хотя бы одного соседа, который заключил контракт с demix
        bdd eq_4 = bddfalse;
        if (!(i < squareSize || i % squareSize == 0)){
            bdd eq_1_1 = bdd_apply(p[0][i - squareSize - 1][4], p[2][i][3], bddop_biimp);
            eq_1 |= eq_1_1;
            bdd eq_2_1 = bdd_apply(p[2][i - squareSize - 1][7], p[3][i][7], bddop_biimp);
            eq_2 |= eq_2_1;
            bdd eq_3_1 = bdd_apply(p[3][i - squareSize - 1][5], p[0][i][5], bddop_biimp);
            eq_3 |= eq_3_1;
            bdd eq_4_1 = bdd_apply(p[2][i - squareSize - 1][0], p[1][i][1], bddop_biimp);
            eq_4 |= eq_4_1;
        } else if (IS_GLUING) {
            int index = -1;
            if (i % squareSize == 0){
                if (i >= squareSize){
                    index = i - 1;
                }
            }
            if (index != -1){
                bdd eq_1_1 = bdd_apply(p[0][index][4], p[2][i][3], bddop_biimp);
                eq_1 |= eq_1_1;
                bdd eq_2_1 = bdd_apply(p[2][index][7], p[3][i][7], bddop_biimp);
                eq_2 |= eq_2_1;
                bdd eq_3_1 = bdd_apply(p[3][index][5], p[0][i][5], bddop_biimp);
                eq_3 |= eq_3_1;
                bdd eq_4_1 = bdd_apply(p[2][index][0], p[1][i][1], bddop_biimp);
                eq_4 |= eq_4_1;
            }
        }
        if (!(i >= N - squareSize || i % squareSize == 0)){
            bdd eq_1_2 = bdd_apply(p[0][i + squareSize - 1][4], p[2][i][3], bddop_biimp);
            eq_1 |= eq_1_2;
            bdd eq_2_2 = bdd_apply(p[2][i + squareSize - 1][7], p[3][i][7], bddop_biimp);
            eq_2 |= eq_2_2;
            bdd eq_3_2 = bdd_apply(p[3][i + squareSize - 1][5], p[0][i][5], bddop_biimp);
            eq_3 |= eq_3_2;
            bdd eq_4_2 = bdd_apply(p[2][i + squareSize - 1][0], p[1][i][1], bddop_biimp);
            eq_4 |= eq_4_2;
        } else if (IS_GLUING) {
            int index = -1;
            if (i % squareSize == 0){
                if (i < N - squareSize){
                    index = i + squareSize * 2 - 1;
                }
            }
            if (index != -1){
                bdd eq_1_2 = bdd_apply(p[0][index][4], p[2][i][3], bddop_biimp);
                eq_1 |= eq_1_2;
                bdd eq_2_2 = bdd_apply(p[2][index][7], p[3][i][7], bddop_biimp);
                eq_2 |= eq_2_2;
                bdd eq_3_2 = bdd_apply(p[3][index][5], p[0][i][5], bddop_biimp);
                eq_3 |= eq_3_2;
                bdd eq_4_2 = bdd_apply(p[2][index][0], p[1][i][1], bddop_biimp);
                eq_4 |= eq_4_2;
            }
            
        }
        if (eq_1 != bddfalse) {
            all_conditions &= eq_1;
        }
        if (eq_2 != bddfalse) {
            all_conditions &= eq_2;
        }
        if (eq_3 != bddfalse) {
            all_conditions &= eq_3;
        }
        if (eq_4 != bddfalse) {
            all_conditions &= eq_4;
        }

        if (all_conditions != bddtrue) {
            result &= all_conditions;
        }
        else {
            result &= !p[2][i][3];
            result &= !p[3][i][7];
            result &= !p[0][i][5];
            result &= !p[1][i][1];
        }
    }
}

void limit5(bdd &solution, const bdd (&p)[M][N][N]) {
  for (unsigned i = 0; i < N; i++) {
    bdd bdd1, bdd2, bdd3, bdd4 = bddfalse;
    for (unsigned j = 0; j < N; j++) {
      bdd1 |= p[0][i][j];
      bdd2 |= p[1][i][j];
      bdd3 |= p[2][i][j];
      bdd4 |= p[3][i][j];
    }
    solution &= bdd1 & bdd2 & bdd3 & bdd4;
  }
}

void limit6(bdd &solution, const bdd (&p)[M][N][N]) {
  for (unsigned j = 0; j < N; j++) {
    for (unsigned i = 0; i < N - 1; i++) {
      for (unsigned k = i + 1; k < N; k++) {
        for (auto &m: p) {
          solution &= m[i][j] >> !m[k][j];
        }
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
    limit5(result, p);
    limit6(result, p);

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