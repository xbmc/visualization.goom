from matplotlib import pyplot
from matplotlib.colors import Colormap, LinearSegmentedColormap
from colormap import colors
from numpy.core import ushort
import copy
import os
from importlib import import_module
from typing import Dict, List, Tuple

from palettable.palette import Palette

COLOR_DATA_DIRNAME = 'color_data'
INCLUDE_RELDIR = f'goomutils/include/goomutils/{COLOR_DATA_DIRNAME}'
SRCE_RELDIR = 'goomutils/src'
CPP_LIBNAME = 'goomutils'
FINAL_INCLUDE_RELDIR = f'{COLOR_DATA_DIRNAME}'
INCLUDE_DIR = '/tmp/' + INCLUDE_RELDIR
SRCE_DIR = '/tmp/' + SRCE_RELDIR

COLOR_MAP_ENUM_H = 'colormap_enums.h'
ALL_MAPS_H = 'color_data_maps.h'
ALL_MAPS_CPP = 'color_data_maps.cpp'
GOOM_NAMESPACE = 'GOOM'
GOOMUTILS_NAMESPACE = 'UTILS'
COLORDATA_NAMESPACE = 'COLOR_DATA'
MAPS_ENUM_NAME = 'ColorMapName'

# TODO FIX THIS
PALETTABLE_DIR = '~/Prj/github/palettable'

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

DIVERGING_BLACK = [
        'pink_black_green(w3c)',
        'red_black_blue',
        'red_black_green',
        'red_black_orange',
        'red_black_sky',
        'yellow_black_blue',
        'yellow_black_sky',
]


def is_number(s: str) -> Tuple[bool, int]:
    try:
        the_num = int(s)
        return True, the_num
    except ValueError:
        return False, 0


def get_first_and_last(name: str) -> Tuple[str, str]:
    parts = name.rsplit('_', 1)
    first = parts[0]
    last = '' if len(parts) <= 1 else parts[1]
    return first, last


def cmap_name_key(name: str) -> str:
    nm = name.lower()
    first, last = get_first_and_last(nm)
    if last == '':
        return nm

    is_num, the_num = is_number(last)
    if not is_num:
        return nm

    return first + '_' + f'{the_num:02}'


def find_palettes(mod):
    return {
            k: v for k, v in vars(mod).items()
            if isinstance(v, Palette) and not k.endswith('_r')}


def get_cpp_name(nm: str) -> str:
    cpp_nm = nm.replace('(', '_')
    cpp_nm = cpp_nm.replace(')', '_')
    return cpp_nm


def get_enum_line_end(name: str, dupl: Dict[str, str]):
    if name not in dupl:
        return '\n'
    return f' // = {dupl[name]}\n'


palettable_maps = {}


def inject_palettable_cmaps():
    for mod, mod_dir in PALETTABLE_MODULES.items():
        palettes = find_palettes(import_module(mod))
        for name, p in palettes.items():
            palettable_maps[name] = p


def get_cmap(name: str) -> Colormap:
    if name in DIVERGING_BLACK:
        c1, c2, c3 = name.split("_")
        # special case of sky, which does not exist
        c3 = c3.replace("sky", "deep sky blue")
        cmap = colors.Colormap().cmap_linear(c1, c2, c3)
    else:
        try:
            cmap = pyplot.get_cmap(name)
        except:
            cmap = None

    if cmap is None:
        palette = palettable_maps[get_cpp_name(name)]
        cmap = LinearSegmentedColormap.from_list(palette.name,
                                                 palette.mpl_colors, N=palette.number)

    cmap.name = name
    return cmap


def get_map_types(all_mps: List[str]) -> Tuple[List[str], Dict[str, str], Dict[str, int]]:
    maps = sorted(list(set(all_mps)), key=cmap_name_key)

    used = []
    dupl = {}
    numbered = {}
    for m in maps:
        if m.endswith('_r'):
            continue

        try:
            cmap = get_cmap(m)
        except Exception as e:
            raise Exception('Invalid color map name: "{}" - exception: "{}"'.format(m, e))

        already_in, first_name, last, num = already_added(used, cmap)
        if not already_in:
            used.append(m)
        else:
            print(f'Already added cmap "{m}" - first use = "{first_name}".')
            dupl[first_name] = m

        if num >= 0:
            # Because maps is sorted, we'll pick up the maximum num by the end.
            numbered[first_name] = num

    return used, dupl, numbered


def already_added(used: List[str], cmap: Colormap) -> Tuple[bool, str, str, int]:
    first, last = get_first_and_last(cmap.name)
    if first not in used:
        return False, first, last, -1

    is_num, the_num = is_number(last)
    if not is_num:
        return False, first, last, -1

    root_cmap = get_cmap(first)
    if root_cmap.N != cmap.N:
        return False, first, last, the_num

    return True, first, last, the_num


def write_cpp_headers(used_mps: List[str]):
    for m in used_mps:
        write_cpp_header(get_cmap(m))


