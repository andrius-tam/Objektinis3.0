#include "mylib.h"
#include "Funkcijos.h"

int main()
{
    //Zmogus s;
    srand(time(NULL));
    int kiek = 0;
    vector <duom> stud;
    char tikrinimas;
    cout << "Jei norite studento galutini bala skaiciuoti naudojant mediana iveskite \"m\", o jei norite galutini bala skaiciuoti naudojant vidurki iveskite \"v\"\n"; cin >> tikrinimas;
    while (tolower(tikrinimas) != 'v' && tolower(tikrinimas) != 'm') {
        cout << "Turite ivesti \"v\" arba \"m\"!" << endl;
        cin >> tikrinimas;
    }
    int dydis = 1000;
    string pavadinimas;
    char gen;
    cout << "Norint sugeneruoti naujus failus iveskite \"t\", o norint naudoti senus iveskite \"n\"\n"; cin >> gen;
    while (tolower(gen) != 't' && tolower(gen) != 'n') {
        cout << "Turite ivesti \"t\" arba \"n\"!" << endl;
        cin >> gen;
    }
    if (gen == 't') {
        for (int i = dydis; i <= 1000000; i *= 10) {
            pavadinimas = "studentai" + to_string(i) + ".txt";
            Generavimas(i, pavadinimas);
        }
    }
    for (int i = dydis; i <= 1000000; i *= 10) {
        pavadinimas = "studentai" + to_string(i) + ".txt";
        auto start1 = std::chrono::high_resolution_clock::now();
        Nuskaitymas(stud, kiek, pavadinimas, tikrinimas);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        string varg_isv2 = "vargsiukai_vector_antras" + to_string(dydis) + ".txt";
        string galv_isv2 = "galvociai_vector_antras" + to_string(dydis) + ".txt";
        vector <duom> vargsiukai2;
        // 2 Vektoriu strategija
        auto startv2 = std::chrono::high_resolution_clock::now();
        sort(stud.begin(), stud.end(), Palyginimas);
        stud.erase(remove_if(stud.begin(), stud.end(), [&vargsiukai2](duom naujas) {
            if (naujas.getBalas() < 5.00) {
                vargsiukai2.push_back(naujas);
                return true;
            }
            else { return false; }
            }), stud.end());
        auto endv2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diffv2 = endv2 - startv2;
        int varg_dyd2 = vargsiukai2.size();
        int pagr_dyd = stud.size();
        auto start2 = std::chrono::high_resolution_clock::now();
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2 - start2;

        cout << "\n" << "Veiksmai su " << i << " failu naudojant klases: ";
        cout << diff1.count() + diff2.count() + diffv2.count() << endl;

        stud.clear();
        vargsiukai2.clear();
    }
    system("pause");
    return 0;
}
