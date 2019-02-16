#include <RcppArmadillo.h>
using namespace Rcpp;


// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat mats(arma::mat X, List model, int method) {
  
  arma::mat V = X.t() * X;
  arma::mat bread1 = inv(V) * X.t(); 
  arma::mat bread2 = X * V.i();
  
  // criando a matriz error_hat
  NumericVector residuals =  model["residuals"];
  int dim = residuals.size();
  arma::mat error_hat = arma::zeros(dim,dim);
  
  for (int i = 0; i < dim; i++){
    error_hat(i,i) = residuals[i];
  }
  // ainda a questao da matriz error_hat
  
  if(method == 0){
    
    arma::mat hc = error_hat * 2;
    
    return hc;
  }
  
  // return hc;
  
}


 /*** R
  mats(X = M, model = modelo, method = 0)
*/
