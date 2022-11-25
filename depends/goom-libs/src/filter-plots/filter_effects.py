import math
from abc import ABC, abstractmethod

import numpy as np


class FilterEffectFunction(ABC):
    def __init__(self, name):
        self.name = name
        self.base_zoom_coeffs = complex(0, 0)

    @abstractmethod
    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        pass


class IdentityZoom(FilterEffectFunction):
    def __init__(self):
        super().__init__('Identity Zoom')

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs


class Amulet(FilterEffectFunction):
    def __init__(self):
        super().__init__('Amulet')
        self.amplitude = 0.9

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        # angle = np.sin(1.0/np.log(abs(np.arctan2(np.imag(z), np.real(z)))))
        return self.base_zoom_coeffs + (self.amplitude * absolute_sq_z * (1 + 1j))


class Wave(FilterEffectFunction):
    def __init__(self, name):
        super().__init__(name)
        self.freq_factor = 2
        self.amplitude = 0.09
        self.periodic_factor = 10
        self.reducer_coeff = 0.001

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        reducer = np.exp(-self.reducer_coeff * absolute_sq_z)
        full_factor = reducer * self.amplitude * self.periodic_factor
        angle = self.freq_factor * absolute_sq_z
        return self.base_zoom_coeffs + (full_factor * self.f_angle(angle) * (1 + 1j))

    @abstractmethod
    def f_angle(self, angle: np.ndarray):
        return 0


class WaveSine(Wave):
    def __init__(self):
        super().__init__('Wave Sine')

    def f_angle(self, angle: np.ndarray):
        return np.sin(angle)


class WaveTan(Wave):
    def __init__(self):
        super().__init__('Wave Tan')

    def f_angle(self, angle: np.ndarray):
        return np.tan(angle)


class Scrunch(FilterEffectFunction):
    def __init__(self):
        super().__init__('Scrunch')
        self.x_amplitude = 0.1
        self.y_amplitude = 3.0

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        x_zoom_in_coeff = self.base_zoom_coeffs.real + (self.x_amplitude * absolute_sq_z)
        y_zoom_in_coeff = self.y_amplitude * x_zoom_in_coeff
        return x_zoom_in_coeff + (y_zoom_in_coeff * 1.0j)


class YOnly(FilterEffectFunction):
    def __init__(self):
        super().__init__('Y Only')
        self.x_freq_factor = 10.1
        self.y_freq_factor = 20.0
        self.x_amplitude = 1.0
        self.y_amplitude = 10.0

    def get_y_only_zoom_in_multiplier(self, z: np.ndarray):
        return np.sin(self.x_freq_factor * z.real) * np.cos(self.y_freq_factor * z.imag)

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        x_zoom_in_coeff = self.base_zoom_coeffs.real * self.x_amplitude * \
                          self.get_y_only_zoom_in_multiplier(z)

        # return x_zoom_in_coeff + x_zoom_in_coeff * 1.0j

        return x_zoom_in_coeff + (
                self.base_zoom_coeffs.imag * self.y_amplitude *
                self.get_y_only_zoom_in_multiplier(z)) * 1.0j


class DistanceField(FilterEffectFunction):
    def __init__(self):
        super().__init__("Distance Field")
        self.sq_dist_mult = 5.0
        self.sq_dist_offset = 2.0
        self.x_amplitude = 0.5
        self.y_amplitude = 0.25

        self.Z_MIN = -2.0
        self.Z_MAX = +2.0
        self.MAX_DISTANCE_SQ = 2.0 * self.Z_MAX - self.Z_MIN

        self.HALF_MIN_COORD = 0.5 * self.Z_MIN
        self.HALF_MAX_COORD = 0.5 * self.Z_MAX
        self.distance_points = [complex(self.HALF_MIN_COORD, self.HALF_MIN_COORD),
                                complex(self.HALF_MAX_COORD, self.HALF_MIN_COORD),
                                complex(self.HALF_MIN_COORD, self.HALF_MAX_COORD),
                                complex(self.HALF_MAX_COORD, self.HALF_MAX_COORD),
                                ]

    def get_closest_distance_point(self, z: complex):
        min_distance_sq = self.MAX_DISTANCE_SQ
        closest_point = None

        for pt in self.distance_points:
            distance_sq = np.abs(z - pt)
            if distance_sq < min_distance_sq:
                min_distance_sq = distance_sq
                closest_point = pt

        assert closest_point is not None

        return min_distance_sq

    def get_distance_field_coeff(self,
                                 base_zoom_in_coeff: float,
                                 sq_dist_from_closest_point: np.ndarray,
                                 amplitude: float) -> np.ndarray:
        return base_zoom_in_coeff + (
                amplitude * (
                (self.sq_dist_mult * sq_dist_from_closest_point) - self.sq_dist_offset))

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray) -> np.ndarray:
        get_closest_distance_point_func = np.vectorize(self.get_closest_distance_point)
        sq_dist_from_closest_point = get_closest_distance_point_func(z) ** 2

        fz_real = self.get_distance_field_coeff(self.base_zoom_coeffs.real,
                                                sq_dist_from_closest_point, self.x_amplitude)
        fz_imag = self.get_distance_field_coeff(self.base_zoom_coeffs.imag,
                                                sq_dist_from_closest_point, self.y_amplitude)
        return fz_real + fz_imag * 1.0j


