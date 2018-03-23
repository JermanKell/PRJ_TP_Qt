#ifndef DEF_FONC_SORT_PATIENT
#define DEF_FONC_SORT_PATIENT

#include "Modele/client.h"
#include <algorithm>

using namespace std;

class FoncteurSortResource {

public:
    bool operator()(Client & client1, Client & client2) {
        double indPrio1 = (client1.getPriorite() * 100) + (client1.getNomRessources().size() * 10) + client1.getDureeRDV();
        double indPrio2 = (client2.getPriorite() * 100) + (client2.getNomRessources().size() * 10) + client2.getDureeRDV();

        return indPrio1 > indPrio2;
	}
};

#endif // !DEF_FONC_SORT_PATIENT
