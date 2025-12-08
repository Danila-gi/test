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
  
    result &= p[0][3][0];

    result &= p[1][5][1];

    result &= p[3][1][1];

    result &= p[0][7][1];

    result &= p[2][6][0];

    result &= p[3][2][0];

    result &= p[0][8][2];
}

void limitN2(bdd &result, const bdd (&p)[M][N][N]) {
    // 5 штук ограничений n2
    for (unsigned i = 0; i < N; i++) {
        result &= bdd_apply(p[0][i][3], p[1][i][7], bddop_biimp);

        result &= bdd_apply(p[0][i][6], p[2][i][7], bddop_biimp);

        result &= bdd_apply(p[1][i][2], p[3][i][2], bddop_biimp);

        result &= bdd_apply(p[1][i][5], p[2][i][5], bddop_biimp);

        result &= bdd_apply(p[0][i][7], p[1][i][6], bddop_biimp);
    }
}

void limitN3(bdd &result, const bdd (&p)[M][N][N]) {
    // 4 штуки ограничения n4
    // Соседи: сверху-слева, снизу-слева
    unsigned index;
    const int squareSize = (int)std::sqrt(N);
    for (unsigned i = 0; i < N; i++) {
    if ((i < N - squareSize) && (i % squareSize != 0)) {
        index = i + squareSize - 1;
        
        result &= bdd_apply(p[2][index][1], p[0][i][2], bddop_biimp);
        
        result &= bdd_apply(p[1][index][3], p[0][i][8], bddop_biimp);

        result &= bdd_apply(p[0][index][5], p[2][i][1], bddop_biimp);
    }

    if (IS_GLUING && (i < N - squareSize) && (i % squareSize == 0)) {
        index = i + 2 * squareSize - 1;
        result &= bdd_apply(p[2][index][1], p[0][i][2], bddop_biimp);
        result &= bdd_apply(p[1][index][3], p[0][i][8], bddop_biimp);

        result &= bdd_apply(p[0][index][5], p[2][i][1], bddop_biimp);
    }

    if (!IS_GLUING && (i < N - squareSize) && (i % squareSize == 0)) {
        index = i + 2 * squareSize - 1;
        result &= !p[0][i][2];
        result &= !p[0][i][8];
        result &= !(p[2][index][1]);
        result &= !(p[1][index][3]);


        result &= !(p[2][i][1]);
        
    }

    if ((i >= squareSize) && (i % squareSize != 0)) {
        index = i - squareSize - 1;
        
        result &= bdd_apply(p[1][index][2], p[3][i][4], bddop_biimp);
        
        result &= bdd_apply(p[2][index][2], p[3][i][3], bddop_biimp);
        
    }

    if (IS_GLUING && (i >= squareSize) && (i % squareSize == 0)) {
        index = i - 1;
        result &= bdd_apply(p[1][index][2], p[3][i][4], bddop_biimp);
        result &= bdd_apply(p[2][index][2], p[3][i][3], bddop_biimp);
    }

    if (!IS_GLUING && (i >= squareSize) && (i % squareSize == 0)) {
        result &= !(p[3][i][4]);
        result &= !(p[3][i][3]);
        index = i - 1;
        result &= !(p[1][index][2]);
        result &= !(p[2][index][2]);
    }


    }
}

