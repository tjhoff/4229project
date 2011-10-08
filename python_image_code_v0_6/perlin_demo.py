## @package perlin_demo 
# Illustrates some functions in the perlin_noise module.

from __future__ import division
from __future__ import with_statement

from PIL import Image

from perlin_noise import *
from gradient import *
from image import *

def demo_2d():
	w = h = 512
	octaves = 9
	persistence = 0.5

	print 'Making smooth noise...'
	s_noise = SmoothNoise(w, h)

	#~ for k in range(octaves):
		#~ print k

		#~ grid = s_noise.generate(k)

		#~ with open('smooth_noise' + str(k) + '.dat', 'w') as f:
			#~ f.write('%s\n' % w)
			#~ f.write('%s\n' % h)
			#~ f.write('g\n') #greyscale

			#~ for cell in grid.cell_iter():
				#~ f.write('%s\n' % cell)

	print 'Making Perlin noise...'
	p_noise = perlin_noise_from_smoothnoise(w, h, octaves, persistence, s_noise, True)

	gradient = SimpleGradient((1, 0, 0, 1), (1, 1, 1, 1))
	color_grid = map_gradient(gradient, p_noise)
	grid_to_rgb_image(color_grid, 'p_test_02.png')

	print 'Done.'

def offsetPixels(grid2d, pixelOffset):
	gt = grid2d[pixelOffset:,:].clone()
	gb = grid2d[:pixelOffset,:].clone()

	grid2d[:-pixelOffset,:] = gt
	grid2d[-pixelOffset:,:] = gb

def demo_3d():
	w = h = d = 128
	print 'Making 3D Perlin noise... This might take several minutes!'
	p = perlin_noise_3d(w, h, d, 7, 0.5, 1)

	for pi in p:
		for k in range(d):
			ns = '%03d' % k

			print 'Writing image to disk:', k

			offsetPixels(pi[:,:,k], k)

			with open('p_o/p_o_' + ns + '.dat', 'w') as f:
				f.write('%s\n' % w)
				f.write('%s\n' % h)
				f.write('g\n') #greyscale

				for i in range(w):
					for j in range(h): 				
						f.write('%s\n' % pi[i, j, k])

## Takes a long time to execute.
# Produces the images for demo_stitch.
def demo_channels():
	w = h = 128
	octaves = 8
	persistence = 0.5

	for k in range(126):	
		p_noise = [None] * 3

		for i in range(3):
			print 'Making smooth noise...'
			s_noise = SmoothNoise(w, h)
			print 'Making Perlin noise...'
			p_noise[i] = perlin_noise_from_smoothnoise(w, h, octaves, persistence, s_noise, True)

		grid = channels_to_rgb_grid(p_noise)
		grid = normalize(grid)

		grid_to_rgb_image(grid, 'perlin_noise/perlin_lin_channels_' + str(k) + '.png')



#demo_2d()
#demo_3d() #Really slow! Takes +/- 30 minutes to run
demo_channels()

