#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

bool is_wholenumber(NumericVector x, double tol){
  
  bool boreliano;
  NumericVector rounding = round(x,0);
  for(int i = 0; i < x.size(); i++){
    
   boreliano = wrap(abs(x[i] - rounding[i]) < tol);
    
  }
  return boreliano;
}

/*** R
s <- rnorm(10)
is_wholenumber(s, .Machine$double.eps)
*/