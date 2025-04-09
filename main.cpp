#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

class Pozitie
{
    float x;
    float y;
public:
    Pozitie(const float& X, const float& Y) : x{X}, y{Y}{}

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
    bool rez_magie;
    Pozitie poz_curenta;
    unsigned long long index_pozitie;

public:
    Inamic(const std::string& nume, const int hp, const int sum, const movement_speed& move_s,
        const bool& rez, const Pozitie& poz_c) :
    nume_inamic{nume},
    HP{hp},
    suma{sum},
    move_spd{move_s},
    rez_magie{rez},
    poz_curenta{poz_c},
    index_pozitie{0}{}

    Inamic(const Inamic& other) :
    nume_inamic{other.nume_inamic},
    HP{other.HP},
    suma{other.suma},
    move_spd{other.move_spd},
    rez_magie{other.rez_magie},
    poz_curenta{other.poz_curenta},
    index_pozitie{other.index_pozitie}
    {}

    ~Inamic() = default;

    Inamic& operator=(const Inamic& other)
    {
        if (this == &other)
            return *this;
        nume_inamic = other.nume_inamic;
        HP = other.HP;
        move_spd.val = other.move_spd.val;
        move_spd.tip = other.move_spd.tip;
        rez_magie = other.rez_magie;
        poz_curenta = other.poz_curenta;
        return *this;
    }

    friend bool operator==(const Inamic& other1, const Inamic& other2)
    {
        if (other1.HP == other2.HP && other1.nume_inamic == other2.nume_inamic &&
            other1.move_spd.val == other2.move_spd.val && other1.move_spd.tip == other2.move_spd.tip &&
            other1.rez_magie == other2.rez_magie && other1.poz_curenta == other2.poz_curenta)
            return true;
        return false;
    }


    friend std::ostream& operator<<(std::ostream& os, const Inamic& obj)
    {
        return os << "HP: " << obj.HP << " nume_inamic: " << obj.nume_inamic;
    }

    void mutaInamic(const Drum& drum);

    [[nodiscard]] Pozitie getPozInamic() const
    {
        return poz_curenta;
    }
    [[nodiscard]] int getHP() const
    {
        return HP;
    }

    void set_hp(const int hp)
    {
        HP = hp;
    }

    [[nodiscard]] bool mort() const    // logica de inamic mort ?????
    {
        return HP <= 0;
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

};

void Inamic::mutaInamic(const Drum& drum)
{
    if (index_pozitie < drum.getLungime() - 1)
    {
        index_pozitie++;
        poz_curenta = drum.getPozitie(index_pozitie);
    }
}

class Glont
{
    int viteza;
    Pozitie poz_plecare;
    Pozitie poz_finala;

public:

    Glont(const int viteza, const Pozitie& poz_plecare, const Pozitie& poz_finala)
        : viteza(viteza),
          poz_plecare(poz_plecare),
          poz_finala(poz_finala)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Glont& object)
    {
        return os << object.viteza << object.poz_plecare << object.poz_finala;
    }
};

class Turn
{
    std::string nume_turn;
    Glont tip_glont;
    Pozitie poz_turn;   // nici asta
    std::vector<int> damage;
    std::vector<float> range;
    std::vector<int> attk_spd;
    std::vector<int> pret;
    int nivel;

public:
    Turn(const std::string& nume_t,
            const Glont& tip_g,
            const std::vector<int>& dmg,
            const std::vector<float>& rng,
            const std::vector<int>& atk,
            const std::vector<int>& prt,
            const int& niv) :   nume_turn{nume_t},
                                tip_glont{tip_g},
                                poz_turn{0, 0},
                                damage{dmg},
                                range{rng},
                                attk_spd{atk},
                                pret{prt},
                                nivel{niv} {}

    friend std::ostream& operator<<(std::ostream& os, const Turn& object)
    {
        return os << object.nume_turn << " Nivel: " << object.nivel;
    }

    void set_poz_turn(const Pozitie& poz_turn)
    {
        this->poz_turn = poz_turn;
    }

