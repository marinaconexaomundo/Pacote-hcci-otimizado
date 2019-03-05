#include <RcppArmadillo.h>
using namespace Rcpp;
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]


float pboot(List model, double significance) {
  
  // no primeiro if
  NumericVector residuals =  model["residuals"];
  int length_res = residuals.size();
  int L = pow(length_res,3);
  
  double sig_2 = significance * significance;
  double sig_plus = significance + 0.25;
  float sig13 = pow(sig_plus,1.0/3.0);
  float gamma2 = 0.5 * (1/sig_2) * (1 - significance) * sig13;
  
  int L2 = L*L;
  float J = gamma2 * L2;
  
  float L3 = pow(L,(2.0/3.0));

  //double gamma_1 = 1/gamma2;
  float K = (1/gamma2) * L3;
  
  
  // fim do primeiro if.
  return K;
}


/*** R
pboot(modelo, 0.05)
*/
