#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <memory>


class Jucator;

class Pozitie
{
    float x;
    float y;
public:
    Pozitie(const float& X = 0, const float& Y = 0) : x{X}, y{Y}{}

    friend std::ostream& operator<<(std::ostream& os, const Pozitie& obj)
    {
        return os
            << "x: " << obj.x
            << " y: " << obj.y;
    }

    friend bool operator==(const Pozitie& other1, const Pozitie& other2)
    {
        if (other1.y == other2.y && other1.x == other2.x)
            return true;
        return false;
    }

    Pozitie(const Pozitie& other)
        : x(other.x),
          y(other.y)
    {
    }

    Pozitie& operator=(const Pozitie& other)
    {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    ~Pozitie() = default;

    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }

};

class Drum
{
    std::vector<Pozitie> traseu;
public:
    explicit Drum(const std::vector<Pozitie>& traseu)
        : traseu(traseu)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Drum& obj)
    {
        for (auto const& i : obj.traseu)
            return os << i;
        return os;
    }

    // [[nodiscard]] std::vector<Pozitie> getTraseu() const
    // {
    //     return traseu;
    // }

    [[nodiscard]] Pozitie getPozitie(const unsigned long long index) const
    {
        if (index < traseu.size())
            return traseu[index];
        return traseu.back();
    }

    [[nodiscard]] unsigned long long getLungime() const
    {
        return traseu.size();
    }
};



class Inamic
{
    std::string nume_inamic;
    int HP;
    int suma;
    struct movement_speed
    {
        int val;
        std::string tip;
    };
    movement_speed move_spd;
    Pozitie poz_curenta;
    unsigned long long index_pozitie;
    bool rez_magie;

public:
    Inamic(const std::string& nume, const int hp, const int sum, const movement_speed& move_s,
           const Pozitie& poz_c, const bool rez_m) :
    nume_inamic{nume},
    HP{hp},
    suma{sum},
    move_spd{move_s},
    poz_curenta{poz_c},
    rez_magie{rez_m},
    index_pozitie{0}{}

    Inamic(const Inamic& other) :
    nume_inamic{other.nume_inamic},
    HP{other.HP},
    suma{other.suma},
    move_spd{other.move_spd},
    poz_curenta{other.poz_curenta},
    rez_magie{other.rez_magie},
    index_pozitie{other.index_pozitie}
    {}

    ~Inamic() = default;

    Inamic& operator=(const Inamic& other)
    {
        if (this == &other)
            return *this;
        nume_inamic = other.nume_inamic;
        HP = other.HP;
        suma =other.suma;
        move_spd.val = other.move_spd.val;
        move_spd.tip = other.move_spd.tip;
        poz_curenta = other.poz_curenta;
        rez_magie = other.rez_magie;
        index_pozitie = other.index_pozitie;
        return *this;
    }

    friend bool operator==(const Inamic& other1, const Inamic& other2)
    {
        if (other1.HP == other2.HP && other1.nume_inamic == other2.nume_inamic && other1.suma == other2.suma &&
            other1.move_spd.val == other2.move_spd.val && other1.move_spd.tip == other2.move_spd.tip && other1.rez_magie == other2.rez_magie &&
            other1.poz_curenta == other2.poz_curenta)
            return true;
        return false;
    }


    friend std::ostream& operator<<(std::ostream& os, const Inamic& obj)
    {
        return os << obj.nume_inamic << " | " << "HP ramas: " << obj.HP;
    }

    void mutaInamic(const Drum& drum);

    [[nodiscard]] Pozitie get_Poz_Inamic() const
    {
        return poz_curenta;
    }
    // [[nodiscard]] int get_HP() const
    // {
    //     return HP;
    // }


    [[nodiscard]] bool mort() const
    {
        return HP <= 0;
    }

    bool rez_la_magie() const
    {
        return rez_magie;
    }

    [[nodiscard]] bool final_drum(const Drum& drum) const
    {
        if (index_pozitie < drum.getLungime() - 1)
            return false;
        return true;
    }

    void afiseazaPoz(const Drum& drum) const
    {
        if (final_drum(drum))
            std::cout << nume_inamic << " este la pozitia " << poz_curenta <<  " si a ajuns la final!\n" ;
        else
            std::cout << nume_inamic << " se afla la pozitia " << poz_curenta << std::endl;
    }

