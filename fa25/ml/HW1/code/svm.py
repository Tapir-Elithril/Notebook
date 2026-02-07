import numpy as np
from scipy.optimize import minimize

def svm(X, y):
    '''
    SVM Support vector machine.

    INPUT:  X: training sample features, P-by-N matrix.
            y: training sample labels, 1-by-N row vector.

    OUTPUT: w: learned perceptron parameters, (P+1)-by-1 column vector.
            num: number of support vectors

    '''
    P, N = X.shape
    # w = np.zeros((P + 1, 1))
    w = np.zeros(P + 1)
    num = 0

    # YOUR CODE HERE
    # Please implement SVM with scipy.optimize. You should be able to implement
    # it within 20 lines of code. The optimization should converge wtih any method
    # that support constrain.
    #TODO
    # begin answer
    """
    min_{w,b} 1/2 ||w||^2,s.t. y_i(w.T X_i + b) > 1
    """
    X = np.vstack((np.ones((1, N)), X))
    def constraint(w):
        margins = y * np.dot(w.T, X)
        return (margins - 1).flatten()

    def objective(w):
        w = w[1:] # remove b
        return 0.5 * np.dot(w, w)

    constraints = {'type':'ineq', 'fun':constraint}
    result = minimize(
        fun=objective,
        x0=w,
        method='SLSQP',
        constraints = constraints
    )
    w = result.x.reshape(-1, 1) # column vector
    margins = (y * np.dot(w.T, X)).flatten()
    num = np.sum(np.abs(margins - 1) < 1e-4) # support vectors are the margins with interval close to 1
    # end answer
    return w, num

