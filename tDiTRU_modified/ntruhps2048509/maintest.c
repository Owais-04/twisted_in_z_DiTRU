#include <stdio.h>
#include "poly.h"
#include "params.h"
#include "rng.h"
#include "sample.h"

#include "crypto_hash_sha3256.h"

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

    poly product;
    poly *product_ptr = &product;
    // poly_S3_mul_tDiTRU(product_ptr, x1, invf_mod3_ptr);

    // printf("result poly is: ");
    // for (int i = 0; i < ORDER; i++)
    // {
    //     printf("%d ", product_ptr->coeffs[i]);
    // }

     poly_S3_tobytes(sk,x1);
    //  printf("invf_mod3\n");
    //  print_poly_values(invf_mod3_ptr);
     poly_S3_tobytes(sk+tDiTRU_PACK_TRINARY_BYTES, invf_mod3_ptr);
    
     
      poly_Z3_to_Zq_tDiTRU(x1);
      poly_Z3_to_Zq_tDiTRU(x2);
    

      /* g = 3*g */
      for(int i=0; i<ORDER; i++)
      x2->coeffs[i] = 3 * x2->coeffs[i];
      
    poly_Rq_inv(x3,x1);
    poly_Rq_mul_tDiTRU(gf, x2, x1, True);
//   printf("\ngf: \n");
//   print_poly_values(gf);
//   poly_Rq_inv_tDiTRU(x3,x1);
//   printf("verify inverse f:\n");
//   poly_Rq_mul_tDiTRU(tmp,x3,x1 , False);
//   print_poly_values(tmp);

  poly_Rq_inv_tDiTRU(invgf, gf);
  poly_Rq_mul_tDiTRU(tmp , invgf , gf,False);
  printf("verify inverse gf:\n");
  print_poly_values(tmp);
/*  
  poly_Rq_mul_tDiTRU(tmp, invgf, x1, False);
  print_poly_values(tmp);

  poly_Sq_mul_tDiTRU(invh, tmp, x1); //need to write this for tditru (order)
  poly_Sq_tobytes(sk+2*tDiTRU_PACK_TRINARY_BYTES, invh);

  poly_Rq_mul_tDiTRU(tmp, invgf, x2, False);
  poly_Rq_mul_tDiTRU(x3, tmp, x2, False);
    printf("\nverify h:\n");
  print_poly_values(x3);//h
  poly_Rq_sum_zero_tobytes(pk, x3);
      

//End of key gen .....................................
//requirments for message
 poly r, m;
 poly *r1=&r;
 poly *m1=&m;
  unsigned char ss[tDiTRU_SHAREDKEYBYTES];
  unsigned char rm[tDiTRU_OWCPA_MSGBYTES];
  unsigned char rm_seed[tDiTRU_SAMPLE_RM_BYTES];

  randombytes(rm_seed, tDiTRU_SAMPLE_RM_BYTES);

  sample_rm_tDiTRU(r1, m1, rm_seed);
  print_poly_values(r1);
  print_poly_values(m1);

  poly_S3_tobytes(rm, r1);
  poly_S3_tobytes(rm+tDiTRU_PACK_TRINARY_BYTES, m1);
  crypto_hash_sha3256(ss, rm, tDiTRU_OWCPA_MSGBYTES);
// printf("\nr1\n");
//  print_poly_values(r1);
  poly_Z3_to_Zq_tDiTRU(r1);
  //checking its back conversion:
//   poly_trinary_Zq_to_Z3_tDiTRU(r1);
//   print_poly_values(r1);

 

//.............................
poly c,lift;
poly *ct=&c;
poly*liftm=&lift;
unsigned char cipher[tDiTRU_CIPHERTEXTBYTES];
 poly_Rq_sum_zero_frombytes(x3, pk);//h
 poly_Rq_mul_tDiTRU(ct, r1, x3,False);
poly_lift(liftm, m1);
  for(int i=0; i<ORDER; i++)
    ct->coeffs[i] = ct->coeffs[i] + liftm->coeffs[i];
poly_Rq_sum_zero_tobytes(cipher, ct);
print_poly_values(ct);
 
// printf("end");
//end enc.......................................
unsigned char rm1[tDiTRU_OWCPA_MSGBYTES];
unsigned char buf[tDiTRU_PRFKEYBYTES+tDiTRU_CIPHERTEXTBYTES];
 poly_Rq_sum_zero_frombytes(ct, cipher);//last term of ct different
 print_poly_values(ct);
 poly f1,cf1,mf1,finv;
 poly *x11= &f1;
 poly *cf= &cf1;
 poly *mf=&mf1;
 poly *finv3=&finv;
 

// print_poly_values(x1);

 poly_S3_frombytes_tDiTRU(x11,sk);

 poly_Z3_to_Zq_tDiTRU(x11);

 //print_poly_values(x11);
 poly_Rq_mul_tDiTRU(cf,ct,x11,False);
 poly_Rq_to_S3(mf, cf);   


  poly_S3_frombytes_tDiTRU(finv3, sk+tDiTRU_PACK_TRINARY_BYTES);
  poly_S3_mul_tDiTRU(m1, mf, finv3);
  poly_S3_tobytes(rm1+tDiTRU_PACK_TRINARY_BYTES, m1);

  poly_lift(liftm,m1);
  poly b1;
  poly *b = &b1;
    for(int i=0; i<ORDER; i++)
    b->coeffs[i] = ct->coeffs[i] - liftm->coeffs[i];

//   /* r = b / h mod (q, Phi_n) */
//   poly_Sq_frombytes(invh, sk+2*tDiTRU_PACK_TRINARY_BYTES);
//   poly_Sq_mul_tDiTRU(r1, b, invh);
//   poly_trinary_Zq_to_Z3_tDiTRU(r1);
//   poly_S3_tobytes(rm1, r1);
//   print_poly_values(r1);

//   crypto_hash_sha3256(ss, rm1, tDiTRU_OWCPA_MSGBYTES);
//   /* shake(secret PRF key || input ciphertext) */
//   for(int i=0;i<tDiTRU_PRFKEYBYTES;i++)
//     buf[i] = sk[i+tDiTRU_OWCPA_SECRETKEYBYTES];
//   for(int i=0;i<tDiTRU_CIPHERTEXTBYTES;i++)
//     buf[tDiTRU_PRFKEYBYTES + i] = cipher[i];
//   crypto_hash_sha3256(rm, buf, tDiTRU_PRFKEYBYTES+tDiTRU_CIPHERTEXTBYTES); */
    return 0;
}






/*
sampled sucessfully.
inverse not calculated well
added tditru s3 mul funciton:
    
    for separately taking mod for both parts
    

*/
