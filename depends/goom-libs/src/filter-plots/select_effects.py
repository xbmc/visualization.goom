from typing import Tuple

import after_effects
import filter_effects
from after_effects import AfterEffectFunction
from filter_effects import FilterEffectFunction


def get_effects() -> Tuple[FilterEffectFunction, AfterEffectFunction]:
    identity_zoom_filter_effect = filter_effects.IdentityZoom()
    amulet_filter_effect = filter_effects.Amulet()
    distance_field_filter_effect = filter_effects.DistanceField()
    wave_sine_filter_effect = filter_effects.WaveSine()
    wave_tan_filter_effect = filter_effects.WaveTan()
    scrunch_filter_effect = filter_effects.Scrunch()
    speedway_filter_effect = filter_effects.Speedway()
    y_only_filter_effect = filter_effects.YOnly()
    exp_reciprocal_filter_effect = filter_effects.ExpReciprocal()
    mandelbrot_set_filter_effect = filter_effects.MandelbrotSet()
    mobius_filter_effect = filter_effects.Mobius()
    power_filter_effect = filter_effects.Power()
    sine_filter_effect = filter_effects.Sine()
    strange_sine_filter_effect = filter_effects.StrangeSine()
    manual_plugin_filter_effect = filter_effects.ManualPlugin()

    zero_after_effect = after_effects.Zero()
    tan_after_effect = after_effects.Tan()
    xy_lerp_after_effect = after_effects.XYLerp()

    # filter_effect = identity_zoom_filter_effect
    # filter_effect = amulet_filter_effect
    # filter_effect = distance_field_filter_effect
    # filter_effect = scrunch_filter_effect
    # filter_effect = speedway_filter_effect
    # filter_effect = wave_sine_filter_effect
    # filter_effect = wave_tan_filter_effect
    # filter_effect = y_only_filter_effect
    filter_effect = exp_reciprocal_filter_effect
    # filter_effect = mandelbrot_set_filter_effect
    # filter_effect = mobius_filter_effect
    # filter_effect = power_filter_effect
    # filter_effect = sine_filter_effect
    # filter_effect = strange_sine_filter_effect
    # filter_effect = manual_plugin_filter_effect

    after_effect = zero_after_effect
    # after_effect = tan_after_effect
    # after_effect = xy_lerp_after_effect

    return filter_effect, after_effect
