##@package draw Contains some drawing functions.
##

from __future__ import division

from math import pi
from math import cos
from math import sin
from math import log
from math import ceil

from enhanced_grid import Grid2D
from image import greyscale_grid_to_rgb_grid
from image import grid_to_rgb_image
from perlin_noise import SmoothNoise1D
from perlin_noise import perlin_noise_from_smoothnoise_1d

TWO_PI = 2 * pi
LOG2 = log(2)

## Draws a circle at a point in a grid.
def draw_circle(grid, centre, radius):
    circumference = TWO_PI * radius
    power = ceil(log(circumference) / LOG2)    
    sample_count = pow(2, power)
    print sample_count
    x0, y0 = centre
    
    for i in range(sample_count):
        angle = i / sample_count * TWO_PI
        
        x = int(x0 + radius * cos(angle))
        y = int(y0 + radius * sin(angle))
        
        grid[x,y] = 1

## Draws an ellipse at a point in a grid.        
def draw_ellipse(grid, centre, radius1, radius2, theta):
    circumference = pi * (radius1 + radius2) #approx
    power = ceil(log(circumference) / LOG2)    
    sample_count = pow(2, power)
    print sample_count
    x0, y0 = centre
    
    sintheta = sin(theta)
    costheta = cos(theta)
    
    for i in range(sample_count):
        angle = i / sample_count * TWO_PI
        cosangle = cos(angle)
        sinangle = sin(angle)
        
        x = int(x0 + radius1 * cosangle*costheta - radius2*sinangle*sintheta)
        y = int(y0 + radius2 * sinangle*costheta + radius1*cosangle*sintheta)
        
        grid[x,y] = 1

#Draws a Perlin-noise modified ellipse.
def draw_perlin_ellipse(grid, centre, radius1, radius2, theta, displacement, noise=None):

    x0, y0 = centre
    
    if noise == None:
        circumference = TWO_PI * (radius1 + radius2 + displacement) #approx
        power = ceil(log(circumference) / LOG2)    
        sample_count = int(pow(2, power))
        print sample_count    
        smooth_noise = SmoothNoise1D(sample_count)
        noise = perlin_noise_from_smoothnoise_1d(sample_count, 8, 0.5, smooth_noise)    
    else:
        sample_count = len(noise)
    
    sintheta = sin(theta)
    costheta = cos(theta)
    
    for i in range(sample_count):
        angle = i / sample_count * TWO_PI
        cosangle = cos(angle)
        sinangle = sin(angle)
        
        displaced_radius1 = radius1 +  displacement*noise[i];
        displaced_radius2 = radius2 +  displacement*noise[i];

        
        x = int(x0 + displaced_radius1 * cosangle*costheta - displaced_radius2 * sinangle*sintheta)
        y = int(y0 + displaced_radius2 * sinangle*costheta + displaced_radius1 * cosangle*sintheta)
        
        grid[x,y] = 1

## Draws a Perlin-noise modified circle.
def draw_perlin_circle(grid, centre, radius, displacement, noise=None):
    circumference = TWO_PI * (radius + 2*displacement)
    power = ceil(log(circumference) / LOG2)    
    sample_count = int(pow(2, power))
    
    x0, y0 = centre
    if noise == None:
        smooth_noise = SmoothNoise1D(sample_count)
        noise = perlin_noise_from_smoothnoise_1d(sample_count, 8, 0.5, smooth_noise)
    
    for i in range(sample_count):
        angle = i / sample_count * TWO_PI
        displaced_radius = radius + displacement*noise[i]
        x = int(x0 + displaced_radius * cos(angle))
        y = int(y0 + displaced_radius * sin(angle))
        
        grid[x,y] = 1

## Draws a recursive circle pattern.
def draw_circle_tree(grid, centre, radius, levels, branches):
    draw_circle(grid, centre, radius)
    x0, y0 = centre
    if levels > 1:
        for i in range(branches):
            angle = i * TWO_PI / branches            
            x = x0 + radius * cos(angle)
            y = y0 + radius * sin(angle)
            draw_circle_tree(grid, (x, y), 0.4 * radius, levels - 1, branches)

## Draws a recursive circle pattern using Perlin-noise modified trees.
def draw_perlin_circle_tree(grid, centre, radius, levels, branches, subradius=None):
    displacement = radius
    if subradius == None:
        subradius = radius
    circumference = TWO_PI * (radius + 2*displacement)
    power = ceil(log(circumference) / LOG2)    
    sample_count = int(pow(2, power))
    
    smooth_noise = SmoothNoise1D(sample_count)
    noise = perlin_noise_from_smoothnoise_1d(sample_count, 8, 0.5, smooth_noise)
    
    draw_perlin_circle(grid, centre, radius, displacement, noise)
    x0, y0 = centre
    if levels > 1:
        for i in range(branches):
            angle = i * TWO_PI / branches
            displaced_radius = subradius + displacement*noise[i*sample_count//branches]
            
            x = x0 + displaced_radius * cos(angle)
            y = y0 + displaced_radius * sin(angle)
            draw_perlin_circle_tree(grid, (x, y), 0.4 * radius, levels - 1, branches, 0.4*subradius)

## Draws a recursive ellipse pattern using Perlin-noise modified trees.
def draw_perlin_ellipse_tree(grid, centre, radius1, radius2, theta, displacement, levels, branches, innerfactor=None):
    if innerfactor == None:
        innerfactor = 1
        
    subradius1 = radius1 * innerfactor
    subradius2 = radius2 * innerfactor
    
    sintheta = sin(theta)
    costheta = cos(theta)
    
    circumference = 2 * pi * (radius1 + radius2 + displacement)
    power = ceil(log(circumference) / LOG2)    
    sample_count = int(pow(2, power))
    
    smooth_noise = SmoothNoise1D(sample_count)
    noise = perlin_noise_from_smoothnoise_1d(sample_count, 8, 0.5, smooth_noise)
    
    draw_perlin_ellipse(grid, centre, radius1, radius2, theta, displacement, noise)
    draw_ellipse(grid, centre, radius1, radius2, theta)
    
    x0, y0 = centre
    if levels > 1:
        for i in range(branches):
            angle = i * TWO_PI / branches
            noise_index = i*sample_count//branches
            cosangle = cos(angle)
            sinangle = sin(angle)
            
            displaced_radius1 = subradius1 +  displacement*noise[noise_index];
            displaced_radius2 = subradius2 +  displacement*noise[noise_index];
        
            x = int(x0 + displaced_radius1 * cosangle*costheta - displaced_radius2 * sinangle*sintheta)
            y = int(y0 + displaced_radius2 * sinangle*costheta + displaced_radius1 * cosangle*sintheta)
        
        
            draw_perlin_ellipse_tree(grid, (x, y), 0.4 * radius1, 0.4 * radius2, theta, 0.4*displacement, levels - 1, branches, innerfactor)            

## Demos the functions in this module.
def demo_draw():
    
    grid = Grid2D((600, 600), 0)
    
    draw_perlin_ellipse_tree(grid, (300, 300), 100, 70, pi/4, 70, 3, 4, 0.8)

    grid = greyscale_grid_to_rgb_grid(grid, [1, 1, 1, 1])
    grid_to_rgb_image(grid, 'draw/perlin_ellipse_tree.png')
    
demo_draw();
