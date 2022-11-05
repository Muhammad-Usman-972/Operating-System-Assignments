echo Align : $1
echo size  : $2
align=$1
size=$2
var1="left"
var2="right"
var3="full"
if [ $size -lt 1 ];then
	echo "Invalid Size"
fi
if [ "$align" = "$var1" ];then
   for ((a=1;a<=$size;a++))
   do
   	for ((b=0;b<a-1;b++))
   	do
   		echo -n "*"	
   	done
   	echo ""		
   done	
   for ((a=1;a<=$size;a++))
   do
   	for ((b=a;b<=$size;b++))
   	do
   		echo -n "*"	
   	done
   	echo ""		
   done	
fi
if [ "$align" = "$var2" ];then
    for ((a=1;a<=$size;a++))
    do
    	for ((b=$size;b>=a;b--))		
    	do
    		echo -n " "
    	done
    	for ((c=1;c<=a;c++))	
    	do
    		echo -n "*"
    	done
   echo "" 	
   done
    for ((a=1;a<=$size;a++))
    do
    	for ((b=0;b<=a;b++))
    	do
    		echo -n " "
    	done
    	for ((c=$size-a;c>0;c--))
    	do
    		echo -n "*"
    	done
   echo "" 	
   done
fi
if [[ "$align" = "$var3" ]];then
    for ((a=1;a<=$size;a++))
    do
    	for ((b=$size;b>=a;b--))
    	do
    		echo -n " "
    	done
    	
    	for ((c=1;c<=2*a-1;c++))		
    	do
    		echo -n "*"		 
    	done
   echo "" 	
   done
   
    for ((a=1;a<=$size;a++))
    do

    	for ((b=0;b<=a;b++))
    	do
    		echo -n " "
    	done
    	
    	for ((c=1; c <= 2*($size-a)-1;c++))
    	do
    		echo -n "*"
    	done
   echo ""
   done
fi