    [[nodiscard]] Pozitie getPoz_pos() const
    {
        return poz_turn;
    }

    [[nodiscard]] int getPret() const
    {
        return pret[nivel - 1];
    }

    void cresteNivel()
    {
        if (nivel <= 4)
            nivel++;
    }



private:
    [[nodiscard]] bool detecteazaInamic(const Inamic& inamic) const;
public:
    void ataca(Inamic& inamic) const;
};

bool Turn::detecteazaInamic(const Inamic& inamic) const
{
        float const dx = inamic.getPozInamic().getX() - poz_turn.getX();
        float const dy = inamic.getPozInamic().getY() - poz_turn.getY();

        if (range[nivel - 1] >= std::sqrt(dx * dx + dy * dy))
            return true;
    return false;
}

void Turn::ataca(Inamic& inamic) const
{
    if (detecteazaInamic(inamic))
    {
        inamic.set_hp(inamic.getHP() - damage[nivel - 1]);
        std::cout << "Turnul " << nume_turn << " a lovit "
              << "! HP ramas: " << inamic.getHP() << std::endl;
    }
}

class Jucator
{
    std::string nume_jucator;
    int bani;
    int nr_vieti;
    std::vector<Turn> turnuri;
public:
    Jucator(const std::string& nume_jucator, int bani, int nr_vieti, const std::vector<Turn>& turnuri)
        : nume_jucator(nume_jucator),
          bani(bani),
          nr_vieti(nr_vieti),
          turnuri(turnuri)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Jucator& obj)
    {
        return os << obj.nume_jucator << " " << obj.bani << " " << obj.nr_vieti;
    }


private:
    void pierdeVieti() { nr_vieti--; }

    void castigaBani(const Inamic& inamic) { bani = bani + inamic.getSuma(); }

public:
    [[nodiscard]] std::vector<Turn> get_turnuri() const
    {
        return turnuri;
    }

    [[nodiscard]] int get_nr_vieti() const
    {
        return nr_vieti;
    }

    [[nodiscard]] int get_bani() const
    {
        return bani;
    }

    void actiuniJucator(const Inamic& inamic, const Drum& drum)
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
private:
    bool alegePozTurn(const std::vector<Pozitie>& p_turnuri, Turn& T) const;

    void plaseazaTurn(const Turn& turn)
    {
        if (bani >= turn.getPret())
        {
            bani = bani - turn.getPret();
            std::cout << "Bani: " << bani << std::endl;
            turnuri.push_back(turn);
        }
        else
            std::cout << "Nu ai destui bani!\n";
    }

public:
    void alegeSiPlaseazaTurn(const std::vector<Turn>& turnuriDisponibile, const std::vector<Pozitie>& p_turnuri);
};

