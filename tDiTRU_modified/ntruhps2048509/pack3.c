#include "poly.h"

void poly_S3_tobytes(unsigned char msg[tDiTRU_OWCPA_MSGBYTES], const poly *a)
{
  int i;
  unsigned char c;
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<tDiTRU_PACK_DEG/5; i++)
  {
    c =        a->coeffs[5*i+4] & 255;
    c = (3*c + a->coeffs[5*i+3]) & 255;
    c = (3*c + a->coeffs[5*i+2]) & 255;
    c = (3*c + a->coeffs[5*i+1]) & 255;
    c = (3*c + a->coeffs[5*i+0]) & 255;
    msg[i] = c;
  }
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = tDiTRU_PACK_DEG/5;
  c = 0;
  for(j = tDiTRU_PACK_DEG - (5*i) - 1; j>=0; j--)
    c = (3*c + a->coeffs[5*i+j]) & 255;
  msg[i] = c;
#endif
}

void poly_S3_frombytes(poly *r, const unsigned char msg[tDiTRU_OWCPA_MSGBYTES])
{ 

  int i;
  unsigned char c;
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<tDiTRU_PACK_DEG/5; i++)
  {
    c = msg[i];
    r->coeffs[5*i+0] = c;
    r->coeffs[5*i+1] = c * 171 >> 9;  // this is division by 3
    r->coeffs[5*i+2] = c * 57 >> 9;  // division by 3^2
    r->coeffs[5*i+3] = c * 19 >> 9;  // division by 3^3
    r->coeffs[5*i+4] = c * 203 >> 14;  // etc.
  }
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = tDiTRU_PACK_DEG/5;
  c = msg[i];
  for(int j=0; (5*i+j)<tDiTRU_PACK_DEG ; j++)
  {
    r->coeffs[5*i+j] = c;
    c = c * 171 >> 9;
  }
#endif
  r->coeffs[N-1] = 0;
  poly_mod_3_Phi_n(r);

}
void poly_S3_frombytes_tDiTRU(poly *r, const unsigned char msg[tDiTRU_OWCPA_MSGBYTES])
{ 

  int i;
  unsigned char c;
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<tDiTRU_PACK_DEG/5; i++)
  {
    c = msg[i];
    r->coeffs[5*i+0] = c;
    r->coeffs[5*i+1] = c * 171 >> 9;  // this is division by 3
    r->coeffs[5*i+2] = c * 57 >> 9;  // division by 3^2
    r->coeffs[5*i+3] = c * 19 >> 9;  // division by 3^3
    r->coeffs[5*i+4] = c * 203 >> 14;  // etc.
  }
#if tDiTRU_PACK_DEG > (tDiTRU_PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = tDiTRU_PACK_DEG/5;
  c = msg[i];
  for(int j=0; (5*i+j)<tDiTRU_PACK_DEG ; j++)
  {
    r->coeffs[5*i+j] = c;
    c = c * 171 >> 9;
  }
#endif
  r->coeffs[ORDER-1] = 0;
  poly_mod_3_Phi_n_tDiTRU(r);

}


