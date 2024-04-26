/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering(millisekunder)
 ----------------------------------
    150	27		7
    200	77		13			
    300	226		30
    400	524		56
    800	4018		235
   1600	32040		978
   3200	~128160	4206
   6400	~512640	17807
  12800	~2050560	~71228


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N⁴) Eftersom programmet innehåller fyra for-loopar, som går igenom N, N/2, N/4, N/8 itereringar. Det vill säga: N*N/2*N/4*N/8 = N⁴/64 => O(N⁴).

Sortering: O(N²) Eftersom den innehåller två for-loopar, vilka går igenom N och N itereringar.
Sorteringen av listan med punkter och lutningar har tidskomplexitet i O(log(N)), men detta försummas på grund av den inre for-loopen med tidskomplexitet O(N). Det vill säga: N(N+log(N)) = N² + Nlog(N) => O(N²).
