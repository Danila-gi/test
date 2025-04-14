#include <iostream>
#include <vector>

void makeLangrange(const std::vector<float>& X, const std::vector<float>& Y, int n, std::vector<std::vector<float>>& p, std::vector<float>& p_0){
    for (int i = 0; i < n; i++){
        std::vector<float> p_i;
        float p_den = 1;
        for (int j = 0; j < n; j++){
            if (i != j){
                p_i.push_back(X[j]);
                p_den *= (X[i] - X[j]);
            }
        }
        p[i] = p_i;
        p_0[i] = p_den;
    }
}

float langrangeFunction(float x, const std::vector<std::vector<float>>& p, const std::vector<float>& p_0, const std::vector<float>& Y){
    float result = 0;
    int i = 0;
    for (auto p_i: p){
        float p_num = 1;
        for (auto a: p_i){
            p_num *= (x - a);
        }
        result += (p_num * Y[i] / p_0[i]);
        i++;
    }
    return result;
}

int main(){
    int n = 11;
    std::vector<float> X = {1.9816, 2.0952, 2.1016, 2.7384, 2.8872, 3.4816, 4.0768, 4.9888, 5.1256, 5.5200};
    std::vector<float> Y = {0.0184, -0.0943, -0.1006, -0.3358, -0.1889, 1.7707, 6.8806, 23.7099, 27.4096, 40.0942, 45.1488};
    std::vector<std::vector<float>> p(n);
    std::vector<float> p_0(n);
    makeLangrange(X, Y, n, p, p_0);

    float x;
    std::cin >> x;
    std::cout << langrangeFunction(x, p, p_0, Y);
}
