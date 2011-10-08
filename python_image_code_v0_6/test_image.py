## @package test_image
## Unit tests for image (under constrcution).

from unittest import TestCase
from unittest import TestSuite

from image import mix_color

class MixColorTestCase (TestCase):
    def setUp(self):
        self.yellow = (1, 1, 0, 1)
        self.blue = (0, 0, 1, 1)
        
    def test_mix_color_left(self):
        r, g, b, a = mix_color(self.yellow, self.blue, 0)
        
        self.assertAlmostEqual(r, 1)
        self.assertAlmostEqual(g, 1)
        self.assertAlmostEqual(b, 0)
        self.assertAlmostEqual(a, 1)
        
    def test_mix_color_right(self):   
        r, g, b, a = mix_color(self.yellow, self.blue, 1)
        self.assertAlmostEqual(r, 0)
        self.assertAlmostEqual(g, 0)
        self.assertAlmostEqual(b, 1)
        self.assertAlmostEqual(a, 1)
        
    def test_mix_color_mid(self):
        r, g, b, a = mix_color(self.yellow, self.blue, .5)
        self.assertAlmostEqual(r, .5)
        self.assertAlmostEqual(g, .5)
        self.assertAlmostEqual(b, .5)
        self.assertAlmostEqual(a, 1)
        
