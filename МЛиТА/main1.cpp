#include <bdd.h>
#include <iostream>
#include <cmath>

constexpr int log2(int x) {
  return x < 3 ? 1 : 1 + log2(x - x / 2);
}

constexpr bool ENABLE_GLUING = false;  // true = со склейкой, false = без склейки

constexpr int N = 9;                             // число объектов
constexpr int M = 4;                             // число свойств
constexpr int LOG_N = log2(N);                // логарифм по основанию 2
constexpr int N_VAR = N * M * LOG_N;             // число булевых переменных
char var[N_VAR];                                 // массив булевых переменных
const int DIMENSION = (int) std::sqrt(N); // размерность сетки
bdd p[M][N][N];                                  // вводим функцию p(property, object, value)

// Свойство 0: Цвет отделки
const char* COLOR_NAMES[] = {
    "белый",      // 0
    "серый",      // 1
    "бежевый",    // 2
    "синий",      // 3
    "зелёный",    // 4
    "чёрный",     // 5
    "коричневый", // 6
    "красный",    // 7
    "жёлтый"      // 8
};

// Свойство 1: Отдел
const char* DEPARTMENT_NAMES[] = {
    "бухгалтерия", // 0
    "IT",          // 1
    "маркетинг",   // 2
    "HR",          // 3
    "продажи",     // 4
    "логистика",   // 5
    "юридический", // 6
    "разработка",  // 7
    "аналитика"    // 8
};

// Свойство 2: Напиток
const char* DRINK_NAMES[] = {
    "кофе",      // 0
    "чай",       // 1
    "вода",      // 2
    "сок",       // 3
    "энергетик", // 4
    "какао",     // 5
    "лимонад",   // 6
    "смузи",     // 7
    "молоко"     // 8
};

// Свойство 3: Оборудование
const char* EQUIPMENT_NAMES[] = {
    "принтер",  // 0
    "сервер",   // 1
    "проектор", // 2
    "сканер",   // 3
    "плоттер",  // 4
    "телефон",  // 5
    "планшет",  // 6
    "ноутбук",  // 7
    "моноблок"  // 8
};

// Массив всех свойств для удобства
const char** PROPERTY_NAMES[] = {
    COLOR_NAMES,      // Свойство 0
    DEPARTMENT_NAMES, // Свойство 1
    DRINK_NAMES,      // Свойство 2
    EQUIPMENT_NAMES   // Свойство 3
};

const char* PROPERTY_LABELS[] = {
    "Цвет",
    "Отдел",
    "Напиток",
    "Оборудование"
};
// ============================================================

void fill();                                     // заполняем функцию p
void limit1(bdd &);                              // выставляем ограничения 1-го типа
void limit2(bdd &);                              // выставляем ограничения 2-го типа
void limit3(bdd &);                              // выставляем ограничения 3-го типа
void limit4(bdd &);                              // выставляем ограничения 4-го типа
void limit5(bdd &);                              // выставляем ограничения на уникальность значений свойства
void limit6(bdd &);                              // выставляем ограничения на значения свойства
void print_func(char *, int);                    // функция для вывода решений

int main() {

  int A = 16;
  int B = 03342;
  int C = 24;
  int a = A + B;
  int b = A + C;
  int v1 = (a % 28) + 1;
  int v2 = (b % 2) + 1;
  int v3 = (A % 4) + 1;

  std::cout << "v1: " << v1  << std::endl;
  std::cout << "|   |   | * |" << std::endl;
  std::cout << "|   | 0 |   |" << std::endl;
  std::cout << "|   |   | * |" << std::endl << std::endl;
  std::cout << "v2: " << v2 << ":    левая-правая границы " << std::endl << std::endl;
  std::cout << "v3: " << v3 << std::endl;
  std::cout << "| n1 | n2 | n3 | n4 |" << std::endl;
  std::cout << "| 6  | 8  | 5  | 3  |" << std::endl << std::endl;
  // инициализация BuDDy
  bdd_init(100000000, 1000000);
  bdd_setvarnum(N_VAR);

  // Информация о режиме работы
  std::cout << "======================================" << std::endl;
  std::cout << "  Задача Эйнштейна (сетка " << DIMENSION << "x" << DIMENSION << ")" << std::endl;
  std::cout << "  Режим: " << (ENABLE_GLUING ? "СО СКЛЕЙКОЙ ✓" : "БЕЗ СКЛЕЙКИ") << std::endl;
  std::cout << "======================================\n" << std::endl;

  // БДД, являющаяся решением задачи
  bdd solution = bddtrue;
  fill();
  limit1(solution);
  limit2(solution);
  limit3(solution);
  //limit4(solution);
  limit5(solution);
  limit6(solution);

  auto satcount = (unsigned) bdd_satcount(solution);
  std::cout << "Found " << satcount << " solution(s)\n";
  if (satcount) {
    //bdd_allsat(solution, print_func);
  }

  // Завершение работы с библиотекой BuDDy
  std::cout << "Found " << satcount << " solution(s)\n";
  bdd_done();
  return 0;
}