class Speedway(FilterEffectFunction):
    def __init__(self):
        super().__init__("Speedway")
        self.x_amplitude = 2.0
        self.y_amplitude = 1.0
        self.SQ_DIST_FACTOR = 0.01

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        x_add = self.SQ_DIST_FACTOR * absolute_sq_z

        x_zoom_in_coeff = self.base_zoom_coeffs.real * (self.x_amplitude * (z.imag + x_add))
        y_zoom_in_coeff = self.y_amplitude * x_zoom_in_coeff

        return x_zoom_in_coeff + y_zoom_in_coeff * 1.0j


class Mobius(FilterEffectFunction):
    def __init__(self):
        super().__init__("Mobius")
        self.a = +1.0
        self.b = +1.0
        self.c = +1.0
        self.d = -1.0
        self.amplitude = 0.1

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs + self.amplitude * (
                (self.a * z + self.b) / (self.c * z + self.d))


class ExpReciprocal(FilterEffectFunction):
    def __init__(self):
        super().__init__("Exp Reciprocal")
        self.amplitude = 0.1
        self.factor = 1.0
        self.recipr_exp = 3.0
        self.offset = complex(0.0, 0.0)
        rotate_angle = 0.9 * 2.0 * math.pi
        self.rotate = math.cos(rotate_angle) + math.sin(rotate_angle) * 1.0J

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        fz = np.exp(
                1.0 / ((self.factor * self.rotate * (z + self.offset)) ** self.recipr_exp))
        fz_arg = np.angle(fz)
        fz_norm = np.absolute(fz) ** 2
        phase = np.cos(fz_arg) + np.sin(fz_arg) * 1.0j
        inv_log_abs_sq_z = 1.0 / np.log(1.5 + absolute_sq_z)
        return self.base_zoom_coeffs + inv_log_abs_sq_z * self.amplitude * phase


class Sine(FilterEffectFunction):
    def __init__(self):
        super().__init__("Sine")
        self.amplitude = 0.1
        self.freq = 12.0
        self.offset = complex(0, 0)

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        #t = 0.1
        #return np.cos(t + z ** 2) - np.sin(t + 1.0 + z ** 4)
        freq_factor = 2
        angle = freq_factor * absolute_sq_z
        return self.base_zoom_coeffs + (
                self.amplitude * np.sin(angle) * np.sin(self.freq * (z + self.offset)))


class StrangeSine(FilterEffectFunction):
    def __init__(self):
        super().__init__("Strange Sine")
        self.amplitude = 0.1
        self.factor = 0.01

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs + ((self.amplitude * np.sin(z ** 3)) / (self.factor * z))


class Power(FilterEffectFunction):
    def __init__(self):
        super().__init__("Power")
        self.amplitude = 0.001

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs + z ** 6 + 1


class MandelbrotSet(FilterEffectFunction):
    def __init__(self):
        super().__init__("Mandelbrot Set")
        self.amplitude = 4.0
        self.max_iterations: int = 20
        self.escape_radius: float = 2.0

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs + self.amplitude * self.stability(z, smooth=True,
                                                                       clamp=True) * z

    def stability(self, c: np.ndarray, smooth=False, clamp=True) -> np.ndarray:
        get_escape_count_func = np.vectorize(self.escape_count)
        value = get_escape_count_func(c, smooth) / self.max_iterations
        return np.clip(value, 0.0, 1.0)

    def escape_count(self, c: complex, smooth=False) -> int | float:
        z = 0
        for iteration in range(self.max_iterations):
            z = z ** 2 + c
            if np.absolute(z) > self.escape_radius:
                if smooth:
                    return iteration + 1.0 - np.log(np.log(abs(z))) / np.log(2)
                return iteration
        return self.max_iterations


class ManualPlugin(FilterEffectFunction):
    def __init__(self):
        super().__init__("Manual Plugin")

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray):
        return self.base_zoom_coeffs + (z ** 2 - 1.0) * (z + 2.0 - 1.0j) * 2.0 / (
                    z ** 2 + 2.0 - 2.0 * 1.0j)
