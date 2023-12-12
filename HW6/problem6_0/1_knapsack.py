# # A naive recursive implementation 
# # of 0-1 Knapsack Problem 
  
# # Returns the maximum value that 
# # can be put in a knapsack of 
# # capacity W 
  
  
# def knapSack(W, wt, val, n): 
  
#     # Base Case 
#     if n == 0 or W == 0: 
#         return 0
  
#     # If weight of the nth item is 
#     # more than Knapsack of capacity W, 
#     # then this item cannot be included 
#     # in the optimal solution 
#     if (wt[n-1] > W): 
#         return knapSack(W, wt, val, n-1) 
  
#     # return the maximum of two cases: 
#     # (1) nth item included 
#     # (2) not included 
#     else: 
#         return max( 
#             val[n-1] + knapSack( 
#                 W-wt[n-1], wt, val, n-1), 
#             knapSack(W, wt, val, n-1)) 
  
# # end of function knapSack 
  
  
# # Driver Code 
# if __name__ == '__main__': 
#     profit = [10,11,12,13,14,15] 
#     weight = [1,1,2,3,4,3] 
#     W = 11
#     n = len(profit) 
#     print (knapSack(W, weight, profit, n))
# Python3 code for Dynamic Programming
# based solution for 0-1 Knapsack problem
 
# Prints the items which are put in a 
# knapsack of capacity W
def printknapSack(W, wt, val, n):
    K = [[0 for w in range(W + 1)]
            for i in range(n + 1)]
             
    # Build table K[][] in bottom
    # up manner
    for i in range(n + 1):
        for w in range(W + 1):
            if i == 0 or w == 0:
                K[i][w] = 0
            elif wt[i - 1] <= w:
                K[i][w] = max(val[i - 1] 
                  + K[i - 1][w - wt[i - 1]],
                               K[i - 1][w])
            else:
                K[i][w] = K[i - 1][w]
 
    # stores the result of Knapsack
    res = K[n][W]
    print(res)
     
    w = W
    for i in range(n, 0, -1):
        if res <= 0:
            break
        # either the result comes from the
        # top (K[i-1][w]) or from (val[i-1]
        # + K[i-1] [w-wt[i-1]]) as in Knapsack
        # table. If it comes from the latter
        # one/ it means the item is included.
        if res == K[i - 1][w]:
            continue
        else:
 
            # This item is included.
            print(wt[i - 1])
             
            # Since this weight is included
            # its value is deducted
            res = res - val[i - 1]
            w = w - wt[i - 1]
 
# Driver code
val = [10,11,12,13,14,15] 
wt = [1,1,2,3,4,3]
W = 11
n = len(val)
     
printknapSack(W, wt, val, n)
 
# This code is contributed by Aryan Garg.