#!/bin/bash
#echo  "Total recognition times:" >> ~/test/result.log
EXIT=exit
if [[ ! $1 ]] || [[ "$1" = "--help" ]]; then
  echo "Please Enter File Name"
  $EXIT
fi

LOG=$1
total_num=$(grep -c "silfp_algo_auth:" ${LOG})
echo "Total recognition times:"${total_num} >> ~/test/result.log
num=$(grep -c "silfp_algo_auth:754" ${LOG})
echo "Recognition success times:"${num} >> ~/test/result.log

start=$(cat ${LOG} | grep -n -C10 "silfp_algo_auth:754" | grep -n "fp_identifyImage_identify:223" | awk '{print $3}')
end=$(cat ${LOG} | grep -n -C10 "silfp_algo_auth:754" | grep -n "fp_identifyImage_identify:258" | awk '{print $3}')

start_value=()
index=1
for value in ${start};do
	start_value[index]=${value}
	index=`expr ${index} + 1`
done

end_value=()
index=1
for value in ${end};do
        end_value[index]=${value}
        index=`expr ${index} + 1`
done

echo "Recognition success time:" >> ~/test/result.log

for index in $(seq 1 ${num});do
	echo "start:"${start_value[index]} >> ~/test/result.log
	echo "end:  "${end_value[index]} >> ~/test/result.log
	echo >> ~/test/result.log

	start_value[index]=${start_value[index]:0-5}
	end_value[index]=${end_value[index]:0-5}
done

echo "time consuming:" >> ~/test/result.log

total=0
for index in $(seq 1 ${num});do 
	value=$(echo ${end_value[index]}*1000 - ${start_value[index]}*1000 | bc)
	echo ${value:0:2} >> ~/test/result.log
	#value=echo ${end_value[index]} - ${start_value[index]} | bc
	total=`expr ${total} + ${value:0:2}`
done

echo "time average:" >> ~/test/result.log

awk 'BEGIN{printf "%0.3f\n",('${total}'/'${num}')}' >> ~/test/result.log

