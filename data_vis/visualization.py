import numpy as np
import plotly.graph_objects as go
import matplotlib.pyplot as plt
import csv

from numpy import sin, cos, sqrt, arccos, arctan2


def spheric2cart(r: float, theta: float, phi: float) -> tuple[float, float, float]:
    """
    Convert spherical coordinates to cartesian coordinates.

    The conventions used are from the wikipedia page for spherical coordinate
    system -- https://en.wikipedia.org/wiki/Spherical_coordinate_system.

    Args:
        r (float): The radial distance in cm.
        theta (float): Polar angle which is with respect to positive polar
          axis. Otherwise referred to as the 'tilt'.
        phi (float): azimuthal angle -- angle of rotation from the initial
          meridian plane.

    Returns:
        A tuple consisting of (x, y, z) in cartesian space.
    """
    x = r * sin(theta) * cos(phi)
    y = r * sin(theta) * sin(phi)
    z = r * cos(theta)
    return x, y, z


def cart2spheric(x: float, y: float, z: float) -> tuple[float, float, float]:
    """
    Convert a single Cartesian coordinate to a spherical coordinate.

    Args:
        x (float): A float representing x.
        y (float): A float representing y.
        z (float): A float representing z.

    Returns:
        tuple[float, float, float]: A tuple in the form of
          (radial distance, polar angle, azimuthal angle).
    """
    r = sqrt(x * x + y * y + z * z)
    theta = arccos(z / r)
    phi = arctan2(y, x)
    return r, theta, phi


def gen_sample_data(num_points: int = 30) -> tuple[list, list, list]:
    """
    Generate a sample dataset of Cartesian coordinates that form a circle.

    Args:
        num_points (int, optional): The number of points of generate. Defaults to 30.

    Returns:
        tuple[list, list, list]: A tuple of lists that each represent x, y, and
          z, respectively.
    """
    # Constant x value
    x = 10  # Just an arbitrary x value, which can be modified.

    # Create an array of angles evenly spaced between 0 and 2*pi
    angles = np.linspace(0, 2 * np.pi, num_points)

    # Calculate y and z coordinates for points on a circle with radius 5
    radius = 5
    y = radius * cos(angles)
    z = radius * sin(angles)

    # Create a tuple of lists for (x, y, z) coordinates
    return (list(x for _ in range(num_points)), y.tolist(), z.tolist())


def scatter_3d_plotly(x_data: list, y_data: list, z_data: list):
    """
    Plots data as a 3d scatter plot using plotly.

    Args:
        x_data (list): A list of x coordinates.
        y_data (list): A list of y coordinates.
        z_data (list): A list of z coordinates.
    """
    # Round the data to 2 decimal places -- Plotly seems to have issues with
    # very long floats.
    x_data = np.round(x_data, 2)
    y_data = np.round(y_data, 2)
    z_data = np.round(z_data, 2)

    # Create a trace for the 3D scatter plot
    trace = go.Scatter3d(
        x=x_data,
        y=y_data,
        z=z_data,
        mode="markers",  # Set mode to 'markers'
        marker=dict(
            size=3,  # Adjust the size of markers
            opacity=0.8,
            color="blue",  # Set marker color
        ),
    )

    # Create a layout for the plot
    layout = go.Layout(
        scene=dict(
            xaxis_title="X",
            yaxis_title="Y",
            zaxis_title="Z",
        )
    )

    # Create the figure
    fig = go.Figure(data=[trace], layout=layout)

    # Show the plot
    fig.show()


def scatter_3d_mpl(x_data: list, y_data: list, z_data: list):
    """
    Plots data as a 3d scatter plot using matplotlib.

    Args:
        x_data (list): A list of x coordinates.
        y_data (list): A list of y coordinates.
        z_data (list): A list of z coordinates.
    """
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    ax.scatter(x_data, y_data, z_data, c="b", marker="o")

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")

    ax.set_box_aspect([1, 1, 1])

    plt.show()


def test_plot():
    """
    Tests the functionality of the conversions and plotting.
    """
    # Let's start with Cartesian coordinates to check if the conversions work.
    data = gen_sample_data()  # in form of [x_data], [y_data], [z_data]
    # transpose to get the form of [x1, y1, z1]
    data_transposed = np.array(data).transpose()
    # Round the numbers to 3 decimal places
    data_transposed = data_transposed.round(3)

    # Save as a csv file for future access
    with open("data.csv", "w", newline="") as file:
        data_writer = csv.writer(file, delimiter=",")
        data_writer.writerows(data_transposed)

    # Opening the saved file again
    data_transposed = np.loadtxt("data.csv", delimiter=",", dtype=float)
    x_data, y_data, z_data = data_transposed.transpose()

    # Initialize the spherical coordinate setup
    r = []
    theta = []
    phi = []
    # Now, convert to spherical:
    for i, _ in enumerate(x_data):
        r_i, theta_i, phi_i = cart2spheric(x_data[i], y_data[i], z_data[i])
        r.append(r_i)
        theta.append(theta_i)
        phi.append(phi_i)

    # We have a functional conversion between Cartesian and spherical if we can
    # convert the spherical back into Cartesian as what we began with.
    x_data, y_data, z_data = spheric2cart(r, theta, phi)

    # One way to check the conversion is to look at the plot.
    scatter_3d_plotly(x_data, y_data, z_data)


# Run the test function
# If you see a circle with a fixed x value, our test was successful.
# test_plot() # Uncomment this line to test.