void Jucator::alegeSiPlaseazaTurn(const std::vector<Turn>& turnuriDisponibile, const std::vector<Pozitie>& p_turnuri)
{
    std::cout << "\nTurnuri disponibile:\n";
    for (long long unsigned int i = 0; i < turnuriDisponibile.size(); i++)
    {
        std::cout << i + 1 << ". " << turnuriDisponibile[i] << " | Pret: " << turnuriDisponibile[i].getPret() << "\n";
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

    Turn turnAles = turnuriDisponibile[alegere - 1];

    if (alegePozTurn(p_turnuri, turnAles))
    {
        plaseazaTurn(turnAles);
    }
}

bool Jucator::alegePozTurn(const std::vector<Pozitie>& p_turnuri, Turn& T) const   // jucatorul trebuie sa aleaga o pozitie valida pe care sa isi amplaseze turnul
{
    float x, y;

    std::cout << "Pozitii posibile: ";

    for (long long unsigned int i = 0; i < p_turnuri.size(); i++)
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
            if (p.getPoz_pos() == pozNoua)
            {
                std::cout << "Exista deja un turn pe aceasta pozitie!\n";
                return false;
            }

        if (T.getPoz_pos().getX() == 0 && T.getPoz_pos().getY() == 0)
            T.set_poz_turn(pozNoua);
        return true;
    }
    std::cout << "Pozitie invalida";
    return false;
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



int main()
{

    const std::vector<Pozitie> traseu = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, // Orizontal (10 pași)
                                             {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {9, 6}, {9, 7}, {9, 8}, {9, 9}, {9, 10} };

    const std::vector<Pozitie> poz_pos_turn = { {1, 1}, {1, -1}, {7, -1}, {10, 3}, {8, 8} };
    const Drum drum(traseu);
    const std::vector dmgt1 = {4,7,10,13};
    const std::vector dmgt2 = {10,15,20,25};
    const std::vector dmgt3 = {6,13,17,20};
    const std::vector dmgt4 = {2,4,7,10};
    const std::vector<float> rng1 = {1.5,1.7,1.9,2.1};
    const std::vector<float> rng2 = {1.3,1.4,1.5,1.7};
    const std::vector<float> rng3 = {1,1.1,1.2,1.4};
    const std::vector atk_spd = {1,2,3,4};
    const std::vector prt = {70,110,160,210};
    int nivel = 1;

    Pozitie p1{0, 0};
    Glont g1{2, p1, p1};
    Turn t1{"Invatat", g1, dmgt1, rng1, atk_spd, prt, nivel};
    Turn t2{"Somn", g1, dmgt2, rng1, atk_spd, prt, nivel};
    Turn t3{"Redbull", g1, dmgt3, rng2, atk_spd, prt, nivel};
    Turn t4{"Intrebari", g1, dmgt4, rng3, atk_spd, prt, nivel};


    std::vector<Turn> turnuriDisponibile = {t1, t2, t3, t4};
    std::vector<Turn> turnuri;
    Jucator P1{"stefi", 300, 10, turnuri};

    Inamic i1{"BD", 10, 5, {1, "mediu"}, false, {0, 0}};
    Inamic i2{"SD", 300, 30, {1, "lent"}, false, {0, 0}};
    Inamic i3{"LFA", 100, 15, {1, "rapid"}, false, {0, 0}};
    Inamic i4{"GAL", 70, 10, {1, "rapid"}, false, {0, 0}};
    Inamic i5{"LMC", 25, 7, {1, "mediu"}, false, {0, 0}};
    Inamic i6{"POO", 1000, 100, {1, "lent"}, false, {0, 0}};

    std::vector<Inamic> inamici{i1, i1, i1};
    while (P1.get_bani() >= prt[nivel - 1])
    {
        P1.alegeSiPlaseazaTurn(turnuriDisponibile, poz_pos_turn);
        for (auto& turn : P1.get_turnuri())
            std::cout << turn << std::endl;
    }

    while (!inamici.empty())
    {
        for (auto& inamic : inamici)
        {
            inamic.afiseazaPoz(drum);
            if (inamic.final_drum(drum))
                inamici.pop_back();
            else
                inamic.mutaInamic(drum);
            for (auto& turn : P1.get_turnuri())
            {
                turn.ataca(inamic);

                P1.actiuniJucator(inamic, drum);
                if (inamic.mort())
                    inamici.pop_back();
                if (inamici.empty())
                    break;
            }
        }
        if (P1.get_nr_vieti() <= 0)
        {
            std::cout << "Ai luat RESTANTA la toate materiile...o sa repeti anul...\n";
            break;
        }
    }

    // for (auto& inamic : inamici)
    // {
    //     inamic.afiseazaPoz(drum);
    //     if (P1.alegeSiPlaseazaTurn(turnuriDisponibile, poz_pos_turn))
    //     {
    //         for (auto& turn : P1.get_turnuri())
    //         {
    //             turn.ataca(inamic);
    //         }
    //     }
    // }













    // //P1.plaseazaTurn(t1);
    //
    // for (unsigned long long i = 0; i < drum.getLungime(); i++)
    // {
    //     if (!i1.mort())
    //     {
    //         i1.afiseazaPoz(drum);
    //         t1.ataca(i1);
    //         P1.actiuniJucator(i1, drum);
    //         i1.mutaInamic(drum);
    //     }
    // }
    //std::cout << P1;
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

