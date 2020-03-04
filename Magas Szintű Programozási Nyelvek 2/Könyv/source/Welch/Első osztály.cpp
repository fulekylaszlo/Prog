#include <iostream>
#include <math.h>
using namespace std;

class Polar{
public:
double tarolt;
bool nincstarolt=true;
double kovetkezo();


} ;
double Polar::kovetkezo(){
if(nincstarolt) {
            
            double u1, u2, v1, v2, w;
            do {
                u1 = (double)rand()/((double)RAND_MAX+1);
                u2 = (double)rand()/((double)RAND_MAX+1);
                
                v1 = 2*u1 - 1;
                v2 = 2*u2 - 1;
                
                w = v1*v1 + v2*v2;
                
            } while(w > 1);
            
            double r = sqrt((-2*log(w))/w);
            
            tarolt = r*v2;
            nincstarolt = !nincstarolt;
            
            return r*v1;
            
        } else {
            nincstarolt = !nincstarolt;
            return tarolt;
        }


}





int main(){
Polar g;
for (int i = 0; i < 9; ++i)
{
	cout<<g.kovetkezo()<<endl;
}



}
