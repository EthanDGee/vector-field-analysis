# configs

TOML configuration files for the simulator and analyzer. Each file defines one named scenario.

| Config | Description |
|--------|-------------|
| [`vortex_256x256.toml`](vortex_256x256.toml) | Single counter-clockwise vortex with viscous decay, 256×256 grid |
| [`vortex_512x512.toml`](vortex_512x512.toml) | Single counter-clockwise vortex with viscous decay, 512×512 grid |
| [`karman_street_1000x1000.toml`](karman_street_1000x1000.toml) | Von Kármán vortex street — alternating vortices downstream of a bluff body, 1000×1000 grid |
| [`source_grid_divergent_512x512.toml`](source_grid_divergent_512x512.toml) | Five uniform background flows at varied angles on a 512×512 grid |

## Running

```sh
# Run a single config through the full pipeline
scripts/pipeline.sh vortex_256x256

# Run all configs
scripts/pipeline.sh
```

Output is written to `data/<stem>/` for each config stem.
