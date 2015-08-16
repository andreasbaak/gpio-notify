# gpio-notify

## OVERVIEW ##

The gpio-notify tool allows you to watch for changes in a file located
in /sys/class/gpio just like you would watch for changes in a normal
file with inotify. Since the files in /sys/class/gpio are special files
created by the kernel, inotify does not recognize changes to the content
of such files.

The gpio-notify tool waits and blocks until the file contents of the
watched file have changed. Then, it prints the filename and the
contents of the changed file to stdout.

## USAGE ##

  Enable a gpio port using

    export <portnumber> /sys/class/gpio/export
    echo "in" > /sys/class/gpio/gpio<portnumber>/direction
    echo "both" > /sys/class/gpio/gpio<portnumber>/edge

  Start the gpio-notify tool:

    gpio-notify /sys/class/gpio<portnumber1>/value

  You specify any number of gpio value files in the command line. The
  tool will trigger on the first file that changes.


## IMPORTANT RESOURCES ##

  * Source Code Repository: https://github.com/andreasbaak/gpio-notify.git

## MAINTAINERS ##

  * Andreas Baak <andreas.baak@gmail.com>

## CONTRIBUTORS ##

  * Andreas Baak <andreas.baak@gmail.com>

## HOW TO CONTRIBUTE ##

  Contributions are welcome! Please contact the maintainer via email
  or send a pull request.

