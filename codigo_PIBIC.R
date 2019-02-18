hcc <- function (model, method = 4, k = 0.7){
  
  if (class(model) != "lm") 
    stop("The argument model must have class lm.")
  if (method %in% c(0, 2, 3, 4, 5) == FALSE) {
    warning("The argument method should be 0, 2, 3, 4 or 5. How did you choose method = ", 
            method, " that is not an option,\n  the calculation is considering method = 4.")
    method = 4L
  }
  
  M <- as.matrix(cbind(1, model$model[, -1]))
  h <- as.vector(hatvalues(model))
  
  mats(X = M, model = model, method = method,  h = h, k = k)

}
