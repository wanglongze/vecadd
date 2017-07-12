echo env = $XILINX_SDACCEL
if [ "$#" -ne 2 ]; then 
    echo Usage : sh example.sh \[tool\] \[flow\]
    exit 1
fi

tool=$1;
flow=$2;
if [ $tool = "aocl" ]; then
    if [ $flow = "opt" ]; then
        merlincc -c vec_add_kernel.cpp
    elif [ $flow = "hls" ]; then
        merlincc merlincc_export -flow=hls
    elif [ $flow = "sim" ]; then
        merlincc merlincc_export -flow=sim
    elif [ $flow = "host" ]; then
        make host
    elif [ $flow = "impl" ]; then
        merlincc merlincc_export -flow=impl
    elif [ $flow = "simrun" ]; then
        merlincc merlincc_export -flow=simrun -bin host_top -kernel kernel_top.aocx
    else
        echo Error : Do not support flow $flow    
    fi
elif [ $tool = "sdx" ] || [ $tool = "sdaccel" ]; then
    if [ $flow = "opt" ]; then
        merlincc -c vec_add_kernel.cpp
    elif [ $flow = "hls" ]; then
        merlincc merlincc_export -flow=hls
    elif [ $flow = "sim" ]; then
        merlincc merlincc_export -flow=sim
    elif [ $flow = "host" ]; then
        make host
    elif [ $flow = "impl" ]; then
        merlincc merlincc_export -flow=impl
    elif [ $flow = "simrun" ]; then
        merlincc merlincc_export -flow=simrun -bin host_top -kernel kernel_top.xclbin
    else
        echo Error : Do not support flow $flow    
    fi
else
    echo Error : Do not support tool $tool.
fi