void fill() {
  for (unsigned property = 0; property < M; ++property) {
    for (unsigned object = 0; object < N; ++object) {
      for (unsigned value = 0; value < N; ++value) {
        p[property][object][value] = bddtrue;
        for (unsigned t = 0; t < LOG_N; ++t) {
          const unsigned index = LOG_N * M * object + LOG_N * property + t;
          p[property][object][value] &= (((value >> t) & 1) ? bdd_ithvar((int) index) : bdd_nithvar((int) index));
        }
      }
    }
  }
}

void limit1(bdd &solution) {
  // 1.1: "В офисе 5 отделка белого цвета"
  solution &= p[0][5][0];
  
  // 1.2: "В офисе 3 располагается IT-отдел"
  solution &= p[1][3][1];
  
  // 1.3: "В офисе 1 установлен сервер"
  solution &= p[3][1][1];
  
  // 1.4: "В офисе 7 отделка серого цвета"
  solution &= p[0][7][1];
  
  // 1.5: "В офисе 8 предпочитают кофе"
  solution &= p[2][8][0];
  
  // 1.6: "В офисе 0 установлен принтер"
  solution &= p[3][0][0];
  
  
}

void limit2(bdd &solution) {
  for (unsigned i = 0; i < N; i++) {
    // 2.1: "Если в офисе синяя отделка, то там отдел разработки (и наоборот)"
    solution &= !(p[0][i][3] ^ p[1][i][7]);
    
    // 2.2: "Если в офисе коричневая отделка, то там пьют смузи (и наоборот)"
    solution &= !(p[0][i][6] ^ p[2][i][7]);
    
    // 2.3: "Если в офисе отдел маркетинга, то там есть проектор (и наоборот)"
    solution &= !(p[1][i][2] ^ p[3][i][2]);
    
    // 2.4: "Если в офисе отдел логистики, то там пьют какао (и наоборот)"
    solution &= !(p[1][i][5] ^ p[2][i][5]);
    
    // 2.5: "Если в офисе красная отделка, то там юридический отдел (и наоборот)"
    solution &= !(p[0][i][7] ^ p[1][i][6]);
    
    // 2.6: "Если в офисе пьют сок, то там стоит моноблок (и наоборот)"
    solution &= !(p[2][i][3] ^ p[3][i][8]);
    
    // 2.7: "Если в офисе зелёная отделка, то там есть планшет (и наоборот)"
    solution &= !(p[0][i][4] ^ p[3][i][6]);
    
    // 2.8: "Если в офисе отдел аналитики, то там пьют лимонад (и наоборот)"
    solution &= !(p[1][i][8] ^ p[2][i][6]);
  }
}

