def pow(a, b):
    if (b == 0):
        return a
    return a + pow(a, b-1)

def fib(n):
    if (n == 0):
        return 0 
    elif (n == 1):
        return 1
    return fib(n-1) + fib(n-2)

def isPalindrome(str):
    if len(str) < 2: return True
    if str[0] != str[-1]: return False
    return isPalindrome(str[1:-1])
