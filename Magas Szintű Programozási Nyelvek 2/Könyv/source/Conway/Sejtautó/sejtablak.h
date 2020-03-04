#ifndef SEJTABLAK_H
#define SEJTABLAK_H

#include <QMainWindow>
#include <QPainter>
#include "sejtszal.h"

class SejtSzal;

class SejtAblak : public QMainWindow
{
  Q_OBJECT
  
public:
  SejtAblak(int szelesseg = 100, int magassag = 75, QWidget *parent = 0);

  ~SejtAblak();
  // Egy sejt lehet Èlı
  static const bool ELO = true;
  // vagy halott
  static const bool HALOTT = false;
  void vissza(int racsIndex);
  
protected:
  // KÈt r·csot haszn·lunk majd, az egyik a sejttÈr ·llapot·t
  // a t_n, a m·sik a t_n+1 idıpillanatban jellemzi.
  bool ***racsok;
  // Valamelyik r·csra mutat, technikai jelleg˚, hogy ne kelljen a
  // [2][][]-bÛl az elsı dimenziÛt haszn·lni, mert vagy az egyikre
  // ·llÌtjuk, vagy a m·sikra.
  bool **racs;
  // Megmutatja melyik r·cs az aktu·lis: [r·csIndex][][]
  int racsIndex;
  // Pixelben egy cella adatai.
  int cellaSzelesseg;
  int cellaMagassag;
  // A sejttÈr nagys·ga, azaz h·nyszor h·ny cella van?
  int szelesseg;
  int magassag;    
  void paintEvent(QPaintEvent*);
  void siklo(bool **racs, int x, int y);
  void sikloKilovo(bool **racs, int x, int y);
  
private:
  SejtSzal* eletjatek;
  
};

#endif // SEJTABLAK_H
