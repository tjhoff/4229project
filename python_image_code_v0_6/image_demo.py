## @package image_demo
# Illustrates some of the functions in the image module.

from __future__ import division

from enhanced_grid import *
from image import *

## Demonstrates combimining several images into s signle image,
def demo_stitch():
    i = 0
    j = 0

    large_grid = Grid2D((128*14, 9*128))
    
    for k in range(126):
        fname = 'perlin_noise/perlin_lin_channels_' + str(k) + '.png'
        grid = rgb_image_to_grid(fname)

        print k

        for small_i in range(128):
            for small_j in range(128):
                large_grid[128 * i + small_i, j*128 + small_j] = grid[small_i, small_j]

        i += 1

        if i >= 14:
            i = 0
            j += 1

    grid_to_rgb_image(large_grid, 'large_im.png')

## Demonstrates the edge detection algorithm.
def demo_edge():
    grid = rgb_image_to_grid('bar.png')
    new_grid = edge(grid, 0)
    grid_to_rgb_image(new_grid, 'edge2_%2d.png' % 0 )

def demo_normalize():
    grid = rgb_image_to_grid('perlin_lin_channels_104.png')
    new_grid = normalize(grid)
    grid_to_rgb_image(new_grid, 'normalize.png')
def demo_entropy():
    grid = rgb_image_to_grid('bar.png')

    for k in range(10, 200, 10):    
        new_grid = normalize(entropy2(grid, k))
        grid_to_rgb_image(new_grid, 'entropy2_%3d.png' % k)
def demo():    
    #demo_stitch()
    #demo_edge()
    #demo_normalize()
    demo_entropy()

demo()
