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
        for (auto const i : obj.traseu)
            return os << i;
        return os;
    }

    // [[nodiscard]] std::vector<Pozitie> getTraseu() const
    // {
    //     return traseu;
    // }

    [[nodiscard]] Pozitie getPozitie(const int index) const
    {
        if (index >= 0 && index < traseu.size())
            return traseu[index];

        return traseu.back();
    }

    [[nodiscard]] unsigned long long getLungime() const
    {
        return traseu.size();
    }
};

class Inamici
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
    int index_pozitie;

public:
    Inamici(const std::string& nume, const int hp, const int sum, const movement_speed& move_s,
        const bool& rez, const Pozitie& poz_c) :
    nume_inamic{nume},
    HP{hp},
    suma{sum},
    move_spd{move_s},
    rez_magie{rez},
    poz_curenta{poz_c},
    index_pozitie{0}{}

    Inamici(const Inamici& other) :
    nume_inamic{other.nume_inamic},
    HP{other.HP},
    suma{other.suma},
    move_spd{other.move_spd},
    rez_magie{other.rez_magie},
    poz_curenta{other.poz_curenta},
    index_pozitie{other.index_pozitie}
    { std::cout << "cc inamici\n"; }

    ~Inamici() = default;

    Inamici& operator=(const Inamici& other)
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

    friend bool operator==(const Inamici& other1, const Inamici& other2)
    {
        if (other1.HP == other2.HP && other1.nume_inamic == other2.nume_inamic &&
            other1.move_spd.val == other2.move_spd.val && other1.move_spd.tip == other2.move_spd.tip &&
            other1.rez_magie == other2.rez_magie && other1.poz_curenta == other2.poz_curenta)
            return true;
        return false;
    }


    friend std::ostream& operator<<(std::ostream& os, const Inamici& obj)
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

    [[nodiscard]] bool final_drum(const Drum& drum) const
    {
        if (index_pozitie < drum.getLungime() - 1)
            return false;
        return true;
    }

    void afiseazaPoz(const Drum& drum) const
    {
        if (final_drum(drum))
            std::cout << nume_inamic << " a ajuns la final!\n";
        else
            std::cout << nume_inamic << " se afla la pozitia " << poz_curenta << std::endl;
    }

    [[nodiscard]] int getSuma() const { return suma; }
};

void Inamici::mutaInamic(const Drum& drum)
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
    Pozitie poz_curenta1;
    Pozitie poz_curenta2;
    Pozitie poz_finala;

public:

    Glont(const int viteza, const Pozitie& poz_plecare, const Pozitie& poz_curenta1, const Pozitie& poz_curenta2,
        const Pozitie& poz_finala)
        : viteza(viteza),
          poz_plecare(poz_plecare),
          poz_curenta1(poz_curenta1),
          poz_curenta2(poz_curenta2),
          poz_finala(poz_finala)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Glont& object)
    {
        return os << object.viteza << object.poz_plecare << object.poz_curenta1 << object.poz_curenta2 <<
            object.poz_finala;
    }
};

class Turnuri
{
    std::string nume_turn;
    Glont tip_glont;
    std::vector<Pozitie> poz_posibile;
    std::vector<int> damage;
    std::vector<float> range;
    std::vector<int> attk_spd;
    std::vector<int> pret;
    int nivel;

public:
    Turnuri(const std::string& nume_t,
            const Glont& tip_g,
            const std::vector<Pozitie>& poz_pos,
            const std::vector<int>& dmg,
            const std::vector<float>& rng,
            const std::vector<int>& atk,
            const std::vector<int>& prt,
            const int& niv) :   nume_turn{nume_t},
                                tip_glont{tip_g},
                                poz_posibile{poz_pos},
                                damage{dmg},
                                range{rng},
                                attk_spd{atk},
                                pret{prt},
                                nivel{niv} {}

    friend std::ostream& operator<<(std::ostream& os, const Turnuri& object)
    {
        return os << object.nume_turn << object.tip_glont << object.nivel;
    }

    [[nodiscard]] Pozitie getPoz_pos() const
    {
        return poz_posibile[nivel];
    }

    [[nodiscard]] int getPret() const
    {
        return pret[nivel];
    }

    void cresteNivel()
    {
        if (nivel <= 4)
            nivel++;
    }

private:
    [[nodiscard]] bool detecteazaInamic(const Inamici& inamic) const;
public:
    void ataca(Inamici& inamic) const
    {
        if (detecteazaInamic(inamic))
        {
            inamic.set_hp(inamic.getHP() - damage[nivel]);
            std::cout << "Turnul " << nume_turn << " a lovit "
                  << "! HP ramas: " << inamic.getHP() << std::endl;
        }
    }
};

bool Turnuri::detecteazaInamic(const Inamici& inamic) const
{
    for (const auto poz : poz_posibile)
    {
        float dx = inamic.getPozInamic().getX() - poz.getX();
        float dy = inamic.getPozInamic().getY() - poz.getY();

        if (range[nivel] >= std::sqrt(dx * dx + dy * dy))
            return true;
    }
    return false;
}

class Jucator
{
    std::string nume_jucator;
    int bani;
    int nr_vieti;
    std::vector<Turnuri> turnuri;
public:
    Jucator(const std::string& nume_jucator, int bani, int nr_vieti, const std::vector<Turnuri>& turnuri)
        : nume_jucator(nume_jucator),
          bani(bani),
          nr_vieti(nr_vieti),
          turnuri(turnuri)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Jucator& obj)
    {
        return os << obj.nume_jucator << " " << obj.bani << " " << obj.nr_vieti;
    }

    void plaseazaTurn(const Turnuri& turn)
    {
        if (bani >= turn.getPret())
        {
            bani = bani - turn.getPret();
            turnuri.push_back(turn);
        }
    }

    void pierdeVieti() { nr_vieti--; }

    void castigaBani(const Inamici& Inamic){ bani = bani + Inamic.getSuma(); }

};

// class Joc
// {
//
// };

// class Harta
// {
//
// };



int main()
{
    const std::vector<Pozitie> traseu = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0} };
    const std::vector<Pozitie> traseu1 = { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1} };
    const Drum drum(traseu);
    const std::vector<int> dmg = {1,2,3,4};
    const std::vector<float> rng = {1,2,3,4};
    const std::vector<int> atk = {1,2,3,4};
    const std::vector<int> prt = {1,2,3,4};
    int nivel = 1;

    Pozitie p1{1, 2};
    Pozitie p2(p1), p3(p2), p4(p3);
    Glont g1{2, p1, p2, p3, p4};
    Turnuri t1{"Invatat", g1, traseu1, dmg, rng, atk, prt, nivel};
    std::vector<Turnuri> turnuri;
    turnuri.push_back(t1);
    Jucator P1{"stefi", 300, 10, turnuri};

    Inamici i1{"BD", 10, 5, {1, "lent"}, false, {0, 0}};

    P1.plaseazaTurn(t1);

    for (int i = 0; i < drum.getLungime(); i++)
    {
        i1.afiseazaPoz(drum);
        t1.ataca(i1);
        i1.mutaInamic(drum);
    }

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

