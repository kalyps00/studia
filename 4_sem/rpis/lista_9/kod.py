import numpy as np
from scipy import stats

def solve_tasks():
    # Zadanie 1-3
    data01 = np.array([5.42, 4.58, 5.2, 5.63, 1.14, 4.44, 2.08, -0.44, 0.56, 1.7, 3.23, 1.53, 0.55, 4.99, 9.36, 1.27, -0.03, 8.05, 4.07, 3.1, -1.24, 5.42, 0.08, 1.74, 1.42, 0.27, -3.31, 4.8, 3.61, -2.69, 2.71, -1.21, 5.19, 3.72, 0.48, 0.36, -1.72, -2.22, 3.83, 5.63, -3.14, 5.09, 3.09, 0.65, 3.48, 2.89, -0.2, 0.9, -0.68, -1.33])
    n = len(data01)
    mean_x = np.mean(data01)
    s2 = np.var(data01, ddof=1)
    
    # Zadanie 2
    z_15 = (mean_x - 1.5) / (np.sqrt(8)/np.sqrt(n))
    z_175 = (mean_x - 1.75) / (np.sqrt(8)/np.sqrt(n))
    
    # Zadanie 3
    t_15 = (mean_x - 1.5) / (np.sqrt(s2)/np.sqrt(n))
    t_175 = (mean_x - 1.75) / (np.sqrt(s2)/np.sqrt(n))
    
    # Zadanie 5
    data05 = np.array([11, 6, 7, 1, 5, 5, 10, 4, 6, 3, 4, 3, 5, 11, 7, 4, 4, 6, 8, 5, 3, 2, 3, 6, 2, 3, 3, 6, 6, 3, 3, 6, 7, 5, 1, 5, 7, 6, 4, 5, 5, 7, 4, 4, 4, 7, 0, 5, 1, 5])
    lambda_mle = np.mean(data05)
    
    # Zadanie 9
    data09 = np.array([9, 10, 9, 9, 6, 10, 7, 6, 7, 6, 9, 6, 7, 6, 8, 11, 4, 7, 4, 9, 11, 6, 8, 13, 7, 14, 9, 4, 7, 6])
    p_hat = np.mean(data09) / 20
    
    return {
        "Z1": (mean_x, s2),
        "Z2_Phi": (stats.norm.cdf(z_15), stats.norm.cdf(z_175)),
        "Z3_t": (stats.t.cdf(t_15, n-1), stats.t.cdf(t_175, n-1)),
        "Z5_lambda": lambda_mle,
        "Z9_p": p_hat
    }

if __name__ == "__main__":
    print(solve_tasks())