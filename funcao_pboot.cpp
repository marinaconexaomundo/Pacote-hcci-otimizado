#include <RcppArmadillo.h>
#include <cmath>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

List pboot(List model, double significance, int J, int K){
  
  // no primeiro if
  if(J == 0 || K == 0){
    
    NumericVector residuals =  model["residuals"];
    int length_res = residuals.size();
    
    // trazendo do r a funcao "vector_escalar"
    Function vector_escalar("vector_escalar");
    int L =  as<int>(vector_escalar(length_res, 2));
    
    float sig_plus3 = as<float>(vector_escalar(significance + 0.25, 1/3));
    double sig_2 = significance * significance;
    float gamma2 = 0.5 * (1/sig_2) * (1 - significance) * sig_plus3;
    int L2 = L * L;
    //
    // TRANSFORMAR PARA INTEIRO
    //
    float JJ = gamma2 * L2;
    int L3 = as<int>(vector_escalar(L, 1/3));
    float KK = (1/gamma2) * L3;
    
    // int int_J = as<int>JJ;
    // int int_K = as<int>KK;
    
    return List::create(_["J"] = JJ,
                        _["K"] = KK);
  }
}


/*** R
pboot(modelo, 0.01, J = 0, K = 0)
*/
