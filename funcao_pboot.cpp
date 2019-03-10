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
    int L =  length_res * length_res * length_res;
  
    double sig_2 = significance * significance;
    double sig_plus = significance + 0.25;
    float sig13 = pow(sig_plus,1.0/3.0);
    float gamma2 = 0.5 * (1/sig_2) * (1 - significance) * sig13;
  
    int L2 = L * L;
    //
    // TRANSFORMAR PARA INTEIRO
    //
    float JJ = gamma2 * L2;
    int L3 = cbrt(L);
    float KK = (1/gamma2) * L3;


    return List::create(_["J"] = JJ,
                        _["K"] = KK);

  }
}


/*** R
pboot(modelo, 0.01, J = 0, K = 0)
*/
