"""
Generate color map images and fill in the docs to point to them.

"""
from __future__ import print_function

import os
from importlib import import_module

from palettable.palette import Palette

PALETTABLE_MODULES = {
    'palettable.colorbrewer.diverging': './colorbrewer/diverging',
    'palettable.colorbrewer.qualitative': './colorbrewer/qualitative',
    'palettable.colorbrewer.sequential': './colorbrewer/sequential',
    'palettable.tableau': './tableau',
    'palettable.wesanderson': './wesanderson',
    'palettable.cubehelix': './cubehelix',
    'palettable.matplotlib': './matplotlib',
    'palettable.mycarta': './mycarta',
    'palettable.cmocean.diverging': './cmocean/diverging',
    'palettable.cmocean.sequential': './cmocean/sequential',
    'palettable.cartocolors.diverging': './cartocolors/diverging',
    'palettable.cartocolors.qualitative': './cartocolors/qualitative',
    'palettable.cartocolors.sequential': './cartocolors/sequential',
    'palettable.lightbartlein.diverging': './lightbartlein/diverging',
    'palettable.lightbartlein.sequential': './lightbartlein/sequential',
    'palettable.scientific.diverging': './scientific/diverging',
    'palettable.scientific.sequential': './scientific/sequential',
}


def find_palettes(mod):
    return {
        k: v for k, v in vars(mod).items()
        if isinstance(v, Palette) and not k.endswith('_r')}


if __name__ == '__main__':
    for mod, mod_dir in PALETTABLE_MODULES.items():
        print(f'Running module "{mod}"...')
        palettes = find_palettes(import_module(mod))
        for name, p in palettes.items():
            print(f'Getting cmap for for palette "{name}"...')
            print(f'cmap = {p.mpl_colormap.name}, type = {p.type}, N = {p.number}')
