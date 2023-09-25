import serial

# Set up serial communication

# Use `with` statement to avoid unclosed serial communication after the end of
# program.
with serial.Serial() as scanner:
    # Initialize the scanner with the specifics
    scanner.port = "/dev/tty.usbmodem1101"  # Replace with actual port
    scanner.baudrate = (9600)  # This must match whatever baudrate the Arduino has.

    # Attempt to open the serial connection
    try:
        scanner.open()
    except serial.serialutil.SerialException:
        print("No scanner found on the port. Try again with a different port.")

    # Attempt to read data from serial connection
    try:
        # Continue to run as long as the scanner's connection is open
        while scanner.is_open:
             # Read and parse incoming data from the Arduino
            data = scanner.readline().decode().strip()

            # Assuming that the data from Arduino will look something like
            # "r,tilt,pan" -- we can split by comma and map as floats.
            # r, tilt, pan = map(float, data.split(",")) # supposed to be map(function,iterable)
            print(data)

            # TODO Update the plot with the new data
            # TODO Save the data into a local file (maybe a .csv file)

    except KeyboardInterrupt:
        scanner.close()  # Close the serial port on Ctrl+C
