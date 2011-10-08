## @package blend_demo 
## Demonstrates how to make blends of seamless tiles.

from __future__ import division

from image import *
from perlin_noise import *
from tiles import *

WHITE = (1, 1, 1, 1)

## Blends an image with colours - one for each corner.
def blend_corners(grid, corner_colors, amount):
	w, h = grid.dims
	new_grid = Grid2D((w, h))

	for i in range(w):
		horizontal_blend = i / w

		color1 = mix_color(corner_colors[0], corner_colors[1], horizontal_blend)
		color2 = mix_color(corner_colors[2], corner_colors[3], horizontal_blend)

		for j in range(h):            
			vertical_blend = j / h

			color = mix_color(color1, color2, vertical_blend)

			new_grid[i, j] = mix_color(grid[i, j], color, amount)

	return new_grid

## Multiplies an image with colours - one for each corner.
def multiply_corners(grid, corner_colors, amount):
	w, h = grid.dims
	new_grid = Grid2D((w, h))

	for i in range(w):
		horizontal_blend = i / w

		color1 = mix_color(corner_colors[0], corner_colors[1], horizontal_blend)
		color2 = mix_color(corner_colors[2], corner_colors[3], horizontal_blend)

		for j in range(h):            
			vertical_blend = j / h

			color = mix_color(color1, color2, vertical_blend)

			red1, green1, blue1, alpha1 = color
			red2, green2, blue2, alpha2 = grid[i, j]

			new_color = red1 * red2, green1 * green2, blue1 * blue2, 1

			new_grid[i, j] = new_color

	return new_grid

## Makes Perlin tiles used for creating perlin ramp blend masks
def make_perlin_tiles(width, height):
	perlin_grids = perlin_noise_tileable(width, height, 6, 0.5, 2)

	return perlin_grids

## Adds a planar ramp to the given image.
def add_ramp(grid, ramp_height):
	w, h = grid.dims
	new_grid = Grid2D((w, h), 0)

	for i in range(w):
		for j in range(h):
			new_grid[i, j] = grid[i, j] + j / h * ramp_height

	return new_grid

## Makes a Perlin ramp that can be used as a blend mask.
def make_perlin_ramp_images():
	perlin_grids = make_perlin_tiles(128, 128)
	for i, perlin_grid in enumerate(perlin_grids):
		perlin_grid = add_ramp(perlin_grid, 2) #0.5 .. 2.5
		perlin_grid = multiply_grid(perlin_grid, 2) #1.. 5
		perlin_grid = add_grid(perlin_grid, -2.5) #-1.5 .. 2.5
		perlin_grid = saturate(perlin_grid)       

		#sharp version
		sharp_perlin_grid = threshold(perlin_grid, 0.5)
		sharp_perlin_grid = greyscale_grid_to_rgb_grid(sharp_perlin_grid, (1, 1, 1, 1))
		grid_to_rgb_image(sharp_perlin_grid, 'blend_demo_files/perlin_ramp_sharp%d.png' % i)
		
		#smooth version
		perlin_grid = greyscale_grid_to_rgb_grid(perlin_grid, (1, 1, 1, 1))
		grid_to_rgb_image(perlin_grid, 'blend_demo_files/perlin_ramp%d.png' % i)
		



# Shows blending of images using different blend masks
def blend_mask_demo():
	#Load first image
	grid1 = rgb_image_to_grid('blend_demo_files/grass.png')

	#Load second image
	grid2 = rgb_image_to_grid('blend_demo_files/stone.png')

	mask_types = [
		'smooth_v',
		'perlin_ramp0',
		'perlin_ramp1',
		'perlin_ramp_sharp0',
	]


	for mask_type in mask_types:   
		#Load mask
		mask = rgb_grid_to_greyscale_grid(rgb_image_to_grid('blend_demo_files/' + mask_type + '.png'))

		#Blend images
		new_grid = blend(grid1, grid2, mask)

		#Save result
		grid_to_rgb_image(new_grid, 'blend_demo_files/blended_' + mask_type + '.png')
		
# Shows blending of images using quilting
def quilt_demo():
	#Load first image
	grid1 = rgb_image_to_grid('blend_demo_files/grass.png')

	#Load second image
	grid2 = rgb_image_to_grid('blend_demo_files/stone.png')
 
	#Blend images
	new_grid = quilt(grid1, grid2, 128)

	#Save result
	grid_to_rgb_image(new_grid, 'blend_demo_files/quilted.png')

## Shows four images blended together
def blend_demo4():
	source_tiles = [
		'grass', 
		'stone',
		'twigs',
		'red_grass']

	grids = []

	for source_tile in source_tiles:
		grids.append(rgb_image_to_grid('blend_demo_files/%s.png' % source_tile))

	mask_type1 = 'smooth_h'
	mask_type2 = 'smooth_v'

	mask1 = rgb_grid_to_greyscale_grid(rgb_image_to_grid('blend_demo_files/' + mask_type1 + '.png'))
	mask2 = rgb_grid_to_greyscale_grid(rgb_image_to_grid('blend_demo_files/' + mask_type2 + '.png'))    

	tiles = []

	new_grid1 = blend(grids[0], grids[1], mask1)
	new_grid2 = blend(grids[2], grids[3], mask1)

	new_grid = blend(new_grid1, new_grid2, mask2)

	tiles.append(new_grid)
	tiles.append(new_grid1)
	tiles.append(new_grid2)

	new_grid1 = blend(grids[0], grids[2], mask2)
	new_grid2 = blend(grids[1], grids[3], mask2)

	tiles.append(new_grid1)
	tiles.append(new_grid2)

	for i, tile in enumerate(tiles):
		grid_to_rgb_image(tile, 'blend_demo_files/blended_' + 'smooth_2_' + str(i) + '.png')

## Shows altering an images colours
def blend_corners_demo():
	grid = rgb_image_to_grid('blend_demo_files/grass_grey.png')

	green = (0, 1, 0, 1)
	yellow_green = (0.5, 1, 0, 1)
	blue_green = (0, 1, 0.5, 1)
	dark_green = (0, 0.5, 0, 1)
	red = (1, 0, 0, 1)
	green = (0, 1, 0, 1)
	blue = (0, 0, 1, 1)
	black = (0, 0, 0, 1)

	color_sets = [
		[ green, yellow_green, blue_green, dark_green],
		[ red, green, blue, black],
		[WHITE, WHITE, WHITE, WHITE]
	]

	for i, color_set in enumerate(color_sets):
		new_grid = multiply_corners(grid, color_set, 1)
		grid_to_rgb_image(new_grid, 'blend_demo_files/corners_multiply_%d.png' % i)
		
		new_grid = blend_corners(grid, color_set, .3)
		grid_to_rgb_image(new_grid, 'blend_demo_files/corners_blend_%d.png' % i)		

make_perlin_ramp_images()
blend_mask_demo()
quilt_demo()
blend_demo4()
blend_corners_demo()