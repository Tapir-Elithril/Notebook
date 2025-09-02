# nash_verifier.py
import numpy as np

class NashVerifier:
    """极简纳什均衡验证器（仅检查最优响应）"""
    
    def __init__(self, payoff_matrix: np.ndarray):
        self.M = payoff_matrix  # 行玩家收益矩阵
        self.n_rows, self.n_cols = payoff_matrix.shape
    
    def is_equilibrium(self, 
                      row_strategy: np.ndarray, 
                      col_strategy: np.ndarray,
                      tol: float = 1e-2) -> bool:
        """
        检查是否为纳什均衡（双方是否都是最优响应）
        
        参数:
            row_strategy: 行玩家混合策略（概率向量）
            col_strategy: 列玩家混合策略（概率向量）
            tol: 数值容忍度，默认1e-2，不需要改动
            
        返回:
            bool: 是否为均衡
        """
        
        # 请在下方填写你的代码，实现完成后可以将 exception 注释
        # raise NotImplementedError("NashVerifier is not implemented.")
        
        # 检查行玩家是否最优
        u_Amix = row_strategy @ self.M @ col_strategy
        # 测试纯策略
        for i in range(self.n_rows):
            pure_row_strategy = np.zeros(self.n_rows)
            pure_row_strategy[i] = 1 # 各个纯策略
            u_A_pure = pure_row_strategy @ self.M @ col_strategy
            if(u_A_pure - u_Amix > tol): # tol for precision
                return False
        
        # 检查列玩家是否最优
        u_Bmix = -row_strategy @ self.M @ col_strategy
        # 测试纯策略
        for i in range(self.n_cols):
            pure_col_strategy = np.zeros(self.n_cols)
            pure_col_strategy[i] = 1
            u_B_pure = -row_strategy @ self.M @ pure_col_strategy
            if(u_B_pure - u_Bmix > tol):
                return False
        
        return True