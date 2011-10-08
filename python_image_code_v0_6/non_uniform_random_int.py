## @package non_uniform_random_int
## Provides functionality for generating non-uniform random integers.

from __future__ import division
from random import random
from copy import copy

#Used in asserts for floating point comparisons.
FLOAT_ERROR = 0.000001

## Class for generating random integers between 0 (inclusive) and and upperbound (exlusive),
## with given probabilities.
##
## Based on the algorithm in Donald Knuth's The Art of Programming, 2ed. V2 3.4.1.A, p.119. 
## See also Exercise 7 (p. 139) and its solution (p. 585) of that section.
## [#131 #151 #597].
##
## @author: Herman Tulleken
## @date: 25 April 2009
class NonUniformRandomInt:
    def __init__(self, relative_probs_list):
        absolute_prob_list = self.make_absolute_probs_list(relative_probs_list)
        self.up_bound = len(absolute_prob_list)
        self.probs, self.overflow = self.calc_tables(absolute_prob_list)        

    ##@private
    def make_absolute_probs_list(self, relative_probs_list):
        total = sum(relative_probs_list)
        absolute_prob_list = []
        
        for relative_prob in relative_probs_list:
            absolute_prob_list.append(relative_prob / total)

        return absolute_prob_list
    
    ##@private        
    def calc_tables(self, probs_list):
        #Make a list of tuples that combine a value with a probability
        distribution = []
        
        for i, prob in enumerate(probs_list):
            distribution.append((i, prob))
            
        # Sort the list of tuples according to the probabilities
        
        ## Comparrison function used to compare tuples of values and probabilities
        # according to the probabilities
        def comp_probs(x, y):
            if x[1] > y[1]:
                return 1
            elif x[1] < y[1]:
                return -1
            else:
                return 0
        #---------------------------------------------------------------------------
        
        distribution.sort(comp_probs)
        
        # Make new empty tables
        probs = [0] * self.up_bound
        overflow = [0] * self.up_bound
                
        for n in range(self.up_bound):    
            min_val, min_prob = distribution[0]
            assert min_prob <= 1/self.up_bound + FLOAT_ERROR
            
            max_val, max_prob = distribution[-1]
            assert max_prob >= 1/self.up_bound - FLOAT_ERROR
            
            probs[min_val] = self.up_bound * min_prob
            assert probs[min_val] <= 1 + FLOAT_ERROR
            
            overflow[min_val] = max_val            
            
            del distribution[0]
            
            if (len(distribution) > 0):
                del distribution[-1]

            #remaining_prob = 
            #   = max_prob - {prob of choosing cell min_val} * {prob of not using cell value}
            #   = max_prob - 1/self.up_bound*[(1 - self.up_bound * min_prob)]
            #   = max_prob - 1 / self.up_bound - 1 / self.up_bound + min_prob 
            remaining_prob = max_prob + min_prob - 1 / self.up_bound
            
            i = 0
            if len(distribution) > 0:                  
                while distribution[i][1] < remaining_prob:
                    i += 1
                    if i >= len(distribution):
                        break
               
            distribution.insert(i, (max_val, remaining_prob))                
            
        return probs, overflow
    
    ## Returns a random integer. The range and distribution depends on the
    # parameters with which this class has been constructed.
    def random(self):
        uniform = random() * self.up_bound
        int_uniform = int(uniform)
        frac_uniform = uniform - int_uniform
        
        if frac_uniform < self.probs[int_uniform]:
            return int_uniform
        else:
            return self.overflow[int_uniform]    

## Calculates the expected average for a list of probabilities. Used by the demo.
def calc_expected(probs_list):
    expected = 0
    total = sum(probs_list)
    for i, prob in enumerate(probs_list):
        expected += prob * i / total
    return expected

## Demonstrates the usage of NonUniformRandomInt.
def demo_NonUniformRandomInt():
    probs_list = [3/18, 7/18, 8/18]
    r = NonUniformRandomInt(probs_list)    
    s = 0
    L = 100000
    frequencies = [0, 0, 0]
    
    for i in xrange(L):
        n = r.random()
        frequencies[n] += 1/L
        s += n
        
    print s / L, calc_expected(probs_list), frequencies

demo_NonUniformRandomInt()
        