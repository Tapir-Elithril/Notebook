import numpy as np

from layers import *
from layer_utils import *


class TwoLayerNet(object):
    """
    A two-layer fully-connected neural network with ReLU nonlinearity and
    softmax loss that uses a modular layer design. We assume an input dimension
    of D, a hidden dimension of H, and perform classification over C classes.

    The architecure should be affine - relu - affine - softmax.

    Note that this class does not implement gradient descent; instead, it
    will interact with a separate Solver object that is responsible for running
    optimization.

    The learnable parameters of the model are stored in the dictionary
    self.params that maps parameter names to numpy arrays.
    """

    def __init__(self, input_dim=1 * 28 * 28, hidden_dim=100, num_classes=10,
                 weight_scale=1e-3, reg=0.0):
        """
        Initialize a new network.

        Args:
          input_dim: An integer giving the size of the input
          hidden_dim: An integer giving the size of the hidden layer
          num_classes: An integer giving the number of classes to classify
          weight_scale: Scalar giving the standard deviation for random
          initialization of the weights.
          reg: Scalar giving L2 regularization strength.
        """
        self.params = {}
        self.reg = reg

        ############################################################################
        # TODO: Initialize the weights and biases of the two-layer net. Weights    #
        # should be initialized from a Gaussian with standard deviation equal to   #
        # weight_scale, and biases should be initialized to zero. All weights and  #
        # biases should be stored in the dictionary self.params, with first layer  #
        # weights and biases using the keys 'W1' and 'b1' and second layer weights #
        # and biases using the keys 'W2' and 'b2'.                                 #
        ############################################################################
        # begin answer
        self.params['W1'] = weight_scale * np.random.randn(input_dim, hidden_dim) # (D, H)
        self.params['b1'] = np.zeros(hidden_dim) # (H,)
        self.params['W2'] = weight_scale * np.random.randn(hidden_dim, num_classes) # (H, C)
        self.params['b2'] = np.zeros(num_classes) # (C,)
        # end answer

    def loss(self, X, y=None):
        """
        Compute loss and gradient for a minibatch of data.

        Args:
        - X: Array of input data of shape (N, d_1, ..., d_k)
        - y: Array of labels, of shape (N,). y[i] gives the label for X[i].

        Returns:
        If y is None, then run a test-time forward pass of the model and return:
        - scores: Array of shape (N, C) giving classification scores, where
          scores[i, c] is the classification score for X[i] and class c.

        If y is not None, then run a training-time forward and backward pass and
        return a tuple of:
        - loss: Scalar value giving the loss
        - grads: Dictionary with the same keys as self.params, mapping parameter
          names to gradients of the loss with respect to those parameters.
        """
        scores = None
        ############################################################################
        # TODO: Implement the forward pass for the two-layer net, computing the    #
        # class scores for X and storing them in the scores variable.              #
        ############################################################################
        # begin answer
        w1 = self.params['W1']
        b1 = self.params['b1']
        w2 = self.params['W2']
        b2 = self.params['b2']
        out_1, cache_1 = affine_relu_forward(X, w1, b1)
        out_2, cache_2 = affine_forward(out_1, w2, b2)
        if y is None:
          # test-time forward pass
          scores = out_2
          return scores
        else:
          # training-time forward pass
          loss, dout_2 = softmax_loss(out_2, y)
          # L2 regularization:reg / 2 * \sum w**2
          loss += 0.5 * self.reg * (np.sum(w1**2) + np.sum(w2**2))
          # backward
          dout_1, dw2, db2 = affine_backward(dout_2, cache_2)
          dX, dw1, db1 = affine_relu_backward(dout_1, cache_1)
          # regularization grad:dreg = (reg / 2 * w**2)' = reg * w
          dw1 += self.reg * w1
          dw2 += self.reg * w2
          grads = {}
          grads['W2'] = dw2
          grads['b2'] = db2
          grads['W1'] = dw1
          grads['b1'] = db1
          return loss, grads
        # end answer


