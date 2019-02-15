Renda.Paraiba
banco <- Renda.Paraiba
attach(banco)

modelo <- lm(RendaCapita ~  Adol2grau + AdultoSuperior + AdultosAnalfa + Morte1ano)
summary(modelo)



hcc <- function (model, method = 4, k = 0.7) 
{
  if (class(model) != "lm") 
    stop("The argument model must have class lm.")
  if (method %in% c(0, 2, 3, 4, 5) == FALSE) {
    warning("The argument method should be 0, 2, 3, 4 or 5. How did you choose method = ", 
            method, " that is not an option,\n  the calculation is considering method = 4.")
    method = 4L
  }
  
  M <- as.matrix(cbind(1, modelo$model[, -1]))
  error_hat <- as.vector(modelo$residuals)
  h <- as.vector(hatvalues(modelo))
  
  bread <- mats(M)
  # bread_1 <- mats1(M)
  # bread_2 <- mats2(M)

  if (method == 0L) {
    omega = diag(error_hat^2)
    hc = bread_1 %*% omega %*% bread_2
  }
  if (method == 2L) omega = diag((error_hat^2)/(1 - h))
  if (method == 3L) omega = diag((error_hat^2)/((1 - h)^2))
  if (method == 4L) {
    delta = pmin(4, h/mean(h))
    omega = diag((error_hat^2)/((1 - h)^delta))
    }
  if (method == 5L) {
    alpha = pmin(h/mean(h), max(4, k * max(h)/mean(h)))
    omega = diag((error_hat^2)/sqrt((1 - h)^alpha))
    }

  hc(X = M, omega)

}
