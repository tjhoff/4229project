## @package perlin_images_demo
# Illustrates some perlin_noise features.

from __future__ import with_statement

from perlin_noise import perlin_noise
from perlin_noise import SmoothNoise
from perlin_noise import perlin_noise_from_smoothnoise

w = h = 512
octaves = 9
persistence = 0.5

def make_smooth_noise_images():
  print 'Making smooth noise...'
  s_noise = SmoothNoise(w, h)

  for k in range(octaves):
    print k
    
    grid = s_noise.generate(k)
    
    with open('article_images/smooth_noise' + str(k) + '.dat', 'w') as f:
      f.write('%s\n' % w)
      f.write('%s\n' % h)
      f.write('g\n') #greyscale
      
      for cell in grid.cell_iter():
        f.write('%s\n' % cell)
  
  print 'Making Perlin noise...'
  p_noise = perlin_noise_from_smoothnoise(w, h, octaves, persistence, s_noise, True)
  
  with open('article_images/perlin_noise' + '.dat', 'w') as f:
    f.write('%s\n' % w)
    f.write('%s\n' % h)
    f.write('g\n') #greyscale
    
    for cell in p_noise.cell_iter():
      f.write('%s\n' % cell)
  
  print 'Done.'


def main():
  make_smooth_noise_images()
  
main()