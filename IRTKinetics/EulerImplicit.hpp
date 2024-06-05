#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

// Типы для удобства
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using SystemFunction = std::function<Vector(const Vector&)>;

// Норма вектора для проверки сходимости
double norm(const Vector& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

// Функция для решения системы нелинейных уравнений методом Ньютона
Vector newtonSolve(const SystemFunction& F, const Vector& x0, double tol = 1e-6, int max_iter = 100) {
    int n = x0.size();
    Vector x = x0;
    Vector Fx = F(x);
    Matrix J(n, Vector(n));
    
    for (int iter = 0; iter < max_iter; ++iter) {
        Fx = F(x);

        // Построение якобиана
        for (int i = 0; i < n; ++i) {
            Vector x_perturbed = x;
            double eps = 1e-8;
            x_perturbed[i] += eps;
            Vector Fx_perturbed = F(x_perturbed);
            for (int j = 0; j < n; ++j) {
                J[j][i] = (Fx_perturbed[j] - Fx[j]) / eps;
            }
        }

        // Решение системы J * delta_x = -Fx
        Vector delta_x(n);
        for (int i = 0; i < n; ++i) {
            delta_x[i] = -Fx[i];
            for (int j = 0; j < n; ++j) {
                delta_x[i] += J[i][j] * delta_x[j];
            }
        }

        // Обновление решения
        for (int i = 0; i < n; ++i) {
            x[i] += delta_x[i];
        }

        // Проверка сходимости
        if (norm(delta_x) < tol) {
            break;
        }
    }

    return x;
}

// Неявный метод Эйлера для системы уравнений
std::vector<Vector> implicitEuler(SystemFunction f, const Vector& y0, double t0, double t1, double h) {
    std::vector<Vector> result;
    result.push_back(y0);
    Vector y = y0;
    double t = t0;

    while (t < t1) {
        // Определение функции для метода Ньютона
        SystemFunction G = [&](const Vector& y_next) {
            Vector F = f(y_next);
            Vector G(y_next.size());
            for (size_t i = 0; i < y_next.size(); ++i) {
                G[i] = y_next[i] - y[i] - h * F[i];
            }
            return G;
        };

        // Решение нелинейной системы уравнений
        y = newtonSolve(G, y);
        result.push_back(y);
        t += h;
    }

    return result;
}

// Пример использования
//int main() {
//    // Пример системы дифференциальных уравнений: dy/dt = -y
//    auto f = [](const Vector& y) -> Vector {
//        return {-y[0]};
//    };
//
//    Vector y0 = {1.0}; // начальные условия
//    double t0 = 0.0;
//    double t1 = 10.0;
//    double h = 0.1;
//
//    std::vector<Vector> solution = implicitEuler(f, y0, t0, t1, h);
//
//    for (size_t i = 0; i < solution.size(); ++i) {
//        std::cout << "t = " << t0 + i * h << ", y = " << solution[i][0] << std::endl;
//    }
//
//    return 0;
//}