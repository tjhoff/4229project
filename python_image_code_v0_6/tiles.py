## @package tiles
## Provides funtions for quilting images together; to be used in seamless tile generation algorithms.
## Warning: still under construction; use at own peril.


from enhanced_grid import Grid2D
from image import rgb_image_to_grid
from image import grid_to_rgb_image
from image import normalize_grey
from image import greyscale_grid_to_rgb_grid
from image import transpose

from random import random
from random import randint

ENERGY_MAX = 10000
R_COMP_P = .3

def rg(a, b):
    if a > b:
        return True
    elif a < b:
        return False
    else:
        return random() < R_COMP_P
    
def rl(a, b):
    if a < b:
        return True
    elif a > b:
        return False
    else:
        return random() < R_COMP_P
    
def is_non_negative(lst):
    for item in lst:
        if item < 0:
            return False
    return True

###
def find_min_seam_debug(grid1, grid2):
    w, h = grid1.dims
    
    acc_energy = Grid2D((w, h))
    energy = Grid2D((w, h))
    
    seam = []
    
    # Calcaulte accumulative energy
    
    # First row
    # First cell
    acc_energy[0, 0] = ENERGY_MAX
    energy[0, 0] = ENERGY_MAX
    
    
    for i in range(1, w):
        acc_energy[i, 0] = energy2(grid1[i-1, 0], grid2[i, 0])
        energy[i, 0] = energy2(grid1[i-1, 0], grid2[i, 0])
        
    # Other rows
    
    for j in range (1, h):
        acc_energy[0, j] = ENERGY_MAX
        energy[0, j] = ENERGY_MAX
        
        for i in range(1, w - 1):
            if acc_energy[i + 1, j - 1] < acc_energy[i, j - 1] and acc_energy[i + 1, j - 1] < acc_energy[i - 1, j - 1]:
                e = energy3(grid2[i, j], grid1[i - 1, j], grid1[i, j - 1])
            else:
                e = energy3(grid2[i, j], grid1[i - 1, j], grid2[i, j - 1])
            acc_energy[i, j] = min(acc_energy[i - 1:i+2, j-1]) + e
            energy[i, j] = e
        
        #Last cell
        e = energy3(grid2[i, j], grid1[i - 1, j], grid2[i, j - 1])

        acc_energy[-1, j] = min(acc_energy[-2:, j-1]) + e
        energy[-1, j] = e
        
    last_seam = argmin(acc_energy[:, -1])
    seam.append(last_seam)
    
    for j in range(h - 2, -1, -1):
        if last_seam == 1:
            last_seam + argmin(acc_energy[last_seam: last_seam + 2, j])
        elif last_seam == w - 2:
            last_seam = last_seam - 1 + argmin(acc_energy[last_seam - 1: last_seam + 1, j])
        else:
            last_seam = last_seam - 1 + argmin(acc_energy[last_seam - 1: last_seam + 2, j])
        seam.append(last_seam)
        
    seam.reverse()
    
    return seam, energy
    
def quilt_debug(grid1, grid2, w):
    seam, energy = find_min_seam_debug(grid1[-w:, :], grid2[:w, :])    
        
    res = Grid2D((grid1.width + grid2.width - w, grid1.height))
    
    for i in range(res.width):
        for j in range(res.height):
            if i < grid1.width - w + seam[j]:
                res[i, j] = grid1[i, j]
            elif i == grid1.width - w + seam[j]:
                res[i, j] = (1, 0, 0, 1)
            else:
                res[i, j] = grid2[i - grid1.width + w , j]                
    return res, energy
###

def energy2_old(col1, col2):
    s1 = sum(col1)
    s2 = sum(col2)
    
    return abs(s1 - s2)

def energy3(col_centre, col_left, col_top):
    s_centre = sum(col_centre)
    s_top = sum(col_top)
    s_left = sum(col_left)
    
    return abs(s_centre - s_top) + abs(s_centre - s_left)

def energy2(col1, col2):    
    return abs(col1[0] - col2[0]) + abs(col1[1] - col2[1]) + abs(col1[2] - col2[2])

def energy3(col_centre, col_left, col_top):    
    return abs(col_centre[0] - col_top[0]) + abs(col_centre[0] - col_left[0]) + \
           abs(col_centre[1] - col_top[1]) + abs(col_centre[1] - col_left[1]) + \
           abs(col_centre[2] - col_top[2]) + abs(col_centre[2] - col_left[2])

def energy4(col_centre, col_left, col_top, col_top_left):    
    return abs(col_centre[0] - col_top[0]) + abs(col_centre[0] - col_left[0]) + abs(col_centre[0] - col_top_left[0]) + \
           abs(col_centre[1] - col_top[1]) + abs(col_centre[1] - col_left[1]) + abs(col_centre[1] - col_top_left[1]) + \
           abs(col_centre[2] - col_top[2]) + abs(col_centre[2] - col_left[2]) + abs(col_centre[2] - col_top_left[2]) 


