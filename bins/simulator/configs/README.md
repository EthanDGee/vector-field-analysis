# Simulator Configs

Ready-to-run TOML configs for the simulator. Each file is fully self-contained
and documented with the physics behind it.

## Running a config

```sh
simulator bins/simulator/configs/<name>.toml
mise run visualize
```

## Config file format

All settings live under a `[simulation]` table. Field layers are `[[layers]]`
array entries and are summed by superposition. See
[`bins/simulator/README.md`](../README.md) for the full schema reference.

---

## Demos

Simple fields that demonstrate individual layer types and the config system.

### `vortex.toml`

Single counter-clockwise vortex. Decays via viscosity.

```sh
simulator bins/simulator/configs/vortex.toml
```

### `spiral.toml`

Inward spiral -- vortex rotation blended 70% toward a sink. Viscous decay
makes the field fade to zero over time.

```sh
simulator bins/simulator/configs/spiral.toml
```

### `dual_vortex.toml`

Two counter-rotating vortices side by side. The left spins CCW (strength +1),
the right CW (strength -1). Both decay via viscosity.

```sh
simulator bins/simulator/configs/dual_vortex.toml
```

### `source_sink.toml`

A source on the left and a sink on the right. Flow radiates from the source,
crosses the domain, and converges into the sink. A noise layer adds turbulent
disturbance and viscous decay weakens the field over time.

```sh
simulator bins/simulator/configs/source_sink.toml
```

### `noise.toml`

Pure Perlin noise field. No symmetry, organic-looking flow. Good for
stress-testing the analyzer with irregular input.

```sh
simulator bins/simulator/configs/noise.toml
```

### `layered.toml`

Three layers combined: a central vortex, an off-center source, and
low-amplitude noise. Demonstrates how layers compose into complex fields.

```sh
simulator bins/simulator/configs/layered.toml
```

### `custom_rotation.toml`

Solid-body rotation that oscillates in speed with `cos(0.5*t)` -- the field
slows, reverses, then spins back up. Demonstrates the `custom` layer type and
use of the `t` variable in expressions.

```sh
simulator bins/simulator/configs/custom_rotation.toml
```

---

## Real-world simulations

### `hurricane.toml`

Tropical cyclone (Northern Hemisphere). Three-layer model:

- Core spiral with 12% inward convergence (matches real surface inflow angle)
- Perlin noise for outer rainband turbulence
- Weak uniform steering flow on a NW track

Viscous decay simulates gradual weakening.

```sh
simulator bins/simulator/configs/hurricane.toml
```

### `karman_street.toml`

Von Kármán vortex street -- the alternating vortex pattern that forms
downstream of any bluff body (bridge pier, smokestack, island, aircraft wing).

Uses the **exact analytical formula** for two infinite periodic rows of point
vortices (Lamb's *Hydrodynamics*). The rows advect rightward in real time.
The implied cylinder is off the left edge of the domain.

```sh
simulator bins/simulator/configs/karman_street.toml
```

### `wind_tunnel.toml`

Potential flow around a circular cylinder. Combines a uniform free stream with
a doublet at the origin -- the exact irrotational solution. The free stream
pulses with `sin(0.3*t)` to simulate gusts. The cylinder boundary (r = 0.3)
is visible where arrows reverse inside the solid body.

```sh
simulator bins/simulator/configs/wind_tunnel.toml
```

### `accretion_disk.toml`

Black hole / neutron star accretion disk. Keplerian orbital speed
(`v ∝ 1/sqrt(r)`) combined with ~20% radial infall, driven by
angular momentum transport (magneto-rotational instability in real disks).
A noise layer approximates MRI-driven turbulence in the disk midplane.

```sh
simulator bins/simulator/configs/accretion_disk.toml
```

### `kelvin_helmholtz.toml`

Kelvin-Helmholtz shear instability. Occurs at any interface where two fluid
layers slide past each other: ocean-atmosphere boundary, jet stream edges,
cloud formations, Jupiter's bands, stellar interiors.

A `tanh` shear profile is perturbed by a sinusoidal transverse displacement
that grows exponentially with time (`exp(0.12*t)`), mimicking the linear
instability growth rate. By the final steps the perturbation rolls up into
billows.

```sh
simulator bins/simulator/configs/kelvin_helmholtz.toml
```

### `magnetosphere.toml`

Earth's magnetosphere interacting with the solar wind. Viewed in the
noon-midnight meridional plane (cross-section through the magnetic poles).

Earth's dipole uses two 1/r²-decaying custom poles. The magnetopause
(standoff at ~r = 1.0) is visible as the boundary where the solar wind and
dipole pressures balance. The solar wind pulses with `sin(0.4*t)`, simulating
pressure variations from a passing coronal mass ejection.

```sh
simulator bins/simulator/configs/magnetosphere.toml
```

### `pulsatile_flow.toml`

Pulsatile blood flow in a large artery (coronary or aorta). The parabolic
Poiseuille profile satisfies the no-slip condition at the walls (y = ±1).
The amplitude cycles at 1.2 rad/s (≈ 72 bpm resting heart rate), including
a brief flow reversal during diastole -- physiologically normal in the
coronary arteries.

```sh
simulator bins/simulator/configs/pulsatile_flow.toml
```
