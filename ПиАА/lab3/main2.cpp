#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

// Структура, описывающаяя состояние конкретного узла бора
struct state {
    std::string blockName; // имя узла
    std::map<char, int> transitions; // потомки узла
    int suffLink = -1; // номер состояния, котрое является суффиксной ссылкой
    int finalLink = -1; // номер состояния, котрое является конечной ссылкой
    bool inDict = false; // является ли этот узел шаблоном
    int templateNumber; // номер узла
};

// Класс алгоритма, содержащий методы для решения задачи
class AhoCorasick {
private:
    std::vector<state> automaton; // вектор, хранящий все узлы дерева
    int root = 0; // номер корня дерева
    std::vector<std::string> patterns; // переданные шаблоны

    // Метод для построения дерева по шаблонам
    void buildTrie() {
        automaton.resize(1); // заполняем в первую очередь корнем
        automaton[0].blockName = "";
        for (int i = 0; i < patterns.size(); i++) { // пробегаемся по шаблонам
            int current = root; // начинаем обход с корня
            for (char ch : patterns[i]) { // пробегаемся по символам
                if (automaton[current].transitions.find(ch) == automaton[current].transitions.end()) { // если в данном состоянии нет перехода по символу, создаем новый узел
                    automaton[current].transitions[ch] = automaton.size();
                    automaton.emplace_back();
                    automaton[automaton.size() - 1].blockName = automaton[current].blockName + ch;
                }
                current = automaton[current].transitions[ch]; // переход в следующее состояние
            }
            automaton[current].inDict = true; // номер состояния, до которого мы дошли, будет содержать в себе весь шаблон
            automaton[current].templateNumber = i + 1;
        }
    }
 
    // Метод для построения ссылок
    void buildLinks() {
        std::queue<int> q; // будем делать обход в ширину через очередь
        for (auto& pair : automaton[root].transitions) { // для первых потомков корня ссылками будет как раз корень
            q.push(pair.second);
            automaton[pair.second].suffLink = root;
            automaton[pair.second].finalLink = root;
        }

        while (!q.empty()) { // заполняем ссылки для каждого узла
            int current = q.front();
            q.pop();

            for (auto& pair : automaton[current].transitions) { // обход по потомкам конкретного узла
                char ch = pair.first;
                int nextState = pair.second;
                q.push(nextState);

                int link = automaton[current].suffLink;
                 // если суффиксная ссылка узла имеет тот же переход, что и между этим узлом и его потомком, то потомок суффиксной ссылки будет суффиксной ссылкой потомка
                while (link != -1 && automaton[link].transitions.find(ch) == automaton[link].transitions.end()) {
                    link = automaton[link].suffLink;
                }

                if (link == -1) {
                    automaton[nextState].suffLink = root;
                } else {
                    automaton[nextState].suffLink = automaton[link].transitions[ch];
                }

                // Если найденная раннее суффиксная ссылка относится к шаблоону, то она же будет и конечной
                if (automaton[automaton[nextState].suffLink].inDict) {
                    automaton[nextState].finalLink = automaton[nextState].suffLink;
                } else { // в противном случае находим ее конечную ссылку 
                    automaton[nextState].finalLink = automaton[automaton[nextState].suffLink].finalLink;
                }
            }
        }
        /*int index = 0;
        for (auto x: automaton){
            std::cout << index++ << std::endl;
            std::cout << "Block: " << x.blockName << std::endl;
            std::cout << "InDict: " << x.inDict << std::endl;
            std::cout << "Number: " << x.templateNumber << std::endl;
            for (auto y: x.transitions){
                std::cout << y.first << " - " << y.second << std::endl;
            }
            std::cout << "SuffLink: " << x.suffLink << std::endl;
            std::cout << "FinalLink: " << x.finalLink << std::endl;
            std::cout << "=============\n";
        }*/
    }

public:

    // Инициализация списка шаблонов и построение дерева
    AhoCorasick(const std::vector<std::string>& patterns) : patterns(patterns) {
        buildTrie();
        buildLinks();
    }

    // Функция поиска шаблонов в переданной строке
    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::set<std::pair<int, int>> uniqueMatches; // множество, в котором будут храниться наши результаты
        int current = root; // начинаем обход с корня
    
