#include <RcppArmadillo.h>
using namespace Rcpp;
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

double pboot(List model, double significance) {
  
  
  
  // no primeiro if
  NumericVector residuals =  model["residuals"];
  NumericVector L = pow(residuals,3);
  
  double sig_2 = significance * significance;
  double sig_plus = significance + 0.25;
  double sig13;
  double isso = 1/3;
  for(int i = 0; i < 1; i++){
    sig13 = pow(sig_plus,isso);
  }
  
  // double sig_plus3 = pow(sig_plus,1/3);
   double gamma2 = 0.5 * (1/sig_2) * (1 - significance) * (1/sig13);
  
  NumericVector L2 = L*L;
  // NumericVector J = gamma2 * L2;
  
  NumericVector L3 = pow(L,3);

  //double gamma_1 = 1/gamma2;
  // NumericVector K = (1/gamma2) * (1/L3);
  
  
  // fim do primeiro if.
  return sig13;
}


/*** R
pboot(modelo, 0.05)
*/
