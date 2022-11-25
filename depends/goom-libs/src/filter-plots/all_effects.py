import numpy as np

from after_effects import AfterEffectFunction
from filter_effects import FilterEffectFunction

X_MIN = -2.1
X_MAX = -X_MIN
Y_MIN = X_MIN
Y_MAX = -Y_MIN


class Viewport:
    WIDTH = X_MAX - X_MIN
    HEIGHT = Y_MAX - Y_MIN

    def __init__(self, x0: float = X_MIN, y0: float = Y_MIN, x1: float = X_MAX, y1: float = Y_MAX):
        self.x_scale = (x1 - x0) / self.WIDTH
        self.y_scale = (y1 - y0) / self.HEIGHT
        self.x_offset = (x0 + x1) / 2
        self.y_offset = (y0 + y1) / 2

    def get_z(self, world_z: np.ndarray) -> np.ndarray:
        return (self.x_offset + (self.x_scale * world_z.real)) + (
                self.y_offset + (self.y_scale * world_z.imag)) * 1.0j


class CombinedEffects:
    def __init__(self, viewport: Viewport, f_filter_effect: FilterEffectFunction,
                 f_after_effect: AfterEffectFunction):
        self.viewport = viewport
        self.f_filter_effect = f_filter_effect
        self.f_after_effect = f_after_effect

    def get_name(self) -> str:
        return f'{self.f_filter_effect.name} - {self.f_after_effect.name}'

    def f(self, z: np.ndarray):
        fz = self.f_zoom(z)

        return fz
        # return np.clip(fz, -2.0, +2.0)

    def f_zoom(self, z: np.ndarray):
        # print(f'z.shape = {z.shape}')

        base_zoom_coeffs = 0.1 + 0.1j
        # base_zoom_coeffs = -1 + -1j
        # base_zoom_coeffs = -0.1 + -0.5j
        # base_zoom_coeffs = 0 + 0j

        self.f_filter_effect.base_zoom_coeffs = base_zoom_coeffs
        self.f_after_effect.base_zoom_coeffs = base_zoom_coeffs

        z_view = self.viewport.get_z(z)
        absolute_sq_z_view = np.absolute(z_view) ** 2
        zoom_in_coeffs = self.f_filter_effect.f(z_view, absolute_sq_z_view)
        # return zoom_in_coeffs

        zoom_in_factor = 1.0 + 1.0j - zoom_in_coeffs
        # zoom_in_factor = zoom_in_coeffs

        zoom_in_point = (zoom_in_factor.real * z.real) + (zoom_in_factor.imag * z.imag) * 1.0j
        # return zoom_in_point

        zoom_in_velocity = z - zoom_in_point
        absolute_sq_z = np.absolute(z) ** 2
        after_effects_velocity = self.f_after_effect.f(z, absolute_sq_z, zoom_in_velocity)
        after_effects_zoom_in_point = zoom_in_point - after_effects_velocity

        return after_effects_zoom_in_point
        # return np.clip(after_effects_zoom_in_point, -2.0, +2.0)