    [[nodiscard]] int getSuma() const { return suma; }

    void iaDamage(const int& dmg);

};

void Inamic::mutaInamic(const Drum& drum)
{
    if (index_pozitie < drum.getLungime() - 1)
    {
        index_pozitie++;
        poz_curenta = drum.getPozitie(index_pozitie);
    }
}

void Inamic::iaDamage(const int& dmg)
{
    HP = HP - dmg;
    if (HP < 0)
        HP = 0;
}


class Glont
{
    int viteza{};
    Pozitie poz_plecare;
    Pozitie poz_finala;

public:

    Glont() = default;

    // Glont(const int viteza, const Pozitie& poz_plecare, const Pozitie& poz_finala)
    //     : viteza(viteza),
    //       poz_plecare(poz_plecare),
    //       poz_finala(poz_finala)
    // {}

    friend std::ostream& operator<<(std::ostream& os, const Glont& object)
    {
        return os << object.viteza << object.poz_plecare << object.poz_finala;
    }

    friend bool operator==(const Glont& lhs, const Glont& rhs)
    {
        return lhs.viteza == rhs.viteza
            && lhs.poz_plecare == rhs.poz_plecare
            && lhs.poz_finala == rhs.poz_finala;
    }

    friend bool operator!=(const Glont& lhs, const Glont& rhs)
    {
        return !(lhs == rhs);
    }
};

class Turn
{
    std::string nume_turn;
    Glont tip_glont{};
protected:
    Pozitie poz_turn{0, 0};   // nici asta
    std::vector<int> damage;
private:
    std::vector<double> range;
    std::vector<int> attk_spd;
    std::vector<int> pret;
protected:
    int nivel{};

    inline static std::vector<Inamic>* inamici_context = nullptr;

public:

    //Turn() = default;
    Turn(const std::string& nume_t,
            const Glont& tip_g,
            const std::vector<int>& dmg,
            const std::vector<double>& rng,
            const std::vector<int>& atk,
            const std::vector<int>& prt,
            const int& niv) :   nume_turn{nume_t},
                                tip_glont{tip_g},
                                damage{dmg},
                                range{rng},
                                attk_spd{atk},
                                pret{prt},
                                nivel{niv} {}

    virtual ~Turn() = default;

    [[nodiscard]] virtual std::shared_ptr<Turn> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Turn& object)
    {
        os << object.nume_turn << " Nivel: " << object.nivel << " ";
        object.afisare(os);
        return os;
    }
private:
    virtual void afisare(std::ostream& os) const {}

public:
    friend bool operator==(const Turn& lhs, const Turn& rhs)
    {
        return lhs.nume_turn == rhs.nume_turn
            && lhs.tip_glont == rhs.tip_glont
            && lhs.poz_turn == rhs.poz_turn
            && lhs.damage == rhs.damage
            && lhs.range == rhs.range
            && lhs.attk_spd == rhs.attk_spd
            && lhs.pret == rhs.pret
            && lhs.nivel == rhs.nivel;
    }

    friend bool operator!=(const Turn& lhs, const Turn& rhs)
    {
        return !(lhs == rhs);
    }

    static void seteazaContextInamici(std::vector<Inamic>& inamici)
    {
        inamici_context = &inamici;
    }

    void set_poz_turn(const Pozitie& poz_turn_)
    {
        this->poz_turn = poz_turn_;
    }

    [[nodiscard]] const std::string& get_nume_turn() const
    {
        return nume_turn;
    }

    [[nodiscard]] Pozitie getPoz_pos() const
    {
        return poz_turn;
    }

    [[nodiscard]] int get_Pret() const
    {
        return pret[nivel - 1];
    }

    [[nodiscard]] int get_nivel() const
    {
        return nivel;
    }

    void cresteNivel()
    {
        if (nivel <= 4)
            nivel++;
    }
protected:
    [[nodiscard]] bool detecteazaInamic(const Inamic& inamic) const;
public:
    virtual void ataca(Inamic& inamic) const = 0;
    [[nodiscard]] double distanta(const Pozitie& poz1, const Pozitie& poz2) const
    {
        double const dx = poz1.getX() - poz2.getX();
        double const dy = poz1.getY() - poz2.getY();
        return sqrt(dx * dx + dy * dy);
    }

};

