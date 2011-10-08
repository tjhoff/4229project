## @package super_saturation
# Under construction - do not use!

from __future__ import division

from PIL import Image

from enhanced_grid import *

def to_byte(f):
	v = (int) (255 * f)
	if v < 0:
		v = 0
	elif v > 255:
		v = 255
		
	return v

## returns every channel as a grid
def image_to_channels(image):
	
	dims = image.size
	
	grids = (
		Grid2D(dims, 0),
		Grid2D(dims, 0),
		Grid2D(dims, 0))
		
	pix = image.load()
	
	for index in grids[0].index_iter():
		pixel = pix[index]
		
		for channel in range(3):
			grids[channel][index] = pixel[channel] / 255
			
	return grids
			
def channels_to_image(channels):
	
	image = Image.new('RGBA', channels[0].dims)
	pix = image.load()
	
	for index in channels[0].index_iter():
		pix[index] = (
			to_byte(channels[0][index]), 
			to_byte(channels[1][index]), 
			to_byte(channels[2][index]))
		
	return image
			
def multiply(grid, factor):
	for index in grid.index_iter():
		grid[index] = grid[index] * factor

def diffuse_super_saturation_window(src_grid, dest_grid, point, windowSize):	
	if src_grid[point] > 1.0:
		excess = src_grid[point] - 1.0
	else:
		excess = 0
	
	window_size = 2.0
	
	excess_per_cell = excess / (window_size * window_size)
	
	dest_grid[point] = src_grid[point] - excess
	
	for index in src_grid.square_index_iter(point, windowSize):
		if(index != point):
			dest_grid[index] = dest_grid[index] + excess_per_cell

def diffuse_super_saturation(channels):
	
	dims = channels[0].dims
	
	for channel in channels:
		multiply(channel, 2.0)
	
	dest_channels = (
		Grid2D(dims, 0),
		Grid2D(dims, 0),
		Grid2D(dims, 0))
	
	for channel , dest_channel in zip(channels, dest_channels):
		for index in channel.index_iter():
			diffuse_super_saturation_window(channel, dest_channel, index, 1)
			
	return channels_to_image(dest_channels)			
			
	
	
	
def demo():
	image = Image.open('screenshot_1.png')
	channels = image_to_channels(image)
	new_image = diffuse_super_saturation(channels)
	new_image.save('screenshot_1_ss.png')
	
demo()
	