        for (int i = 0; i < text.size(); i++) { // проходим по каждому символу текста
            char ch = text[i];
            //printf("Try to find for text[%d]=%c\n", i, ch);
    
            // Если из данного состояния можем сделать переход по данному символу, то этот переход будет в тексте
            while (current != -1 && automaton[current].transitions.find(ch) == automaton[current].transitions.end()) {
                current = automaton[current].suffLink; // иначе идем по суффиксной ссылке
                //std::cout << "Next current: " << current << std::endl;
            }
    
            if (current == -1) {
                current = root;
            } else {
                current = automaton[current].transitions[ch]; // обновляем текущее состояние после перехода
            }
            //std::cout << "Next current: " << current << std::endl;
    
            int state = current; // будем делать временный обход по этому состоянию, чтобы найти конечные ссылки, которые также войдут в текст
            while (state != -1) {
                //std::cout << "Move to: " << automaton[state].blockName << std::endl;
                if (automaton[state].inDict) {
                    uniqueMatches.insert({i - patterns[automaton[state].templateNumber - 1].size() + 2, automaton[state].templateNumber});
                }
                state = automaton[state].finalLink;
            }
        }
    
        std::vector<std::pair<int, int>> matches(uniqueMatches.begin(), uniqueMatches.end());
        return matches;
    }

    // Нахождение образцов, имеющих пересечения с другими найденными образцами
    // Для шаблонов идет проверка условия: (startA <= startB + lenB - 1) && (startB <= startA + lenA - 1)
    void findIntersections(const std::string& text){
        std::vector<std::pair<int, int>> matches = this->search(text);
        sort(matches.begin(), matches.end());
        std::set<std::string> result;
        for (int i = 0; i < matches.size(); i++) {
            int startA = matches[i].first;
            int lenA = patterns[matches[i].second - 1].size();
            for (int j = i + 1; j < matches.size(); j++){
                int startB = matches[j].first;
                int lenB = patterns[matches[j].second - 1].size();
                if ((startA <= startB + lenB - 1) && (startB <= startA + lenA - 1)){
                    result.insert(patterns[matches[i].second - 1]);
                    result.insert(patterns[matches[j].second - 1]);
                }
            }
        }
        std::cout << "========" << std::endl;
        for (auto& str : result) {
            std::cout << str << std::endl;
        }
        std::cout << "========" << std::endl;
    }
};


int main() {
    std::string Q; // шаблон с джокером
    std::string T; // текст
    char wildCard; // символ джокера

    std::cin >> T >> Q >> wildCard;

    std::vector<std::string> vectorQ; // вектор для хранения набор подстрок Q, разделенными масками
    std::vector<int> vectorL; // позиции Qi в шаблоне
    std::string current = "";
    for (int i = 0; i < Q.size(); i++){ // цикл для разделения Q на подстроки по символу джокера
        if (Q[i] != wildCard && current == ""){
            vectorL.push_back(i + 1);
            //std::cout << i + 1 <<std::endl;
        }
        if (Q[i] == wildCard && current != ""){
            vectorQ.push_back(current);
            //std::cout << current << std::endl;
            current = "";
            continue;
        }
        else if (Q[i] == wildCard){
            continue;
        }
        current += Q[i];
    }
    if (current != ""){ // если после цикла осталась строка, она будет подходить
        vectorQ.push_back(current);
    }

    // инициализация C, где C[i] — количество встретившихся в тексте безмасочных подстрок шаблона, который начинается в тексте на позиции i
    std::vector<int> C(T.size());
    AhoCorasick ac(vectorQ);
    std::vector<std::pair<int, int>> matches = ac.search(T); // по алгоритму Ахо-Карасика находим индексы вхождения Qi в текст

    sort(matches.begin(), matches.end());

    for (auto& match : matches) { // заполнение C
        int index = (match.first - 1) - vectorL[match.second - 1] + 1;
        if (index >= 0 && index < T.size()) { // избегаем выходов за границу массива
            C[index]++;
        }
        for (int i = 0; i < vectorQ.size(); i++){
            if (i != match.second - 1 && vectorQ[i] == vectorQ[match.second - 1]){ // учитываем, если могли встретиться одинаковые подстроки, а Ахо-Красика это не учел
                index = (match.first - 1) - vectorL[i] + 1;
                if (index >= 0 && index < T.size()) {
                    C[index]++;
                }
            }
        }
    }

    /*std::cout << "========" << std::endl;
    for (int i = 0; i < C.size(); i++){
        printf("For C[%d]=%d\n", i, C[i]);
    }
    std::cout << "========" << std::endl;*/

    for (int i = 0; i <= C.size() - Q.size(); i++){
        if (C[i] == vectorQ.size()) // вывод нужной позиции
            std::cout << i + 1 << std::endl;
    }

    return 0;
}