void limit3(bdd &solution) {
  unsigned index;
  for (unsigned i = 0; i < N; i++) {
    if ((i >= DIMENSION) && (i % DIMENSION != DIMENSION - 1)) {
      index = i - DIMENSION + 1;
      
      // 3.1: "Если у соседа справа-сверху пьют чай, то в текущем офисе бежевая отделка (и наоборот)"
      solution &= !(p[2][index][1] ^ p[0][i][2]);
      
      // 3.2: "Если у соседа справа-сверху отдел HR, то в текущем офисе жёлтая отделка (и наоборот)"
      solution &= !(p[1][index][3] ^ p[0][i][8]);

      solution &= !(p[0][index][5] ^ p[2][i][1]);
    }
    
    if (ENABLE_GLUING && (i >= DIMENSION) && (i % DIMENSION == DIMENSION - 1)) {
      index = i - 2 * DIMENSION + 1;
      solution &= !(p[2][index][1] ^ p[0][i][2]);
      solution &= !(p[1][index][3] ^ p[0][i][8]);

      solution &= !(p[0][index][5] ^ p[2][i][1]);
    }

    // if (!ENABLE_GLUING && (i >= DIMENSION) && (i % DIMENSION == DIMENSION - 1)) {
    //   index = i - 2 * DIMENSION + 1;
    //   solution &= !p[0][i][2];  // офис 2: не бежевый
    //   solution &= !p[0][i][8];  // офис 2: не жёлтый
    //   solution &= !(p[2][index][1]);
    //   solution &= !(p[1][index][3]);


    //   solution &= !(p[2][i][1]);
      
    // }
    
    if ((i < N - DIMENSION) && (i % DIMENSION != DIMENSION - 1)) {
      index = i + DIMENSION + 1;
      
      // 3.3: "Если у соседа справа-снизу отдел маркетинга, то в текущем офисе есть плоттер (и наоборот)"
      solution &= !(p[1][index][2] ^ p[3][i][4]);
      
      // 3.4: "Если у соседа справа-снизу пьют воду, то в текущем офисе есть сканер (и наоборот)"
      solution &= !(p[2][index][2] ^ p[3][i][3]);
      
      // 3.5: "Если у соседа справа-снизу работает отдел аналитики, то в текущем офисе зелёная отделка (и наоборот)"
      solution &= !(p[1][index][8] ^ p[0][i][4]);

      
    }
    
    if (ENABLE_GLUING && (i < N - DIMENSION) && (i % DIMENSION == DIMENSION - 1)) {
      index = i + 1;
      solution &= !(p[1][index][2] ^ p[3][i][4]);
      solution &= !(p[2][index][2] ^ p[3][i][3]);
      solution &= !(p[1][index][8] ^ p[0][i][4]);
    }

    // if (!ENABLE_GLUING && (i < N - DIMENSION) && (i % DIMENSION == DIMENSION - 1)) {
    //   solution &= !(p[3][i][4]);  // офисы 5,8: не плоттер
    //   solution &= !(p[3][i][3]);  // офисы 5,8: не сканер
    //   solution &= !(p[0][i][4]);  // офисы 5,8: не зелёный
    //   index = i + 1;
    //   solution &= !(p[1][index][2]);
    //   solution &= !(p[2][index][2]);
    //   solution &= !(p[1][index][8]);
    // }

    
  }
}

