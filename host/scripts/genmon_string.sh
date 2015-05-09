#!/bin/bash

# Generate string for xfce4-genmon-plugin with the GPU temp in green
# to match CPU temp output from Sensor plugin.
# Why I need the <txt> tags is unclear. It is not really accroding to
# documentation, but it doesn't work without it.
echo "<txt><span color='#00b000'>" $(nvidia-settings -q gpucoretemp -t) "°C</span></txt>"
