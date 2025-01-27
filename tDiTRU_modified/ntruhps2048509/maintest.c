#include <stdio.h>
#include "poly.h"
#include "params.h"
#include "rng.h"
#include "sample.h"

#include "helper_print.h"
int main()
{   
    poly f, g,h,k,k1,k2,temp;
    poly *x3=&h;
    poly *gf=&k;
    poly *invgf=&k1,*tmp=&temp;
    poly *invh =&k2;
    unsigned char sk[ORDER];
    unsigned char pk[ORDER];

    poly *x1 = &f;
    poly *x2 = &g;
    poly invf_mod3;
    poly *invf_mod3_ptr = &invf_mod3;
    
   
    unsigned char uniformbytes[tDiTRU_SAMPLE_FG_BYTES];
    randombytes(uniformbytes,tDiTRU_SAMPLE_FG_BYTES);
    sample_fg_tDiTRU(x1, x2, uniformbytes);
    poly_S3_inv_tDiTRU(invf_mod3_ptr, x1); 

    // poly product;
    // poly *product_ptr = &product;
    //poly_S3_mul_tDiTRU(product_ptr, x1, invf_mod3_ptr);

    // printf("result poly is: ");
    // for (int i = 0; i < ORDER; i++)
    // {
    //     printf("%d ", product_ptr->coeffs[i]);
    // }
    //printf("before: ");
    //print_poly_values(x1);
     poly_S3_tobytes(sk,x1);
     //print_poly_values(invf_mod3_ptr);
     poly_S3_tobytes(sk+tDiTRU_PACK_TRINARY_BYTES, invf_mod3_ptr);
     poly_S3_frombytes_tDiTRU(x3,sk+tDiTRU_PACK_TRINARY_BYTES);
     poly_S3_frombytes_tDiTRU(x3,sk);
     
      poly_Z3_to_Zq_tDiTRU(x1);
      poly_Z3_to_Zq_tDiTRU(x2);
    

      /* g = 3*g */
      for(int i=0; i<ORDER; i++)
      x2->coeffs[i] = 3 * x2->coeffs[i];
      
      
  poly_Rq_mul_tDiTRU(gf, x2, x1, True);

  poly_Rq_inv_tDiTRU(invgf, gf);

  poly_Rq_mul_tDiTRU(tmp, invgf, x1, False);

  poly_Sq_mul_tDiTRU(invh, tmp, x1); //need to write this for tditru (order)
  poly_Sq_tobytes(sk+2*tDiTRU_PACK_TRINARY_BYTES, invh);

  poly_Rq_mul_tDiTRU(tmp, invgf, x2, False);
  poly_Rq_mul_tDiTRU(x3, tmp, x2, False);
  print_poly_values(x3);
  poly_Rq_sum_zero_tobytes(pk, x3);
      
printf("end\n");
//End of key gen .....................................
  poly_Rq_sum_zero_frombytes(x3,pk);
  poly ct;
  poly *ct_ptr=&ct;
  unsigned char c[tDiTRU_CIPHERTEXTBYTES];
  poly r;
  poly liftm;
  poly m;
  poly *m_ptr=&m;
  poly *liftm_ptr=&liftm;
  poly_Rq_mul_tDiTRU(&ct, &r, x3,False);
  
  poly_lift(liftm_ptr, m_ptr);
  print_poly_values(liftm_ptr);
  for(int i=0; i<ORDER; i++)
    ct_ptr->coeffs[i] = ct_ptr->coeffs[i] + liftm_ptr->coeffs[i];

  poly_Rq_sum_zero_tobytes(c, ct_ptr);


  




    return 0;
}






/*
sampled sucessfully.
inverse not calculated well
added tditru s3 mul funciton:
    
    for separately taking mod for both parts
    

*/
