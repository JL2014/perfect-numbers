// g++ -o sum_odd_cubes sum_odd_cubes.cpp -lflint -L/usr/local/lib
#include <iostream>
#include <string>
#include <flint/fmpz.h>

using namespace std;

void sum_odd_cubes_print(const string &Nstr) // calcule S(N) = somme des cubes des impairs de 1 à N
{
    fmpz_t N, m, tmp, result;
    fmpz_init(N);

    if (fmpz_set_str(N, Nstr.c_str(), 10) != 0) {
        cerr << "Entrée invalide : '" << Nstr << "'" << endl;
        fmpz_clear(N);
        return;
    }

    fmpz_init(m);
    fmpz_init(tmp);
    fmpz_init(result);

    // m = (N + 1) / 2  (nombre d'impairs ≤ N)
    fmpz_add_ui(m, N, 1);
    fmpz_fdiv_q_ui(m, m, 2UL);  // division entière plancher (floor)

    // result = 2*m^4 - m^2
    fmpz_mul(tmp, m, m);          // tmp = m^2
    fmpz_mul(result, tmp, tmp);   // result = m^4
    fmpz_mul_ui(result, result, 2UL); // 2*m^4
    fmpz_sub(result, result, tmp);    // - m^2

    fmpz_print(result);
    cout << endl;

    fmpz_clear(N); fmpz_clear(m); fmpz_clear(tmp); fmpz_clear(result);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <N>" << endl;
        return 1;
    }

    string Nstr = argv[1];
    sum_odd_cubes_print(Nstr);
    return 0;
}