bool Turn::detecteazaInamic(const Inamic& inamic) const
{
        double const dist = distanta(inamic.get_Poz_Inamic(), poz_turn);

        if (range[nivel - 1] >= dist)
            return true;
    return false;
}

// void Turn::ataca(Inamic& inamic) const
// {
//     if (detecteazaInamic(inamic))
//     {
//         inamic.iaDamage(damage[nivel - 1]);
//         std::cout << "Turnul " << nume_turn << " a lovit inamicul " << inamic << std::endl;
//     }
// }


class TurnInvatat : public Turn   // critical chance
{
    std::vector<double> sansa_crit;
    std::vector<double> val_crit;

public:

    TurnInvatat(const std::string& nume_t,
            const Glont& tip_g,
            const std::vector<int>& dmg,
            const std::vector<double>& rng,
            const std::vector<int>& atk,
            const std::vector<int>& prt,
            const int& niv,
            const std::vector<double>& sc,
            const std::vector<double>& vc) : Turn(nume_t, tip_g, dmg, rng, atk, prt, niv), sansa_crit{sc}, val_crit{vc} {}

    ~TurnInvatat() override = default;

    void afisare(std::ostream& os) const override
    {
        os << "cu sansa crit de " << sansa_crit[nivel - 1] * 100 << "%";
    }

    [[nodiscard]] std::shared_ptr<Turn> clone() const override { return std::make_shared<TurnInvatat>(*this); }

    void ataca(Inamic& inamic) const override;

private:
    [[nodiscard]] bool sansaCritHit() const;
};

bool TurnInvatat::sansaCritHit() const
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution dist(0.0, 1.0);
    return dist(gen) < sansa_crit[nivel - 1];
}

void TurnInvatat::ataca(Inamic& inamic) const
{
    if (detecteazaInamic(inamic))
    {
        if (sansaCritHit())
        {
            inamic.iaDamage(static_cast<int>(damage[nivel - 1] * val_crit[nivel - 1]));
            std::cout << "Turnul " << *this << " a lovit inamicul cu critical hit\n" << inamic << "\n";
        }
        else
        {
            inamic.iaDamage(damage[nivel - 1]);
            std::cout << "Turnul " << *this << " a lovit inamicul fara critical hit\n" << inamic << std::endl;
        }
    }
}


class TurnRedbull : public Turn  // magic damage
{
public:
    TurnRedbull(const std::string& nume_t,
            const Glont& tip_g,
            const std::vector<int>& dmg,
            const std::vector<double>& rng,
            const std::vector<int>& atk,
            const std::vector<int>& prt,
            const int& niv) : Turn(nume_t, tip_g, dmg, rng, atk, prt, niv) {}
    ~TurnRedbull() override = default;

    void afisare(std::ostream& os) const override
    {
        os << "cu damage magic ";
    }

    [[nodiscard]] std::shared_ptr<Turn> clone() const override { return std::make_shared<TurnRedbull>(*this); }


    void ataca(Inamic& inamic) const override;
};

void TurnRedbull::ataca(Inamic& inamic) const
{
    if (detecteazaInamic(inamic))
    {
        if (inamic.rez_la_magie())
        {
            inamic.iaDamage(damage[nivel - 1] / 2);
            std::cout << *this << " a lovit un inamic cu rezistenta la magie\n" << inamic << "\n";
        }
        else
        {
            inamic.iaDamage(damage[nivel - 1]);
            std::cout << "Turnul " << *this << "a lovit inamicul\n" << inamic << std::endl;
        }
    }
}

class TurnSomn : public Turn  // splash damage
{
    double raza_splash;
public:
    TurnSomn(const std::string& nume_t,
                const Glont& tip_g,
                const std::vector<int>& dmg,
                const std::vector<double>& rng,
                const std::vector<int>& atk,
                const std::vector<int>& prt,
                const int& niv,
                const double& raza) : Turn(nume_t, tip_g, dmg, rng, atk, prt, niv), raza_splash{raza} {}
    ~TurnSomn() override = default;

    void afisare(std::ostream& os) const override
    {
        os << "cu splash damage ";
    }

