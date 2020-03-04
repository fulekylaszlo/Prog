// sejtszal.cpp
//
// …letj·tÈk rajzolÛ
// ProgramozÛ P·ternoszter
//
// Copyright (C) 2011, B·tfai Norbert, nbatfai@inf.unideb.hu, nbatfai@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthetı illetve mÛdosÌthatÛ a
// Free Software Foundation ·ltal kiadott GNU General Public License
// dokumentum·ban leÌrtak; ak·r a licenc 3-as, ak·r (tetszıleges) kÈsıbbi
// v·ltozata szerint.
//
// Ez a program abban a remÈnyben ker¸l kˆzread·sra, hogy hasznos lesz,
// de minden egyÈb GARANCIA N…LK‹L, az ELADHAT”S¡GRA vagy VALAMELY C…LRA
// VAL” ALKALMAZHAT”S¡GRA valÛ sz·rmaztatott garanci·t is beleÈrtve.
// Tov·bbi rÈszleteket a GNU General Public License tartalmaz.
//
// A felhaszn·lÛnak a programmal egy¸tt meg kell kapnia a GNU General
// Public License egy pÈld·ny·t; ha mÈgsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.
//
//
// Version history:
//
// 0.0.1    A kÈt oszt·ly tervezÈsÈnek fı szempontja az volt, hogy
// ne vagy alig k¸lˆnbˆzzˆn az elsı C++-os pÈld·tÛl, a MandelostÛl:
// http://progpater.blog.hu/2011/02/26/tan_csodallak_amde_nem_ertelek_de_kepzetem_hegyvolgyedet_bejarja
// ezÈrt az olyan kÈnyesebb dolgokkal, hogy kezelj¸k a racsIndex-et a
// kÈt oszt·lyra bontott C++ megold·sban, amikor Ìrjuk ·t a Jav·sbÛl, nem foglalkoztunk
// a kiindulÛ Jav·s: http://www.tankonyvtar.hu/informatika/javat-tanitok-1-2-080904-1
// (a baz·r eszme: ÑRelease Early, Release Often" Ìrjuk ki a posztra)
//

#include "sejtszal.h"

SejtSzal::SejtSzal(bool ***racsok, int szelesseg, int magassag, int varakozas, SejtAblak *sejtAblak)
{
    this->racsok = racsok;
    this->szelesseg = szelesseg;
    this->magassag = magassag;
    this->varakozas = varakozas;
    this->sejtAblak = sejtAblak;

    racsIndex = 0;
}

/**
   * Az kÈrdezett ·llapotban lÈvı nyolcszomszÈdok sz·ma.
   *
   * @param   r·cs    a sejttÈr r·cs
   * @param   sor     a r·cs vizsg·lt sora
   * @param   oszlop  a r·cs vizsg·lt oszlopa
   * @param   ·llapor a nyolcszomszÈdok vizsg·lt ·llapota
   * @return int a kÈrdezett ·llapotbeli nyolcszomszÈdok sz·ma.
   */
int SejtSzal::szomszedokSzama(bool **racs,
                              int sor, int oszlop, bool allapot) {
    int allapotuSzomszed = 0;
    // A nyolcszomszÈdok vÈgigzongor·z·sa:
    for(int i=-1; i<2; ++i)
        for(int j=-1; j<2; ++j)
            // A vizsg·lt sejtet mag·t kihagyva:
            if(!((i==0) && (j==0))) {
        // A sejttÈrbıl szÈlÈnek szomszÈdai
        // a szembe oldalakon ("periÛdikus hat·rfeltÈtel")
        int o = oszlop + j;
        if(o < 0)
            o = szelesseg-1;
        else if(o >= szelesseg)
            o = 0;

        int s = sor + i;
        if(s < 0)
            s = magassag-1;
        else if(s >= magassag)
            s = 0;

        if(racs[s][o] == allapot)
            ++allapotuSzomszed;
    }

    return allapotuSzomszed;
}

/**
 * A sejttÈr idıbeli fejlıdÈse a John H. Conway fÈle
 * Èletj·tÈk sejtautomata szab·lyai alapj·n tˆrtÈnik.
 * A szab·lyok rÈszletes ismertetÈsÈt l·sd pÈld·ul a
 * [MATEK J¡T…K] hivatkoz·sban (Cs·k·ny BÈla: DiszkrÈt
 * matematikai j·tÈkok. Polygon, Szeged 1998. 171. oldal.)
 */
void SejtSzal::idoFejlodes() {

    bool **racsElotte = racsok[racsIndex];
    bool **racsUtana = racsok[(racsIndex+1)%2];

    for(int i=0; i<magassag; ++i) { // sorok
        for(int j=0; j<szelesseg; ++j) { // oszlopok

            int elok = szomszedokSzama(racsElotte, i, j, SejtAblak::ELO);

            if(racsElotte[i][j] == SejtAblak::ELO) {
                /* …lı Èlı marad, ha kettı vagy h·rom Èlı
             szomszedja van, k¸lˆnben halott lesz. */
                if(elok==2 || elok==3)
                    racsUtana[i][j] = SejtAblak::ELO;
                else
                    racsUtana[i][j] = SejtAblak::HALOTT;
            }  else {
                /* Halott halott marad, ha h·rom Èlı
             szomszedja van, k¸lˆnben Èlı lesz. */
                if(elok==3)
                    racsUtana[i][j] = SejtAblak::ELO;
                else
                    racsUtana[i][j] = SejtAblak::HALOTT;
            }
        }
    }
    racsIndex = (racsIndex+1)%2;
}


/** A sejttÈr idıbeli fejlıdÈse. */
void SejtSzal::run()
{
    while(true) {
        QThread::msleep(varakozas);
        idoFejlodes();
        sejtAblak->vissza(racsIndex);
    }

}

SejtSzal::~SejtSzal()
{
}
