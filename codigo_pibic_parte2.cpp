#include <RcppArmadillo.h>
using namespace Rcpp;


// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat mats(arma::mat X, List model, int method) {
  
  arma::mat V = X.t() * X;
  arma::mat bread_1 = inv(V) * X.t(); 
  arma::mat bread_2 = X * V.i();
  

  if(method == 0){
    
    // criando a matriz error_hat
    NumericVector residuals =  model["residuals"];
    int dim = residuals.size();
    arma::mat error_hat = arma::zeros(dim,dim);
    // ainda a questao da matriz error_hat
    
    // NumericVector residuals = pow(residuals,2);
  
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = residuals[i];
    }
    arma::mat omega = pow(error_hat,2);
    arma::mat hc = bread_1 * omega * bread_2;
    
    return hc;
  }
  
  // return hc;
  
}


 /*** R
  mats(X = M, model = modelo, method = 0)
*/
