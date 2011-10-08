## @package random_distributions_demo
## Demonstrates to generation of numbers from an arbitrary distribution.
##

from __future__ import division

from random_distributions import *
from enhanced_grid import Grid2D
from random import random
from random_image import samples_to_image

## Demonstrates to generation of points from a 2D distribution.
def demo_distribution_1d():
	seed(0)	

	# Some arbitrary distribution curve
	inputSamples = [-20, -10, 0, 10, 20, 30, 40, 50, 60]
	outputSamples = [2, 10, 80, 75, 60, 30, 10, 5, 1]

	newInputMin = outputSamples[0]
	newInputMax = sum(outputSamples)

	newOutputMax = inputSamples[-1]
	newOutputMin = inputSamples[0]

	curve = make_distribution_curve(inputSamples, outputSamples)	

	for i in range(newSampleCount):
		input = (i / (newSampleCount - 1)) * (newInputMax - newInputMin) + newInputMin
		output = curve(input)
	
	#test the distribution
	testSampleCount = 100;
	count = [0] * testSampleCount

	# generate 10 000 random numbers, and check count occurrences in distribution bands.
	for i in range(10000):
		uniformRandVal = random() #random value between 0 and 1 

		#The random value that follows the desired distribution.
		curvedRandVal = curve(uniformRandVal)

		# Calculate the distribution band of the random value.
		countIndex = int((curvedRandVal - newOutputMin) / (newOutputMax - newOutputMin) * testSampleCount)

		# Used for debugging.
		#printf("%d %f %f %f %d\n", rr, r, newInput, dr, countIndex);

		if (countIndex < testSampleCount):
			count[countIndex] += 1
		else: # a rare occurence, but possible. Just bundle with the last distribution band.
			count[testSampleCount - 1] += 1

	# Print out, so that the values can be pasted into Excel or Calc.
	for i in range(testSampleCount):
		print '%d\t%d' % (i, count[i])

## Demonstrates to generation of points from a 2D distribution.
# An image is produced that shows an estimate of the distribution
# for a samnple of points generate from the specified distribution.
def demo_distribution_2d():	
#	grid = Grid2D((100, 100), 0)

#	for index in grid.index_iter():
#		x, y = index
#		grid[index] = (x + 1)*(y + 1)

	grid = Grid2D((4, 4))
	grid[..., ...] = [[1, 2, 4, 8],
				 [2, 3, 5, 11],
				 [4, 5, 7, 11],
				 [8, 11, 11, 11]]
	
	print grid
		
	probs = distribution_from_grid(grid, 4, 4)	
	
	print probs

	d = Distribution2D(probs, (0, 0), (500, 500))
	
	samples = []

	for k in range(10000):			
		samples.append(d(random(), random()))
		
	samples_to_image(samples, (200, 200), 'rand_dist.png')

#Run any of these to see how they work.	
#demo_distribution_1d()
demo_distribution_2d()