    [[nodiscard]] std::shared_ptr<Turn> clone() const override { return std::make_shared<TurnSomn>(*this); }


    void ataca(Inamic& inamic) const override;
};

void TurnSomn::ataca(Inamic& inamic) const
{
    if (!inamici_context)
        return;

    std::cout << "Turnul " << *this << "loveste pe " << inamic << " si aplica splash:\n";

    for (Inamic& i : *inamici_context)
    {
        double dist = distanta(i.get_Poz_Inamic(), inamic.get_Poz_Inamic());

        if (!i.mort() && dist <= raza_splash)
        {
            i.iaDamage(damage[nivel - 1]);
            std::cout << "-> Inamic " << i << " a primit " << damage[nivel - 1] << " splash damage\n";
        }
    }
}

class TurnIntrebari : public Turn  // long range
{
    double rangeL;
public:
    TurnIntrebari(const std::string& nume_t,
                const Glont& tip_g,
                const std::vector<int>& dmg,
                const std::vector<double>& rng,
                const std::vector<int>& atk,
                const std::vector<int>& prt,
                const int& niv,
                const double& range) : Turn(nume_t, tip_g, dmg, rng, atk, prt, niv), rangeL{range} {}
    ~TurnIntrebari() override = default;

    void afisare(std::ostream& os) const override
    {
        os << "cu range mare ";
    }

    [[nodiscard]] std::shared_ptr<Turn> clone() const override { return std::make_shared<TurnIntrebari>(*this); }

    void ataca(Inamic& inamic) const override;
    bool detecteazaInamic(const Inamic& inamic, const double& range) const;

};

void TurnIntrebari::ataca(Inamic& inamic) const
{
    if (detecteazaInamic(inamic, rangeL))
    {
        inamic.iaDamage(damage[nivel - 1]);
        std::cout << "Turnul " << *this << " a lovit inamicul " << inamic << " la distanta mare\n";
    }
}

bool TurnIntrebari::detecteazaInamic(const Inamic& inamic, const double& range) const
{
    double const dist = distanta(inamic.get_Poz_Inamic(), poz_turn);

    if (range >= dist)
        return true;
    return false;
}


class Jucator
{
    std::string nume_jucator;
    int bani;
    int nr_vieti;
    std::vector<std::shared_ptr<Turn>> turnuri;
public:
    Jucator(const std::string& nume_jucator, int bani, int nr_vieti, const std::vector<std::shared_ptr<Turn>>& turnuri)
        : nume_jucator(nume_jucator),
          bani(bani),
          nr_vieti(nr_vieti),
          turnuri(turnuri)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Jucator& obj)
    {
        return os << "Numele tau: " << obj.nume_jucator << "\n" << "Ai " << obj.bani << " de bani.\n" << "Restante disponibile: " << obj.nr_vieti;
    }


private:
    void pierdeVieti() { nr_vieti--; }

    void castigaBani(const Inamic& inamic) { bani = bani + inamic.getSuma(); }

public:
    [[nodiscard]] const std::vector<std::shared_ptr<Turn>>& get_turnuri() const
    {
        return turnuri;
    }

    [[nodiscard]] int get_nr_vieti() const
    {
        return nr_vieti;
    }

    // [[nodiscard]] int get_bani() const
    // {
    //     return bani;
    // }

    void statusJucator(const Inamic& inamic, const Drum& drum)
    {
        if (inamic.mort())
        {
            castigaBani(inamic);
            std::cout << "Ai " << bani << " bani\n";
        }
        else
            if (inamic.final_drum(drum))
            {
                pierdeVieti();
                std::cout << "Mai ai " << nr_vieti << " RESTANTE disponibile\n";
            }
    }

    bool scadeBani(const int valoare)
    {
        if (bani >= valoare)
        {
            bani = bani - valoare;
            if (bani >= 20)
                std::cout << "Mai ai : " << bani << " de bani\n";
            else
                std::cout << "Mai ai : " << bani << " bani\n";
            return true;
        }
        std::cout << "Nu ai destui bani!\n";
        return false;
    }
