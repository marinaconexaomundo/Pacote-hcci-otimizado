#include <RcppArmadillo.h>
#include <cmath>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

int pboot(List model, double significance, NumericVector J, NumericVector K, double tol){
  
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
    
    NumericVector U = (1/gamma2) * L3;
    NumericVector T = gamma2 * L2;
    
    // Trazendo do rcpp a funcao "is_wholenumber"
    Function is_wholenumber("is_wholenumber");
  
    while(is_wholenumber(U/2, tol) > 0 &  is_wholenumber((T+1)*significance, tol) > 0) {
    
      while(is_wholenumber(U, tol) > 0) U = U + 1;
      while(is_wholenumber((T+1)*significance, tol) > 0) T = T + 1;
      while(is_wholenumber((T + 1)/K, tol) > 0) U = U + 1;
    }
  return 1;
  }

}


/*** R
pboot(modelo, 0.01, J = NULL, K = NULL, tol = .Machine$double.eps ^ 0.5)
*/