def write_namespace_begin(f):
    f.write('#if __cplusplus > 201402L\n')
    f.write(f'namespace {GOOM_NAMESPACE}::{GOOMUTILS_NAMESPACE}::{COLORDATA_NAMESPACE}\n')
    f.write('{\n')
    f.write('#else\n')
    f.write(f'namespace {GOOM_NAMESPACE}\n')
    f.write('{\n')
    f.write(f'namespace {GOOMUTILS_NAMESPACE}\n')
    f.write('{\n')
    f.write(f'namespace {COLORDATA_NAMESPACE}\n')
    f.write('{\n')
    f.write('#endif\n')


def write_namespace_end(f):
    f.write('#if __cplusplus > 201402L\n')
    f.write(f'}} // namespace {GOOM_NAMESPACE}::{GOOMUTILS_NAMESPACE}::{COLORDATA_NAMESPACE}\n')
    f.write('#else\n')
    f.write(f'}} // namespace {COLORDATA_NAMESPACE}\n')
    f.write(f'}} // namespace {GOOMUTILS_NAMESPACE}\n')
    f.write(f'}} // namespace {GOOM_NAMESPACE}\n')
    f.write('#endif\n')


def write_cpp_header(cm: Colormap):
    with open(f'{INCLUDE_DIR}/{get_cpp_name(cm.name)}.h', 'w') as f:
        f.write('#pragma once\n')
        f.write('\n')
        f.write('#include "vivid/types.h"\n')
        f.write('#include <vector>\n')
        f.write('\n')
        write_namespace_begin(f)
        f.write('\n')
        f.write('// clang-format off\n')
        f.write(f'static const std::vector<vivid::srgb_t> {get_cpp_name(cm.name)}\n')
        f.write('{\n')
        for i in range(cm.N):
            vals = cm(i)
            f.write(f'  {{ {vals[0]:9.5f}f, {vals[1]:9.5f}f, {vals[2]:9.5f}f }},\n')
        f.write('};\n')
        f.write('// clang-format on\n')
        f.write('\n')
        write_namespace_end(f)


def write_colormaps_enums_header(maps: List[str], dupl: Dict[str, str]):
    with open(f'{INCLUDE_DIR}/{COLOR_MAP_ENUM_H}', 'w') as f:
        f.write('#pragma once\n')
        f.write('\n')
        write_namespace_begin(f)
        f.write('\n')
        f.write(f'enum class {MAPS_ENUM_NAME}\n')
        f.write('{\n')
        f.write(f'  _NULL = -1,\n')
        for m in maps:
            f.write(f'  {get_cpp_name(m)},' + get_enum_line_end(m, dupl))
        f.write(f'  _NUM,\n')
        f.write(f'}};\n')
        f.write('\n')
        write_namespace_end(f)


def write_all_maps_header(color_map_grps: Dict[str, List[str]], num_maps: int):
    with open(f'{INCLUDE_DIR}/{ALL_MAPS_H}', 'w') as f:
        f.write('#pragma once\n')
        f.write('\n')
        f.write(f'#include "{FINAL_INCLUDE_RELDIR}/{COLOR_MAP_ENUM_H}"\n')
        f.write('#include "vivid/types.h"\n')
        f.write('\n')
        f.write('#include <array>\n')
        f.write('#include <string>\n')
        f.write('#include <utility>\n')
        f.write('#include <vector>\n')
        f.write('\n')
        write_namespace_begin(f)
        f.write('\n')
        f.write(f'// array of raw maps matching elements of enum \'{MAPS_ENUM_NAME}\'\n')
        f.write(
                f'extern const std::array<std::pair<{MAPS_ENUM_NAME}, std::vector<vivid::srgb_t>>, {num_maps}> allMaps;\n')
        f.write('\n')
        for grp in color_map_grps:
            f.write(f'extern const std::vector<{MAPS_ENUM_NAME}> {grp}Maps;\n')
        f.write('\n')
        write_namespace_end(f)


