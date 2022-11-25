import argparse
import os
import matplotlib.pyplot as plt
from typing import List

import numpy as np

DATA_DIR = '/home/greg/docker/kodi-nightly/.kodi/userdata/addon_data/visualization.goom/goom_dumps'
MIN_TIMELINE_ELEMENTS = 10


def check_for_long_updates(subdirs, filename):
    print()
    for subdir in subdirs:
        data_array = load_data_from_file(subdir, filename)
        max_val = max(data_array)
        if max_val > 200:
            print(f'Large update time in "{os.path.join(subdir, filename)}":  {int(max_val)}')


def get_full_path(subdir, filename):
    return os.path.join(DATA_DIR, subdir, filename)


def load_data_from_file(subdir, filename):
    return np.loadtxt(os.path.join(DATA_DIR, subdir, filename))


def load_data_from_files(subdir_list, filename):
    data_array = load_data_from_file(subdir_list[0], filename)
    for subdir in subdir_list[1:]:
        next_array = load_data_from_file(subdir, filename)
        data_array = np.append(data_array, [next_array])

    return data_array


def get_percent_buckets(data_array):
    buckets = dict()

    for data in data_array:
        if data not in buckets:
            buckets[data] = 0
        buckets[data] += 1

    total = len(data_array)
    percent_buckets = dict()
    for bucket in buckets:
        n = buckets[bucket]
        percent_buckets[bucket] = int(round((100.0 * float(n)) / float(total)))

    return percent_buckets


def print_percent_buckets(name, buckets):
    str = ''
    for bucket in sorted(buckets):
        str += f'{int(bucket):>2}:{buckets[bucket]:>3}% '

    print(f'{name:>3}: {str}')


def add_plot(ax, data_array, yaxis_label, ymin, ymax, yticks, line_color):
    if len(data_array) < MIN_TIMELINE_ELEMENTS:
        raise Exception(
                f'Too few timeline elements: {len(data_array)} (< {MIN_TIMELINE_ELEMENTS}).')

    ax.plot(data_array, color=line_color)
    ax.set(ylabel=yaxis_label)
    ax.set_ylim([ymin, ymax])
    ax.set_yticks(yticks)
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)


def get_subdirs_name(subdirs):
    name = ""
    if len(subdirs) == 1:
        name = subdirs[0]
    else:
        name = f'{subdirs[0]}  ...  {subdirs[-1]}'
    return name.replace('_', ' ')


class DataType:
    def __init__(self, filename, label, ymin, ymax, yticks, color, print_percent):
        self.filename = filename
        self.label = label
        self.ymin = ymin
        self.ymax = ymax
        self.yticks = yticks
        self.color = color
        self.print_percent = print_percent

    def get_ymax(self, data_array):
        if self.ymax != -1 or self.ymax > self.ymin:
            return self.ymax
        return max(data_array)

    def get_yticks(self, data_array):
        if self.yticks:
            return self.yticks
        return (0, max(data_array) / 2, max(data_array))


def plot_groups(subdirs, plot_data, axs):
    print()

    i = 0
    for data_type in plot_data:
        i = plot_group(subdirs, data_type, axs, i)


def plot_group(subdirs, group, axs, axs_index):
    for data_type in group:
        data_array = load_data_from_files(subdirs, data_type.filename)

        if data_type.print_percent:
            print_percent_buckets(data_type.label, get_percent_buckets(data_array))

        add_plot(axs[axs_index], data_array, data_type.label, data_type.ymin,
                 data_type.get_ymax(data_array),
                 data_type.get_yticks(data_array), data_type.color)

        axs_index += 1

    return axs_index


def plot(subdirs):
    main_data = [
            DataType('goom_states.dat', 'st', 0, 43, (0, 20, 43), 'red', True),
            DataType('filter_modes.dat', 'fil', 0, 18, (0, 10, 18), 'green', True),
            DataType('hypercos_overlays.dat', 'hyp', 0, 4, (0, 4), 'blue', True),
    ]
    sound_data = [
            DataType('goom_volumes.dat', 'vol', 0.0, 1.0, (0, 1), 'orange', False),
            DataType('goom_powers.dat', 'pwr', 0.0, 1.0, (0, 1), 'purple', False),
            DataType('times_since_last_goom.dat', 'lst', 0, -1, (), 'orange', False),
            DataType('times_since_last_big_goom.dat', 'big', 0, -1, (), 'purple', False),
            DataType('total_gooms_in_current_cycle.dat', 'cyc', 0, -1, (), 'orange', False),
    ]
    effects_data = [
            DataType('blocky_wavy_effects.dat', 'blk', 0, 1, (0, 1), 'orange', True),
            DataType('image_velocity_effects.dat', 'img', 0, 1, (0, 1), 'purple', True),
            DataType('noise_effects.dat', 'nse', 0, 1, (0, 1), 'orange', True),
            DataType('plane_effects.dat', 'pln', 0, 1, (0, 1), 'purple', True),
            DataType('rotation_effects.dat', 'rot', 0, 1, (0, 1), 'orange', True),
            DataType('tan_effects.dat', 'tan', 0, 1, (0, 1), 'orange', True),
    ]
    buffer_data = [
            DataType('buffer_lerps.dat', 'ler', 0, -1, (), 'red', False),
    ]
    update_times_data = [
            DataType('update_times.dat', 'upd', 0, -1, (), 'black', False),
    ]

    plot_data = [
            main_data,
            # sound_data,
            effects_data,
            # buffer_data,
            update_times_data
    ]

    num_subplots = sum(len(data_type) for data_type in plot_data)

    fig = plt.figure(figsize=(10, 8))
    fig.canvas.set_window_title('Goom Timelines')
    gs = fig.add_gridspec(num_subplots, hspace=0.5)
    axs = gs.subplots(sharex=True)
    # Hide x labels and tick labels for all but bottom plot.
    for ax in axs:
        ax.label_outer()

    fig.suptitle(f'Data: {get_subdirs_name(subdirs)}')

    plot_groups(subdirs, plot_data, axs)

    check_for_long_updates(subdirs, 'update_times.dat')

    plt.show()


def get_cleaned_subdirs(subdirs: List[str]):
    return [s.rstrip('/') for s in subdirs]


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            description=f"Plot Goom timelines in the directory '{DATA_DIR}'.")
    parser.add_argument("subdirs", nargs="+")
    args = parser.parse_args()

    plot(get_cleaned_subdirs(args.subdirs))
