##@package random_image_demo
# Demonstrates the usage of some of the fucntions in random_image.

from __future__ import division

from random import random

from image import *
from random_image import *

## Layers white noise of different frequencies on top of each other.
def demo_random_image():
	dims = (256, 256)
	layer_count = 6

	channels = []
	factors = []

	for i in range(layer_count):
		print i
		period = 2**i

		inputSamples = [0, 0.2, 0.4, 0.6, 0.8, 1.0]
		outputSamples = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
		inputSamples = [0.0, 0.1 + (layer_count - i)/(layer_count-1)*0.3, 0.9 - (layer_count - i)/(layer_count-1)*0.3, 1.0]
		outputSamples = [1.0, 1.0, 0.0, 1.0]
		distribution = make_distribution_curve(inputSamples, outputSamples)
		red = random_grid(distribution, dims, period)
		green = random_grid(distribution, dims, period)
		blue = random_grid(distribution, dims, period)

		channels.append(red)
		channels.append(green)
		channels.append(blue)

		grid = channels_to_rgb_grid((red, green, blue))
		grid_to_rgb_image(grid, 'random_%d.png' % i)

		factors.append(1/layer_count)
		
	red = add_grey_grids(channels[0::3], factors)
	green = add_grey_grids(channels[1::3], factors)
	blue = add_grey_grids(channels[2::3], factors)

	grid = channels_to_rgb_grid((red, green, blue))
	grid_to_rgb_image(grid, 'random.png')

## From a list of probabilities, make a list of accumulativer probabilities.
def make_acc(probs):
	acc = [0] * len(probs)
	tot = sum(probs)
	acc[0] = probs[0] / tot

	for i in range(1, len(probs)):
		acc[i] = acc[i - 1] + probs[i] / tot

	return acc

def make_blend_grid(props_list):
	tot = sum(props_list)
	n = int(sqrt(len(props_list)))
	new_props = Grid2D((n, n))
	k = 0
	for index in new_props.index_iter():
		new_props[index] = props_list[k] / tot
		k += 1

	return new_props

def demo_corr():
	dims = (128, 128)

	grid = white_noise(dims)

	for k in range(8, 512):
		
		probs1 = perms(k)
		probs1 = grid_to_list(expand_probs(list_to_grid(probs1)))

		acc_probs = make_acc(probs1)
		
		print k, probs1, acc_probs
		i = 0

		for j in xrange(1, 11):
			grid1 = grid		

			print k, j, 'corr1'
			for i in xrange(25):				
				grid1 = corr(grid1, acc_probs, j / 10)
			grid1 = normalize_grey(grid1)
			rgb_grid = channels_to_rgb_grid([grid1, grid1, grid1])
			grid_to_rgb_image(rgb_grid, 'random_corr_pn_%02d_%02d_%02d.png' % (k, j, i))

def demo_corr3():
	dims = (128, 128)

	grid = white_noise(dims)

	for k in range(28, 29):
		
		probs1 = perms(k)
		probs1 = grid_to_list(expand_probs(list_to_grid(probs1)))

		acc_probs = make_acc(probs1)
		
		print k, probs1, acc_probs
		i = 0

		for j in xrange(9, 10):
			grid1 = grid		

			print k, j, 'corr1'
			for i in xrange(50):				
				grid1 = corr(grid1, acc_probs, j / 10)
				grid1 = normalize_grey(grid1)
				rgb_grid = channels_to_rgb_grid([grid1, grid1, grid1])
				grid_to_rgb_image(rgb_grid, 'random_corr_j_%02d_%02d_%02d.png' % (k, j, i))
			
def demo_corr2():
	dims = (32, 32)

	grid = white_noise(dims)

	for k in range(1, 8):
		
		probs1 = perms(k)
		blend_grid = make_blend_grid(probs1)
		print k, probs1, make_acc(probs1)
		i = 0

		
		grid1 = grid		

		print k
		for i in range(50):
				
			grid1 = corr2(grid1, blend_grid, 1)
		grid1 = normalize_grey(grid1)
		rgb_grid = channels_to_rgb_grid([grid1, grid1, grid1])
		grid_to_rgb_image(rgb_grid, 'random_corr2_%02d_%02d_%02d.png' % (k, 10, i))
			
def perms(m, n=9):
	lst = [0] * n

	for i in range(n):                
		lst[i] = m % 2                
		m = m // 2

	return lst

def list_to_grid(lst):
	m = int(sqrt(len(lst)))
	grid = Grid2D((m, m), 0)
	
	for k, item in enumerate(lst):
		x = k % m
		y = k // m
		
		grid[x, y] = item
		
	return grid

def expand_probs(grid):
	m = (grid.width - 1) + grid.width
	n = (grid.width - 1) // 2
	new_grid = Grid2D((m, m), 0)
	sum = 0
	for i in xrange(0, m - 2*n):
		for j in xrange(0, m - 2*n):
			for x in xrange(grid.width):
				for y in xrange(grid.height):
					v = grid[x, y]*grid[i, j]
					new_grid[i + x, j + y] += v
					sum += v
	
	sum_resp = 1 / sum

	for index in new_grid.index_iter():
		new_grid[index] *= sum_resp

	return new_grid

def grid_to_list(grid):
	lst = [0] * (grid.width * grid.height)
	
	for index in grid.index_iter():
		x, y = index
		lst[x + grid.width * y] = grid[index]
	return lst

def demo_corr_window():
	k = 68        
	grid = rgb_image_to_image_grid_channels('bar.png' % k)[0] #red only!

	energy = corr_window(grid, 1)
	print energy

	print perms(k)

def demo():
	seed(0)
	demo_random_image()
	#demo_corr3()
	#demo_corr2()	
	#demo_corr_window()
	#

demo()