void limit4(bdd &solution) {
  unsigned right_top_index;
  unsigned right_bottom_index;
  
  for (unsigned i = 0; i < N; i++) {
    if ((i >= DIMENSION) && (i < N - DIMENSION) && (i % DIMENSION != DIMENSION - 1)) {
      right_top_index = i + DIMENSION + 1;
      right_bottom_index = i - DIMENSION + 1;
      
      // 4.1: "Если коричневая отделка, то хотя бы у одного соседа есть телефон"
      solution &= !p[0][i][6] | p[3][right_top_index][5] | p[3][right_bottom_index][5];
      
      // 4.2: "Если чёрная отделка, то хотя бы у одного соседа есть ноутбук"
      solution &= !p[0][i][5] | p[3][right_top_index][7] | p[3][right_bottom_index][7];
      
      // 4.3: "Если коричневая отделка, то хотя бы у одного соседа есть жёлтый цвет"
      solution &= !p[0][i][6] | p[0][right_top_index][8] | p[0][right_bottom_index][8];
    }
    
    else if ((i < DIMENSION) && (i % DIMENSION != DIMENSION - 1)) {
      right_top_index = i + DIMENSION + 1;
      
      // 4.1: "Если коричневая отделка, то у соседа есть телефон (и наоборот)"
      solution &= !(p[0][i][6] ^ p[3][right_top_index][5]);
      
      // 4.2: "Если чёрная отделка, то у соседа есть ноутбук (и наоборот)"
      solution &= !(p[0][i][5] ^ p[3][right_top_index][7]);
      
      // 4.3: "Если коричневая отделка, то у соседа есть жёлтый цвет (и наоборот)"
      solution &= !(p[0][i][6] ^ p[0][right_top_index][8]);
    }
    
    else if ((i >= N - DIMENSION) && (i % DIMENSION != DIMENSION - 1)) {
      right_bottom_index = i - DIMENSION + 1;
      
      // 4.1: "Если коричневая отделка, то у соседа есть телефон (и наоборот)"
      solution &= !(p[0][i][6] ^ p[3][right_bottom_index][5]);
      
      // 4.2: "Если чёрная отделка, то у соседа есть ноутбук (и наоборот)"
      solution &= !(p[0][i][5] ^ p[3][right_bottom_index][7]);
      
      // 4.3: "Если коричневая отделка, то у соседа есть жёлтый цвет (и наоборот)"
      solution &= !(p[0][i][6] ^ p[0][right_bottom_index][8]);
    }
    
    if (ENABLE_GLUING && (i % DIMENSION == DIMENSION - 1)) {
      if (i < DIMENSION) {
        right_top_index = i + 1;
        solution &= !(p[0][i][6] ^ p[3][right_top_index][5]);
        solution &= !(p[0][i][5] ^ p[3][right_top_index][7]);
        solution &= !(p[0][i][6] ^ p[0][right_top_index][8]);
      }
      else if ((i >= DIMENSION) && (i < N - DIMENSION)) {
        right_top_index = i + 1;
        right_bottom_index = i - 2 * DIMENSION + 1;
        solution &= !p[0][i][6] | p[3][right_top_index][5] | p[3][right_bottom_index][5];
        solution &= !p[0][i][5] | p[3][right_top_index][7] | p[3][right_bottom_index][7];
        solution &= !p[0][i][6] | p[0][right_top_index][8] | p[0][right_bottom_index][8];
      }
      else if (i >= N - DIMENSION) {
        right_bottom_index = i - 2 * DIMENSION + 1;
        solution &= !(p[0][i][6] ^ p[3][right_bottom_index][5]);
        solution &= !(p[0][i][5] ^ p[3][right_bottom_index][7]);
        solution &= !(p[0][i][6] ^ p[0][right_bottom_index][8]);
      }
    }
    // if (!ENABLE_GLUING && (i % DIMENSION == DIMENSION - 1)) {
    //   if (i < DIMENSION) {
    //     right_top_index = i + 1;
    //     solution &= !(p[0][i][6]);
    //     solution &= !(p[0][i][5]);
    //   }
    //   else if ((i >= DIMENSION) && (i < N - DIMENSION)) {
    //     right_top_index = i + 1;
    //     right_bottom_index = i - 2 * DIMENSION + 1;
    //     solution &= !p[0][i][6];
    //     solution &= !p[0][i][5];
    //   }
    //   else if (i >= N - DIMENSION) {
    //     right_bottom_index = i - 2 * DIMENSION + 1;
    //     solution &= !(p[0][i][6]);
    //     solution &= !(p[0][i][5]);
    //   }
    // }



  }
}

void limit5(bdd &solution) {
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

void limit6(bdd &solution) {
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

void print() {
  for (unsigned i = 0; i < N; ++i) {
    std::cout << i << ": ";
    for (unsigned j = 0; j < M; ++j) {
      unsigned J = i * M * LOG_N + j * LOG_N;
      unsigned num = 0;
      for (unsigned k = 0; k < LOG_N; ++k) {
        num += (unsigned) (var[J + k] << k);
      }
      std::cout << num << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

// Красивый вывод решения с названиями свойств
void print_readable() {
  std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
  std::cout << "║                    РЕШЕНИЕ В ФОРМАЛЬНОМ ВИДЕ                   ║\n";
  std::cout << "╚════════════════════════════════════════════════════════════════╝\n\n";
  
  for (unsigned i = 0; i < N; ++i) {
    std::cout << "Офис " << i << ":\n";
    
    for (unsigned j = 0; j < M; ++j) {
      unsigned J = i * M * LOG_N + j * LOG_N;
      unsigned num = 0;
      for (unsigned k = 0; k < LOG_N; ++k) {
        num += (unsigned) (var[J + k] << k);
      }
      
      std::cout << "  " << PROPERTY_LABELS[j] << ": " 
                << PROPERTY_NAMES[j][num] << "\n";
    }
    std::cout << "\n";
  }
  
  std::cout << "═══════════════════════════════════════════════════════════════\n\n";
}

void build(const char *varset, const unsigned n, const unsigned I) {
  if (I == n - 1) {
    if (varset[I] >= 0) {
      var[I] = varset[I];
      print();
      //print_readable(); 
      return;
    }
    var[I] = 0;
    print();
    //print_readable();
    var[I] = 1;
    print();
    //print_readable();
    return;
  }
  if (varset[I] >= 0) {
    var[I] = varset[I];
    build(varset, n, I + 1);
    return;
  }
  var[I] = 0;
  build(varset, n, I + 1);
  var[I] = 1;
  build(varset, n, I + 1);
}

void print_func(char *varset, int size) {
  build(varset, size, 0);
}