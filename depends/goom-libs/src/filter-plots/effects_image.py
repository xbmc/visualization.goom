import matplotlib.image as mpimg
import matplotlib.pyplot as pyplot
import numpy as np

import select_effects
from all_effects import CombinedEffects, Viewport


def get_effects_map(wid, hgt):
    z_min = -2.0
    z_max = +2.0
    z_len = z_max - z_min
    z = np.ndarray(wid * hgt, dtype=complex)

    i = 0
    for y in range(0, hgt):
        for x in range(0, wid):
            z[i] = complex(z_min + z_len * float(x) / (wid - 1),
                           z_min + z_len * float(y) / (hgt - 1))
            i += 1

    fz = combined_effects.f(z)
    # fz = np.log(fz0.real) + np.log(fz0.imag)

    # fz_max = min(50.0, max(z_len, np.max(np.absolute(fz.real)), np.max(np.absolute(fz.imag))))
    fz_max = z_len

    remap = dict()
    i = 0
    for y in range(0, hgt):
        for x in range(0, wid):
            ix = np.clip(int((1.0 / fz_max) * (fz[i].real - z_min) * (wid - 1)), 0, wid - 1)
            iy = np.clip(int((1.0 / fz_max) * (fz[i].imag - z_min) * (hgt - 1)), 0, hgt - 1)
            remap[(x, y)] = (ix, iy)
            i += 1

    return remap


def get_remap(wid, hgt):
    remap = dict()
    for y in range(0, hgt):
        for x in range(0, wid):
            remap[(x, y)] = (x, hgt - 1 - y)
    return remap


def get_remapped_image(img_remap, img, wid, hgt):
    remapped_img = np.ndarray(img.shape)

    for y in range(0, hgt):
        for x in range(0, wid):
            (ix, iy) = img_remap[(x, y)]
            remapped_img[y, x] = img[iy, ix]

    return remapped_img


def get_combined_effects() -> CombinedEffects:
    viewport = Viewport()
    # viewport = Viewport(-0, -0, 2.1, 2.1)

    filter_effect, after_effect = select_effects.get_effects()

    return CombinedEffects(viewport, filter_effect, after_effect)


if __name__ == "__main__":
    combined_effects = get_combined_effects()

    image = mpimg.imread(
#            '/home/greg/Prj/github/xbmc/visualization.goom/visualization.goom/resources/images/displacements/mountain_sunset.png')
            '/home/greg/Prj/github/xbmc/visualization.goom/depends/goom-libs/src/filter-plots/tile-pattern-512x512.png')
    height = image.shape[0]
    width = image.shape[1]
    depth = image.shape[2]
    print(f'width = {width}, height = {height}, depth = {depth}')
    print(f'image item size = {image.itemsize}')

    # image_remap = get_remap(width, height)
    image_remap = get_effects_map(width, height)

    remapped_image = get_remapped_image(image_remap, image, width, height)

    img_plot = pyplot.imshow(remapped_image)
    pyplot.show()
