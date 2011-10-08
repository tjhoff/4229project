## @package test_tiles
## Unit tests for tiles (under constrcution).

from unittest import TestCase
from unittest import TestSuite

from enhanced_grid import Grid2D

from tiles import energy2
from tiles import energy3
from tiles import calc_acc_energy
from tiles import find_min_seam
from tiles import quilt

from tiles import ENERGY_MAX

from image import greyscale_grid_to_rgb_grid
from image import grid_to_rgb_image

def add_colors(obj):
    obj.white = (1, 1, 1, 1)
    obj.black = (0, 0, 0, 1)
    obj.grey = (0.5, 0.5, 0.5, 1)
    
    obj.brown = (0.7, 0.3, 0.1, 1)
    obj.washblue = (0.1, 0.3, 0.7, 1)
    
    obj.red = (1, 0, 0, 1)        
    obj.green = (0, 1, 0, 1)
    obj.blue = (0, 0, 1, 1)
    
    obj.darkred = (0.5, 0, 0, 1)
    obj.darkgreen = (0, 0.5, 0, 1)
    obj.darkblue = (0, 0, 0.5, 1)
    
    
def make_checker_grid(col_obj):
    checker_grid = Grid2D((50, 30), col_obj.white)
        
    for index in checker_grid.index_iter():
        x, y = index
        if (x + y) % 2 == 0:
            checker_grid[index] = col_obj.black
    return checker_grid
            
def make_half_checker_grids(col_obj):
    checker_grid1 = Grid2D((50, 30), col_obj.white)
    checker_grid2 = Grid2D((50, 30), col_obj.white)
        
    for index in checker_grid1.index_iter():
        x, y = index
        checker_grid = checker_grid1
        
        if x < 25:
            checker_grid = checker_grid2
        if x != 25:
            if (x + y) % 2 == 0:
                checker_grid[index] = col_obj.black
            else:
                checker_grid[index] = col_obj.grey
            
    return checker_grid1, checker_grid2

class TestEnergy2(TestCase):
    def setUp(self):
        add_colors(self)
        
    def testMax(self):
        self.assertAlmostEqual(energy2(self.black, self.white), 3)
        self.assertAlmostEqual(energy2(self.white, self.black), 3)
        
    def testSymmetry(self):
        self.assertAlmostEqual(energy2(self.washblue, self.brown), energy2(self.brown, self.washblue))
        
    def testZeroEnergy(self):
        self.assertAlmostEqual(energy2(self.brown, self.brown), 0)
        
    def testChannelEquivalence(self):
        self.assertAlmostEqual(energy2(self.red, self.darkred), 
                               energy2(self.blue, self.darkblue))
        self.assertAlmostEqual(energy2(self.red, self.darkred), 
                               energy2(self.green, self.darkgreen))
        
class TestEnergy3(TestCase):
    def setUp(self):
        add_colors(self)
        
    def testMax(self):
        self.assertAlmostEqual(energy3(self.white, self.black, self.black), 6)
        self.assertAlmostEqual(energy3(self.black, self.white, self.white), 6)
        
    def testSymmetry(self):
        self.assertAlmostEqual(energy3(self.black, self.washblue, self.brown), 
                               energy3(self.black, self.brown, self.washblue))
        self.assertAlmostEqual(energy3(self.black, self.brown, self.washblue), 
                               energy3(self.black, self.washblue, self.brown))
        self.assertAlmostEqual(energy3(self.brown, self.washblue, self.black), 
                               energy3(self.washblue, self.brown, self.black))
        self.assertAlmostEqual(energy3(self.washblue, self.brown, self.black), 
                               energy3(self.brown, self.washblue, self.black))
        
    def testZero(self):
        self.assertAlmostEqual(energy3(self.brown, self.brown, self.brown), 0)
        
    def testChannelEquivalence(self):
        self.assertAlmostEqual(energy3(self.red, self.darkred, self.black), 
                               energy3(self.blue, self.darkblue, self.black))
        self.assertAlmostEqual(energy3(self.red, self.darkred, self.black), 
                               energy3(self.green, self.darkgreen, self.black))
        
    def testDouble(self):
        self.assertAlmostEqual(2*energy3(self.brown, self.washblue, self.brown),
                               1*energy3(self.brown, self.washblue, self.washblue))
        self.assertAlmostEqual(2*energy3(self.washblue, self.washblue, self.brown),
                               1*energy3(self.washblue, self.brown, self.brown))
        
class TestCalcAccEnergy(TestCase):
    def setUp(self):
        add_colors(self)       
                
        self.checker_grid = make_checker_grid(self)
        self.checker_grid1, self.checker_grid2 = make_half_checker_grids(self)        
    
    def testZero(self):
        washblue_grid = Grid2D((50, 30), self.washblue)

        acc_energy = calc_acc_energy(washblue_grid, washblue_grid)
        
        for index in acc_energy.index_iter():
            x, y = index
            if (x > 0):
                self.assertAlmostEqual(acc_energy[index], 0)
            else:
                self.assertAlmostEqual(acc_energy[index], ENERGY_MAX)
                
    def testGrowing(self):
        acc_energy = calc_acc_energy(self.checker_grid, self.checker_grid)
        
        w, h = self.checker_grid.dims
        for i in range(1, w-1):
            for j in range(1, h):
                self.assertTrue(acc_energy[i, j] >= min(acc_energy[i, j-1], acc_energy[i-1, j-1], acc_energy[i+1, j-1]))
                
    def testAccEnergy(self):
        acc_energy = calc_acc_energy(self.checker_grid1, self.checker_grid2)
        
        print acc_energy[:,0]
                

class TestFindMinSeam(TestCase):
    def setUp(self):
        add_colors(self)       
                
        self.checker_grid = make_checker_grid(self)
        self.checker_grid1, self.checker_grid2 = make_half_checker_grids(self)
        
    def testSeam(self):
        seam = find_min_seam(self.checker_grid1, self.checker_grid2)

        for item in seam:
            self.assertEqual(item, 25)
            
        
                