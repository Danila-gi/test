#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

/* Структура, описывающая элементы, которые будут
храниться в стеке*/ 
struct StackElement {
    std::vector<std::vector<int>> grid; // матрица, описывающая состояние каждой клетки столешницы 
    std::vector<std::tuple<int, int, int>> squaresUsed; // вектор использованных квадратов (координаты и размер)
    std::pair<int, int> emptyCell; // пара чисел, хранящая следующие пустые клетки на столешнице
};

void printMatrix(const std::vector<std::vector<int>>& grid) {
    // Функция для вывода в консоль текущего состояния матрицы
    for (const auto& row : grid) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isValid(int x, int y, int w, int n, const std::vector<std::vector<int>>& grid) {
    // Функция, которая проверяет возможность поставить на координаты (x, y) квадрат размера w
    if (x + w > n || y + w > n) {
        return false;
    }
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + w; j++) {
            if (grid[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

void placeSquare(int x, int y, int w, std::vector<std::vector<int>>& grid, int value) {
    // Функция для вставки на соответствующие координаты столешницы квадрата размера w
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + w; j++) {
            grid[i][j] = value;
        }
    }
}

std::pair<int, int> findEmptyCell(const std::vector<std::vector<int>>& grid, int n) {
    // Функция для нахождения по определенному алгоритму пустой клетки
    for (int x = 0; x < n; x++){
        // Сначала идет поиск свободного места на на границах столешницы
        if (grid[x][0] == 0) { // Проверка первого столбца
            return {x, 0};
        }
        if (grid[0][x] == 0) { // Проверка первой строки
            return {0, x};
        }
    }
    for (int i = 1; i < n; i++) { // Обход всех оставшихся клеток
        for (int j = 1; j < n; j++) {
            if (grid[i][j] == 0) {
                return {i, j};
            }
            if (grid[j][i] == 0) { // Оптимизация для симметричной проверки
                return {j, i};
            }
        }
    }
    return {-1, -1};
}

void newStateForStack(int x, int y, int w, const std::vector<std::vector<int>>& grid, const std::vector<std::tuple<int, int, int>>& squaresUsed, std::vector<StackElement>& stack, int n){
    // Функция для добавления нового состояния в стек
    std::vector<std::vector<int>> newGrid = grid;
    placeSquare(x, y, w, newGrid, squaresUsed.size() + 1); // Копирование предыдущего состояния сетки и добавление нового квадрата

    std::vector<std::tuple<int, int, int>> newSquares = squaresUsed;
    newSquares.push_back({x + 1, y + 1, w}); // Копирование предыдущего состояния вектора квадратов и добавление нового
    std::pair<int, int> nextEmptyCell = findEmptyCell(newGrid, n);

    stack.push_back({newGrid, newSquares, nextEmptyCell}); // Добавление обновленных полей
}

std::vector<std::tuple<int, int, int>> solve(int n) {
    // Функция с алгоритмом решения в виде итеративного бэктрекинга
    std::vector<std::vector<int>> grid(n, std::vector<int>(n, 0)); // Инициализация матрицы столешницы размера n*n нулями
    std::vector<StackElement> stack; // Стек, куда будут добавляться все возможные варианты и поочередно рассматриваться
    std::vector<std::tuple<int, int, int>> bestSolution; // Вектор множества квадратов (координаты и размеры), из которых можно заполнить столешницу

    for (int i = n / 2; i < n; i++) { // Начальное заполнение матрицы максимально большим квадратом
        newStateForStack(0, 0, i, grid, {}, stack, n);
    }

    while (!stack.empty()) { // Цикл для обхода всех состояний столешницы
        StackElement current = stack.back(); // Получение последнего состояния
        stack.pop_back();

        if (!bestSolution.empty() && current.squaresUsed.size() >= bestSolution.size()) {
            // Если в данном состоянии уже есть перебор по количеству квадратов по сравнению с последним лучшим решением,
            // происходит выход из этой ветки и переход к следующей
            /*std::cout<< "Stop check this state: " << current.squaresUsed.size() << std::endl;
            printMatrix(current.grid);*/
            continue;
        }

        if (current.emptyCell.first == -1 && current.emptyCell.second == -1) {
            if (bestSolution.empty() || current.squaresUsed.size() < bestSolution.size()) {
                // Обновление нового лучшего решения, если столешница заполнена и было затрачено меньше квадратов
                /*std::cout<< "Add new best solution: " << current.squaresUsed.size() << std::endl;
                printMatrix(current.grid);*/
                bestSolution = current.squaresUsed;
            }
            continue;
        }

        int x = current.emptyCell.first;
        int y = current.emptyCell.second;

        if (x == 0 || y == 0){
            // Если есть свободные клетки на границах матрицы, идет добавление матрицы максимально возможного размера для оптимизации
            int w = std::min({n - x, n - y});
            if (isValid(x, y, w, n, current.grid)) {
                newStateForStack(x, y, w, current.grid, current.squaresUsed, stack, n);
            }
            continue;
        }

        for (int w = 1; w <= std::min({n - x, n - y, n - 1}); w++) {
            // Если на предыдущем шаге не удалось добавить квадрат,
            // для свободной клетки идет перебор всех возможных размеров квадрата и добавление этих состояний в стек
            if (isValid(x, y, w, n, current.grid)) {
                newStateForStack(x, y, w, current.grid, current.squaresUsed, stack, n);
            }
        }
    }

    // Выход из цикла означает пустоту стека и рассмотрение всех возможных вариантов. Возвращаем лучшее решение
    return bestSolution;
}

int main() {
    int n;
    std::cin >> n; // Чтение входных данных
    auto solution = solve(n);

    std::cout << solution.size() << std::endl;
    for (const auto& square : solution) { // Обход вектора и вывод всех чисел каждого кортежа (x, y, w)
        std::cout << std::get<0>(square) << " " << std::get<1>(square) << " " << std::get<2>(square) << std::endl;
    }

    return 0;
}