## @package quadtree_demo
# Shows how to use the quadtree and quadtree_image functions and classes.

from __future__ import division

from random import seed

from image import *
from perlin_noise import *
from quadtree_image import *

pallet = [
    (1.0, 0, 0, 1),
    (1.0, 0, 0, 1),
    (.6, 0, 0, 1),
    (.6, .3, .3, 1),
    (0, .3, .3, 1),
    (0, .5, .5, 1),
    (0, .5, .5, 1)
    ]

CHANNEL_DETAIL = 0.1
IMAGE_DETAIL = 0.05

def round_grid(grid):
    new_grid = Grid2D(grid.dims)

    for index in grid.index_iter():
        try:
            new_grid[index] = int(round(grid[index]))
        except:
            print grid[index]

    return new_grid

def int_rand_grid(grid):
    new_grid = Grid2D(grid.dims)

    for index in grid.index_iter():
        x = grid[index]        
        n1 = int(x)
        d = x - n1
        n2 = n1 + 1

        if random() < d:
            n = n2
        else:
            n = n1

        new_grid[index] = n

    return new_grid

## Demonstrates the working of a Quadtree
def demo_quadtree():
    grid = Grid2D((4, 4), 0)
    
    grid[0, 0] = .9
    grid[0, 1] = 1
    grid[1, 0] = .8
    grid[1, 1] = 1
    
    quadtree = Quadtree(grid, Measure(), .2)
    
    for cell in quadtree:
        print cell

## This demo illustrates how to get better results
# with quadtrees holding discrete data.
#
# Four methods are tested:
#   rounding
#   randomisation
#   rounding on interpolated data
#   randomisation on interpolated data
#
# We assume the discrete data to be taken from
# an ordered tile set. For comparisson, trees
# with continuous data are also generated.
def demo_discrete_rnd_interpolation():
    qnames = ['normal', 'interpolated']
    inames = ['rounded', 'randomised']

    grid = int_perlin_noise(128, 128, 5, len(pallet))[0]
    rgb_grid = index_grid_to_rgb_grid(grid, pallet)
    grid_to_rgb_image(rgb_grid, 'discrete_grid.png')

    tree = Quadtree(grid, ChannelMeasure(), 0.5)

    tree2 = Quadtree(rgb_grid, ImageMeasure(), 0.1)
    print tree.count(False), tree2.count(False)

    qgrids = [
        render_outline(tree2, 1, False, False),
        render_outline(tree2, 1, False, True)]

    
    
    for qgrid, qname in zip(qgrids, qnames):
        grid_to_rgb_image(qgrid, 'continuous_quadtree_%s.png' % qname)

    qgrids = [
        render_outline(tree, 1, False, False),
        render_outline(tree, 1, False, True)]

    for qgrid, qname in zip(qgrids, qnames):
        iqgrids = [
            round_grid(qgrid),
            int_rand_grid(qgrid)]       
    
        for iqgrid, iname in zip(iqgrids, inames):
            rgb_qgrid = index_grid_to_rgb_grid(iqgrid, pallet)
            grid_to_rgb_image(rgb_qgrid, 'discrete_quadtree_%s_%s.png' % (qname, iname))

    
    #print grid

## Demonstrates the working of the Quadtree with ImageMeasure.
def demo_quadtree_image(): 
    base_name = 'bar'
    grid = rgb_image_to_grid(base_name + '.png')
    tree = Quadtree(grid, ImageMeasure(), IMAGE_DETAIL) #51
    
    print tree.count(False), tree.count(True)
    
    new_grid = render_outline(tree, 1, False)
    grid_to_rgb_image(new_grid, base_name + '_quadtree_' + '.png')
    channels = rgb_image_to_image_grid_channels(base_name + '.png')  
    grids = []
    
    cnames = ['red', 'green', 'blue']
    colors = [
        (1, 0, 0, 1),
        (0, 1, 0, 1),
        (0, 0, 1, 1)]
    
    for channel, cname, color in zip(channels, cnames, colors):
        tree = Quadtree(channel, ChannelMeasure(), CHANNEL_DETAIL)
        
        print tree.count(False), tree.count(True)
        
        new_grid = render_outline(tree, 1.5, False, False)
        grids.append(new_grid)
        
        rgb_grid = greyscale_grid_to_rgb_grid(new_grid, color)    
        
        grid_to_rgb_image(rgb_grid, base_name + '_channel_' +  cname +'.png')
    
    new_grid = channels_to_rgb_grid(grids)
    
    grid_to_rgb_image(new_grid, base_name + '_channel_all.png')    

## Demonstrates the working of the Quadtree with ImageMeasure.
def demo_quadtree_interpolate(): 
    base_name = 'bar'
    grid = rgb_image_to_grid(base_name + '.png')
    tree = Quadtree(grid, ImageMeasure(), IMAGE_DETAIL) #51
    
    print tree.count(False), tree.count(True)
    
    new_grid = render_outline(tree, 1, False, True)
    grid_to_rgb_image(new_grid, base_name + '_quadtree_interpolate_' + '.png')
    
    channels = rgb_image_to_image_grid_channels(base_name + '.png')  
    grids = []
    
    cnames = ['red', 'green', 'blue']
    colors = [
        (1, 0, 0, 1),
        (0, 1, 0, 1),
        (0, 0, 1, 1)]
  
    for channel, cname, color in zip(channels, cnames, colors):
        tree = Quadtree(channel, ChannelMeasure(), CHANNEL_DETAIL)
        
        print tree.count(False), tree.count(True)
        
        new_grid = render_outline(tree, 1, False, True)
        grids.append(new_grid)
        
        rgb_grid = greyscale_grid_to_rgb_grid(new_grid, color)    
       
        grid_to_rgb_image(rgb_grid, base_name + '_channel_interpolate_' +  cname +'.png')
  
    new_grid = channels_to_rgb_grid(grids)    
    grid_to_rgb_image(new_grid, base_name + '_channel_interpolate_all.png')     

def demo():
    seed(0)
    demo_quadtree()
    #demo_quadtree_interpolate()
    demo_quadtree_image()
    #demo_discrete_rnd_interpolation()

demo()