void limitN4(bdd &result, const bdd (&p)[M][N][N]) {
    unsigned right_top_index;
    unsigned right_bottom_index;
    const int squareSize = (int)std::sqrt(N);
  
    for (unsigned i = 0; i < N; i++) {
        if ((i >= squareSize) && (i < N - squareSize) && (i % squareSize != 0)) {
            right_top_index = i + squareSize - 1;
            right_bottom_index = i - squareSize - 1;
            
            result &= !p[0][i][6] | p[3][right_top_index][5] | p[3][right_bottom_index][5];
            
            result &= !p[0][i][5] | p[3][right_top_index][7] | p[3][right_bottom_index][7];
            
            result &= !p[0][i][6] | p[0][right_top_index][8] | p[0][right_bottom_index][8];

            result &= !p[3][i][3] | p[0][right_top_index][3] | p[0][right_bottom_index][3];
        }
    
        else if ((i < squareSize) && (i % squareSize != 0)) {
            right_top_index = i + squareSize - 1;
            
            result &= bdd_apply(p[0][i][6], p[3][right_top_index][5], bddop_biimp);
            
            result &= bdd_apply(p[0][i][5], p[3][right_top_index][7], bddop_biimp);
            
            result &= bdd_apply(p[0][i][6], p[0][right_top_index][8], bddop_biimp);

            result &= bdd_apply(p[3][i][3], p[0][right_top_index][3], bddop_biimp);
        }
    
        else if ((i >= N - squareSize) && (i % squareSize != 0)) {
            right_bottom_index = i - squareSize - 1;
            
            result &= bdd_apply(p[0][i][6], p[3][right_bottom_index][5], bddop_biimp);
            
            result &= bdd_apply(p[0][i][5], p[3][right_bottom_index][7], bddop_biimp);
            
            result &= bdd_apply(p[0][i][6], p[0][right_bottom_index][8], bddop_biimp);

            result &= bdd_apply(p[3][i][3], p[0][right_bottom_index][3], bddop_biimp);
        }
    
        if (IS_GLUING && (i % squareSize == 0)) {
            if (i < squareSize) {
                right_top_index = i + 2 * squareSize - 1;
                result &= bdd_apply(p[0][i][6], p[3][right_top_index][5], bddop_biimp);
                result &= bdd_apply(p[0][i][5], p[3][right_top_index][7], bddop_biimp);
                result &= bdd_apply(p[0][i][6], p[0][right_top_index][8], bddop_biimp);
                result &= bdd_apply(p[3][i][3], p[0][right_top_index][3], bddop_biimp);
            }
            else if ((i >= squareSize) && (i < N - squareSize)) {
                right_top_index = i - 1;
                right_bottom_index = i + 2 * squareSize - 1;
                result &= !p[0][i][6] | p[3][right_top_index][5] | p[3][right_bottom_index][5];
                result &= !p[0][i][5] | p[3][right_top_index][7] | p[3][right_bottom_index][7];
                result &= !p[0][i][6] | p[0][right_top_index][8] | p[0][right_bottom_index][8];
                result &= !p[3][i][3] | p[0][right_top_index][3] | p[0][right_bottom_index][3];
            }
            else if (i >= N - squareSize) {
                right_bottom_index = i - 1;
                result &= bdd_apply(p[0][i][6], p[3][right_bottom_index][5], bddop_biimp);
                result &= bdd_apply(p[0][i][5], p[3][right_bottom_index][7], bddop_biimp);
                result &= bdd_apply(p[0][i][6], p[0][right_bottom_index][8], bddop_biimp);
                result &= bdd_apply(p[3][i][3], p[0][right_bottom_index][3], bddop_biimp);
            }
        }
        if (!IS_GLUING && (i % squareSize == 0)) {
            if (i < squareSize) {
                right_top_index = i + 2 * squareSize - 1;
                result &= !(p[0][i][6]);
                result &= !(p[0][i][5]);
                result &= !(p[3][i][3]);
                result &= !(p[3][right_top_index][5]);
                result &= !(p[3][right_top_index][7]);
                result &= !(p[0][right_top_index][8]);
                result &= !(p[0][right_top_index][3]);
            }
            else if ((i >= squareSize) && (i < N - squareSize)) {
                right_top_index = i - 1;
                right_bottom_index = i + 2 * squareSize - 1;
                result &= !p[0][i][6];
                result &= !p[0][i][5];
                result &= !p[3][i][3];

                result &= !(p[3][right_top_index][5]);
                result &= !(p[3][right_top_index][7]);
                result &= !(p[0][right_top_index][8]);
                result &= !(p[0][right_top_index][3]);

                result &= !(p[3][right_bottom_index][5]);
                result &= !(p[3][right_bottom_index][7]);
                result &= !(p[0][right_bottom_index][8]);
                result &= !(p[0][right_bottom_index][3]);
            }
            else if (i >= N - squareSize) {
                right_bottom_index = i - 1;
                result &= !(p[0][i][6]);
                result &= !(p[0][i][5]);
                result &= !(p[3][i][3]);
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
    std::cout << bdd_satcount(result) << " results:\n" << std::endl;
    limitN2(result, p);
    std::cout << bdd_satcount(result) << " results:\n" << std::endl;
    limitN3(result, p);
    std::cout << bdd_satcount(result) << " results:\n" << std::endl;
    limitN4(result, p);
    std::cout << bdd_satcount(result) << " results:\n" << std::endl;
    limitCompletenessOfProperties(result, p);
    limitUniqOfProperties(result, p);

    out.open("out.txt");
    unsigned satcount = (unsigned)bdd_satcount(result);
    out << satcount << " results:\n" << std::endl;
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