def write_all_maps_cpp(color_map_grps: Dict[str, List[str]], used_mps: List[str], dupl: Dict[str, str]):
    with open(f'{SRCE_DIR}/{ALL_MAPS_CPP}', 'w') as f:
        f.write(f'#include "{FINAL_INCLUDE_RELDIR}/{ALL_MAPS_H}"\n')
        f.write('\n')
        f.write('// clang-format off\n')
        for m in used_mps:
            f.write(f'#include "{FINAL_INCLUDE_RELDIR}/{get_cpp_name(m)}.h"' + get_enum_line_end(m, dupl))
        f.write('// clang-format on\n')
        f.write('\n')
        f.write(f'#include "{FINAL_INCLUDE_RELDIR}/{COLOR_MAP_ENUM_H}"\n')
        f.write('#include "vivid/types.h"\n')
        f.write('\n')
        f.write('#include <array>\n')
        f.write('#include <utility>\n')
        f.write('#include <vector>\n')
        f.write('\n')
        write_namespace_begin(f)
        f.write('\n')
        f.write('// clang-format off\n')
        f.write(
                f'const std::array<std::pair<{MAPS_ENUM_NAME}, std::vector<vivid::srgb_t>>, {len(used_mps)}> allMaps\n')
        f.write('{\n')
        for m in used_mps:
            f.write(
                    f'  std::make_pair({MAPS_ENUM_NAME}::{get_cpp_name(m)}, {COLORDATA_NAMESPACE}::{get_cpp_name(m)}),'
                    + get_enum_line_end(m, dupl))
        f.write(f'}};\n')
        f.write('\n')

        # Do the groups
        not_done_maps = copy.deepcopy(used_mps)
        for map_nm in color_map_grps:
            f.write(f'const std::vector<{MAPS_ENUM_NAME}> {get_cpp_name(map_nm)}Maps\n')
            f.write('{\n')
            for m in color_map_grps[map_nm]:
                if m not in used_mps:
                    continue
                f.write(f'    {MAPS_ENUM_NAME}::{get_cpp_name(m)},' + get_enum_line_end(m, dupl))
                if m in not_done_maps:
                    not_done_maps.remove(m)
            f.write(f'}};\n')

        if len(not_done_maps) > 0:
            print('WARNING: There were uncategorised maps: "{}".'.format(','.join(not_done_maps)))

        f.write('// clang-format on\n')
        f.write('\n')
        write_namespace_end(f)


if __name__ == '__main__':
    inject_palettable_cmaps()

    matplotlib_color_map_groups: Dict[str, List[str]] = {
            'perc_unif_sequential': [
                    'viridis',
                    'plasma',
                    'inferno',
                    'magma',
                    'cividis',
            ],
            'sequential': [
                    'Greys',
                    'Purples',
                    'Blues',
                    'Greens',
                    'Oranges',
                    'Reds',
                    'YlOrBr',
                    'YlOrRd',
                    'OrRd',
                    'PuRd',
                    'RdPu',
                    'BuPu',
                    'GnBu',
                    'PuBu',
                    'YlGnBu',
                    'PuBuGn',
                    'BuGn',
                    'YlGn'
            ],
            'sequential2': [
                    'binary',
                    'gist_yarg',
                    'gist_gray',
                    'gray',
                    'bone',
                    'pink',
                    'spring',
                    'summer',
                    'autumn',
                    'winter',
                    'cool',
                    'Wistia',
                    'hot',
                    'afmhot',
                    'gist_heat',
                    'copper'
            ],
            'diverging': [
                    'PiYG',
                    'PRGn',
                    'BrBG',
                    'PuOr',
                    'RdGy',
                    'RdBu',
                    'RdYlBu',
                    'RdYlGn',
                    'Spectral',
                    'coolwarm',
                    'bwr',
                    'seismic'
            ],
            'diverging_black': [
                    'pink_black_green(w3c)',
                    'red_black_blue',
                    'red_black_green',
                    'red_black_orange',
                    'red_black_sky',
                    'yellow_black_blue',
                    'yellow_black_sky',
            ],
            'qualitative': [
                    'Pastel1',
                    'Pastel2',
                    'Paired',
                    'Accent',
                    'Dark2',
                    'Set1',
                    'Set2',
                    'Set3',
                    'tab10',
                    'tab20',
                    'tab20b',
                    'tab20c'
            ],
            'misc': [
                    'flag',
                    'prism',
                    'ocean',
                    'gist_earth',
                    'terrain',
                    'gist_stern',
                    'gnuplot',
                    'gnuplot2',
                    'CMRmap',
                    'cubehelix',
                    'brg',
                    'gist_rainbow',
                    'rainbow',
                    'jet',
                    'nipy_spectral',
                    'gist_ncar'
            ],
            'cyclic': [
                    'twilight',
                    'twilight_shifted',
                    'hsv'
            ],
    }

    os.makedirs(INCLUDE_DIR)
    os.makedirs(SRCE_DIR)

    color_map_groups = matplotlib_color_map_groups.copy()
    for key in matplotlib_color_map_groups:
        color_map_groups[key + '_slim'] = matplotlib_color_map_groups[key].copy()

    for key in palettable_maps:
        color_group = palettable_maps[key].type
        if key not in color_map_groups[color_group]:
            color_map_groups[color_group].append(key)

    for key in color_map_groups:
        color_map_groups[key] = sorted(color_map_groups[key], key=cmap_name_key)

    all_maps = []
    for key in color_map_groups:
        all_maps.extend(color_map_groups[key])

    used_maps, duplicate_maps, numbered_maps = get_map_types(all_maps)
    write_cpp_headers(used_maps)
    write_colormaps_enums_header(used_maps, duplicate_maps)

    write_all_maps_header(color_map_groups, len(used_maps))
    write_all_maps_cpp(color_map_groups, used_maps, duplicate_maps)
