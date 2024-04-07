#!/bin/bash

METRICA="FLOPS_DP"
PROGRAMA="perfSL"
ENTRADA="SL.in"

make -B

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./$PROGRAMA <$ENTRADA >${k}_perfSL.log
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make clean
