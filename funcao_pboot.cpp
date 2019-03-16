#include <RcppArmadillo.h>
#include <cmath>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

NumericVector pboot(List model, double significance, NumericVector J, NumericVector K, double tol){
  
  if(J[0] == 1 || K[0] == 1){
    
    NumericVector residuals =  model["residuals"];
    int length_res = residuals.size();
    
    // trazendo do rcpp a funcao "vector_escalar"
    Function vector_escalar("vector_escalar");
    int L =  as<int>(vector_escalar(length_res, 2));
    
    float sig_plus3 = as<float>(vector_escalar(significance + 0.25, 1/3));
    double sig_2 = significance * significance;
    float gamma2 = 0.5 * (1/sig_2) * (1 - significance) * sig_plus3;
    int L2 = L * L;
    //
    // TRANSFORMAR PARA INTEIRO
    //
    J[1] = gamma2 * L2;
    int L3 = as<int>(vector_escalar(L, 1/3));
    K[1] = (1/gamma2) * L3;
    
    
  // Trazendo do rcpp a funcao "is_wholenumber"
  Function is_wholenumber("is_wholenumber");

  NumericVector ava_J_significance = (J[1] + 1) * significance;
  NumericVector J_K = (J[1] + 1)/K[1];
  
  double whole1 = is_wholenumber(K[1]/2, tol);
  double whole2 = is_wholenumber(ava_J_significance, tol);
  double whole3 = is_wholenumber(J_K, tol);
  
  while(whole1 > 0 &  whole2 > 0) {
    
    ava_J_significance = (J + 1) * significance;
    J_K = (J + 1)/K;
    
    whole1 = is_wholenumber(K/2, tol);
    whole2 = is_wholenumber(ava_J_significance, tol);
    whole3 = is_wholenumber(J_K);
    
    while(whole1 > 0) K = K + 1;
    while(whole2 > 0) J = J + 1;
    while(whole3 > 0) K = K + 1;
  }
  }
}
}


/*** R
pboot(modelo, 0.01, J = NULL, K = NULL, tol = .Machine$double.eps ^ 0.5)
*/
