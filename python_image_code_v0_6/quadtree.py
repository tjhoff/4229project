## @package quadtree
## @brief A general purpose (compression) Quadtree class.
## See: 
##  - http://code-spot.co.za/2008/10/06/quadtrees/
##  - http://code-spot.co.za/2008/11/15/quadtrees/

from __future__ import division

from math import sqrt

from enhanced_grid import Container2D


## Constant for the index of the top left quadrant of a quadtree in a children list. 
TOP_LEFT = 0
## Constant for the index of the top right quadrant of a quadtree in a children list. 
TOP_RIGHT = 1

## Constant for the index of the bottom  left quadrant of a quadtree in a children list. 
BOTTOM_LEFT = 2

## Constant for the index of the bottom right quadrant of a quadtree in a children list. 
BOTTOM_RIGHT = 3

## Constant that denotes the root node. 
ROOT = 4

## A general purpose (compression) Quadtree class.
class Quadtree(Container2D):

	## Represents a node of this Quadtree
	class Node:
		## Constructs a new node.
		#
		# @param tree
		#           The quad tree containing this node
		# @param grid
		#           The raw data in an enhanced_grid
		# @param corner
		#           An x,y tuplet denoting the top-left corner of the region that this 
		#           node represents.
		# @param dims
		#           An x, y, tuplet denoting the dimensions of the region that this 
		#           node represents.  
		def __init__(self, tree, grid, corner, dims, parent, corner_index):
			self.tree = tree
			self.corner = corner
			self.dims = dims
			self.parent = parent
			self.corner_index = corner_index      
			self.x, self.y = corner
			self.width, self.height = dims

			self.hw = self.width // 2
			self.hh = self.height // 2

			if tree.measure.detail(grid, corner, dims, self.width*self.height/(grid.dims[0]*grid.dims[1])) < tree.threshold:
				self.value = tree.measure.aproximate(grid, corner, dims)        
				self.children = None
			else:
				self.value = None

				self.children = (
					tree.Node(self.tree, grid, corner, (self.hw, self.hh), self, TOP_LEFT),
					tree.Node(self.tree, grid, (self.x + self.hw, self.y), (self.width - self.hw, self.hh), self, TOP_RIGHT),
					tree.Node(self.tree, grid, (self.x, self.y + self.hh), (self.hw, self.height - self.hh), self, BOTTOM_LEFT),
					tree.Node(self.tree, grid, (self.x + self.hw, self.y + self.hh), (self.width - self.hw, self.height - self.hh), self, BOTTOM_RIGHT))

		## Allows access to a node's pixel data with the notation node[x, y].
		# @param p A tuplet (x, y) contaning coordinates.
		def __getitem__(self, p):
			return self.get_node(p).value		

		## Gets the node that holds the data for the specified point
		# @param p A tuplet (x, y) contaning coordinates.
		#
		def get_node(self, p):
			if self.value == None:
				i, j = p

				if i < self.x + self.hw:
					if j < self.y + self.hh:
						return self.children[TOP_LEFT].get_node(p)
					else:
						return self.children[BOTTOM_LEFT].get_node(p)
				else:
					if j < self.y + self.hh:
						return self.children[TOP_RIGHT].get_node(p)
					else:
						return self.children[BOTTOM_RIGHT].get_node(p)
			else:
				return self

		## @private
		def is_root(self):
			return self.corner_index == ROOT
		
		##@{
		##These functions are used to find neighnoring nodes. It 
		##is not a very good way to do it - for instance, a better way to find 
		##the left node neighbor is
		## @code
		##
		## node[self.x - 1, y]
		##
		## @endcode
		## @todo Implement the simpler version.
		
		## @private
		def is_left_node(self):
			return self.corner_index == TOP_LEFT or self.corner_index == BOTTOM_LEFT
		
		## @private
		def is_right_node(self):
			return self.corner_index == TOP_RIGHT or self.corner_index == BOTTOM_RIGHT

		## @private
		def is_top_node(self):
			return self.corner_index == TOP_LEFT or self.corner_index == TOP_RIGHT
		
		## @private
		def is_bottom_node(self):
			return self.corner_index == BOTTOM_LEFT or self.corner_index == BOTTOM_RIGHT

		## @private
		def get_left_parent(self):
			if self.is_root():
				return None
			if self.is_left_node():
				return self.parent.get_left_parent()
			elif self.corner_index == TOP_RIGHT:
				return self.parent.children[TOP_LEFT]
			else: #self.corner_index == BOTTOM_RIGHT:
				return self.parent.children[BOTTOM_LEFT]

		## @private
		def get_rightmost_node(self, y):
			if self.value == None:
				if y < self.y + self.hh:
					return self.children[TOP_RIGHT].get_rightmost_node(y)
				else:
					return self.children[BOTTOM_RIGHT].get_rightmost_node(y)
			else:
				return self

		## @private
		def get_left_neighbor(self, p):
			node = self.get_left_parent()

			if node == None:
				return None
			else:
				return node.get_rightmost_node(p[1])			

		## @private
		def get_right_parent(self):
			if self.is_root():
				return None
			if self.is_right_node():
				return self.parent.get_right_parent()
			elif self.corner_index == TOP_LEFT:
				return self.parent.children[TOP_RIGHT]
			else: #self.corner_index == BOTTOM_LEFT:
				return self.parent.children[BOTTOM_RIGHT]

		## @private
		def get_leftmost_node(self, y):
			if self.value == None:
				if y < self.y + self.hh:
					return self.children[TOP_LEFT].get_leftmost_node(y)
				else:
					return self.children[BOTTOM_LEFT].get_leftmost_node(y)
			else:
				return self

		## @private
		def get_right_neighbor(self, p):
			node = self.get_right_parent()

			if node == None:
				return None
			else:
				return node.get_leftmost_node(p[1])

			
		## @private
		def get_top_parent(self):
			if self.is_root():
				return None
			if self.is_top_node():
				return self.parent.get_top_parent()
			elif self.corner_index == BOTTOM_LEFT:
				return self.parent.children[TOP_LEFT]
			else: #self.corner_index == BOTTOM_RIGHT:
				return self.parent.children[TOP_RIGHT]

		## @private
		def get_bottommost_node(self, x):
			if self.value == None:
				if x < self.x + self.hw:
					return self.children[BOTTOM_LEFT].get_bottommost_node(x)
				else:
					return self.children[BOTTOM_RIGHT].get_bottommost_node(x)
			else:
				return self

		## @private
		def get_top_neighbor(self, p):
			node = self.get_top_parent()

			if node == None:
				return None
			else:
				return node.get_bottommost_node(p[0])

		## @private
		def get_bottom_parent(self):
			if self.is_root():
				return None
			if self.is_bottom_node():
				return self.parent.get_bottom_parent()
			elif self.corner_index == TOP_LEFT:
				return self.parent.children[BOTTOM_LEFT]
			else: #self.corner_index == TOP_RIGHT:
				return self.parent.children[BOTTOM_RIGHT]

		## @private
		def get_topmost_node(self, x):
			if self.value == None:
				if x < self.x + self.hw:
					return self.children[TOP_LEFT].get_topmost_node(x)
				else:
					return self.children[TOP_RIGHT].get_topmost_node(x)
			else:
				return self

		## @private
		def get_bottom_neighbor(self, p):
			node = self.get_bottom_parent()

			if node == None:
				return None
			else:
				return node.get_topmost_node(p[0])
			
		##@}
			
		## Similar to __getitem__ but returns an 
		# interpolated value instead. The Measure 
		# used for this Quadtree must implement the 
		# blend method for this method to work.
		def interpolate(self, p):
			node = self.get_node(p)
			#return node.value
			left_node = self.get_left_neighbor(p)
			top_node = self.get_top_neighbor(p)

			right_node = self.get_right_neighbor(p)
			bottom_node = self.get_bottom_neighbor(p)

			if node.width == 1:
				return node.value

			if left_node == None:
				col1 = node.value
			else:
				ratio1 = (p[0] - left_node.x - left_node.width) / (node.width - 1)      
				col1 = self.tree.measure.blend(node.value, left_node.value, ratio1)

			if top_node == None:
				col2 = node.value        
			else:
				ratio2 = (p[1] - top_node.y - top_node.height) / (node.height - 1)        
				col2 = self.tree.measure.blend(node.value, top_node.value, ratio2)

			if right_node == None:
				col3 = node.value
			else:
				ratio3 = (right_node.x - p[0]) / node.width
				col3 = self.tree.measure.blend(node.value, right_node.value, ratio3)

			if bottom_node == None:
				col4 = node.value
			else:
				ratio4 = (bottom_node.y - p[1]) / node.height
				col4 = self.tree.measure.blend(node.value, bottom_node.value, ratio4)

			col_a = self.tree.measure.blend(col1, col2, 0.5)
			col_b = self.tree.measure.blend(col3, col4, 0.5)

			return self.tree.measure.blend(col_a, col_b, 0.5)

		## Similar to __getitem__ but returns an 
		# interpolated value instead. The Measure 
		# used for this Quadtree must implement the 
		# blend method for this method to work.
		# This interpolation is better than that provided by interpolate.
		def interpolate2(self, p):
			x, y = p
			node = self.get_node(p)
			left_node = self.get_left_neighbor(p)
			top_node = self.get_top_neighbor(p)

			right_node = self.get_right_neighbor(p)
			bottom_node = self.get_bottom_neighbor(p)

			if None in (left_node, right_node, top_node, bottom_node):
				return node.value      

			top_y = top_node.y + top_node.height
			left_x = left_node.x + left_node.width

			x1, y1 = (left_x + x) / 2, (y + top_y) / 2
			x2, y2 = (x + right_node.x) / 2, (top_y + y) / 2
			x3, y3 = (right_node.x + x) / 2, (y + bottom_node.y) / 2
			x4, y4 = (x + left_x) / 2, (y + bottom_node.y) / 2

			dx1, dy1 = x1 - x, y1 - y
			dx2, dy2 = x2 - x, y2 - y
			dx3, dy3 = x3 - x, y3 - y
			dx4, dy4 = x4 - x, y4 - y

			d1 = sqrt(dx1 * dx1 + dy1 * dy1)
			d2 = sqrt(dx2 * dx2 + dy2 * dy2)
			d3 = sqrt(dx3 * dx3 + dy3 * dy3)
			d4 = sqrt(dx4 * dx4 + dy4 * dy4)

			a1 = d1 / (d1 + d3)
			a2 = d2 / (d2 + d3)

			col1 = self.tree.measure.blend(right_node.value, top_node.value, 1-a1)
			col2 = self.tree.measure.blend(bottom_node.value, left_node.value, 1-a1)

			return self.tree.measure.blend(col2, col1, 1-a2)

		## Similar to __getitem__ but returns an 
		# interpolated value instead. The Measure 
		# used for this Quadtree must implement the 
		# blend3 method for this method to work.
		# This interpolation is better than that provided by interpolate2.
		def interpolate3(self, p):
			x, y = p
			node = self.get_node(p)

			x1, y1 = node.x + node.hw, node.y + node.hh

			col1 = node.value
			col2 = node.value
			col3 = node.value

			x2, y2 = x, y
			x3, y3 = x, y

			#test in which quadrant the point is

			if x < x1:
				left_node = self.get_left_neighbor(p)

				if left_node != None:
					x3, y3 = left_node.x + left_node.width, y
					col3 = left_node.value
				else:
					x3, y3 = node.x, y

				if y < y1: #top left
					top_node = self.get_top_neighbor(p)

					if top_node != None:          
						x2, y2 = x, top_node.y + top_node.height
						col2 = top_node.value
					else:
						x2, y2 = x, node.y

				else: #bottom left
					bottom_node = self.get_bottom_neighbor(p)

					if bottom_node != None:
						x2, y2 = x, bottom_node.y
						col2 = bottom_node.value
					else:
						x2, y2 = x, node.y + node.height

			else:
				right_node = self.get_right_neighbor(p)

				if right_node != None:
					x3, y3 = right_node.x, y
					col3 = right_node.value
				else:
					x3, y3 = node.x + node.width, y

				if y < y1: #top right
					top_node = self.get_top_neighbor(p)

					if top_node != None:          
						x2, y2 = x, top_node.y + top_node.height
						col2 = top_node.value
					else:
						x2, y2 = x, node.y

				else: #bottom right
					bottom_node = self.get_bottom_neighbor(p)

					if bottom_node != None:
						x2, y2 = x, bottom_node.y
						col2 = bottom_node.value
					else:
						x2, y2 = x, node.y + node.height

			col2 = self.tree.measure.blend(col2, col1, 0.5)
			col3 = self.tree.measure.blend(col3, col1, 0.5)

			dx1, dy1 = x1 - x, y1 - y
			dx2, dy2 = x2 - x, y2 - y
			dx3, dy3 = x3 - x, y3 - y

			d1 = sqrt(dx1 * dx1 + dy1 * dy1)
			d2 = sqrt(dx2 * dx2 + dy2 * dy2)
			d3 = sqrt(dx3 * dx3 + dy3 * dy3)

			s = (d1 + d2 + d3)
			col0 = (0, 255, 255, 255)
			if s == 0:
				return col0

			ratio1 = 1-(2*(d1) / s)
			ratio2 = 1-(2*(d2) / s)
			ratio3 = 1-(2*(d3) / s)
			col4 = (255, 0, 0, 255)
			col5 = (0, 255, 0, 255)
			col6 = (0, 0, 255, 255)

			return self.tree.measure.blend3(col1, col2, col3, ratio1, ratio2, ratio3)      

		## Returns an iterator of indexes over the region that this node represents.
		def index_iter(self):
			return self.tree.window_index_iter((self.corner), (self.x+self.width, self.y+self.height))

		## Counts the nodes from this node downwards. 
		# If count_self is False, only 
		# leaf nodes are counted.
		# If count_self is True, all children nodes including this node will 
		# be counted. Otherwise, only leaf nodes are counted.
		def count(self, count_self = True):
			if(self.value == None):
				count = 1 if count_self else 0

				for child in self.children:
					count += child.count(count_self)

				return count
			return 1

	## Constructs a new Quadtree from a grid.
	#
	# Measure is a class that implements two methods, as in the example below.
	# Threshold is a value between 0 and 1; a node is not split when the detail of 
	# that tree section is less than the threshold.
	def __init__(self, grid, measure, threshold):    
		self.measure = measure
		self.threshold = threshold
		self.root = Quadtree.Node(self, grid, (0, 0), grid.dims, None, ROOT)
		self.dims = grid.dims
		self.width, self.height = self.dims		
		
	## Alows access to the tree's pixel data using the notation tree[x, y].
	def __getitem__(self, p):
		return self.root[p[0], p[1]]

	## Count the nodes in this tree. If count_self is False, only leaf nodes are 
	#counted.
	def count(self, count_self):
		return self.root.count(count_self)