def argmin(lst):
    min_item = lst[0]
    min_i = 0
    
    for i, item in enumerate(lst[1:]):
        if rl (item, min_item):
            min_item = item
            min_i = i + 1     
    return min_i            

## Calcaulte accumulative energy
def calc_acc_energy(grid1, grid2):  
    w, h = grid1.dims    
    acc_energy = Grid2D((w, h))
    
    # First row
    # First cell
    acc_energy[0, 0] = ENERGY_MAX
    
    for i in range(1, w):
        acc_energy[i, 0] = energy2(grid1[i-1, 0], grid2[i, 0])
        
    # Other rows
    
    for j in range (1, h):
        acc_energy[0, j] = ENERGY_MAX
        
        for i in range(1, w - 1):
            if acc_energy[i + 1, j - 1] < acc_energy[i, j - 1] and acc_energy[i + 1, j - 1] < acc_energy[i - 1, j - 1]:
                e = energy3(grid2[i, j], grid1[i - 1, j], grid1[i, j - 1])
            else:
                e = energy3(grid2[i, j], grid1[i - 1, j], grid2[i, j - 1])
            acc_energy[i, j] = min(acc_energy[i - 1:i+2, j-1]) + e
        
        #Last cell
        e = energy3(grid2[i, j], grid1[i - 1, j], grid2[i, j - 1])
        acc_energy[-1, j] = min(acc_energy[-2:, j-1]) + e
        
    return acc_energy

## Calcaulte accumulative energy
def calc_acc_energy2(grid1, grid2):  
    w, h = grid1.dims    
    acc_energy = Grid2D((w, h))
    
    # First row
    # First cell
    acc_energy[0, 0] = ENERGY_MAX
    
    for i in range(1, w):
        acc_energy[i, 0] = energy2(grid1[i, 0], grid2[i, 0])
        
    # Other rows
    
    for j in range (1, h):
        acc_energy[0, j] = ENERGY_MAX
        
        for i in range(1, w - 1):
            e = energy2(grid1[i, j], grid2[i, j])
            acc_energy[i, j] = min(acc_energy[i - 1:i+2, j-1]) + e
        
        #Last cell
        e = energy2(grid1[i, j], grid2[i, j])
        acc_energy[-1, j] = min(acc_energy[-2:, j-1]) + e
        
    return acc_energy

def find_min_seam(grid1, grid2):
    w, h = grid1.dims    
    acc_energy = calc_acc_energy2(grid1, grid2)    
    last_seam = argmin(acc_energy[:, -1])
    seam = []
    seam.append(last_seam)
    
    for j in range(h - 2, -1, -1):
        if last_seam == 1:
            last_seam + argmin(acc_energy[last_seam: last_seam + 2, j])
        elif last_seam == w - 2:
            last_seam = last_seam - 1 + argmin(acc_energy[last_seam - 1: last_seam + 1, j])
        else:
            last_seam = last_seam - 1 + argmin(acc_energy[last_seam - 1: last_seam + 2, j])
        seam.append(last_seam)
        
    seam.reverse()
    
    return seam
    
def quilt(grid1, grid2, w):
    seam = find_min_seam(grid1[grid1.width-w:, :], grid2[:w, :])    
    assert is_non_negative(seam)
        
    res = Grid2D((grid1.width + grid2.width - w, grid1.height))
    
    for i in range(res.width):
        for j in range(res.height):
            if i < grid1.width - w + seam[j]:
                res[i, j] = grid1[i, j]            
            else:
                res[i, j] = grid2[i - grid1.width + w , j]           
 #           if i == grid1.width - w + seam[j]:
 #               r, g, b, a = res[i, j]
 #               res[i, j] = (r, g, b, 0.5)
    return res

def quilt_multi_h(src, w, h, nx, qw):    
    x0 = randint(0, src.width - w - 1)
    y0 = randint(0, src.height - h - 1)
    grid = src[x0:x0 + w, y0:y0 + h]
    
    for i in range(nx):
        x0 = randint(0, src.width - w - 1)
        y0 = randint(0, src.height - h - 1)
        new_grid = src[x0:x0 + w, y0:y0 + h]
        grid = quilt(grid, new_grid, qw)
        
    return grid

def quilt_multi(src, w, h, nx, ny, qw, qh):
    grid = transpose(quilt_multi_h(src, w, h, nx, qw))
    
    for i in range(ny):
        new_grid = transpose(quilt_multi_h(src, w, h, nx, qw))
        grid = quilt(grid, new_grid, qh)
        
    return transpose(grid)


    
    