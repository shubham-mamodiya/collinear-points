from cProfile import label
import matplotlib.pyplot as plt
import pandas as pd
import sys


def main() -> None:
    if len(sys.argv) != 3:
        print("Usage: python main.py <points.csv> <segments.csv>")
        return None

    point_file_path = sys.argv[1]
    segmenst_file_path = sys.argv[2]
    points = pd.read_csv(point_file_path, header=None, names=["x", "y"])
    segments = pd.read_csv(
        segmenst_file_path, header=None, names=["x1", "y1", "x2", "y2"]
    )

    _, ax = plt.subplots()

    ax.scatter(points["x"], points["y"], marker="x", label="points")

    for _, row in segments.iterrows():
        ax.plot([row["x1"], row["x2"]], [row["y1"], row["y2"]])

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_title("Points and Line Segments")
    ax.legend()
    ax.grid(True)

    plt.show()


if __name__ == "__main__":
    main()
