// sejtablak.cpp
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

#include "sejtablak.h"

SejtAblak::SejtAblak(int szelesseg, int magassag, QWidget *parent)
: QMainWindow(parent)
{
  setWindowTitle("A John Horton Conway-fÈle Èletj·tÈk");
  
  this->magassag = magassag;
  this->szelesseg = szelesseg;

  
  cellaSzelesseg = 6;
  cellaMagassag = 6;

  setFixedSize(QSize(szelesseg*cellaSzelesseg, magassag*cellaMagassag));
  
  racsok = new bool**[2];
  racsok[0] = new bool*[magassag];
  for(int i=0; i<magassag; ++i)
    racsok[0][i] = new bool [szelesseg];
  racsok[1] = new bool*[magassag];
  for(int i=0; i<magassag; ++i)
    racsok[1][i] = new bool [szelesseg];

  racsIndex = 0;
  racs = racsok[racsIndex];

  // A kiindulÛ racs minden cell·ja HALOTT
  for(int i=0; i<magassag; ++i)
    for(int j=0; j<szelesseg; ++j)
      racs[i][j] = HALOTT;
    // A kiindulÛ racsra "ELOlÈnyeket" helyez¸nk
    //siklo(racs, 2, 2);

    sikloKilovo(racs, 5, 60);

  eletjatek = new SejtSzal(racsok, szelesseg, magassag, 120, this);

  eletjatek->start();
  
}

void SejtAblak::paintEvent(QPaintEvent*) {
  QPainter qpainter(this);
  
  // Az aktu·lis
  bool **racs = racsok[racsIndex];
  // racsot rajzoljuk ki:
  for(int i=0; i<magassag; ++i) { // vÈgig lÈpked a sorokon
    for(int j=0; j<szelesseg; ++j) { // s az oszlopok
      // Sejt cella kirajzol·sa
      if(racs[i][j] == ELO)
	qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
			  cellaSzelesseg, cellaMagassag, Qt::black);
	else
	  qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
			    cellaSzelesseg, cellaMagassag, Qt::white);
	  qpainter.setPen(QPen(Qt::gray, 1));
	
	qpainter.drawRect(j*cellaSzelesseg, i*cellaMagassag,
			  cellaSzelesseg, cellaMagassag);
    }
  }
  
  qpainter.end();
}


SejtAblak::~SejtAblak()
{
  delete eletjatek;
  
  for(int i=0; i<magassag; ++i) {
    delete[] racsok[0][i];
    delete[] racsok[1][i];
  }
  
  delete[] racsok[0];
  delete[] racsok[1];
  delete[] racsok;
  
  
}

void SejtAblak::vissza(int racsIndex)
{
  this->racsIndex = racsIndex;
  update();
}

/**
 * A sejttÈrbe "ELOlÈnyeket" helyez¸nk, ez a "siklÛ".
 * Adott ir·nyban halad, m·solja mag·t a sejttÈrben.
 * Az ELOlÈny ismertetÈsÈt l·sd pÈld·ul a
 * [MATEK J¡T…K] hivatkoz·sban (Cs·k·ny BÈla: DiszkrÈt
 * matematikai j·tÈkok. Polygon, Szeged 1998. 172. oldal.)
 *
 * @param   racs    a sejttÈr ahov· ezt az ·llatk·t helyezz¸k
 * @param   x       a befoglalÛ tÈgla bal felsı sark·nak oszlopa
 * @param   y       a befoglalÛ tÈgla bal felsı sark·nak sora
 */
void SejtAblak::siklo(bool **racs, int x, int y) {
  
  racs[y+ 0][x+ 2] = ELO;
  racs[y+ 1][x+ 1] = ELO;
  racs[y+ 2][x+ 1] = ELO;
  racs[y+ 2][x+ 2] = ELO;
  racs[y+ 2][x+ 3] = ELO;
  
}
/**
 * A sejttÈrbe "ELOlÈnyeket" helyez¸nk, ez a "siklÛ ·gy˙".
 * Adott ir·nyban siklÛkat lı ki.
 * Az ELOlÈny ismertetÈsÈt l·sd pÈld·ul a
 * [MATEK J¡T…K] hivatkoz·sban /Cs·k·ny BÈla: DiszkrÈt
 * matematikai j·tÈkok. Polygon, Szeged 1998. 173. oldal./,
 * de itt az ·bra hib·s, egy oszloppal told mÈg balra a
 * bal oldali 4 sejtes nÈgyzetet. A helyes ·gy˙ rajz·t
 * l·sd pl. az […LET CIKK] hivatkoz·sban /Robert T.
 * Wainwright: Life is Universal./ (MegemlÌthetj¸k, hogy
 * mindkettı tartalmaz kÈt felesleges sejtet is.)
 *
 * @param   racs    a sejttÈr ahov· ezt az ·llatk·t helyezz¸k
 * @param   x       a befoglalÛ tÈgla bal felsı sark·nak oszlopa
 * @param   y       a befoglalÛ tÈgla bal felsı sark·nak sora
 */
void SejtAblak::sikloKilovo(bool **racs, int x, int y) {
  
  racs[y+ 6][x+ 0] = ELO;
  racs[y+ 6][x+ 1] = ELO;
  racs[y+ 7][x+ 0] = ELO;
  racs[y+ 7][x+ 1] = ELO;
  
  racs[y+ 3][x+ 13] = ELO;
  
  racs[y+ 4][x+ 12] = ELO;
  racs[y+ 4][x+ 14] = ELO;
  
  racs[y+ 5][x+ 11] = ELO;
  racs[y+ 5][x+ 15] = ELO;
  racs[y+ 5][x+ 16] = ELO;
  racs[y+ 5][x+ 25] = ELO;
  
  racs[y+ 6][x+ 11] = ELO;
  racs[y+ 6][x+ 15] = ELO;
  racs[y+ 6][x+ 16] = ELO;
  racs[y+ 6][x+ 22] = ELO;
  racs[y+ 6][x+ 23] = ELO;
  racs[y+ 6][x+ 24] = ELO;
  racs[y+ 6][x+ 25] = ELO;
  
  racs[y+ 7][x+ 11] = ELO;
  racs[y+ 7][x+ 15] = ELO;
  racs[y+ 7][x+ 16] = ELO;
  racs[y+ 7][x+ 21] = ELO;
  racs[y+ 7][x+ 22] = ELO;
  racs[y+ 7][x+ 23] = ELO;
  racs[y+ 7][x+ 24] = ELO;
  
  racs[y+ 8][x+ 12] = ELO;
  racs[y+ 8][x+ 14] = ELO;
  racs[y+ 8][x+ 21] = ELO;
  racs[y+ 8][x+ 24] = ELO;
  racs[y+ 8][x+ 34] = ELO;
  racs[y+ 8][x+ 35] = ELO;
  
  racs[y+ 9][x+ 13] = ELO;
  racs[y+ 9][x+ 21] = ELO;
  racs[y+ 9][x+ 22] = ELO;
  racs[y+ 9][x+ 23] = ELO;
  racs[y+ 9][x+ 24] = ELO;
  racs[y+ 9][x+ 34] = ELO;
  racs[y+ 9][x+ 35] = ELO;
  
  racs[y+ 10][x+ 22] = ELO;
  racs[y+ 10][x+ 23] = ELO;
  racs[y+ 10][x+ 24] = ELO;
  racs[y+ 10][x+ 25] = ELO;
  
  racs[y+ 11][x+ 25] = ELO;
  
}
