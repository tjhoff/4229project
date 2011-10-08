##@package tiles_demo demo functions in tiles.

from __future__ import division

from tiles import *
from image import *

def demo():
    #grid1 = rgb_image_to_grid('im_t5.png')
    #grid2 = rgb_image_to_grid('im_t5.png')
    
    #grid = quilt(grid1, grid2, 80)
    #energy = normalize_grey(energy)
    #energy = greyscale_grid_to_rgb_grid(energy, (1, 1, 1, 1))
    
    #grid_to_rgb_image(energy, 'energy.png')
    
    src = rgb_image_to_grid('contrast.png')
    grid = quilt_multi(src, 100, 100, 4, 4, 70, 70)
    grid_to_rgb_image(grid, 'quilted.png')
    
demo()