private:
    bool alegePozTurn(const std::vector<Pozitie>& p_turnuri, std::shared_ptr<Turn>& T) const;

    void plaseazaTurn(const std::shared_ptr<Turn>& turn)
    {
        if (bani >= turn->get_Pret())
        {
            std::cout << "Ai plasat turnul la pozitia " << turn->getPoz_pos() << std::endl;
            scadeBani(turn->get_Pret());
            turnuri.push_back(turn);
        }
        else
            std::cout << "Nu ai destui bani!\n";
    }

public:
    void alegeSiPlaseazaTurn(const std::vector<std::shared_ptr<Turn>>& turnuriDisponibile, const std::vector<Pozitie>& p_turnuri);

    void upgrade(unsigned long t, const std::vector<int>& upgrade_val);
};

void Jucator::alegeSiPlaseazaTurn(const std::vector<std::shared_ptr<Turn>>& turnuriDisponibile, const std::vector<Pozitie>& p_turnuri)
{
    std::cout << "\nTurnuri disponibile:\n";
    for (auto i = 0ull; i < turnuriDisponibile.size(); i++)
    {
        std::cout << i + 1 << ". " << *turnuriDisponibile[i] << " | Pret: " << turnuriDisponibile[i]->get_Pret() << "\n";
    }

    int alegere;
    std::cout << "Alege un turn (un numar de la 1 la 4) sau apasa 0 pentru a anula: ";
    std::cin >> alegere;
    if (alegere < 0 || alegere > 4)
    {
        std::cout << "Alegere invalida\n";
        return;
    }

    if (alegere == 0)
    {
        std::cout << "Ai anulat\n";
        return;
    }

    std::shared_ptr<Turn> turnAles = turnuriDisponibile[alegere - 1]->clone();

    if (alegePozTurn(p_turnuri, turnAles))
    {
        plaseazaTurn(turnAles);
    }
}

bool Jucator::alegePozTurn(const std::vector<Pozitie>& p_turnuri, std::shared_ptr<Turn>& T) const   // jucatorul trebuie sa aleaga o pozitie valida pe care sa isi amplaseze turnul
{
    float x, y;

    std::cout << "Pozitii posibile: ";

    for (auto i = 0ull; i < p_turnuri.size(); i++)
        if (i != p_turnuri.size() - 1)
            std::cout << p_turnuri[i] << " sau ";
        else
            std::cout << p_turnuri[i] << ": ";

    std::cin >> x >> y;
    const Pozitie pozNoua(x, y);
    bool ok = false;

    for (const auto& t : p_turnuri ) // verific daca poztita noua este valida
        if (t == pozNoua)
        {
            ok = true;
            break;
        }

    if (ok == true)
    {
        for (const auto& p : turnuri)   // verific daca pozitiile turnurilor sunt deja ocupate
            if (p->getPoz_pos() == pozNoua)
            {
                std::cout << "Exista deja un turn pe aceasta pozitie!\n";
                return false;
            }

        if (T->getPoz_pos().getX() == 0 && T->getPoz_pos().getY() == 0)
            T->set_poz_turn(pozNoua);
        return true;
    }
    std::cout << "Pozitie invalida";
    return false;
}

void Jucator::upgrade(const unsigned long t, const std::vector<int>& upgrade_val)
{
    if (turnuri[t - 1]->get_nivel() < 4)
    {
        if (scadeBani(upgrade_val[turnuri[t - 1]->get_nivel()]))
        {
            turnuri[t - 1]->cresteNivel();
            std::cout << "Nivelul nou al turnului " << turnuri[t - 1]->get_nume_turn() <<": " << turnuri[t - 1]->get_nivel() << std::endl;
        }
    }
    else
        std::cout << "Nivel maxim atins\n";
}


// class Level
// {
//     int nr_waves;
//     int suma_initiala;
// };

// class Harta
// {
//
// };

void upgrade_Turn(Jucator& P, const std::vector<int>& upgrade_val)
{
    char al = 'y';
    while (al == 'y')
    {
        std::cout << "Vrei sa faci upgrade unui turn? y/n:\n";
        std::cin >> al;
        if (al == 'y')
        {
            std::cout << "Carui turn vrei sa ii faci upgrade?(alege indexul turnului) \n";
            for (long unsigned int i = 0; i < P.get_turnuri().size(); i++)
                std::cout << i + 1 << ". " << *P.get_turnuri()[i] << std::endl;
            long unsigned int t;
            std::cin >> t;
            if (t >= 1 && t <= P.get_turnuri().size())
                P.upgrade(t, upgrade_val);
            else
                std::cout << "Alege un turn valid!\n";
        }
    }
}