## This class shows which methods a Measure class must implement
# if it is to be used for a Quadtree
class AbstractMeasure:
	## Measures the detail of the region of the 
	# grid between the points corner and corner+dims.
	# Returns a value between 0 and 1. (0 is no detail, 1 is full detail).
	# The bias can be ignored - it is the ratio of cells to the entire grid 
	# represented by the piece of node. 
	# @todo Remove bias: can be calculated from grid.dims and dims!
	def detail(self, grid, corner, dims, bias):
		raise NotImplementedError()

	## Aproximates the region of the grid between corner and corner+dims.
	# The return type must be the same as the data content type of the tree's node
	# in which this AbstractMeasure is used.
	def aproximate(self, grid, corner, dims):
		raise NotImplementedError()

	## Blends two node values.
	# Ratio is a value between 0 and 1. If it is 0, 
	# the second value is returned. If it is 1, the first value is returned.
	def blend(self, col1, col2, ratio):
		raise NotImplementedError()
	
	## Blends three node values.
	# The three ratios must add up to 1. If the three ratios are 0 1 0, the 
	# result is the same as the second value.
	def blend3(self, col1, col2, col3, ratio1, ratio2, ratio3):
		raise NotImplementedError()


###
# DEMO

##This is an example Measure object, as is required by a Quadtree.
class Measure(AbstractMeasure):

	## Calculates the average absolute difference from the average of a region.
	# @todo remove bias - see AbstractMeasure
	def detail(self, grid, corner, dims, bias):
		average = self.aproximate(grid, corner, dims)

		w, h = dims
		x, y = corner
		end_corner = (x + w, y + h)
		sum = 0

		for cell in grid.window_iter(corner, end_corner):
			sum += abs(average - cell)

		return sum / (w * h)

	## Calculates the average pixel value over a region.
	def aproximate(self, grid, corner, dims):
		w, h = dims
		x, y = corner
		end_corner = (x + w, y + h)
		sum = 0

		for cell in grid.window_iter(corner, end_corner):
			sum += cell

		return sum / (w*h)   
	
	## Blends two node values.
	def blend(self, col1, col2, ratio):
		col = col1 * ratio + col2 * (1 - ratio)

		return col

	## Blends three node values.
	def blend3(self, col1, col2, col3, ratio1, ratio2, ratio3):
		col = col1 * ratio1 + col2 * ratio2 + col3 * ratio3