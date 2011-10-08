## @package quadtree_image
#
# Functions to manipulate images in Quadtrees.

from __future__ import division

from PIL import Image

from quadtree import *
from image import *

## Change a 2D grid into a 1D list.
def linearise(grid):
	lst = []
	for cell in grid:
		lst.append(cell)

	return lst

## Converts a 1D list into a 2D grid.
def gridify(lst, dims):
	grid = Grid2D(dims, None)

	for index, item in zip(grid.index_iter(), lst):
		grid[index] = item  

## Takes the pointwise maximum of two tuples. For example, 
# given the two tuples (100, 3, 50) and (20, 20, 20), the result is
# the tuple (100, 20, 50).
def max_tuple(tuple1, tuple2):
	lst = [] 

	for el1, el2 in zip(tuple1, tuple2):
		lst.append(max(el1, el2))

	return tuple(lst)

## Takes the point-wise maximum of a list of grids.  
def max_grid(grids):
	new_grid = Grid2D(grids[0].dims, None)

	for index in grids[0].index_iter():
		new_grid[index] = grids[0][index]

	for grid in grids[1:]:
		for index in grid.index_iter():
			#for i in range(3):
			new_grid[index] = max_tuple(new_grid[index], grid[index])

	return new_grid

## A Measure class that works on a single channel.
class ChannelMeasure(AbstractMeasure):
	def detail(self, grid, corner, dims, bias):    
		col0 = self.aproximate(grid, corner, dims)
		w, h = dims
		x, y = corner
		end_corner = (x + w, y + h)
		col = 0

		for cell in grid.window_iter(corner, end_corner):
			col1 = cell
			col += abs(col1 - col0)

		detail = (col) / (w * h)

		return detail

	def aproximate(self, grid, corner, dims):
		w, h = dims
		x, y = corner
		end_corner = (x + w, y + h)
		col = 0

		for cell in grid.window_iter(corner, end_corner):
			col0 = cell      
			col += col0

		area = w*h

		return col / area

	def blend(self, col1, col2, ratio):
		col = col1 * ratio + col2 * (1 - ratio)

		return col

	def blend3(self, col1, col2, col3, ratio1, ratio2, ratio3):
		col = col1 * ratio1 + col2 * ratio2 + col3 * ratio3
		
		return col

	##Returns a colour that is used to draw the edges of a quadtree.
	def outline_color(self):
		return 1


## A Measure class that works on a RGB image.  
class ImageMeasure(AbstractMeasure):
	def detail(self, grid, corner, dims, bias):   #bias between 0 and 1 
		red0, green0, blue0, alpha0 = self.aproximate(grid, corner, dims)
		w, h = dims
		#w, h = grid.dims
		x, y = corner
		end_corner = (x + w, y + h)
		red = 0
		blue = 0
		green = 0    

		for cell in grid.window_iter(corner, end_corner):
			red1, green1, blue1, alpha1 = cell
			red += abs(red1 - red0)
			green += abs(green1 - green0)
			blue += abs(blue1 - blue0)

		detail = (red + blue + green) / (3 * w * h)

		return detail

	def aproximate(self, grid, corner, dims):
		w, h = dims
		x, y = corner
		end_corner = (x + w, y + h)
		red = 0
		blue = 0
		green = 0
		alpha = 0

		for cell in grid.window_iter(corner, end_corner):
			red0, green0, blue0, alpha0 = cell

			red += red0
			green += green0
			blue += blue0   
			alpha += alpha0
		area = w*h

		return (red / area, green / area, blue / area, alpha / area)

	def blend(self, col1, col2, ratio):
		ratio_i = 1 - ratio

		red1, green1, blue1, alpha1 = col1
		red2, green2, blue2, alpha2 = col2

		red = red1 * ratio + red2 * ratio_i
		green = green1 * ratio + green2 * ratio_i
		blue = blue1 * ratio + blue2 * ratio_i
		alpha = alpha1 * ratio + alpha2 * ratio_i    

		return (red, green, blue, alpha)

	def blend3(self, col1, col2, col3, ratio1, ratio2, ratio3):
		red1, green1, blue1, alpha1 = col1
		red2, green2, blue2, alpha2 = col2
		red3, green3, blue3, alpha3 = col3

		red = red1 * ratio1 + red2 * ratio2 + red3 * ratio3
		green = green1 * ratio1 + green2 * ratio2 + green3 * ratio3
		blue = blue1 * ratio1 + blue2 * ratio2 + blue3 * ratio3
		alpha = alpha1 * ratio1 + alpha2 * ratio2 + alpha3 * ratio3

		return (red, green, blue, alpha)

	##Returns a colour that is used to draw the edges of a quadtree.
	def outline_color(self):
		return (1, 1, 1, 1)

## @private
# Renders a node into a grid
def render_node(grid, node, outline=False, interpolate=False):
	if node.value == None:
		for child in node.children:
			render_node(grid, child, outline, interpolate)
	else:
		for index in node.index_iter():
			if outline and (index[0] == node.x or index[1] == node.y):
				grid[index] = node.tree.measure.outline_color()
			else:
				if interpolate:
					grid[index] = node.interpolate3(index)
				else:
					grid[index] = node.tree[index]


## Renders a tree into a grid.
def render_outline(tree, factor, outline=False, interpolate=False):
	new_grid = Grid2D(tree.dims, (0, 0, 0, 1))

	render_node(new_grid, tree.root, outline, interpolate)
	return new_grid 