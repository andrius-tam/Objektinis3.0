#include "mylib.h"
#include "Funkcijos.h"

double vid_med(char tikrinimas, vector <int>& laik, int paz_sk, int egzaminas)
{
    double vid;
    if (tolower(tikrinimas) == 'v') {
        if (paz_sk == 0) vid = 0;
        else vid = accumulate(laik.begin(), laik.end(), 0.0) / double(paz_sk);
    }
    else
    {
        if (paz_sk == 0)
        {
            vid = 0;
        }
        else {
            sort(laik.begin(), laik.end());
            if (paz_sk % 2 == 0)
            {
                vid = double(laik[(paz_sk - 1) / 2] + laik[paz_sk / 2]) / 2.0;
            }
            else
            {
                vid = double(laik[paz_sk / 2]);
            }
        }

    }
    return vid * 0.4 + double(egzaminas) * 0.6;
}

void Nuskaitymas(vector <duom>& func, int& kiek, string pavadinimas, char tikrinimas)
{
    try
    {
        ifstream df;
        df.open(pavadinimas);
        string eil;
        string header, laik;
        if (df.is_open())
        {
            int sk, nd, egz;
            getline(df >> ws, header);
            stringstream stream(header);
            sk = (distance(istream_iterator<string>(stream), istream_iterator<string>())) - 3;
            while (getline(df >> ws, eil))
            {
                duom naujas;
                stringstream stream(eil);
                stream >> laik;
                naujas.setVardas(laik);
                stream >> laik;
                naujas.setPavarde(laik);
                vector <int> paz;
                for (int i = 0; i < sk; i++) {
                    stream >> nd;
                    paz.push_back(nd);
                }
                naujas.setPazymiai(paz);
                naujas.setPazKiek(sk);
                stream >> egz;
                naujas.setEgzas(egz);
                int rez = vid_med(tikrinimas, paz, sk, egz);
                naujas.setBalas(rez);
                func.push_back(naujas);
            }
        }
        else throw std::runtime_error(pavadinimas);
        kiek = func.size();
        df.close();
    }
    catch (const exception& e) {
        cout << "Failo nuskaityti nepavyko: " << e.what() << endl;
    }
}

void Generavimas(int dydis, string pavadinimas) {
    stringstream buff;
    ofstream gf;
    gf.open(pavadinimas);
    int ndsk = rand() % 10 + 1;
    buff << setw(20) << left << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < ndsk; i++)buff << setw(20) << "ND" + to_string(i + 1);
    buff << setw(20) << "Egz." << "\n";
    for (int i = 0; i < dydis; i++) {
        buff << setw(20) << left << "Vardas" + to_string(i + 1) << setw(20) << "Pavarde" + to_string(i + 1);
        for (int j = 0; j < ndsk; j++) {
            buff << setw(20) << (rand() % 10 + 1);
        }
        buff << setw(20) << (rand() % 10 + 1) << "\n";
    }
    gf << buff.str();
    buff.clear();
    gf.close();
}

bool Palyginimas(const duom& stud1, const duom& stud2)
{
    if (stud1.getBalas() < stud2.getBalas()) { return true; }
    else { return false; }
}
