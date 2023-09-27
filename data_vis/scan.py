"""This module is for serial communication with the scanner."""
from time import strftime, localtime
import numpy as np
import serial
import visualization

# Set up serial communication

# Use `with` statement to avoid unclosed serial communication after the end of
# program.
with serial.Serial() as scanner:
    # Initialize the scanner with the specifics
    scanner.port = "/dev/ttyACM0"  # Replace with actual port
    scanner.baudrate = 9600  # This must match baudrate of Arduino.

    # Attempt to open the serial connection
    try:
        scanner.open()
    except serial.serialutil.SerialException:
        print("No scanner found on the port. Try again with a different port.")

    # Attempt to read data from serial connection
    try:
        # Grab current time for file name
        time_prefix = strftime("%a-%d-%b-%Y-%H-%M", localtime())
        # Continue to run as long as the scanner's connection is open
        while scanner.is_open:
            # Read and parse incoming data from the Arduino
            data = str(scanner.readline().decode().strip())

            # Assuming that the data from Arduino will look something like
            # "r,tilt,pan".
            print(data)
            # Save the data into a local file (maybe a .csv file)
            with open(
                f"{time_prefix}.csv", "a", newline="\n", encoding="utf-8"
                ) as f:
                f.write(data)
                f.write("\n")

    except KeyboardInterrupt:
        scanner.close()  # Close the serial port on Ctrl+C

        # Opening the saved file again
        data_transposed = np.loadtxt(
            f"{time_prefix}.csv", delimiter=",", dtype=float
            )
        data_transposed *= np.pi / 180
        x_data, y_data, z_data = data_transposed.transpose()

        # Plot with collected data
        visualization.scatter_3d_plotly(-(x_data + 5), y_data, z_data)
