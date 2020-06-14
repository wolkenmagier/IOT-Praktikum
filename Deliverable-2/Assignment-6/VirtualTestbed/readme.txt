testbed(WithArguments).txt file has named parameter support.

The parameters are as follows:

1) -s OR --serial: Specify the serial port address.
2) -m OR --mode: Specify the mode ('interactive', 'file', or 'kafka'. The default mode (if no argument given, is 'interactive')
3) -f OR --file: Specify the file path for commands.

Example:

node testbed(WithArguments).js -s "/dev/cu.usbmodem14601" -f "actions.txt"


**NOTE: Currently interactive mode works at all times. Also file mode will work if a file is specified even if -m is not set to "file". So in effect the -m parameter is only used for enabling Kafka mode. We could also change the parameter to -k as a boolean to enable or disable kafka mode.