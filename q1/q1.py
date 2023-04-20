from math import factorial

# Bionomial coefficient: (n choose k)
def choose_func(n, k) -> float:
    return factorial(n)/(factorial(k) * factorial(n - k))


# returns a float showing returns the possibility of raining at least n days
def prob_rain_more_than_n(p, n):
    assert len(p) == 365, "p does not include probabilities for all the given days in the year"

    sum = 0
    for i in range(0, n):
        sum += choose_func(365, i) * p[i]**i * (1 - p[i])**(365 - i)
    
    return (1 - sum)