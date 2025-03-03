#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

double Round(double X, double Delta)
{
  if (Delta <= 1E-9)
  {
    puts("Неверное задание точности округления\n");
    exit(1);
  }

  if (X > 0.0)
  {
    return Delta * long(X / Delta + 0.5);
  }
  else
  {
    return Delta * long(X / Delta - 0.5);
  }
}

double F(double x, double delta)
{

  // Проверка на допустимость аргумента для логарифма
  /*if (x <= -1.0 || x >= 1.0)
  {
    return NAN;
  }*/

  // Вычисляем значение функции f(x)
  /*double term1 = log((1.0 + x) / (1.0 - x)); // ln((1 + x)/(1 - x))
  double term2 = cos(pow(x, 2));             // cos(x^2)
  double result = term1 - term2;             // f(x) = term1 - term2*/

  return Round(pow(x, 4) - 13 * pow(x, 2) + 36 - 1 / x, delta); // Округление до заданной точности
}

double F1(double x)
{
  // функция f'(x)

  // double f = (M_PI * pow(x, M_PI + 7) + 2 * M_PI*pow(x, M_PI + 3) + M_PI * pow(x, M_PI - 1) + 4 * pow(x, 3)) / (pow(x, 8) + 2 * pow(x, 4) + 1);
  return x;
}

double HORDA(double Left, double Right, double Eps, int &N, double delta)
{
  double FLeft = F(Left, delta);
  double FRight = F(Right, delta);
  double X, Y;

  if (FLeft * FRight > 0.0)
  {
    puts("Неверное задание интервала\n");
    exit(1);
  }

  if (Eps <= 0.0)
  {
    puts("Неверное задание точности\n");
    exit(1);
  }

  N = 0;

  if (fabs(FLeft) < Eps)
  {
    return Left;
  }

  if (fabs(FRight) < Eps)
  {
    return Right;
  }

  do
  {
    X = Left - (Right - Left) * FLeft / (FRight - FLeft);
    Y = F(X, delta);

    if (fabs(Y) < Eps)
    {
      return X;
    }

    if (Y * FLeft < 0.0)
    {
      Right = X;
      FRight = Y;
    }
    else
    {
      Left = X;
      FLeft = Y;
    }

    N++;
  } while (fabs(Y) >= Eps);

  std::cout << "jjj" << std::endl;
  return X;
}

int main(){
    int k;
	double a, b, eps, x;

	a = -4.5;
	b = -2.5;
	//printf("eps\t\tdelta\t\ta\t\tb\t\tx\t\tn_m\t\tn\t\tk\tC\n");

	for (double delta = 0.1; delta >= 0.000001; delta /= 10) 
	{
		for (eps = 0.1; eps >= 0.000001; eps /= 10) 
		{
			x = HORDA(a, b, eps, k, delta);
            std::cout << k << std::endl;
			//printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\n", eps, delta, a, b, x, eps / delta, 1 / (double)F1(x), k,  eps / delta> 1 / F1(x));
		}
	}
	return 0;
}