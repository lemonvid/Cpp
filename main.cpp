#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <type_traits>
#include <ios>
#include <limits>

using       towers_t    =   std::stack<int>;

void        hanoi           (unsigned const char ring_nb = 3);
void        printStatus     (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned const int try_nb = 0);
void        moveRings       (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned int try_nb);
const bool  win             (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned const int try_nb);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    hanoi();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void hanoi (unsigned const char ring_nb)
{
    if  (ring_nb && ring_nb > 10)
    {
        std::cout << "Erreur : Nombre de disques trop élevé ( > 10 ) ou insuffisant ( < 0 )" << std::endl;
        return;
    }

    else
    {
        std::vector<towers_t> towers {};             // declaration of the board game
        towers.resize(3);                            // resize to have 3 towers
        for(unsigned char i {0}; i != ring_nb; i++)  // loop to set all of the rings on the first tower
            { towers[0].push(i); }


        unsigned int try_nb {0};
        printStatus(towers, ring_nb, try_nb);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// Print the current status of the game
void printStatus (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned const int try_nb)
{
    while (!win(towers, ring_nb, try_nb))
    {
        std::cout << "\033cPlus un nombre est petit et plus le disque est grand" << "\n\n";
        std::cout << "| Tour 1 |" << "\t" << "| Tour 2 |" << "\t" << "| Tour 3 |" << "\n";
        std::cout << " ════════ " << "\t" << " ════════ " << "\t" << " ════════ " << "\n\n";


        { // NEW SCOPE
            auto tow0_tmp {towers[0]};
            auto tow1_tmp {towers[1]};
            auto tow2_tmp {towers[2]};

            for ( unsigned char i { 0 }; i < ring_nb; ++i )
            {
            /////////////////////////////////////////////////////////////////////// // tow0

                if  ( !tow0_tmp.empty() ) // tow0
                    { std::cout << "|   " << tow0_tmp.top() << "    |\t"; tow0_tmp.pop(); }
                else
                    { std::cout << "|        |\t"; }

                /////////////////////////////////////////////////////////////////////// // tow1

                if  ( !tow1_tmp.empty() )
                    { std::cout << "|   " << tow1_tmp.top() << "    |\t"; tow1_tmp.pop(); }
                else
                    { std::cout << "|        |\t"; }

                /////////////////////////////////////////////////////////////////////// // tow2

                if  ( !tow2_tmp.empty() )
                    { std::cout << "|   " << tow2_tmp.top() << "    |\n"; tow2_tmp.pop(); }
                else
                    { std::cout << "|        |\n"; }
            }   // END OF FOR LOOP
        }   // END OF NEW SCOPE

        std::cout << "\n\tNombre de coups actuel : " << try_nb << std::endl;
        moveRings(towers, ring_nb, try_nb);
    } // END OF WHILE(!win) LOOP
} // END OF FUNCTION


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move the rings from tower to tower
void moveRings (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned int try_nb)
{
    unsigned int from {0};
    unsigned int to   {0};

    std::cout << "\nDes nombres entiers sont attendus\n";

    std::cout << "\nTour de depart : ";
    if( !(std::cin  >> from ) )
       {
           std::cin.clear();
           std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
           printStatus(towers, ring_nb, try_nb);
       }

    std::cout << "\nTour d'arrivee : ";
    if( !(std::cin  >> to ) )
       {
           std::cin.clear();
           std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
           printStatus(towers, ring_nb, try_nb);
       }

    std::cout << std::endl;

    --from;
    --to;

    if ( (from >= 0 && from <= 2) && (to >= 0 && to <= 2) && (from != to) )
    {
        if ( !towers[from].empty() )
        {
            if  ( towers[to].empty() || towers[from].top() > towers[to].top() )
            {
                towers[to].push(towers[from].top());
                towers[from].pop();
                ++try_nb;
            }
        }
    }


    printStatus (towers, ring_nb, try_nb);
}


///////////////////////////////////////////
//////////// Are you a winner ? ///////////
///////////////////////////////////////////
const bool win (std::vector<towers_t> & towers, unsigned const char ring_nb, unsigned const int try_nb)
{
    if  (towers[2].size() == static_cast<std::size_t> (ring_nb) )
    {
        auto min_try = std::pow(2, ring_nb) -1;
        std::cout << "Gagner ! En " << try_nb << " coups !" << "\n";
        std::cout << "Le nombre minimum de coups etait de " << min_try << std::endl;
        return true;
    }

    else
        { return false; }
}
