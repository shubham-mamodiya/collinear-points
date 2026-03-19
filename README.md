# Collinear Points

A small C++20 project for detecting line segments formed by sets of collinear points in 2D.

Given an input file of points, the program:

- Reads all points into memory
- Optionally converts the point list to a CSV file (next to the input file)
- Finds all line segments that contain at least **four** collinear points
- Writes the resulting segments to a CSV file you specify

## Project Layout

- [src](src)
  - main.cpp – command‑line entry point and I/O
  - collinear.h / collinear.cpp – `Point`, `Slope`, `LineSegment` and collinearity algorithms
- [data/input](data/input) – example input point sets
- [data/output](data/output) – place to write result CSVs (you choose the filename)
- [plot](plot) – Python project for visualising points and segments

## Input Format

Text files in `data/input` use this format:

```text
N
x1 y1
x2 y2
...
xN yN
```

- `N` – number of points
- Each following line – integer coordinates `x y`

## Running

From the project root, after building:

```bash
./build/collinear-points <input-file> <output-segments-csv>
```

Example:

```bash
./build/collinear-points data/input/rs1423.txt data/output/rs1423_segments.csv
```

Behaviour:

- If `<output-segments-csv>` already exists, the program asks before overwriting.
- It also writes a **points CSV** next to the input file, with the same basename and a `.csv` extension (e.g. `rs1423.csv`).

## Output Formats

1. **Points CSV** (auto‑generated from the input):

   ```text
   x , y
   ```

2. **Segments CSV** (specified by you as `<output-segments-csv>`):

   ```text
   ax , ay , bx , by
   ```

   where `(ax, ay)` and `(bx, by)` are the endpoints of a maximal collinear segment.

## Plotting

The [plot](plot) directory contains a Python project (see `pyproject.toml`) that can be used to visualise:

- The original points (from the generated points CSV)
- The detected line segments (from the segments CSV)

You can install the plotting dependencies with your preferred tool, for example:

```bash
cd plot
pip install .
```

Then adapt `main.py` (or your own script) to load the points and segments CSVs and draw them.

## Notes

- The implementation uses integer arithmetic for slopes to avoid floating‑point precision issues.
- Only segments with **at least four collinear points** (including the origin point) are reported.
