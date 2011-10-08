from __future__ import division

from fast_grid import Grid2D
from image import mix_color

def blend(grid1, grid2, blend_image):
    dims = blend_image.dims
    
    grid = Grid2D(dims)
    
    for index in grid.index_iter():
        grid[index] = mix_color(grid1[index], grid2[index], blend_image[index])
    
    return grid