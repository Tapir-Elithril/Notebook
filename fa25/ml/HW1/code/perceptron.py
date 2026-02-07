import numpy as np

def perceptron(X, y):
    '''
    PERCEPTRON Perceptron Learning Algorithm.

       INPUT:  X: training sample features, P-by-N matrix.
               y: training sample labels, 1-by-N row vector.

       OUTPUT: w:    learned perceptron parameters, (P+1)-by-1 column vector.
               iter: number of iterations

    '''
    P, N = X.shape
    w = np.zeros((P + 1, 1))
    iters = 0
    # YOUR CODE HERE
    #TODO    
    # begin answer
    X = np.vstack((np.ones((1, N)), X))
    learning_rate = 0.01
    max_iters = 1000
    while iters <= max_iters:
        iters += 1
        true_pred = 0
        for i in range(N):
            pred = np.dot(w.T, X[:, i])
            if y[0, i] * pred <= 0: # wrong prediction
                w = w + learning_rate * y[0, i] * X[:, i].reshape(-1, 1)
            else:
                true_pred += 1
        if true_pred == N:
            break
    # end answer
    
    return w, iters