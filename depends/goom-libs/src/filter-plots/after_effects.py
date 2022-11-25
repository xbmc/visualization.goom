import math
from abc import ABC, abstractmethod

import numpy as np

PI = math.pi
HALF_PI = 0.5 * math.pi


class AfterEffectFunction(ABC):
    def __init__(self, name: str):
        self.name = name
        self.base_zoom_coeffs = 0 + 0j

    @abstractmethod
    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray, velocity: np.ndarray):
        pass


class Zero(AfterEffectFunction):
    def __init__(self):
        super().__init__('No After Effect')

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray, velocity: np.ndarray):
        return 0 + 0j


class Tan(AfterEffectFunction):
    def __init__(self):
        super().__init__('Tan After Effect')
        self.x_amplitude = 0.5
        self.y_amplitude = 0.5
        self.limiting_factor = 1
        self.limit = self.limiting_factor * HALF_PI

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray, velocity: np.ndarray):
        def get_tan_sq_dist(arg):
            return np.tan(arg)

        tan_arg = np.clip(np.fmod(absolute_sq_z, HALF_PI), -self.limit, +self.limit)
        tan_sq_dist = get_tan_sq_dist(tan_arg)
        return self.x_amplitude * (tan_sq_dist * np.real(velocity)) + (
                self.y_amplitude * (tan_sq_dist * np.imag(velocity))) * 1.0j


def lerp(z1: np.ndarray, z2: np.ndarray, t: np.ndarray) -> np.ndarray:
    return z1 + t * (z2 - z1)


class XYLerp(AfterEffectFunction):
    def __init__(self):
        super().__init__('XY Lerp After Effect')
        self.MODE2_OFFSET = 5.5
        self.MODE2_FREQ = 2.0
        self.MODE3_MIN_FACTOR = 0.99
        self.MODE3_MAX_FACTOR = 1.01

        # self.t_freq = 1.0
        self.t_freq = 2.0
        # self.t_freq = 10.0

        # self.flip_xy = False
        self.flip_xy = True

        # self.y_sign = +1.0
        self.y_sign = -1.0

    def f(self, z: np.ndarray, absolute_sq_z: np.ndarray, velocity: np.ndarray):
        t = self.get_t(absolute_sq_z, velocity)
        fz_real = lerp(z.real, z.imag, t)
        fz_imag = lerp(z.imag, z.real, t)

        if self.flip_xy:
            return fz_imag + self.y_sign * fz_real * 1.0j

        return fz_real + self.y_sign * fz_imag * 1.0j

    def get_t(self, absolute_sq_z: np.ndarray, velocity: np.ndarray) -> np.ndarray:
        t = np.cos((self.t_freq * absolute_sq_z) + (self.MODE2_OFFSET + np.sin(self.MODE2_FREQ * absolute_sq_z)))
        # t = np.cos((self.t_freq * absolute_sq_z) * self.MODE3_MIN_FACTOR)
        # t = np.cos((self.t_freq * absolute_sq_z) * self.MODE3_MAX_FACTOR)
        # t = -(2.0 / PI) * (HALF_PI - (self.t_freq * absolute_sq_z))
        # t = -(2.0 / PI) * np.arctan(np.tan(HALF_PI - (self.t_freq * absolute_sq_z))) # RUBBISH ???
        # t = np.abs(np.arctan2(velocity.imag, velocity.real) / PI)

        return t
