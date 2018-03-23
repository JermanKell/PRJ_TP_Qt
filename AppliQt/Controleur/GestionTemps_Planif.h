#ifndef DEF_GESTION_TEMPS_H
#define DEF_GESTION_TEMPS_H

class TimeHandler {
public:
	TimeHandler() {

	}
	~TimeHandler() {

	}
	inline int DecalRDVSup(int finPrecRDV) {
		int debCren = 0;
		int finHrdv = finPrecRDV / 100;
		int finMrdv = finPrecRDV % 100;
		if (finMrdv < 15)
			debCren = 15 - finMrdv;
		if ((finMrdv >= 15) && (finMrdv < 30))
			debCren = 30 - finMrdv;
		if ((finMrdv >= 30) && (finMrdv < 45))
			debCren = 45 - finMrdv;
		if ((finMrdv >= 45) && (finMrdv < 60))
			debCren = 60 - finMrdv;

		finMrdv += debCren;
		if (finMrdv == 60) {
			finHrdv++;
			finMrdv = 0;
		}			

		return (finHrdv * 100) + finMrdv;
	}

	inline int EndDateRDV(int LastHRDV, int TDuration) {
		LastHRDV += TDuration;
		int finHrdv = LastHRDV / 100;
		int finMrdv = LastHRDV % 100;

		while (finMrdv >= 60) {
			finMrdv -= 60;
			finHrdv += 1;
		}
		LastHRDV = (finHrdv * 100) + finMrdv;

		return LastHRDV;
    }

    inline int CalculEcart(int TDebut, int TFin) {
        int HDeb = TDebut / 100;
        int MDeb = TDebut % 100;
        int HFin = TFin / 100;
        int MFin = TFin % 100;

        int ecart = 0;
        bool var = true;

        while (var) {
            if ((HDeb != HFin) && (MDeb != MFin)) {
                var = false;
            }
            if (MDeb < 61) {
                MDeb = 0;
                HDeb++;
            }
            MDeb++;
            ecart++;
        }
        return ecart;
    }
};

#endif // !DEF_GESTION_TEMPS_H

