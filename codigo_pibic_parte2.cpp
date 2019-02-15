#include <RcppArmadillo.h>
using namespace Rcpp;


// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
List mats(arma::mat X) {
  
  arma::mat V = X.t() * X;
  arma::mat bread1 = inv(V) * X.t(); 
  arma::mat bread2 = X * V.i();
  return  List::create(_["bread_1"] = bread1,
                       _["bread_2"] = bread2);
  
}


 /*** R
  mats(M)
 */