class Joc
{
    Drum drum;
    std::vector<Pozitie> poz_pos_turn;
    std::vector<std::shared_ptr<Turn>> turnuriDisponibile;
    std::vector<std::vector<Inamic>> inamici;
    Jucator jucator;
    int numar_wave;
    std::vector<int> costuri_upgrade;
public:
    Joc() :
        drum{{
            {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0},
            {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {9, 6}, {9, 7}, {9, 8}, {9, 9}, {9, 10}
                }},
        poz_pos_turn{{ {1, 1}, {1, -1}, {7, -1}, {10, 3}, {8, 8} }}, jucator{"Anonim,", 300, 10, {}},
        numar_wave{3},
        costuri_upgrade{{70, 110, 160, 210}}
    {
        Glont g1;
        const std::vector<double> sc = {0, 0.2, 0.6, 0.8};
        const std::vector<double> vc = {1, 1.3, 1.6, 2};
        const std::vector dmgt1 = {4,7,10,13};
        const std::vector dmgt2 = {10,15,20,25};
        const std::vector dmgt3 = {6,13,17,20};
        const std::vector dmgt4 = {2,4,7,10};
        const std::vector<double> rng1 = {1.5,1.7,1.9,2.1};
        const std::vector<double> rng2 = {1.3,1.4,1.5,1.7};
        const std::vector<double> rng3 = {1,1.1,1.2,1.4};
        const std::vector atk_spd = {1,2,3,4};
        const std::vector<int> prt = {70, 110, 160, 210};
        turnuriDisponibile = {
            std::make_shared<TurnInvatat>("Invatat", g1, dmgt1, rng1, atk_spd, prt, 1, sc, vc),
            std::make_shared<TurnRedbull>("Redbull", g1, dmgt3, rng2, atk_spd, prt, 1),
            std::make_shared<TurnSomn>("Somn", g1, dmgt2, rng3, atk_spd, prt, 1, 1.5),
            std::make_shared<TurnIntrebari>("Intrebari", g1, dmgt4, rng3, atk_spd, prt, 1, 3),
        };

        inamici = {
            {
                Inamic{"BD", 10, 5, {1, "mediu"}, {0, 0}, false},
                Inamic{"LMC", 25, 7, {1, "mediu"}, {0, 0}, true},
                Inamic{"GAL", 70, 10, {1, "rapid"}, {0, 0}, false}
            },

            {
                Inamic{"SD", 300, 30, {1, "lent"}, {0, 0}, false},
                Inamic{"LFA", 100, 15, {1, "rapid"}, {0, 0}, true}
            },

            {
                Inamic{"POO", 1000, 100, {1, "lent"}, {0, 0}, true}
            }
        };

        std::string nume;
        std::cout << "Alege un nume: ";
        std::cin >> nume;
        jucator = Jucator{nume, 300, 10, {}};
    }

    void ruleaza();
};

void Joc::ruleaza()
{
    std::cout << jucator << "\n";
    jucator.alegeSiPlaseazaTurn(turnuriDisponibile, poz_pos_turn);

    for (int wave = 0; wave < numar_wave && jucator.get_nr_vieti() > 0; wave++)
    {
        std::cout << "\n--- Wave " << wave + 1 << "/" << numar_wave << " ---\n";
        upgrade_Turn(jucator, costuri_upgrade);

        bool bucla_joc = false;
        while (!bucla_joc)
        {
            char yn;
            std::cout << "Vrei sa amplasezi un turn? y/n: ";
            std::cin >> yn;
            if (yn == 'y')
                jucator.alegeSiPlaseazaTurn(turnuriDisponibile, poz_pos_turn);
            bucla_joc = true;

            for (Inamic& i : inamici[wave])
            {
                if (!i.mort() && !i.final_drum(drum))
                {
                    i.mutaInamic(drum);
                    i.afiseazaPoz(drum);
                    bucla_joc = false;
                }
            }

            for (const auto& t : jucator.get_turnuri())
            {
                for (Inamic& i : inamici[wave])
                {
                    if (!i.mort())
                        t->ataca(i);
                }
            }

            if (!bucla_joc)
            {
                for (const Inamic& i : inamici[wave])
                    jucator.statusJucator(i, drum);
            }

            auto& v = inamici[wave];
            v.erase(std::remove_if(v.begin(), v.end(),
                        [](const Inamic& i) { return i.mort(); }), v.end());

            if (!bucla_joc)
            {
                std::cout << "\n--- Tura urmatoare ---\n";
                std::cin.get();
            }
        }

        std::cout << "\nWave-ul " << wave + 1 << " finalizat!\n";
        std::cin.get();
    }

    if (jucator.get_nr_vieti() <= 0)
        std::cout << "\nGAME OVER! Ai ramas fara RESTANTE disponibile. Ai picat anul...\n";
    else
        std::cout << "\nFELICITARI! Ai trecut anul.\n";
}


int main()
{
    try
    {
        Joc joc;
        joc.ruleaza();
    }catch (const std::exception& e)
    {
        std::cerr << "Eroare" << e.what() << "\n";
    }


    /*const std::vector<double> sc = {0, 0.2, 0.6, 0.8};
    const std::vector<double> vc = {1, 1.3, 1.6, 2};
    const std::vector<Pozitie> traseu = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, // Orizontal (10 pași)
                                             {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {9, 6}, {9, 7}, {9, 8}, {9, 9}, {9, 10} };

    const std::vector<Pozitie> poz_pos_turn = { {1, 1}, {1, -1}, {7, -1}, {10, 3}, {8, 8} };
    const Drum drum(traseu);
    const std::vector dmgt1 = {4,7,10,13};
    const std::vector dmgt2 = {10,15,20,25};
    const std::vector dmgt3 = {6,13,17,20};
    const std::vector dmgt4 = {2,4,7,10};
    const std::vector<double> rng1 = {1.5,1.7,1.9,2.1};
    const std::vector<double> rng2 = {1.3,1.4,1.5,1.7};
    const std::vector<double> rng3 = {1,1.1,1.2,1.4};
    const std::vector atk_spd = {1,2,3,4};
    const std::vector<int> prt = {70, 110, 160, 210};

    Pozitie p1{0, 0};
    Glont g1;
    TurnInvatat t1{"Invatat", g1, dmgt1, rng1, atk_spd, prt, 4, sc, vc};
    TurnRedbull t2{"Redbull", g1, dmgt3, rng2, atk_spd, prt, 4};
    TurnSomn t3{"Somn", g1, dmgt4, rng3, atk_spd, prt, 4, 1.5};

    //std::cout << t1;

    Inamic i{"BD", 45, 34, {4, "df"}, {1,1}, true};
    Inamic i1{"GAL", 75, 14, {4, "df"}, {1,1}, false};

    Inamic* ii = &i;
    Inamic* ii1 = &i1;

    std::vector<Inamic> Inamici = {i, i1};
    Turn::seteazaContextInamici(Inamici);

    t1.ataca(i);
    t2.ataca(i1);
    t3.ataca(i);*/
    return 0;
}

    // sf::RenderWindow window;
    // ///////////////////////////////////////////////////////////////////////////
    // /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    // window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    // window.setVerticalSyncEnabled(true);                                    ///
    // /// window.setFramerateLimit(60);                                       ///
    // ///////////////////////////////////////////////////////////////////////////
    //
    // while(window.isOpen()) {
    //     bool shouldExit = false;
    //     sf::Event e{};
    //     while(window.pollEvent(e)) {
    //         switch(e.type) {
    //         case sf::Event::Closed:
    //             window.close();
    //             break;
    //         case sf::Event::Resized:
    //             std::cout << "New width: " << window.getSize().x << '\n'
    //                       << "New height: " << window.getSize().y << '\n';
    //             break;
    //         case sf::Event::KeyPressed:
    //             std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
    //             if(e.key.code == sf::Keyboard::Escape)
    //                 shouldExit = true;
    //             break;
    //         default:
    //             break;
    //         }
    //     }
    //     if(shouldExit) {
    //         window.close();
    //         break;
    //     }
    //     using namespace std::chrono_literals;
    //     std::this_thread::sleep_for(300ms);
    //
    //     window.clear();
    //     window.display();
    // }
    // return 0;