class FullyConnectedNet(object):
    """
    A fully-connected neural network with an arbitrary number of hidden layers,
    ReLU nonlinearities, and a softmax loss function.
    For a network with L layers, the architecture will be:

    {affine - relu} x (L - 1) - affine - softmax

    where the {...} block is repeated L - 1 times.

    Similar to the TwoLayerNet above, learnable parameters are stored in the
    self.params dictionary and will be learned using the Solver class.
    """

    def __init__(self, hidden_dims, input_dim=1 * 28 * 28, num_classes=10,
                 reg=0.0, weight_scale=1e-2,
                 dtype=np.float32):
        """
        Initialize a new FullyConnectedNet.

        Args:
        - hidden_dims: A list of integers giving the size of each hidden layer.
        - input_dim: An integer giving the size of the input.
        - num_classes: An integer giving the number of classes to classify.
        - reg: Scalar giving L2 regularization strength.
        - weight_scale: Scalar giving the standard deviation for random
          initialization of the weights.
        - dtype: A numpy datatype object; all computations will be performed using
          this datatype. float32 is faster but less accurate, so you should use
          float64 for numeric gradient checking.
        """
        self.reg = reg
        self.num_layers = 1 + len(hidden_dims)
        self.dtype = dtype
        self.params = {}

        ############################################################################
        # TODO: Initialize the parameters of the network, storing all values in    #
        # the self.params dictionary. Store weights and biases for the first layer #
        # in W1 and b1; for the second layer use W2 and b2, etc. Weights should be #
        # initialized from a normal distribution with standard deviation equal to  #
        # weight_scale and biases should be initialized to zero.                   #
        #                                                                          #
        ############################################################################
        # begin answer
        self.params['W1'] = weight_scale * np.random.randn(input_dim, hidden_dims[0])
        self.params['b1'] = np.zeros(hidden_dims[0])
        for i in range(1, len(hidden_dims)):
          self.params['W' + str(i+1)] = weight_scale * np.random.randn(hidden_dims[i-1], hidden_dims[i])
          self.params['b' + str(i+1)] = np.zeros(hidden_dims[i])
        self.params['W' + str(self.num_layers)] = weight_scale * np.random.randn(hidden_dims[-1], num_classes)
        self.params['b' + str(self.num_layers)] = np.zeros(num_classes)
        # end answer

        # Cast all parameters to the correct datatype
        for k, v in self.params.items():
            self.params[k] = v.astype(dtype)

    def loss(self, X, y=None):
        """
        Compute loss and gradient for the fully-connected net.

        Input / output: Same as TwoLayerNet above.
        """
        X = X.astype(self.dtype)
        scores = None
        ############################################################################
        # TODO: Implement the forward pass for the fully-connected net, computing  #
        # the class scores for X and storing them in the scores variable.          #
        ############################################################################
        # begin answer
        out = X
        caches = []
        for i in range(self.num_layers - 1):
          w = self.params['W' + str(i+1)]
          b = self.params['b' + str(i+1)]
          out, cache = affine_relu_forward(out, w, b)
          caches.append(cache)
        w_last = self.params['W' + str(self.num_layers)]
        b_last = self.params['b' + str(self.num_layers)]
        out, cache = affine_forward(out, w_last, b_last)
        caches.append(cache)
        scores = out
        # end answer

        # If test mode return early
        if y is None:
            return scores

        loss, grads = 0.0, {}
        ############################################################################
        # TODO: Implement the backward pass for the fully-connected net. Store the #
        # loss in the loss variable and gradients in the grads dictionary. Compute #
        # data loss using softmax, and make sure that grads[k] holds the gradients #
        # for self.params[k]. Don't forget to add L2 regularization!               #
        #                                                                          #
        #                                                                          #
        # NOTE: To ensure that your implementation matches ours and you pass the   #
        # automated tests, make sure that your L2 regularization includes a factor #
        # of 0.5 to simplify the expression for the gradient.                      #
        ############################################################################
        # begin answer
        # y is not none
        loss, dout = softmax_loss(out, y)
        w_sum = 0
        for i in range(1, self.num_layers + 1):
          w_sum += np.sum(self.params['W' + str(i)]**2) 
        loss += 0.5 * self.reg * w_sum
        # backward
        dcur, dw_last, db_last = affine_backward(dout, caches[-1])
        dw_last += self.reg * self.params['W' + str(self.num_layers)]
        grads['W' + str(self.num_layers)] = dw_last
        grads['b' + str(self.num_layers)] = db_last

        for i in range(self.num_layers - 1, 0, -1):
          dcur, dw, db = affine_relu_backward(dcur, caches[i-1])
          dw += self.reg * self.params['W' + str(i)]     
          grads['W' + str(i)] = dw
          grads['b' + str(i)] = db
        # end answer
        return loss, grads
